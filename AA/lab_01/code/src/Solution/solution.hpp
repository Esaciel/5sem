#ifndef SOLUTION_HPP__
#define SOLUTION_HPP__

#include "definitions.hpp"
#include <ctime>

using matrix_time = pair<Matrix, clock_t>;

matrix_time multiply_standart(Matrix& A, Matrix& B);
matrix_time multiply_Vinograd(Matrix& A, Matrix& B);
matrix_time multiply_Vinograd_upd(Matrix& A, Matrix& B);

#endif // SOLUTIN_HPP__
