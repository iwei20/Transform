#include "parser.hpp"
#include "screen.hpp"
#include <fstream>
#include <iostream>

int main() {
    std::ifstream fin("script");
    screen s(500, 500);
    parser p;
    p.parse(s, fin);
    fin.close();
}