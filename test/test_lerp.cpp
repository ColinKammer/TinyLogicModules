#include <gtest/gtest.h>

#include "lerp.h"

using namespace cjk;

TEST(Lerp, Basic)
{
    static constexpr lerp::LERP<double, double> l { { 0.0, -10.0 }, { 10.0, 20.0 } };
    EXPECT_FLOAT_EQ(l(0.0), -10.0);
    EXPECT_FLOAT_EQ(l(5.0), 5.0);
    EXPECT_FLOAT_EQ(l(10.0), 20.0);
    EXPECT_FLOAT_EQ(l(20.0), 50.0);
    EXPECT_FLOAT_EQ(l(-10.0), -40.0);
}

TEST(Lerp, Inverse)
{
    static constexpr lerp::LERP<double, double> l { { 0.0, -10.0 }, { 10.0, 20.0 } };
    static constexpr auto inv = l.GetInverse();
    // more than 4ULP, but probably good enough, caused by 1/3 and 10/3 as inverse coefficients
    EXPECT_NEAR(inv(-10.0), 0.0, 1e-10);
    EXPECT_NEAR(l(5.0), 5.0, 1e-10);
    EXPECT_NEAR(inv(20.0), 10.0, 1e-10);
}

TEST(PicewiseLerp, OnePice)
{
    static constexpr lerp::PicewiseLERP<double, double, 2> l { { lerp::Point { 0.0, -10.0 },
        lerp::Point { 10.0, 20.0 } } };
    EXPECT_FLOAT_EQ(l(0.0), -10.0);
    EXPECT_FLOAT_EQ(l(5.0), 5.0);
    EXPECT_FLOAT_EQ(l(10.0), 20.0);
    EXPECT_FLOAT_EQ(l(20.0), 50.0);
    EXPECT_FLOAT_EQ(l(-10.0), -40.0);
}

TEST(PicewiseLerp, Three)
{
    static constexpr lerp::PicewiseLERP<double, double, 4> l { { lerp::Point { 0.0, -10.0 },
        lerp::Point { 10.0, 20.0 },
        lerp::Point { 20.0, 20.0 },
        lerp::Point { 40.0, 40.0 } } };
    EXPECT_FLOAT_EQ(l(-10.0), -40.0);
    EXPECT_FLOAT_EQ(l(0.0), -10.0);
    EXPECT_FLOAT_EQ(l(5.0), 5.0);
    EXPECT_FLOAT_EQ(l(10.0), 20.0);
    EXPECT_FLOAT_EQ(l(15.0), 20.0);
    EXPECT_FLOAT_EQ(l(20.0), 20.0);
    EXPECT_FLOAT_EQ(l(25.0), 25.0);
    EXPECT_FLOAT_EQ(l(40.0), 40.0);
    EXPECT_FLOAT_EQ(l(50.0), 50.0);
}

TEST(PicewiseLerp, TwoInverse)
{
    static constexpr lerp::PicewiseLERP<double, double, 3> l { { lerp::Point { 0.0, 0.0 },
        lerp::Point { 10.0, 20.0 },
        lerp::Point { 20.0, 30.0 } } };
    static constexpr auto inv = l.GetInverse();

    EXPECT_FLOAT_EQ(inv(0.0), 0.0);
    EXPECT_FLOAT_EQ(inv(10.0), 5.0);
    EXPECT_FLOAT_EQ(inv(20.0), 10.0);
    EXPECT_FLOAT_EQ(inv(25.0), 15.0);
    EXPECT_FLOAT_EQ(inv(27.0), 17.0);
    EXPECT_FLOAT_EQ(inv(30.0), 20.0);
}