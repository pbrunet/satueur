#ifndef KERNEL_MEMORY_FRAME_ALLOC_HPP
#define KERNEL_MEMORY_FRAME_ALLOC_HPP

#include <stddef.h>
#include <stdint.h>

extern uint32_t current_mem_position; // Store current position of the memory ptr.

namespace FrameAlloc
{
    void* kmalloc(uint32_t size, bool aligned=false, uint32_t* phys=nullptr); // size in byte
    uint32_t first_frame();
};

namespace Bitmap {
    uint32_t test_frame(uint32_t frame_addr);
    void clear_frame(uint32_t frame_addr);
    void set_frame(uint32_t frame_addr);
}

#endif
