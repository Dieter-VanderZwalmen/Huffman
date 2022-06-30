
#ifndef UTIL_H
#define UTIL_H
//Add include guard http://pvm.leone.ucll.be/huffman/implementation/include-guards.html


#include <iostream>
#include <bitset>

//alias
//de data dat we moeten compressen of decompressen
typedef uint64_t  u64;

//gewoon om een uint64_t af te korten
typedef uint64_t  Datum;


constexpr unsigned bits_needed(u64 domain_size)
{
    /*
    //count gaat altijd groter worden en ga je returnen
    unsigned count = 1;
    //x = 1 en zal left shit operator met x
    u64 x = 1;

    //x in binary is 0001
    //count is 0001
    //x << count = 0010     //als count 0010 is dan is x << count = 0100
    // je kan << ook zien als * zie  http://pvm.leone.ucll.be/huffman/implementation/bitwise-operations.html#rightshift
    while ((x << count) < domain_size) //bv: 0010 < 1000 
    {
        count++; //dus doe bij count 1 bij
    }// nu ga je 0100 < 1000 doen

    return count;*/

    //attempt 2
    
    auto x = domain_size-1 ;
    auto teller = 0;

    while (x > 0) {
        teller++;
       x = x >> 1;
    }
    return teller;
    
    
   



}

constexpr unsigned bytes_needed(u64 domain_size)
{
    //bits needed delen door 8 
    // dit is de noob manier
    return bits_needed(domain_size) % 8 == 0 ? bits_needed(domain_size) / 8 : bits_needed(domain_size) / 8 + 1;
    //dit is de chad manier
    //return bits_needed(domain_size) + 7 / 8;

}


template<unsigned NBITS> struct SelectIntegerTypeByBytes;

template<> struct SelectIntegerTypeByBytes<1> { typedef uint8_t type; };
template<> struct SelectIntegerTypeByBytes<2> { typedef uint16_t type; };
template<> struct SelectIntegerTypeByBytes<3> { typedef uint32_t type; };
template<> struct SelectIntegerTypeByBytes<4> { typedef uint32_t type; };
template<> struct SelectIntegerTypeByBytes<5> { typedef uint64_t type; };
template<> struct SelectIntegerTypeByBytes<6> { typedef uint64_t type; };
template<> struct SelectIntegerTypeByBytes<7> { typedef uint64_t type; };
template<> struct SelectIntegerTypeByBytes<8> { typedef uint64_t type; };


template<u64 DOMAIN_SIZE> struct SelectIntegerTypeByDomainSize
{
    typedef typename SelectIntegerTypeByBytes<bytes_needed(DOMAIN_SIZE)>::type type;
};




#endif // !UTIL_H
