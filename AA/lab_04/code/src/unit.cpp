#include "measurements.hpp"
#include "solution.hpp"
#include <gtest/gtest.h>

TEST(Recursive, Call)
{
    recursive(50);
    SUCCEED();
}

TEST(Iterative, Call)
{
    iterative(55);
    SUCCEED();
}

TEST(Measurements, Iterative)
{
    ASSERT_NO_THROW(measure(NONREC, 5, 55));
}

TEST(Measurements, Recursive)
{
    ASSERT_NO_THROW(measure(REC, 55, 5));
}

TEST(Measurements, NegativeNumber)
{
    ASSERT_NO_THROW(measure(REC, -5, 505));
}

TEST(Measurements, ZeroIterations)
{
    ASSERT_THROW(measure(NONREC, 505, 0), std::invalid_argument);
}