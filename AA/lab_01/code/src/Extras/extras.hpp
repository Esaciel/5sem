#ifndef EXTRAS_HPP__
#define EXTRAS_HPP__

#include "definitions.hpp"

vector<number> createVector(size_t size);
Matrix createMatrix(size_t row_count, size_t column_count);
bool cmpMatrixes(Matrix& A, Matrix& B);

#endif // EXTRAS_HPP__