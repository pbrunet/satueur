#ifndef KERNEL_MEMORY_FRAME_ALLOC_HPP
#define KERNEL_MEMORY_FRAME_ALLOC_HPP

#include <stddef.h>
#include <stdint.h>

class FrameAlloc
{
    public:
        static void* malloc(uint32_t size, bool page_align=true,
                uint32_t* phys=nullptr);

        static uint32_t get_pos();
        static uint32_t first_frame();
        static void free(void* to_free);

    private:
        static uint32_t m_current_mem_position;
};

namespace Bitmap {
    uint32_t test_frame(uint32_t frame_addr);
    void clear_frame(uint32_t frame_addr);
    void set_frame(uint32_t frame_addr);
}

#endif
