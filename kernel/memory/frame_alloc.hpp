#ifndef KERNEL_MEMORY_FRAME_ALLOC_HPP
#define KERNEL_MEMORY_FRAME_ALLOC_HPP

#include <stddef.h>
#include <stdint.h>

#include <bitmap.hpp>

class FrameAlloc
{
    public:
        void* malloc(uint32_t size, bool page_align=true,
                uint32_t* phys=nullptr);

        uint32_t get_pos() const;
        void free(void* to_free);
        static FrameAlloc& get();
        uint32_t first_frame() const;
        void set_frame(uint32_t i);
        void clear_frame(uint32_t i);

    private:
        FrameAlloc(uint32_t max_size): m_frames(max_size) {}

        Bitmap<FrameAlloc> m_frames;
        // m_current_mem_position have to be static as it has to be initialized
        // before we use malloc (so before we call the Bitmap constructor).
        static uint32_t m_current_mem_position;
};

#endif
