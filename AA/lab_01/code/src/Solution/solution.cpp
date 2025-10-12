#include "solution.hpp"
#include "err.hpp"
#include "extras.hpp"

matrix_time multiply_standart(Matrix& A, Matrix& B)
{
    size_t n = A.size();
    size_t q = A[0].size();
    size_t m = B[0].size();

    if (q != B.size()) throw Unmultipliable();

    clock_t time;

    time = clock();

    Matrix C = createMatrix(n, m);

    for (size_t i = 0; i < n; ++i)
    {
        for (size_t j = 0; j < m; ++j)
        {
            for (size_t k = 0; k < q; ++k)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    time = clock() - time;

    return {C, time};
}

matrix_time multiply_Vinograd(Matrix& A, Matrix& B)
{
    size_t n = A.size();
    size_t q = A[0].size();
    size_t m = B[0].size();

    if (q != B.size()) throw Unmultipliable();

    clock_t time;

    time = clock();

    Matrix C = createMatrix(n, m);
    vector<number> mul_v = createVector(m);
    vector<number> mul_h = createVector(n);

    for (size_t i = 0; i < n; ++i)
    {
        for (size_t k = 0; k < (q / 2); ++k)
        {
            mul_h[i] += A[i][2*k] * A[i][2*k + 1];
        }
    }

    for (size_t j = 0; j < m; ++j)
    {
        for (size_t k = 0; k < (q / 2); ++k)
        {
            mul_v[j] += B[2*k][j] * B[2*k + 1][j];
        }
    }

    for (size_t i = 0; i < n; ++i)
    {
        for (size_t j = 0; j < m; ++j)
        {
            C[i][j] -= mul_h[i] + mul_v[j];

            for (size_t k = 0; k < (q / 2); ++k)
            {
                C[i][j] += (A[i][2*k] + B[2*k + 1][j]) * (A[i][2*k + 1] + B[2*k][j]);
            }

            if (q % 2 == 1)
                C[i][j] += A[i][q-1] * B[q-1][j];

        }
    }

    time = clock() - time;

    return {C, time};
}


matrix_time multiply_Vinograd_upd(Matrix& A, Matrix& B)
{
    size_t n = A.size();
    size_t q = A[0].size();
    size_t m = B[0].size();

    if (q != B.size()) throw Unmultipliable();

    number mul_cur_h{};

    clock_t time;

    time = clock();

    Matrix C = createMatrix(n, m);
    vector<number> mul_v = createVector(m);

    for (size_t j = 0; j < m; ++j)
    {
        for (size_t k = 0; k < (q / 2); ++k)
        {
            mul_v[j] += B[(k<<1)][j] * B[(k<<1) + 1][j];
        }
    }

    for (size_t i = 0; i < n; ++i)
    {
        mul_cur_h = 0;
        for (size_t k = 0; k < (q / 2); ++k)
        {
            mul_cur_h -= A[i][(k<<1)] * A[i][(k<<1) + 1];
        }

        for (size_t j = 0; j < m; ++j)
        {
            C[i][j] = mul_cur_h - mul_v[j];

            for (size_t k = 0; k < (q / 2); ++k)
            {
                C[i][j] += (A[i][(k<<1)] + B[(k<<1) + 1][j]) * (A[i][(k<<1) + 1] + B[(k<<1)][j]);
            }

            if (q % 2 == 1)
                C[i][j] += A[i][q-1] * B[q-1][j];

        }
    }

    time = clock() - time;

    return {C, time};
}