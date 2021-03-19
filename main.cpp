#include "parser.hpp"
#include "screen.hpp"
#include <fstream>
#include <iostream>

int main(int argc, char** argv) {
    std::ifstream fin(argv[1]);
    screen s(500, 500);
    parser p;
    p.parse(s, fin);
    fin.close();
}