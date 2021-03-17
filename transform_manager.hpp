#pragma once

#include "matrix.hpp"
class transform_manager {
    private:
        matrix m;
    public:
        transform_manager();
        void translate(double x_units, double y_units, double z_units);
        void dilate(double x_scale, double y_scale, double z_scale);
        void xRot(double degrees);
        void yRot(double degrees);
        void zRot(double degrees);
        matrix& get_matrix();
        void reset();
};