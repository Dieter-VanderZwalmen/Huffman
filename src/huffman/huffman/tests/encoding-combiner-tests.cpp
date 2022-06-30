#ifdef TEST_BUILD

#include "encoding/encoding-combiner.h"
#include "catch.hpp"
#include "util.h"
#include "encoding/eof-encoding.h"
#include "io/memory-buffer.h"

using namespace encoding;


TEST_CASE("test encoding combining with | operator") {
    io::MemoryBuffer<17> input_buffer;
    io::MemoryBuffer<19> output_buffer;
    Encoding<17, 18> eof1 = eof_encoding<17>();
    Encoding<18, 19> eof2 = eof_encoding<18>();

    auto double_eof = eof1 | eof2;

    for (int i = 0; i <= 16; i++) {
        input_buffer.destination()->create_output_stream()->write(i);
    }

    double_eof->encode(*input_buffer.source()->create_input_stream(), *output_buffer.destination()->create_output_stream());
    output_buffer.data().get()->pop_back();
    output_buffer.data().get()->pop_back();

    REQUIRE(input_buffer.data().get()->back() == output_buffer.data().get()->back());
    REQUIRE(input_buffer.data().get()->back() == 16);
    REQUIRE(input_buffer.data().get()->size() == output_buffer.data().get()->size());
}

#endif