#include "io.hpp"
#include <iostream>
#include <fstream>
#include "err.hpp"
#include "extras.hpp"

void print_matrix(Matrix& M)
{
    for (size_t i = 0; i < M.size(); ++i)
    {
        for (size_t j = 0; j < M[0].size(); ++j)
        {
            cout << M[i][j] << " ";
        }
        cout << "\n";
    }
    cout << endl;
}

Matrix read_matrix_from_file(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        throw FileError();
    }
    
    size_t rows, cols;
    file >> rows >> cols;
    
    if (rows == 0 || cols == 0) {
        throw SizeError();
    }
    
    Matrix matrix = createMatrix(rows, cols);
    
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            if (!(file >> matrix[i][j])) {
                throw DataError();
            }
        }
    }
    
    return matrix;
}

Matrix read_matrix_from_сin()
{    
    size_t rows, cols;
    cout << "Число рядов: ";
    cin >> rows;
    cout << "Число колонн: ";
    cin >> cols;
    
    if (rows == 0 || cols == 0) {
        throw SizeError();
    }

    cout << "Значения: \n";
    
    Matrix matrix = createMatrix(rows, cols);
    
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            if (!(cin >> matrix[i][j])) {
                throw DataError();
            }
        }
    }
    
    return matrix;
}
