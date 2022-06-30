#ifdef TEST_BUILD

#include "util.h"
#include "catch.hpp"
#include <type_traits>
#include "io/memory-buffer.h"
#include "encoding/encoding.h"
#include "encoding/huffman/huffman-encoding.h"
#include "data/FrequencyTable.h"

using namespace encoding;

TEST_CASE("huffman encoding implementation 1 test")
{
    io::MemoryBuffer<256> input_buffer;
    auto output = input_buffer.destination()->create_output_stream();
    const std::vector<Datum> vector{ 8, 7, 6, 5, 4, 3, 2, 1 };

    for (unsigned x = 0; x < vector.size(); x++)
    {
        output->write(vector[x]);
    }

    io::MemoryBuffer<2> temp_buffer;
    io::MemoryBuffer<256> output_buffer3;

    auto huffman = encoding::huffman::huffman_encoding<256>();

    huffman->encode(*input_buffer.source()->create_input_stream(), *temp_buffer.destination()->create_output_stream());
    huffman->decode(*temp_buffer.source()->create_input_stream(), *output_buffer3.destination()->create_output_stream());

    REQUIRE(input_buffer.data()->size() == output_buffer3.data()->size());

    for (unsigned x = 0; x < input_buffer.data()->size(); x++)
    {
        REQUIRE(input_buffer.data()->at(x) == output_buffer3.data()->at(x));
    }
}

TEST_CASE("huffman encoding implementation 2 test")
{
    io::MemoryBuffer<256> input_buffer;
    auto output = input_buffer.destination()->create_output_stream();
    const std::vector<Datum> vector{ 1, 1, 1, 2, 2, 1, 1, 1, 2, 2, 1, 1, 1, 2, 2, 1, 1, 1, 2, 2, 1, 1, 1, 2, 2, 1, 1, 1, 2, 2, 1, 1, 1, 2, 2, 1, 1, 1, 2, 2, 1, 1, 1, 2, 2, 1, 1, 1, 2, 2, 1, 1, 1, 2, 2, 1, 1, 1, 2, 2, 1, 1, 1, 2, 2, 1, 1, 1, 2, 2, 1, 1, 1, 2, 2, 1, 1, 1, 2, 2, 1, 1, 1, 2, 2, 1, 1, 1, 2, 2, 1, 1, 1, 2, 2, 1, 1, 1, 2, 2, 1, 1, 1, 2, 2, 1, 1, 1, 2, 2, 1, 1, 1, 2, 2, 1, 1, 1, 2, 2, 1, 1, 1, 2, 2, 1, 1, 1, 2, 2, 1, 1, 1, 2, 2, 1, 1, 1, 2, 2, 1, 1, 1, 2, 2, 1, 1, 1, 2, 2, 1, 1, 1, 2, 2, 1, 1, 1, 2, 2, 1, 1, 1, 2, 2, 1, 1, 1, 2, 2, 1, 1, 1, 2, 2, 1, 1, 1, 2, 2, 1, 1, 1, 2, 2, 1, 1, 1, 2, 2, 1, 1, 1, 2, 2, 1, 1, 1, 2, 2, 1, 1, 1, 2, 2, 1, 1, 1, 2, 2, 1, 1, 1, 2, 2, 1, 1, 1, 2, 2, 1, 1, 1, 2, 2, 1, 1, 1, 2, 2, 1, 1, 1, 2, 2, 1, 1, 1, 2, 2, 1, 1, 1, 2, 2, 1, 1, 1, 2, 2, 1, 1, 1, 2, 2, 1, 1, 1, 2, 2, 1, 1, 1, 2, 2, 1, 1, 1, 2, 2, 1, 1, 1, 2, 2, 1, 1, 1, 2, 2, 1, 1, 1, 2, 2, 1, 1, 1, 2, 2, 1, 1, 1, 2, 2, 1, 1, 1, 2, 2, 1, 1, 1, 2, 2, 1, 1, 1, 2, 2, 1, 1, 1, 2, 2, 1, 1, 1, 2, 2, 1, 1, 1, 2, 2, 1, 1, 1, 2, 2, 1, 1, 1, 2, 2, 1, 1, 1, 2, 2, 1, 1, 1, 2, 2, 1, 1, 1, 2, 2, 1, 1, 1, 2, 2, 1, 1, 1, 2, 2, 1, 1, 1, 2, 2, 1, 1, 1, 2, 2, 1, 1, 1, 2, 2, 1, 1, 1, 2, 2, 1, 1, 1, 2, 2, 1, 1, 1, 2, 2, 1, 1, 1, 2, 2, 1, 1, 1, 2, 2, 1, 1, 1, 2, 2, 1, 1, 1, 2, 2, 1, 1, 1, 2, 2, 1, 1, 1, 2, 2, 1, 1, 1, 2, 2, 1, 1, 1, 2, 2, 1, 1, 1, 2, 2, 1, 1, 1, 2, 2, 1, 1, 1, 2, 2, 1, 1, 1, 2, 2, 1, 1, 1, 2, 2, 1, 1, 1, 2, 2, 1, 1, 1, 2, 2, 1, 1, 1, 2, 2, 1, 1, 1, 2, 2 };

    for (unsigned x = 0; x < vector.size(); x++)
    {
        output->write(vector[x]);
    }

    io::MemoryBuffer<2> temp_buffer;
    io::MemoryBuffer<256> output_buffer3;

    auto huffman = encoding::huffman::huffman_encoding<256>();

    huffman->encode(*input_buffer.source()->create_input_stream(), *temp_buffer.destination()->create_output_stream());
    huffman->decode(*temp_buffer.source()->create_input_stream(), *output_buffer3.destination()->create_output_stream());

    REQUIRE(input_buffer.data()->size() == output_buffer3.data()->size());

    for (unsigned x = 0; x < input_buffer.data()->size(); x++)
    {
        REQUIRE(input_buffer.data()->at(x) == output_buffer3.data()->at(x));
    }
}

TEST_CASE("huffman encoding implementation 3 test")
{
    io::MemoryBuffer<256> input_buffer;
    auto output = input_buffer.destination()->create_output_stream();
    const std::vector<Datum> vector{ 1, 1, 1, 2, 2, 3, 4, 8, 9, 1, 4, 5,46 };

    for (unsigned x = 0; x < vector.size(); x++)
    {
        output->write(vector[x]);
    }

    io::MemoryBuffer<2> temp_buffer;
    io::MemoryBuffer<256> output_buffer3;

    auto huffman = encoding::huffman::huffman_encoding<256>();

    huffman->encode(*input_buffer.source()->create_input_stream(), *temp_buffer.destination()->create_output_stream());
    huffman->decode(*temp_buffer.source()->create_input_stream(), *output_buffer3.destination()->create_output_stream());

    REQUIRE(input_buffer.data()->size() == output_buffer3.data()->size());

    for (unsigned x = 0; x < input_buffer.data()->size(); x++)
    {
        REQUIRE(input_buffer.data()->at(x) == output_buffer3.data()->at(x));
    }
}

TEST_CASE("huffman encoding implementation 4 test")
{
    io::MemoryBuffer<256> input_buffer;
    auto output = input_buffer.destination()->create_output_stream();
    const std::vector<Datum> vector{ 8 };

    for (unsigned x = 0; x < vector.size(); x++)
    {
        output->write(vector[x]);
    }

    io::MemoryBuffer<2> temp_buffer;
    io::MemoryBuffer<256> output_buffer3;

    auto huffman = encoding::huffman::huffman_encoding<256>();

    huffman->encode(*input_buffer.source()->create_input_stream(), *temp_buffer.destination()->create_output_stream());
    huffman->decode(*temp_buffer.source()->create_input_stream(), *output_buffer3.destination()->create_output_stream());

    REQUIRE(input_buffer.data()->size() == output_buffer3.data()->size());

    for (unsigned x = 0; x < input_buffer.data()->size(); x++)
    {
        REQUIRE(input_buffer.data()->at(x) == output_buffer3.data()->at(x));
    }
}

TEST_CASE("huffman encoding implementation 5 test")
{
    io::MemoryBuffer<256> input_buffer;
    auto output = input_buffer.destination()->create_output_stream();
    const std::vector<Datum> vector{ };

    for (unsigned x = 0; x < vector.size(); x++)
    {
        output->write(vector[x]);
    }

    io::MemoryBuffer<2> temp_buffer;
    io::MemoryBuffer<256> output_buffer3;

    auto huffman = encoding::huffman::huffman_encoding<256>();

    huffman->encode(*input_buffer.source()->create_input_stream(), *temp_buffer.destination()->create_output_stream());
    huffman->decode(*temp_buffer.source()->create_input_stream(), *output_buffer3.destination()->create_output_stream());

    REQUIRE(input_buffer.data()->size() == output_buffer3.data()->size());

    for (unsigned x = 0; x < input_buffer.data()->size(); x++)
    {
        REQUIRE(input_buffer.data()->at(x) == output_buffer3.data()->at(x));
    }
}

#endif