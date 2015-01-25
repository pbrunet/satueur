#ifndef LIBCPP_INCLUDE_BITMAP_HPP
#define LIBCPP_INCLUDE_BITMAP_HPP

#include <stdint.h>

template<class Allocator>
class Bitmap
{
    public:
        Bitmap(uint32_t size);

        ~Bitmap();

        void set(uint32_t i, bool value=true);

        bool test(uint32_t i);

    private:
        uint32_t* m_content;
};

template<class Allocator>
Bitmap<Allocator>::Bitmap(uint32_t size)
{
    m_content = reinterpret_cast<uint32_t*>(
            Allocator::malloc(size / 32 + 1));
}

template<class Allocator>
Bitmap<Allocator>::~Bitmap()
{
    Allocator::free(m_content);
}

template<class Allocator>
void Bitmap<Allocator>::set(uint32_t i, bool value)
{
    char offset = (0x1 << (i % 32));
    if(value)
        m_content[i / 32] |= offset;
    else
        m_content[i / 32] &= ~offset;
}

template<class Allocator>
bool Bitmap<Allocator>::test(uint32_t i)
{
    return m_content[i / 32] & (0x1 << (i % 32));
}

#endif
