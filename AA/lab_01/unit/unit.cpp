#include "solution.hpp"
#include "err.hpp"
#include <gtest/gtest.h>

TEST(MultMatrix, CorrectStd)
{
    Matrix a = {{1,2,3},{4,5,6}};
    Matrix b = {{1},{10},{100}};
    Matrix expected = {{321},{654}};
    EXPECT_EQ(expected, multiply_standart(a,b).first);
}

TEST(MultMatrix, CorrectWin)
{
    Matrix a = {{1,2,3},{4,5,6}};
    Matrix b = {{1},{10},{100}};
    Matrix expected = {{321},{654}};
    EXPECT_EQ(expected, multiply_Vinograd(a,b).first);
}

TEST(MultMatrix, CorrectWinOpt)
{
    Matrix a = {{1,2,3},{4,5,6}};
    Matrix b = {{1},{10},{100}};
    Matrix expected = {{321},{654}};
    EXPECT_EQ(expected, multiply_Vinograd_upd(a,b).first);
}

TEST(MultMatrix, SizeMismatchStd)
{
    Matrix a = {{1, 2, 3}};
    Matrix b = {{4, 5, 6}};
    EXPECT_THROW(multiply_standart(a, b), Unmultipliable);
}

TEST(MultMatrix, SizeMismatchWin)
{
    Matrix a = {{1, 2, 3}};
    Matrix b = {{4, 5, 6}};
    EXPECT_THROW(multiply_Vinograd(a, b), Unmultipliable);
}

TEST(MultMatrix, SizeMismatchWinOpt)
{
    Matrix a = {{1, 2, 3}};
    Matrix b = {{4, 5, 6}};
    EXPECT_THROW(multiply_Vinograd_upd(a, b), Unmultipliable);
}