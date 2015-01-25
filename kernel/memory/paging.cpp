#include <string.h>

#include <descriptors/IDT.hpp>
#include <stdio.h>
#include <stdlib.h>

#include "paging.hpp"

extern uint32_t nframes;
extern uint32_t *frames;

// Macros used in the bitset algorithms.
#define INDEX_FROM_BIT(a) (a/(8*4))
#define OFFSET_FROM_BIT(a) (a%(8*4))

void Paging::initialise_paging()
{
   // The size of physical memory. For the moment we
   // assume it is 16MB big.
   uint32_t mem_end_page = 0x1000000;
   nframes = mem_end_page / 0x1000;
   frames = reinterpret_cast<uint32_t*>(
         FrameAlloc::malloc(INDEX_FROM_BIT(nframes), true));
   memset(frames, 0, INDEX_FROM_BIT(nframes));

   // Let's make a page directory.
   page_directory_t* kernel_directory = \
         reinterpret_cast<page_directory_t*>(
               FrameAlloc::malloc(sizeof(page_directory_t), true));

   // We need to identity map (phys addr = virt addr) from
   // 0x0 to the end of used memory, so we can access this
   // transparently, as if paging wasn't enabled.
   for(uint32_t i = 0; i < FrameAlloc::get_pos(); i += 0x1000)
   {
       // Kernel code is readable but not writeable from userspace.
      Paging::alloc_frame(Paging::get_page(i, 1, kernel_directory), 1, 0);
   }
   // Before we enable paging, we must register our page fault handler.
   IDT::set_isr_callback(14, Paging::page_fault);

   Paging::switch_page_directory(kernel_directory);

   // Enable paging changing cr0 content
   uint32_t cr0;
   asm volatile("mov %%cr0, %0": "=r"(cr0));
   cr0 |= 0x80000000; // Enable paging!
   asm volatile("mov %0, %%cr0":: "r"(cr0));
}

void Paging::switch_page_directory(page_directory_t *dir)
{
   asm volatile("mov %0, %%cr3":: "r"(&dir->tablesPhysical));
}

page_t *Paging::get_page(uint32_t address, int make, page_directory_t *dir)
{
   // Turn the address into an index.
   address /= 0x1000;
   // Find the page table containing this address.
   uint32_t table_idx = address / 1024;
   if (dir->tables[table_idx]) // If this table is already assigned
   {
       return &dir->tables[table_idx]->pages[address%1024];
   }
   else if(make)
   {
       uint32_t tmp;
       dir->tables[table_idx] = (page_table_t*)FrameAlloc::malloc(sizeof(page_table_t), true, &tmp);
       memset(dir->tables[table_idx], 0, 0x1000);
       dir->tablesPhysical[table_idx] = tmp | 0x7; // PRESENT, RW, US.
       return &dir->tables[table_idx]->pages[address%1024];
   }
   else
   {
       return 0;
   }
}

void Paging::page_fault(uint32_t /*isr_num*/, uint32_t err_code)
{
   // A page fault has occurred.
   // The faulting address is stored in the CR2 register.
   uint32_t faulting_address;
   asm volatile("mov %%cr2, %0" : "=r" (faulting_address));

   // The error code gives us details of what happened.
   int present   = !(err_code & 0x1); // Page not present
   int rw = err_code & 0x2;           // Write operation?
   int us = err_code & 0x4;           // Processor was in user-mode?
   int reserved = err_code & 0x8;     // Overwritten CPU-reserved bits of page entry?
   //int id = err_code & 0x10;          // Caused by an instruction fetch?

   // Output an error message.
   printf("Page fault! ( ");
   if (present) {printf("present ");}
   if (rw) {printf("read-only ");}
   if (us) {printf("user-mode ");}
   if (reserved) {printf("reserved ");}
   printf(") at 0x");
   printf("%x", faulting_address);
   printf("\n");
   abort();
}


// Function to allocate a frame.
void Paging::alloc_frame(page_t *page, int is_kernel, int is_writeable)
{
   if (page->frame != 0)
   {
       return; // Frame was already allocated, return straight away.
   }
   else
   {
       uint32_t idx = FrameAlloc::first_frame(); // idx is now the index of the first free frame.
       if (idx == (uint32_t)-1)
       {
           printf("No free frames!");
           abort();
       }
       Bitmap::set_frame(idx*0x1000); // this frame is now ours!
       page->present = 1; // Mark it as present.
       page->rw = (is_writeable)?1:0; // Should the page be writeable?
       page->user = (is_kernel)?0:1; // Should the page be user-mode?
       page->frame = idx;
   }
}

// Function to deallocate a frame.
void Paging::free_frame(page_t *page)
{
   uint32_t frame = page->frame;
   if (!frame)
   {
       return; // The given page didn't actually have an allocated frame!
   }
   else
   {
       Bitmap::clear_frame(frame); // Frame is now free again.
       page->frame = 0x0; // Page now doesn't have a frame.
   }
}
