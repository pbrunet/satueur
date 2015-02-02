#ifndef KERNEL_MEMORY_PAGING_HPP
#define KERNEL_MEMORY_PAGING_HPP

#include <stddef.h>
#include <stdint.h>

#include <descriptors/registers.h>
#include "frame_alloc.hpp"


struct page_t
{
   bool present    : 1;   // Page present in memory
   bool rw         : 1;   // Read-only if clear, readwrite if set
   bool user       : 1;   // Supervisor level only if clear
   bool accessed   : 1;   // Has the page been accessed since last refresh?
   bool dirty      : 1;   // Has the page been written to since last refresh?
   char unused     : 7;   // Amalgamation of unused and reserved bits
   uint32_t frame      : 20;  // Frame address (shifted right 12 bits)
} __attribute__((packed));

struct page_table_t
{
   page_t pages[1024];
};

struct page_directory_t
{
   /*
    * Array of pointers to pagetables.
    */
   page_table_t *tables[1024] __attribute__((aligned(4096)));
   /*
    * Array of pointers to the pagetables above, but gives their *physical*
    * location, for loading into the CR3 register.
    */
   uint32_t tablesPhysical[1024] __attribute__((aligned(4096)));;
};


namespace Paging
{
   /*
    * Sets up the environment, page directories etc and enables paging.
    */
   void initialise_paging();

   /*
    * Causes the specified page directory to be loaded into the CR3 register.
    */
   void switch_page_directory(page_directory_t *new_pd);

   /*
    * Retrieves a pointer to the page required.
    * If make == 1, if the page-table in which this page should
    * reside isn't created, create it!
    */
   page_t *get_page(uint32_t address, int make, page_directory_t *dir);

   /*
    * Handler for page faults.
    */
   void page_fault(uint32_t isr_num, uint32_t err_code);

   /*
    * Fill page and mark frame as use.
    */
   void alloc_frame(page_t *page, int is_kernel, int is_writeable);

   /*
    * Clean page and mark frame as free.
    */
   void free_frame(page_t *page);
}
#endif
