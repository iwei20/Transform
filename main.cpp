#include "edge_matrix.hpp"
#include "screen.hpp"
#include "matrix.hpp"
#include <fstream>
#include <iostream>

void rect(edge_matrix& e, int x, int y, int w, int h) {
    e.add_edge({x, y, 0}, {x + w, y, 0});
    e.add_edge({x, y, 0}, {x, y + h, 0});
    e.add_edge({x + w, y + h, 0}, {x + w, y, 0});
    e.add_edge({x + w, y + h, 0}, {x, y + h, 0});
}

int main() {
    std::ofstream fout("main.ppm");
    screen<512, 512> s;
    edge_matrix e;
    for(double i = 511; i >= 1; i /= 1.2) {
        e.add_edge({0, 0, 0}, {511, i, 0});
    }
    for(double i = 511; i >= 1; i /= 1.2) {
        e.add_edge({0, 0, 0}, {i, 511, 0});
    }
    e.add_edge({0, 0, 0}, {511, 510.5, 0});

    std::cout << "Testing add_edge: \n" << e;
    matrix ident(4, 4);
    for(int i = 0; i < 4; ++i) {
        ident[i][i] = 1;
    }
    e = ident * e;
    std::cout << "Testing identity matrix multiplication: \n" << e;

    matrix reflect45(4, 4);
    reflect45[0][1] = 1;
    reflect45[1][0] = 1;
    reflect45[2][2] = 1;
    reflect45[3][3] = 1;
    e = reflect45 * e;
    std::cout << "Testing y = x reflection matrix multiplication: \n" << e;
    
    matrix m1(4, 4);
    edge_matrix m2;
    std::vector<std::vector<double>> m1s = {{1, 4, 7, 10}, {2, 5, 8, 11}, {3, 6, 9, 12}, {1, 1, 1, 1}};
    for(int i = 0; i < 4; ++i) {
        for(int j = 0; j < 4; ++j) {
            m1[i][j] = m1s[i][j];
        }
    }
    m2.add_edge({1, 2, 3}, {4, 5, 6});
    std::cout << "Matrix mul test on DW website: \n" << m1 * m2;
    s.drawMatrix(e, {0, 255, 0});
    fout << s;
    fout.close();
}