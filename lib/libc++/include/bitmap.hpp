#ifndef LIBCPP_INCLUDE_BITMAP_HPP
#define LIBCPP_INCLUDE_BITMAP_HPP

#include <stdint.h>
#include <string.h>

template<class Allocator>
class Bitmap
{
    public:
        Bitmap(uint32_t size);

        ~Bitmap();

        void set(uint32_t i, bool value=true);

        bool test(uint32_t i) const;

        uint32_t size() const;

        void clear();

    private:
        uint32_t* m_content;
        uint32_t m_size;
};

template<class Allocator>
Bitmap<Allocator>::Bitmap(uint32_t size):
    m_content(reinterpret_cast<uint32_t*>(Allocator::get().malloc((size + 31) / 32))),
    m_size(size)
{
    clear();
}

template<class Allocator>
Bitmap<Allocator>::~Bitmap()
{
    Allocator::get().free(m_content);
}

template<class Allocator>
void Bitmap<Allocator>::set(uint32_t i, bool value)
{
    uint32_t offset = (0x1 << (i % 32));
    if(value)
        m_content[i / 32] |= offset;
    else
        m_content[i / 32] &= ~offset;
}

template<class Allocator>
bool Bitmap<Allocator>::test(uint32_t i) const
{
    return m_content[i / 32] & (0x1 << (i % 32));
}

template<class Allocator>
uint32_t Bitmap<Allocator>::size() const
{
    return m_size;
}

template<class Allocator>
void Bitmap<Allocator>::clear()
{
    memset(m_content, 0, (m_size + 31) / 32);
}

#endif
