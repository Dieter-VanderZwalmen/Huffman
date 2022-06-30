#ifdef TEST_BUILD

#include "util.h"
#include "catch.hpp"
#include "data/binary-tree.h"

using namespace data;

TEST_CASE("test create leaf")
{
    auto leaf = std::make_unique<Leaf<char>>('a');
    REQUIRE(1 == 1);
}

TEST_CASE("test get value from leaf")
{
    auto leaf = std::make_unique<Leaf<char>>('a');
    REQUIRE(leaf->get_leaf() == 'a');
}

TEST_CASE("test create branch")
{
    // Create new leaf
    auto left_leaf = std::make_unique<Leaf<std::string>>("a");
    auto right_leaf = std::make_unique<Leaf<std::string>>("b");

    // Create new Binary tree
    //std::move is used to indicate that an object t may be "moved from", i.e. allowing the efficient transfer of resources from t to another object.

    auto branch = std::make_unique<Branch<std::string>>(std::move(left_leaf), std::move(right_leaf));

    // Query frequencies
    REQUIRE(1 == 1);
}

TEST_CASE("test get leaf from branch")
{
    // Create new leaf
    auto left_leaf = std::make_unique<Leaf<std::string>>("a");
    auto right_leaf = std::make_unique<Leaf<std::string>>("b");

    // Create new Binary tree
    auto branch = std::make_unique<Branch<std::string>>(std::move(left_leaf), std::move(right_leaf));

    // Query frequencies
    REQUIRE(dynamic_cast<const Leaf<std::string>*> (&(branch->get_left_child()))->get_leaf() == "a");
    REQUIRE(dynamic_cast<const Leaf<std::string>*> (&(branch->get_right_child()))->get_leaf() == "b");
}

TEST_CASE("test function map int - int")
{
    // Create new leaf
    auto left_leaf = std::make_unique<Leaf<int>>(1);
    auto right_leaf = std::make_unique<Leaf<int>>(2);

    // Create new Binary tree
    auto branch = std::make_unique<Branch<int>>(std::move(left_leaf), std::move(right_leaf));

    //create a function
    auto function = [](const int& x) { return x + 1; };

    auto tree = map<int, int>(*branch, function);

    auto new_tree = dynamic_cast<const Branch<int>*>(&(*tree));

    // Query frequencies
    REQUIRE(dynamic_cast<const Leaf<int>*> (&(new_tree->get_left_child()))->get_leaf() == 2);
    REQUIRE(dynamic_cast<const Leaf<int>*> (&(new_tree->get_right_child()))->get_leaf() == 3);
}

TEST_CASE("test function map string - int")
{
    // Create new leaf
    auto left_leaf = std::make_unique<Leaf<std::string>>("a");
    auto right_leaf = std::make_unique<Leaf<std::string>>("aaa");

    // Create new Binary tree
    auto branch = std::make_unique<Branch<std::string>>(std::move(left_leaf), std::move(right_leaf));

    //create a function
    auto function = [](const std::string& x) { return x.size(); };

    auto tree = map<std::string, int>(*branch, function);

    auto new_tree = dynamic_cast<const Branch<int>*>(&(*tree));

    // Query frequencies
    REQUIRE(dynamic_cast<const Leaf<int>*> (&(new_tree->get_left_child()))->get_leaf() == 1);
    REQUIRE(dynamic_cast<const Leaf<int>*> (&(new_tree->get_right_child()))->get_leaf() == 3);
}

TEST_CASE("test Get leaf function") {
    // Create new leaf
    auto leaf = std::make_unique<Leaf<std::string>>("leaf");

    // Query frequencies
    REQUIRE(leaf->get_leaf() == "leaf");
}

TEST_CASE("test Get left child function") {
    // Create new leaf & branch
    auto leaf = std::make_unique<Leaf<std::string>>("leaf");
    auto branch = std::make_unique<Branch<std::string>>(std::move(leaf), nullptr);

    // Query frequencies
    REQUIRE(dynamic_cast<const Leaf<std::string>*>(&(branch->get_left_child()))->get_leaf() == "leaf");
}

TEST_CASE("test function map int to int") {
    // Create new leaf
    auto leaf1 = std::make_unique<Leaf<int>>(1);
    auto leaf2 = std::make_unique<Leaf<int>>(2);

    //create a tree
    auto tree = map<int, int>(*std::make_unique<Branch<int>>(std::move(leaf1), std::move(leaf2)), [](const int& i) { return i + 1; });
    auto branch = dynamic_cast<const Branch<int>*>(&(*tree));

    // Query frequencies
    REQUIRE(dynamic_cast<const Leaf<int>*>(&(branch->get_left_child()))->get_leaf() == 2);
    REQUIRE(dynamic_cast<const Leaf<int>*>(&(branch->get_right_child()))->get_leaf() == 3);
}

#endif