#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "action.h"
#include "doctest.h"

#include <vector>
#include <memory>

TEST_CASE("Actions: construtor"){
    SUBCASE("Default"){
        CHECK_NOTHROW(Accept());
        CHECK_NOTHROW(Error());
        CHECK_NOTHROW(Reduce(1));
        CHECK_NOTHROW(Shift(4));
    }
    SUBCASE("Reduce não pode ser do inicial"){
        CHECK_THROWS(Reduce(0));
    }
}

TEST_CASE("Actions: print"){
    CHECK_NOTHROW(std::cout << Accept() << std::endl);
    CHECK_NOTHROW(std::cout << Error() << std::endl);
    CHECK_NOTHROW(std::cout << Reduce(1) \
                  << std::endl);
    CHECK_NOTHROW(std::cout << Shift(4) << std::endl);
}

TEST_CASE("Actions: getTipo"){
    CHECK(Accept().getTipo() == "Accept");
    CHECK(Error().getTipo() == "Error");
    CHECK(Shift(3).getTipo() == "Shift");
    CHECK(Reduce(1).getTipo() == "Reduce");
}

TEST_CASE("Actions: getters"){
    CHECK(Shift(1).getNextIdx() == 1);
    CHECK(Shift(3).getNextIdx() == 3);
    CHECK(Reduce(1).getProdIdx() == 1);
    CHECK(Reduce(4).getProdIdx() == 4);
}