#ifndef GDT_H
#define GDT_H

#include <stdint.h>
#include <stddef.h>

//GDT = Global descriptor table

class GDT {
    public:
// This structure contains the value of one GDT entry.
// We use the attribute 'packed' to tell GCC not to change
// any of the alignment in the structure.

//granularity
//-----------
//|7|6|5|4|3|2|1|0|
//|G|D|0|A|length |
//
//G : Granularity (0 = 1 byte, 1 = 4kbyte)
//D : Operand size (0 = 16bit, 1 = 32bit)
//0 : Always zero
//A : Available for system use (always zero).
//length : end of length field
//
//See also : http://www.jamesmolloy.co.uk/tutorial_html/4.-The%20GDT%20and%20IDT.html
//
//access
//------
//|7|6|5|4|3|2 |1 |0|
//|P|DPL|1|E|DT|RW|A|
//
//P  : Is segment present? (1 = Yes)
//DPL: Descriptor privilege level - Ring 0 - 3.
//1  : Always one
//E  : Executable byte. Set to one if segment can be executed
//DT : 1 to exec from lowest privilege, 0 in others cases
//RW : Readable bit for code selectors or Writable bit for data selectors
//A  : Set to 0, CPU change it when it is accessed.
//
//See Also : http://wiki.osdev.org/GDT
//
//limit => Maximum addressable unit
//base => beginning of segments
//
        struct entry_struct
        {
            uint16_t limit_low;      // The lower 16 bits of the limit.
            uint16_t base_low;       // The lower 16 bits of the base.
            uint8_t  base_middle;    // The next 8 bits of the base.
            uint8_t  access;         // Access flags, determine what ring this segment can be used in.
            uint8_t  granularity;
            uint8_t  base_high;      // The last 8 bits of the base.
        } __attribute__((packed));

        typedef struct entry_struct entry_t;

//To get address of gdt
        struct ptr_struct
        {
            uint16_t size;           // The upper 16 bits of all selector limits.
            uint32_t offset;         // The address of the first entry_t struct.
        } __attribute__((packed));

        typedef struct ptr_struct ptr_t;

        enum access: uint8_t {
            SEG   =0x80,
            RING_0=0x00,
            RING_1=0x20,
            RING_2=0x40,
            RING_3=0x60,
            EXEC  =0x08,
            RW    =0x02,
            ACC_BASE  =0x10
        };

        enum granularity: uint8_t {
            OP16=0x00,
            OP32=0x40,
            GRB =0x00,
            GRKB=0x80,
            GR_BASE=0x00
        };

        constexpr static uint32_t MAX_LIMIT = 0xFFFFF;
        constexpr static uint16_t NB_ENTRIES = 5;

        GDT();


    private:
        ///Attributes
        entry_t m_entries[NB_ENTRIES];
        ptr_t m_ptr;

        ///Methods
        // Add new gdt entry with parameters
        void add_entry(size_t id, uint32_t base, uint32_t limit, uint8_t access,
                       uint8_t granularity);
};

// From assembly
extern "C" void gdt_flush(uint32_t);

#endif
