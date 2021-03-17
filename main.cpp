#include "parser.hpp"
#include <fstream>
#include <iostream>

int main() {
    std::ifstream fin("script");
    screen s(500, 500);
    parser p(s);
    p.parse(fin);
    fin.close();
}