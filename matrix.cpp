#include "matrix.hpp"

#include <stdexcept>
matrix::matrix(int rows, int cols) : data(rows, std::vector<double>(cols)) {}

matrix::matrix(std::vector<std::vector<double>>& vector_2d) : data(vector_2d) {
    // Check if data has uniform column size
    if(data.size() > 1) {
        int col_size = data[0].size();
        for(int i = 1; i < data.size(); ++i) {
            if(data[i].size() != col_size) {
                throw std::invalid_argument("Input 2D vector does not have uniform column size");
            }
        }
    }
}

matrix& matrix::ident(int size) {
    if(size < 0) {
        throw std::invalid_argument("Negative identity matrix size");
    }
    matrix* result = new matrix(size, size);
    for(int i = 0; i < size; ++i) {
        (*result)[i][i] = 1;
    }
    return (*result);
}

std::ostream& operator<<(std::ostream& out, matrix& mat) {
    for(std::vector<double>& row : mat.data) {
        for(double item : row) {
            out << item << " ";
        }
        out << "\n";
    }
    return out;
}

matrix& operator*(matrix& a, matrix& b) {
    if(a.width() != b.height()) {
        throw std::invalid_argument("Number of columns in matrix a should be equal to rows in matrix b");
    }
    matrix* result = new matrix(a.height(), b.width());
    for(int i = 0; i < a.height(); ++i) {
        for(int j = 0; j < b.width(); ++j) {
            double sum = 0;
            for(int k = 0; k < a.width(); ++k) {
                sum += a.data[i][k] * b.data[k][j];
            }
            (*result)[i][j] = sum;
        }
    }
    return (*result);
}

std::vector<double>& matrix::operator[](int index) {
    return data[index];
}

double matrix::get(int row, int col) {
    if(row < 0 || row >= data.size() || col < 0 || col >= data[0].size()) {
        throw std::invalid_argument("Requested matrix element out of bounds");
    }
    return data[row][col];
}

void matrix::set(int row, int col, double num) {
    if(row < 0 || row >= data.size() || col < 0 || col >= data[0].size()) {
        throw std::invalid_argument("Requested matrix element out of bounds");
    }
    data[row][col] = num;
}

int matrix::width() {
    return data[0].size();
}

int matrix::height() {
    return data.size();
}