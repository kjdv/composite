#include <cast.hh>
#include <gtest/gtest.h>
#include <composite.hh>
#include <make.hh>

namespace composite {
namespace {

using namespace std;

TEST(cast_test, from_none)
{
  EXPECT_EQ(none{}, cast<none>(none{}));
  EXPECT_EQ("", cast<string>(none{}));
  EXPECT_EQ(0, cast<int>(none{}));
  EXPECT_EQ(0, cast<unsigned>(none{}));
  EXPECT_EQ(0.0, cast<float>(none{}));
  EXPECT_EQ(false, cast<bool>(none{}));
  EXPECT_EQ(sequence{}, cast<sequence>(none{}));
  EXPECT_EQ(mapping{}, cast<mapping>(none{}));
}

TEST(cast_test, from_bool)
{
  using From = deduce<bool>::type;
  EXPECT_EQ(none{}, cast<none>(From{true}));
  EXPECT_EQ(true, cast<bool>(From{true}));
  EXPECT_EQ(false, cast<bool>(From{false}));
  EXPECT_EQ(1, cast<int>(From{true}));
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
  EXPECT_EQ(-2, cast<int>(From{-2}));
  EXPECT_EQ(2, cast<unsigned int>(From{2}));
  EXPECT_EQ(3.0, cast<double>(From{3}));
  EXPECT_EQ("4", cast<string>(From{4}));
  EXPECT_THROW(cast<sequence>(From{0}), std::bad_cast);
}

TEST(cast_test, from_float)
{
  using From = deduce<double>::type;
  EXPECT_EQ(none{}, cast<none>(From{1.0}));
  EXPECT_EQ(true, cast<bool>(From{1.0}));
  EXPECT_EQ(false, cast<bool>(From{0.0}));
  EXPECT_EQ(-1, cast<unsigned int>(From{-1.3}));
  EXPECT_EQ(2, cast<unsigned int>(From{2.3}));
  EXPECT_EQ(3.14, cast<double>(From{3.14}));
  EXPECT_EQ("3.140000", cast<string>(From{3.14}));
  EXPECT_THROW(cast<mapping>(From{0}), std::bad_cast);
}

TEST(cast_test, from_string)
{
  using From = deduce<string>::type;

  EXPECT_EQ(none{}, cast<none>(From{"abc"}));

  EXPECT_EQ(true, cast<bool>(From{"true"}));
  EXPECT_EQ(true, cast<bool>(From{"Yes"}));
  EXPECT_EQ(true, cast<bool>(From{"t"}));
  EXPECT_EQ(true, cast<bool>(From{"1"}));

  EXPECT_EQ(false, cast<bool>(From{"false"}));
  EXPECT_EQ(false, cast<bool>(From{"no"}));
  EXPECT_EQ(false, cast<bool>(From{"f"}));
  EXPECT_EQ(false, cast<bool>(From{"0"}));

  EXPECT_EQ(123, cast<int>(From{"123"}));
  EXPECT_EQ(123, cast<int64_t>(From{"123"}));
  EXPECT_EQ(123, cast<uint64_t>(From{"123"}));
  EXPECT_EQ(3.14, cast<double>(From{"3.14"}));
  EXPECT_EQ("abc", cast<string>(From{"abc"}));

  EXPECT_THROW(cast<::composite::mapping>(From{""}), std::bad_cast);
}

TEST(cast_test, from_sequence)
{
  auto seq = make_sequence(1, "abc", true);

  EXPECT_EQ(none{}, cast<none>(seq.as<sequence>()));
  EXPECT_EQ(seq.as<sequence>(), cast<sequence>(seq.as<sequence>()));
  EXPECT_EQ("[1, abc, true]", cast<string>(seq.as<sequence>()));

  EXPECT_THROW(cast<int>(seq.as<sequence>()), std::bad_cast);
}

TEST(cast_test, from_mapping)
{
  ::composite::mapping mm;
  mm["pi"] = ::composite::composite(3.14);
  implementation::mapping m(mm);

  EXPECT_EQ(none{}, cast<none>(m));
  EXPECT_EQ(mm, cast<::composite::mapping>(m));
  EXPECT_EQ("{pi: 3.14}", cast<string>(m));

  EXPECT_THROW(cast<int>(m), std::bad_cast);
}

}
}
