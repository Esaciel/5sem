#include "extras.hpp"

vector<number> createVector(size_t size)
{
    return vector<number>(size);
}

Matrix createMatrix(size_t row_count, size_t column_count) 
{
    return Matrix(row_count, vector<number>(column_count));
}

bool cmpMatrixes(Matrix& A, Matrix& B)
{
    if (A.size() != B.size()) return false;
    if (A[0].size() != B[0].size()) return false;
    for (size_t i = 0; i < A.size(); ++i)
    {
        for (size_t j = 0; j < A[0].size(); ++j)
        {
            if (A[i][j] != B[i][j]) return false;
        }
    }
    return true;
}