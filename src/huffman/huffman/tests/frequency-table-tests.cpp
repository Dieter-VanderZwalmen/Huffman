#ifdef TEST_BUILD

#include "util.h"
#include "data/FrequencyTable.h"
#include "catch.hpp"
#include <type_traits>
using namespace data;



//Uit voorbeeld testen valt het mij op dat
//je eerst checkt of je gewoon een instantie kan maken van iets
//en dan pas checkt of het juist werkt
//elke test classe is ook heel specifiek



TEST_CASE("test create FrequencyTable")
{
    // Create new frequency table to count chars
    FrequencyTable<char> freqtable;

    // Query frequencies
    REQUIRE(1 == 1);

    //we doen dit om te checke of het maken van een freqtable wel werkt
}

TEST_CASE("test increment FrequencyTable (werkt de code?)")
{
    // Create new frequency table to count chars
    FrequencyTable<char> freqtable;
    char* a = new char;
    *a = 'a';
    char* b = new char;
    *b = 'b';
    char* c = new char;
    *c = 'c';

    // Count 'a' one time
    freqtable.increment(*a);

    // Count 'b' twice
    freqtable.increment(*b);
    freqtable.increment(*b);

    // Query frequencies
    REQUIRE(1 == 1);
}

TEST_CASE("test increment FrequencyTable (is de frequentie van a juist? waar a=1)")
{
    // Create new frequency table to count chars
    FrequencyTable<char> freqtable;
    char* a = new char;
    *a = 'a';
    char* b = new char;
    *b = 'b';
    char* c = new char;
    *c = 'c';

    // Count 'a' one time
    freqtable.increment(*a);

    // Count 'b' twice
    freqtable.increment(*b);
    freqtable.increment(*b);

    // Query frequencies
    unsigned x = 1;
    REQUIRE(freqtable['a'] == x);
}

TEST_CASE("test increment FrequencyTable (is de frequentie van a juist? waar b=2)")
{
    // Create new frequency table to count chars
    FrequencyTable<char> freqtable;
    char* a = new char;
    *a = 'a';
    char* b = new char;
    *b = 'b';
    char* c = new char;
    *c = 'c';

    // Count 'a' one time
    freqtable.increment(*a);

    // Count 'b' twice
    freqtable.increment(*b);
    freqtable.increment(*b);

    // Query frequencies
    REQUIRE(freqtable['b'] == 2);
}

TEST_CASE("test increment FrequencyTable is de frequentie van a juist? waar c=0")
{
    // Create new frequency table to count chars
    FrequencyTable<char> freqtable;
    char* a = new char;
    *a = 'a';
    char* b = new char;
    *b = 'b';
    char* c = new char;
    *c = 'c';

    // Count 'a' one time
    freqtable.increment(*a);

    // Count 'b' twice
    freqtable.increment(*b);
    freqtable.increment(*b);

    // Query frequencies
    REQUIRE(freqtable['c'] == 0);
}

TEST_CASE("test values FrequencyTable 1")
{
    //deze test vind ik redelijk nutteloos? of ik zie het nut niet (gewoon een template voor de variaties eigenlijk)
    // lijst maken -> values verkrrijgen -> lege lijst == lege lijst
    // 
    // Create new frequency table to count chars
    FrequencyTable<char> freqtable;

    // Query frequencies
    auto values = freqtable.values();
    std::vector<char> vector;
    REQUIRE(values == vector);
}

TEST_CASE("test values FrequencyTable 2")
{
    // Create new frequency table to count chars
    FrequencyTable<char> freqtable;
    char* a = new char;
    *a = 'a';
    char* b = new char;
    *b = 'b';
    char* c = new char;
    *c = 'c';

    // Count 'a' one time
    freqtable.increment(*a);

    // Query frequencies
    auto values = freqtable.values();
    std::vector<char> vector;
    vector.push_back('a');
    REQUIRE(values == vector);
}

TEST_CASE("test values FrequencyTable 3")
{
    // Create new frequency table to count chars
    FrequencyTable<char> freqtable;
    char* a = new char;
    *a = 'a';
    char* b = new char;
    *b = 'b';
    char* c = new char;
    *c = 'c';

    // Count 'a' one time
    freqtable.increment(*a);

    // Count 'b' twice
    freqtable.increment(*b);
    freqtable.increment(*b);

    // Query frequencies
    auto values = freqtable.values();
    std::vector<char> vector;
    vector.push_back('a');
    vector.push_back('b');
    REQUIRE(values == vector);
}

TEST_CASE("test count_frequencies function 1")
{
    // Create new vector with chars
    std::vector<char> vector;
    vector.push_back('a');

    // Create new frequency table with the function
    FrequencyTable<char> table = count_frequencies<char>(vector);
    auto values = table.values();
    REQUIRE(values == vector);
}

TEST_CASE("test count_frequencies function 2")
{
    // Create new vector with chars
    std::vector<char> vector;
    vector.push_back('a');
    vector.push_back('b');

    // Create new frequency table with the function
    FrequencyTable<char> table = count_frequencies<char>(vector);
    auto values = table.values();
    REQUIRE(values == vector);
}

TEST_CASE("test count_frequencies function 3")
{
    // Create new vector with chars
    std::vector<char> vector;
    vector.push_back('a');
    vector.push_back('b');
    vector.push_back('c');

    // Create new frequency table with the function
    FrequencyTable<char> table = count_frequencies<char>(vector);
    auto values = table.values();
    REQUIRE(values == vector);
}

TEST_CASE("test count_frequencies function 4")
{
    // Create new vector with chars
    std::vector<char> vector;
    vector.push_back('a');
    vector.push_back('b');
    vector.push_back('b');
    vector.push_back('b');
    vector.push_back('c');
    vector.push_back('c');

    // Create new frequency table with the function
    FrequencyTable<char> table = count_frequencies<char>(vector);
    auto a = table['a'];
    auto b = table['b'];
    auto c = table['c'];
    REQUIRE(a == 1);
    REQUIRE(b == 3);
    REQUIRE(c == 2);
}

#endif