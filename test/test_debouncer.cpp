#include <gtest/gtest.h>

#include "debouncer.h"

using namespace cjk;

std::string runSequence(auto &d, const std::string &seq)
{
  std::string ret;
  for (const char c : seq)
  {
    const bool in = c == 'T';
    const bool out = d.Process(in);
    ret.push_back(out ? 't' : 'f');
  }
  return ret;
}

TEST(Debouncer, DownwardFlank)
{
  Debouncer<8, 3> d;
  const std::string i = "TFFFFFFFF";
  const std::string o = "tttttffff";
  EXPECT_EQ(runSequence(d, i), o);
}

TEST(Debouncer, UpwardFlank)
{
  Debouncer<8, 3> d;
  const std::string i = "FTTTTTTTT";
  const std::string o = "ffffffttt";
  EXPECT_EQ(runSequence(d, i), o);
}