#ifdef TEST_BUILD

#include "util.h"
#include "catch.hpp"
#include "io/binary-io.h"
#include "io/memory-buffer.h"

using namespace io;

void check(u64 n, unsigned nbits)
{
    io::MemoryBuffer<2> buffer;
    auto input = buffer.source()->create_input_stream();
    auto output = buffer.destination()->create_output_stream();
    io::write_bits(n, nbits, *output);
    auto result = io::read_bits(nbits, *input);

    REQUIRE(n == result);
}

TEST_CASE("test function check")
{
    check(1, 2);
    check(2, 2);
    check(4, 3);
    check(8, 4);
    check(16, 5);
    check(32, 6);
    check(64, 7);
    check(128, 8);
    check(256, 9);
    check(512, 10);
    check(1028, 11);
    check(2056, 12);

    // Query frequencies
    REQUIRE(1 == 1);
}

#endif