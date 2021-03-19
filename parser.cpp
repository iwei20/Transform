#include "parser.hpp"

#include <istream>
#include <string>
#include <fstream>

void parser::parse(screen& s, std::istream& in) {
    std::string line;
    while(in >> line) {
        if(line[0] == '#') {
            continue;
        }
        
        if(line == "line") {
            double x1, y1, z1, x2, y2, z2;
            in >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
            _e.add_edge({x1, y1, z1}, {x2, y2, z2});
        }
        if(line == "ident") {
            _t.reset();
        }
        if(line == "scale") {
            double sx, sy, sz;
            in >> sx >> sy >> sz;
            _t.dilate(sx, sy, sz);
        }
        if(line == "move") {
            double tx, ty, tz;
            in >> tx >> ty >> tz;
            _t.translate(tx, ty, tz);
        }
        if(line == "rotate") {
            char axis;
            double degrees;
            in >> axis >> degrees;
            switch(axis) {
                case 'x':
                    _t.xRot(degrees);
                    break;
                case 'y':
                    _t.yRot(degrees);
                    break;
                case 'z':
                    _t.zRot(degrees);
                    break;
            }
        }
        if(line == "apply") {
            _e = _t.get_matrix() * _e;
        }
        if(line == "display") {
            s.clear();
            s.drawMatrix(_e, {255, 255, 255});
        }
        if(line == "save") {
            std::string filename;
            in >> filename;
            std::ofstream fout(filename);
            fout << s;
            fout.close();
        }
    }
}