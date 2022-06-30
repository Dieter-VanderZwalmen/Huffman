#ifdef TEST_BUILD

#include "encoding/bit-grouper.h"
#include "catch.hpp"
#include "util.h"

using namespace encoding;

TEST_CASE("test bitgrouper function") {
    io::MemoryBuffer<2> buffer;
    io::MemoryBuffer<256> encode_buffer;
    io::MemoryBuffer<2> decode_buffer;

    auto grouper = bit_grouper<8>();

    auto output = buffer.destination()->create_output_stream();

    for (int i = 0; i <= 16; i++) {
        io::write_bits(i, 8, *output);
    }

    encode(buffer.source(), grouper, encode_buffer.destination());

    decode(encode_buffer.source(), grouper, decode_buffer.destination());

    REQUIRE(buffer.data().get()->back() == decode_buffer.data().get()->back());
}

#endif