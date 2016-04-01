#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <iostream>
#include <bitset>

template<class T,typename S>
class bitfield {
public:

    inline bitfield();
    inline bitfield(const T &bit);

    inline const size_t size() const;
    inline const S num_bits() const;
    inline const S get(const T &bit) const;
    inline const S &get_bits() const;

    inline void set(const T &bit);
    inline void clear(const T &bit);
    inline void toggle(const T &bit);

    inline S operator^=(const T &bit);
    inline S operator|=(const T &bit);
    inline S operator&(const T &bit);
    inline S operator=(const T &bit);

    inline const char *dump()const;

private:    
    S bits;
    static const S zero = 0;
    static const S bit_base = 8;
};

template<typename T,typename U>
inline void set_bit(U &bits,const T mask)
{
    bits |= mask;
}

template<typename T,typename U>
inline void toggle_bit(U &bits,const T mask) 
{
    bits ^= mask;
}

template<typename T,typename U>
inline uint8_t clear_bit(U &bits,const T mask) 
{
    return bits &= ~mask;
}

template<typename T,typename U>
inline const bool is_bit_set(const U &bits,const T mask)
{
    return bits & mask;
}

template<class T,typename S>
inline bitfield<T,S>::bitfield()
{
    bits = zero;
}

template<class T,typename S>
inline bitfield<T,S>::bitfield(const T &bit)
{
    bits = bit;
}

template<class T,typename S>
inline const S &bitfield<T,S>::get_bits() const
{
    return bits;
}

template<class T,typename S>
inline const size_t bitfield<T,S>::size() const
{
    return sizeof(*this);
}

template<class T,typename S>
inline const S bitfield<T,S>::num_bits() const
{
    return size()*bit_base;
}

template<class T,typename S>
inline void bitfield<T,S>::set(const T &bit) 
{
    ::set_bit(bits,bit);
}

template<class T,typename S>
inline void bitfield<T,S>::clear(const T &bit)
{
    ::clear_bit(bits,bit);
}

template<class T,typename S>
inline const S bitfield<T,S>::get(const T &bit) const
{
    return ::is_bit_set(bits,bit);
}

template<class T,typename S>
inline void bitfield<T,S>::toggle(const T &bit)
{
    ::toggle_bit(bits,bit);
}

template<class T,typename S>
inline const char *bitfield<T,S>::dump() const
{
    std::string out;
    for(unsigned int i=num_bits();0!=i;i--)
    {
	out += ((1 << (i-1)) & bits) ? "1" : "0";
    }
    return out.c_str();
}

template<class T,typename S>
inline S bitfield<T,S>::operator^=(const T &bit)
{
    ::toggle_bit(bits,bit);
    return bits;
}

template<class T,typename S>
inline S bitfield<T,S>::operator|=(const T &bit)
{
    ::set_bit(bits,bit);
    return bits;
}

template<class T,typename S>
inline S bitfield<T,S>::operator&(const T &bit)
{
    return ::is_bit_set(bits,bit);
}

template<class T,typename S>
inline S bitfield<T,S>::operator=(const T &bit)
{
    return bits = bit;
}

enum Mask16 {
    ab1=0x0001,
    ab2=0x0002,
    ab3=0x0004,
    ab4=0x0008,
    ab5=0x0010,
    ab6=0x0020,
    ab7=0x0040,
    ab8=0x0080,
    ab9=0x0100,
    ab10=0x0200,
    ab11=0x0400,
    ab12=0x0800,
    ab13=0x1000,
    ab14=0x2000,
    ab15=0x4000,
    ab16=0x8000,
};

enum Mask8 {
    b1 = 0x01,
    b2 = 0x02,
    b3 = 0x04,
    b4 = 0x08,
    b5 = 0x10,
    b6 = 0x20,
    b7 = 0x40,
    b8 = 0x80,
};

int main (int argc, char **argv)
{
    bitfield<Mask8,uint8_t> bf8;
    std::cout << "-------------------------------" << std::endl;
    std::cout << "bf8 size: " << bf8.size() << std::endl;
    std::cout << "Bits constructor: " << std::bitset<8>(bf8.get_bits()) << std::endl;

//    bf8.set(b2);
    bf8 |= b2;
    std::cout << "Bit initialized: " << std::bitset<8>(bf8.get_bits()) << std::endl;

    uint8_t bit_flip = 0;
    for(int i=0;i<8;i++)
    {
	bit_flip = (1 << i); 
	const char *p = (bit_flip<=0x08) ? "0x0" : "0x";
	std::cout << "-------------------------------" << std::endl;
	std::cout << "Simulated Mask: " << std::bitset<8>(bit_flip) << std::endl;
	std::cout << "Simulated Hex : " << p << std::hex << (int)bit_flip << std::endl;

//	bf8.toggle(static_cast<Mask8>(bit_flip));
	bf8 ^= static_cast<Mask8>(bit_flip);
//	(bf8.get(static_cast<Mask8>(bit_flip))) ? std::cout << "true" << std::endl :std::cout << "false" << std::endl ;
	(bf8 & static_cast<Mask8>(bit_flip)) ? std::cout << "true" << std::endl :std::cout << "false" << std::endl ;
	std::cout << "bf8.bits " << std::bitset<8>(bf8.get_bits()) << std::endl;
    }

    bitfield<Mask16,uint16_t> bf16;
    std::cout << "-------------------------------" << std::endl;
    std::cout << "bf16 size: " << bf16.size() << std::endl;
    std::cout << "Bits constructor: " << std::bitset<16>(bf16.get_bits()) << std::endl;

    bf16.set(ab9);
    std::cout << "Bit initialized: " << std::bitset<16>(bf16.get_bits()) << std::endl;

    bf16 = ab10;
    std::cout << "Bit initialized: " << std::bitset<16>(bf16.get_bits()) << std::endl;
    std::cout << "num bits: " << std::dec << bf16.num_bits() << std::endl;

    // testing for placement in a telegram!
    struct test_telegram {
	uint8_t version;
	uint8_t type;
	bitfield<Mask8,uint8_t> b;
    }tt = {0};

    std::cout << "-------------------------------" << std::endl;
    std::cout << "tt size: " << sizeof(tt) << std::endl;

    tt.b = b3;
    std::cout << "tt.b: " << std::bitset<8>(tt.b.get_bits()) << std::endl;
    std::cout << "tt.b.dump() : " << tt.b.dump() << std::endl;

    bitfield<Mask8,uint8_t> bf_constructor(b5);
    std::cout << "-------------------------------" << std::endl;
    std::cout << "bf_constructor: " << std::bitset<8>(bf_constructor.get_bits()) << std::endl;
    std::cout << "bf_constructor.dump() : " << bf_constructor.dump() << std::endl;

    // Using the template function to manipulate c style!
    ::set_bit(bf_constructor,b3);
    std::cout << "global function - bf_constructor: " << std::bitset<8>(bf_constructor.get_bits()) << std::endl;

//    ::set_bit(bf_constructor,0x08); // error needs a valid Mask8 type or a cast static_cast<Mask8>(0x08)
//    bf_constructor.set(0x08);       // error needs a valid Mask8 type or a cast static_cast<Mask8>(0x08)
//    bf_constructor.get(0x08);       // error needs a valid Mask8 type or a cast static_cast<Mask8>(0x08)
//    bf_constructor.toggle(0x08);    // error needs a valid Mask8 type or a cast static_cast<Mask8>(0x08)
    return 0;
}
