#include <gtest/gtest.h>

#include "edgeDetector.h"

using namespace cjk;

TEST(EdgeDetector, Basic)
{
  EdgeDetector ed;
  int r = 0;
  int f = 0;
  const auto rising = [&]()
  { r++; };
  const auto falling = [&]()
  { f++; };

  ed.OnEdge(true, rising, falling);
  // no initial Edge
  EXPECT_EQ(r, 0);
  EXPECT_EQ(f, 0);

  ed.OnEdge(true, rising, falling);
  // no Edge, no Effect
  EXPECT_EQ(r, 0);
  EXPECT_EQ(f, 0);

  ed.OnEdge(false, rising, falling);
  EXPECT_EQ(r, 0);
  EXPECT_EQ(f, 1);

  ed.OnEdge(false, rising, falling);
  // no Edge, no Effect
  EXPECT_EQ(r, 0);
  EXPECT_EQ(f, 1);

  ed.OnEdge(true, rising, falling);
  EXPECT_EQ(r, 1);
  EXPECT_EQ(f, 1);
}
