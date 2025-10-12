#ifndef IO_HPP__
#define IO_HPP__

#include "definitions.hpp"
#include <string>

void print_matrix(Matrix& M);
Matrix read_matrix_from_file(const std::string& filename);
Matrix read_matrix_from_сin();

#endif // IO_HPP__