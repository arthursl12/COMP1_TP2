#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "utils.h"
#include "doctest.h"

#include <vector>
#include <memory>

TEST_CASE("Input File: nothrow"){
    std::string input = "tests/teste.in";
    std::vector<std::string> programas;
    CHECK_NOTHROW(inputFile(programas, input));
    CHECK_THROWS(inputFile(programas, "tests/errado.in"));
}

TEST_CASE("Input File: simples"){
    std::string input = "tests/teste.in";
    std::vector<std::string> programas;
    inputFile(programas, input);

    CHECK(programas.size() == 3);
    CHECK(programas[0] == "1 + 1");
    CHECK(programas[1] == "var1 + 35 cos (90 + (log 2))");
    CHECK(programas[2] == "sin 3E+2");
}

TEST_CASE("Input File: impressão"){
    std::string input = "tests/impr.in";
    std::vector<std::string> programas;
    CHECK_NOTHROW(inputFile(programas, input));
    CHECK(programas.size() == 1);
    CHECK(programas[0] == ",,print");
}