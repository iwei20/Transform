#pragma once

#include "edge_matrix.hpp"
#include <ostream>
#include <tuple>

class screen {
    private:
        std::vector<std::vector<std::tuple<short, short, short>>> colorData;
        bool outbounds(int x, int y);
    public:
        screen(int width, int height);
        /**
         * Prints out contents of screen in a PPM ASCII format.
         **/
        friend std::ostream& operator<<(std::ostream& out, screen& s);

        /**
         * Reference to a point
         **/
        std::vector<std::tuple<short, short, short>>& operator[](int index);

        /**
         * Get the color of a point
         **/
        std::tuple<short, short, short> get(int row, int col);

        /**
         * Set the color of a point
         **/
        void set(int row, int col, std::tuple<short, short, short> new_color);

        /**
         * Fills the screen with black
         **/
        void clear();

        /**
         * Draws edge matrix to a screen.  Currently only takes in the x and y coordinates.
         **/
        void drawMatrix(edge_matrix& edges, std::tuple<short, short, short> color);

        /**
         * Draws a line from point a to point b. Keep in mind that these points are not (row, col), but (x, y). 
         **/ 
        void drawLine(std::pair<int, int> a, std::pair<int, int> b, std::tuple<short, short, short> color);
};