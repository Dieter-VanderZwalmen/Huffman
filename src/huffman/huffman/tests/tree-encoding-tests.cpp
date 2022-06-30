#ifdef TEST_BUILD

#include "util.h"
#include "catch.hpp"
#include "encoding/huffman/tree-encoding.h"
#include "data/binary-tree.h"

using namespace encoding::huffman;
using namespace data;

TEST_CASE("encode and decode tree function test") {

    REQUIRE(1 == 1);
    
    auto leaf1 = std::make_unique<Leaf<Datum>>(1);
    auto leaf2 = std::make_unique<Leaf<Datum>>(2);
    auto leaf3 = std::make_unique<Leaf<Datum>>(3);
    auto leaf4 = std::make_unique<Leaf<Datum>>(420);
    io::MemoryBuffer<2> buffer;

    
    
    std::unique_ptr<Branch<Datum>> branch1 = std::make_unique<Branch<Datum>>(std::move(leaf1), std::move(leaf2));
    std::unique_ptr<Branch<Datum>> branch2 = std::make_unique<Branch<Datum>>(std::move(leaf3), std::move(leaf4));
    std::unique_ptr<Branch<Datum>> branch = std::make_unique<Branch<Datum>>(std::move(branch1), std::move(branch2));


    encode_tree(*branch, 9, *buffer.destination()->create_output_stream());
    auto tree = decode_tree(9, *buffer.source()->create_input_stream());

    const Branch<Datum>* branch3 = dynamic_cast<const Branch<Datum>*>(&(*tree));
    const Branch<Datum>* branch4 = dynamic_cast<const Branch<Datum>*>(&(*branch3).get_right_child());
    const Leaf<Datum>* leaf5 = dynamic_cast<const Leaf<Datum>*>(&((*branch4).get_right_child()));
    const Leaf<Datum>* leaf6 = dynamic_cast<const Leaf<Datum>*>(&((*branch4).get_left_child()));

    REQUIRE(420 == leaf5->get_leaf());
    REQUIRE(3 == leaf6->get_leaf());
    
}



#endif