#pragma once

#include "matrix.hpp"

class edge_matrix : public matrix {
    private:
        /**
         * Given tuple (x, y, z), appends x, y, z, and 1 to the end of each row in the edge matrix.
         **/
        void add_point(std::tuple<double, double, double> point);
    public:
        edge_matrix();

        /**
         * Adds points a and b to the end of the matrix.
         **/
        void add_edge(std::tuple<double, double, double> a, std::tuple<double, double, double> b);
        using matrix::operator=;
};