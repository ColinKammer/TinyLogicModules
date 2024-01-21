#include <gtest/gtest.h>

#include "sequencer.h"

using namespace cjk;

TEST(Sequencer, IntArray)
{
    Sequencer<std::array<int, 3>> s(1, 2, 3);
    EXPECT_EQ(s.GetCurrentSequenceElement(), 1);
    EXPECT_EQ(s.Next(), 2);
    EXPECT_EQ(s.GetCurrentSequenceElement(), 2);
    EXPECT_EQ(s.Next(), 3);
    EXPECT_EQ(s.Next(), 1);
};

TEST(Sequencer, BoolVector)
{
    Sequencer<std::vector<bool>> s(true, true, false, false);
    EXPECT_EQ(s.GetCurrentSequenceElement(), true);
    EXPECT_EQ(s.Next(), true);
    EXPECT_EQ(s.GetCurrentSequenceElement(), true);
    EXPECT_EQ(s.Next(), false);
    EXPECT_EQ(s.Next(), false);
    EXPECT_EQ(s.Next(), true);
};
