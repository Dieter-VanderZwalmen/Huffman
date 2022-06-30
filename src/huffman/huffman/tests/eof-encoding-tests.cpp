#ifdef TEST_BUILD

#include "util.h"
#include "catch.hpp"
#include "encoding/eof-encoding.h"
#include "io/memory-buffer.h"
#include <memory>
using namespace encoding;

TEST_CASE("test function eof_encoding 1") {
    io::MemoryBuffer<5> buffer;
    io::MemoryBuffer<6> encoded_buffer;

    Encoding<5, 6> eof = eof_encoding<5>();

    auto destination = buffer.destination()->create_output_stream();

    for (int i = 0; i <= 4; i++) {
        destination->write(i);
    }

    encode(buffer.source(), eof, encoded_buffer.destination());

    encoded_buffer.data().get()->pop_back();

    REQUIRE(buffer.data().get()->back() == encoded_buffer.data().get()->back());
    REQUIRE(buffer.data().get()->front() == encoded_buffer.data().get()->front());
}

TEST_CASE("test function eof_encoding 2") {
    io::MemoryBuffer<17> buffer;
    io::MemoryBuffer<18> encoded_buffer;

    Encoding<17, 18> eof = eof_encoding<17>();

    auto destination = buffer.destination()->create_output_stream();

    for (int i = 0; i <= 15; i++) {
        destination->write(i);
    }

    encode(buffer.source(), eof, encoded_buffer.destination());

    encoded_buffer.data().get()->pop_back();

    REQUIRE(buffer.data().get()->back() == encoded_buffer.data().get()->back());
    REQUIRE(buffer.data().get()->front() == encoded_buffer.data().get()->front());
}

TEST_CASE("test function eof_encoding 3") {
    io::MemoryBuffer<255> buffer;
    io::MemoryBuffer<256> encoded_buffer;

    Encoding<255, 256> eof = eof_encoding<255>();

    auto destination = buffer.destination()->create_output_stream();

    for (int i = 0; i <= 244; i++) {
        destination->write(i);
    }

    encode(buffer.source(), eof, encoded_buffer.destination());

    encoded_buffer.data().get()->pop_back();

    REQUIRE(buffer.data().get()->back() == encoded_buffer.data().get()->back());
    REQUIRE(buffer.data().get()->front() == encoded_buffer.data().get()->front());
}

TEST_CASE("test function eof_decoding 1") {
    io::MemoryBuffer<10> buffer;
    io::MemoryBuffer<11> encoded_buffer;
    io::MemoryBuffer<10> decoded_buffer;

    Encoding<10, 11> eof = eof_encoding<10>();

    for (int i = 0; i <= 9; i++) {
        buffer.destination()->create_output_stream()->write(i);
    }

    encode(buffer.source(), eof, encoded_buffer.destination());
    decode(encoded_buffer.source(), eof, decoded_buffer.destination());

    REQUIRE(buffer.data().get()->back() == decoded_buffer.data().get()->back());
    REQUIRE(buffer.data().get()->front() == decoded_buffer.data().get()->front());
}

TEST_CASE("test function eof_decoding 2") {
    io::MemoryBuffer<255> buffer;
    io::MemoryBuffer<256> encoded_buffer;
    io::MemoryBuffer<255> decoded_buffer;

    Encoding<255, 256> eof = eof_encoding<255>();

    for (int i = 0; i <= 254; i++) {
        buffer.destination()->create_output_stream()->write(i);
    }

    encode(buffer.source(), eof, encoded_buffer.destination());
    decode(encoded_buffer.source(), eof, decoded_buffer.destination());

    REQUIRE(buffer.data().get()->back() == decoded_buffer.data().get()->back());
    REQUIRE(buffer.data().get()->front() == decoded_buffer.data().get()->front());
}

TEST_CASE("test function eof_decoding 3") {
    io::MemoryBuffer<100> buffer;
    io::MemoryBuffer<101> encoded_buffer;
    io::MemoryBuffer<100> decoded_buffer;

    Encoding<100, 101> eof = eof_encoding<100>();

    for (int i = 0; i <= 99; i++) {
        buffer.destination()->create_output_stream()->write(i);
    }

    encode(buffer.source(), eof, encoded_buffer.destination());
    decode(encoded_buffer.source(), eof, decoded_buffer.destination());

    REQUIRE(buffer.data().get()->back() == decoded_buffer.data().get()->back());
    REQUIRE(buffer.data().get()->front() == decoded_buffer.data().get()->front());
}

#endif