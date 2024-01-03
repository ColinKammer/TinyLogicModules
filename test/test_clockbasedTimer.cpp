#include <chrono>

#include <gtest/gtest.h>

#include "clockbasedTimer.h"

using namespace cjk;

TEST(ClockbasedTimer, Int)
{
  ClockbasedTimer<int, int> timer{1};
  int now = 0;
  EXPECT_EQ(timer.CheckPeriodExpired(now), true);
  EXPECT_EQ(timer.CheckPeriodExpired(now), false);
  EXPECT_EQ(timer.CheckPeriodExpired(now), false);
  now++;
  EXPECT_EQ(timer.CheckPeriodExpired(now), true);
  EXPECT_EQ(timer.CheckPeriodExpired(now), false);
}

TEST(ClockbasedTimer, Int_NoIntegralConsistency)
{
  ClockbasedTimer<int, int> timer{1};
  int now = 0;
  EXPECT_EQ(timer.CheckPeriodExpired(now), true);
  EXPECT_EQ(timer.CheckPeriodExpired(now), false);
  now++;
  now++;
  EXPECT_EQ(timer.CheckPeriodExpired(now), true);
  EXPECT_EQ(timer.CheckPeriodExpired(now), false);
}

TEST(ClockbasedTimer, Int_IntegralConsistency)
{
  ClockbasedTimer<int, int, true> timer{1};
  int now = 0;
  EXPECT_EQ(timer.CheckPeriodExpired(now), true);
  EXPECT_EQ(timer.CheckPeriodExpired(now), false);
  now++;
  now++;
  EXPECT_EQ(timer.CheckPeriodExpired(now), true);
  EXPECT_EQ(timer.CheckPeriodExpired(now), true);
  EXPECT_EQ(timer.CheckPeriodExpired(now), false);
}

TEST(ClockbasedTimer, Chrono)
{
  using namespace std::chrono_literals;
  using StdClock = std::chrono::steady_clock;

  ClockbasedTimer<StdClock::time_point, StdClock::duration> timer{100ms};
  EXPECT_EQ(timer.CheckPeriodExpired(StdClock::now()), true);
  EXPECT_EQ(timer.CheckPeriodExpired(StdClock::now()), false);
  std::this_thread::sleep_for(100ms);
  EXPECT_EQ(timer.CheckPeriodExpired(StdClock::now()), true);
  EXPECT_EQ(timer.CheckPeriodExpired(StdClock::now()), false);
}
