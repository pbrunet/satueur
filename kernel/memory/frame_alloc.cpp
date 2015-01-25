#include "frame_alloc.hpp"


// It's adresse is the end of the kernel location (so the begin of memory)
extern uint32_t endkernel;

// Store current position of the memory ptr.
// It is non-ptr type to be able to perform bitmask on it. (alignment, ...)
uint32_t FrameAlloc::m_current_mem_position = \
      reinterpret_cast<uint32_t>(&endkernel);

// FIXME we should be able to specify an alignment depending on allocated type.
void* FrameAlloc::malloc(uint32_t size, bool page_align, uint32_t* phys)
{
    // If the address is not already page-aligned
    if (page_align and (m_current_mem_position & 0xFFFFF000))
    {
        // Align it.
        m_current_mem_position &= 0xFFFFF000;
        m_current_mem_position += 0x1000;
    }
    if(phys)
        *phys = m_current_mem_position;
    void* init_cur = reinterpret_cast<void*>(m_current_mem_position);
    m_current_mem_position += size;
    return init_cur;
}

// A bitset of frames - used or free.
uint32_t *frames;
uint32_t nframes;

// Macros used in the bitset algorithms.
#define INDEX_FROM_BIT(a) (a/(8*4))
#define OFFSET_FROM_BIT(a) (a%(8*4))

// Static function to set a bit in the frames bitset
void Bitmap::set_frame(uint32_t frame_addr)
{
   uint32_t frame = frame_addr/0x1000;
   uint32_t idx = INDEX_FROM_BIT(frame);
   uint32_t off = OFFSET_FROM_BIT(frame);
   frames[idx] |= (0x1 << off);
}

// Static function to clear a bit in the frames bitset
void Bitmap::clear_frame(uint32_t frame_addr)
{
   uint32_t frame = frame_addr/0x1000;
   uint32_t idx = INDEX_FROM_BIT(frame);
   uint32_t off = OFFSET_FROM_BIT(frame);
   frames[idx] &= ~(0x1 << off);
}

// Static function to test if a bit is set.
uint32_t Bitmap::test_frame(uint32_t frame_addr)
{
   uint32_t frame = frame_addr/0x1000;
   uint32_t idx = INDEX_FROM_BIT(frame);
   uint32_t off = OFFSET_FROM_BIT(frame);
   return (frames[idx] & (0x1 << off));
}

// Static function to find the first free frame.
uint32_t FrameAlloc::first_frame()
{
   uint32_t i, j;
   for (i = 0; i < INDEX_FROM_BIT(nframes); i++)
   {
       if (frames[i] != 0xFFFFFFFF) // nothing free, exit early.
       {
           // at least one bit is free here.
           for (j = 0; j < 32; j++)
           {
               uint32_t toTest = 0x1 << j;
               if ( !(frames[i]&toTest) )
               {
                   return i*4*8+j;
               }
           }
       }
   }
   return -1;
}

uint32_t FrameAlloc::get_pos()
{
   return m_current_mem_position;
}

void free(void*)
{
   // This dummy allocator is not able to free memory.
}
