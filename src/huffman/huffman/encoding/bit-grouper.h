#ifndef BIT_GROUPER_H
#define BIT_GROUPER_H

#include <iostream>
#include "encoding.h"

namespace encoding
{
	std::shared_ptr<encoding::EncodingImplementation> create_bit_grouper_implementation(const u64 domain_size);


    //deze gaat gebruikt worden in de app
    template<unsigned GROUP_SIZE>
    Encoding<2, 1 << GROUP_SIZE>bit_grouper() {
        return Encoding<2, 1 << GROUP_SIZE>(create_bit_grouper_implementation(GROUP_SIZE));
    };
}



#endif