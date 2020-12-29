#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "action.h"
#include "doctest.h"

#include <vector>
#include <memory>

TEST_CASE("Actions: construtor"){
    SUBCASE("Default"){
        CHECK_NOTHROW(Accept());
        CHECK_NOTHROW(Error());
        CHECK_NOTHROW(Reduce(NaoTerminal("A"),Terminal("a")));
        CHECK_NOTHROW(Shift(4));
    }
    SUBCASE("Reduce não pode ser do inicial"){
        CHECK_THROWS(Reduce(NaoTerminal("S\'"),Terminal("a")));
    }
}

TEST_CASE("Actions: print"){
    CHECK_NOTHROW(std::cout << Accept() << std::endl);
    CHECK_NOTHROW(std::cout << Error() << std::endl);
    CHECK_NOTHROW(std::cout << Reduce(NaoTerminal("A"),Terminal("a")) \
                  << std::endl);
    CHECK_NOTHROW(std::cout << Shift(4) << std::endl);
}