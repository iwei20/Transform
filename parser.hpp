#pragma once

#include "screen.hpp"
#include "edge_matrix.hpp"
#include "transform_manager.hpp"
#include <istream>
class parser {
    private:
        screen _s;
        edge_matrix _e;
        transform_manager _t;
    public:
        parser(screen& s);
        void parse(std::istream& in);
};