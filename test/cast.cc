#include <cast.hh>
#include <gtest/gtest.h>
#include <composite.hh>

namespace composite {
namespace {

using namespace std;

TEST(cast_test, from_none)
{
  EXPECT_EQ(none{}, cast<none>(none{}));
  EXPECT_EQ("<none>", cast<string>(none{}));
  // none can only be cast into itself and to a string
  EXPECT_THROW(cast<int>(none{}), std::bad_cast);
}

TEST(cast_test, from_bool)
{
  using From = deduce<bool>::type;
  EXPECT_EQ(none{}, cast<none>(From{true}));
  EXPECT_EQ(true, cast<bool>(From{true}));
  EXPECT_EQ(false, cast<bool>(From{false}));
  EXPECT_EQ(1, cast<unsigned int>(From{true}));
  EXPECT_EQ(1.0, cast<double>(From{true}));
  EXPECT_EQ(0.0, cast<double>(From{false}));
  EXPECT_EQ("true", cast<string>(From{true}));
  EXPECT_EQ("false", cast<string>(From{false}));
  EXPECT_THROW(cast<sequence>(From{0}), std::bad_cast);
}

TEST(cast_test, from_int)
{
  using From = deduce<int>::type;
  EXPECT_EQ(none{}, cast<none>(From{-1}));
  EXPECT_EQ(true, cast<bool>(From{1}));
  EXPECT_EQ(2, cast<unsigned int>(From{2}));
  EXPECT_EQ(3.0, cast<double>(From{3}));
  EXPECT_EQ("4", cast<string>(From{4}));
  EXPECT_THROW(cast<sequence>(From{0}), std::bad_cast);
}

}
}
