#include "screen.hpp"

#include <iostream>
screen::screen(int width, int height) : colorData(height, std::vector<std::tuple<short, short, short>>(width)) {}

bool screen::outbounds(int x, int y) {
    return x < 0 || x >= colorData[0].size() || y < 0 || y >= colorData.size();
}

std::ostream& operator<<(std::ostream& out, screen& s) {
    out << "P3\n";
    out << s.colorData.size() << " " << s.colorData[0].size() << "\n";
    out << 255 << "\n";

    for(int i = 0; i < s.colorData.size(); ++i) {
        for(int j = 0; j < s.colorData[i].size(); ++j) {
            short red, green, blue;
            std::tie(red, green, blue) = s.colorData[i][j];
            out << red << " " << green << " " << blue << (j == s.colorData[i].size() - 1 ? "\n" : " ");
        }
    }
    return out;
}

std::vector<std::tuple<short, short, short>>& screen::operator[](int index) {
    return colorData[index];
}

std::tuple<short, short, short> screen::get(int row, int col) {
    if(row < 0 || row >= colorData.size() || col < 0 || col >= colorData[0].size()) {
        throw std::invalid_argument("Requested screen element out of bounds");
    }
    return colorData[row][col];
}

void screen::set(int row, int col, std::tuple<short, short, short> new_color) {
    if(row < 0 || row >= colorData.size() || col < 0 || col >= colorData[0].size()) {
        throw std::invalid_argument("Requested screen element out of bounds");
    }
    colorData[row][col] = new_color;
}

void screen::clear() {
    for(int i = 0; i < colorData.size(); ++i) {
        for(int j = 0; j < colorData[i].size(); ++j) {
            colorData[i][j] = {0, 0, 0};
        }
    }
}

void screen::drawMatrix(edge_matrix& edges, std::tuple<short, short, short> color) {
    for(int i = 0; i < edges.width() - 1; i += 2) {
        drawLine({edges[0][i], edges[1][i]}, {edges[0][i + 1], edges[1][i + 1]}, color);
    }
}

void screen::drawLine(std::pair<int, int> a, std::pair<int, int> b, std::tuple<short, short, short> color) {
    int dx = (b.first - a.first), dy = (b.second - a.second);
    bool drawnOff = false;

    // Gentler slopes
    if(abs(dx) >= abs(dy)) {
        
        int max_x, x, y;
        if(a.first <= b.first) {
            std::tie(x, y) = a;
            max_x = b.first;
        } else {
            std::tie(x, y) = b;
            max_x = a.first;
            dx = -1 * dx;
            dy = -1 * dy;
        }

        // Octant 1 and 5
        if(dy >= 0) {
            int midCompare = 2 * dy - dx; // 2A + B
            while(x <= max_x) {
                if(outbounds(x, y)) {
                    if(!drawnOff) {
                        std::cout << "Warning: drawing off screen\n";
                        drawnOff = true;
                    } 
                } else {
                    colorData[y][x] = color;
                }
                if(midCompare >= 0) {
                    ++y;
                    midCompare -= 2 * dx;
                }
                midCompare += 2 * dy;
                ++x;
            }
        // Octant 4 and 8
        } else {
            int midCompare = 2 * dy + dx; // 2A - B
            while(x <= max_x) {
                if(outbounds(x, y)) {
                    if(!drawnOff) {
                        std::cout << "Warning: drawing off screen\n";
                        drawnOff = true;
                    } 
                } else {
                    colorData[y][x] = color;
                }
                if(midCompare <= 0) {
                    --y;
                    midCompare += 2 * dx;
                }
                midCompare += 2 * dy;
                ++x;
            }
        }
    
    // Steeper slopes
    } else {

        int max_y, x, y;
        if(a.second <= b.second) {
            std::tie(x, y) = a;
            max_y = b.second;
        } else {
            std::tie(x, y) = b;
            max_y = a.second;
            dx = -1 * dx;
            dy = -1 * dy;
        }

        // Octant 2 and 6
        if(dx >= 0) {
            int midCompare = dy - 2 * dx; // A + 2B
            while(y <= max_y) {
                if(outbounds(x, y)) {
                    if(!drawnOff) {
                        std::cout << "Warning: drawing off screen\n";
                        drawnOff = true;
                    } 
                } else {
                    colorData[y][x] = color;
                }
                if(midCompare <= 0) {
                    ++x;
                    midCompare += 2 * dy;
                }
                midCompare -= 2 * dx;
                ++y;
            }
        // Octant 3 and 7
        } else {
            int midCompare = dy + 2 * dx; // A - 2B
            while(y <= max_y) {
                if(outbounds(x, y)) {
                    if(!drawnOff) {
                        std::cout << "Warning: drawing off screen\n";
                        drawnOff = true;
                    } 
                } else {
                    colorData[y][x] = color;
                }
                if(midCompare >= 0) {
                    --x;
                    midCompare -= 2 * dy;
                }
                midCompare -= 2 * dx;
                ++y;
            }
        }
    }

}