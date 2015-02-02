#include <utils/local_static.hpp>

#include "frame_alloc.hpp"


// Its adresse is the end of the kernel location (so the begin of memory)
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
    // For now it is the same as the returned value but it may differe once
    // paging is enabled
    if(phys)
        *phys = m_current_mem_position;
    void* init_cur = reinterpret_cast<void*>(m_current_mem_position);
    m_current_mem_position += size;
    return init_cur;
}

// Static function to find the first free frame.
uint32_t FrameAlloc::first_frame() const
{
    for(uint32_t i=0; i < m_frames.size(); i++)
    {
        if(!(m_frames.test(i)))
           return i;
    }
    return -1;
}

FrameAlloc& FrameAlloc::get()
{
   // The size of physical memory. For the moment we
   // assume it is 16MB big.
   // It will be change later : http://wiki.osdev.org/Detecting_Memory_(x86)

   static FrameAlloc singleton(0x1000);
   return singleton;
}

uint32_t FrameAlloc::get_pos() const
{
   return m_current_mem_position;
}

void FrameAlloc::free(void* p)
{
   clear_frame(reinterpret_cast<uint32_t>(p) / 0x1000);
}

void FrameAlloc::set_frame(uint32_t i)
{
   m_frames.set(i);
}

void FrameAlloc::clear_frame(uint32_t i)
{
   m_frames.set(i, false);
}
