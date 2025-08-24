#include "vector.h"
#include <gtest/gtest.h>

struct AllocCounter
{
  int value;
  static inline uint default_ctor_count{0};
  static inline uint copy_ctor_count{0};
  static inline uint move_ctor_count{0};
  static inline uint copy_assignment_count{0};
  static inline uint dtor_count{0};

  AllocCounter()
      : value{0}
  {
    ++default_ctor_count;
  }
  AllocCounter(const AllocCounter &other)
      : value(other.value)
  {
    ++copy_ctor_count;
  }

  AllocCounter &operator=(const AllocCounter &other)
  {
    AllocCounter(other).swap(*this);
    ++copy_assignment_count;
    return *this;
  }

  void swap(AllocCounter &other) noexcept { std::swap(value, other.value); }

  AllocCounter(AllocCounter &&other) noexcept
      : value{other.value}
  {
    ++move_ctor_count;
  }

  AllocCounter(int val)
      : value{val}
  {
  }

  ~AllocCounter() { ++dtor_count; }

  static void reset()
  {
    default_ctor_count = 0;
    move_ctor_count = 0;
    copy_ctor_count = 0;
    dtor_count = 0;
  }

  bool operator==(const AllocCounter &other) const { return value == other.value; }
};

TEST(VectorTest, DefaultConstructor)
{
    dev::vector<int> v;
    EXPECT_EQ(v.empty(), true);
}

TEST(VectorTest, InitializerListTest)
{
    AllocCounter::reset();
    dev::vector<int> v{1, 2, 3, 4, 5};
    EXPECT_EQ(!v.empty(), true);
    EXPECT_EQ(v.size() == 5, true);
    EXPECT_EQ(v.capacity() > 0, true);
    for (int i{0}; i < v.size(); ++i)
    {
        EXPECT_EQ(v[i], i + 1);
    }

    dev::vector vec{AllocCounter(), AllocCounter(), AllocCounter()};
    EXPECT_EQ(!vec.empty(), true);
    EXPECT_EQ(vec.size() == 3, true);
    EXPECT_EQ(AllocCounter::default_ctor_count == 3, true);
    EXPECT_EQ(AllocCounter::copy_ctor_count == 3, true);
}

TEST(VectorTest, ParametrizedConstructorTest)
{
    dev::vector v(7, 3.4);
    EXPECT_EQ(v.size(), 7);
    EXPECT_EQ(v[0], 7);

    AllocCounter::reset();
    AllocCounter allocCounter;
    dev::vector v1 (10, allocCounter);
    EXPECT_EQ(AllocCounter::default_ctor_count, 1);
    EXPECT_EQ(AllocCounter::copy_ctor_count, 10);
}

TEST(VectorTest, CopyConstructorTest)
{
    dev::vector<int> v {1, 2, 3, 4 , 5};
    dev::vector<int> vec(v);
    EXPECT_EQ(vec.size(), v.size());
    EXPECT_EQ(vec.capacity() > 0, true);
    for(int i {0}; i < v.size(); ++i){
        EXPECT_EQ(vec[i], v[i]);
    }
}

TEST(VectorTest, CopyAssignementTest){
    dev::vector<int> v {1, 2, 3, 4 , 5};
    dev::vector<int> vec;
    vec = v;
    EXPECT_EQ(vec.size(), v.size());
    EXPECT_EQ(vec.capacity() > 0, true);

    for(int i {0}; i < v.size(); ++i){
      EXPECT_EQ(vec[i], v[i]);
    }
}

TEST(VectorTest, MoveConstructorTest)
{
    dev::vector<int> v {1,2,3,4,5};
    dev::vector<int> vec;

    auto* v_data {v.data()};
    auto v_size {v.size()};

    vec = std::move(v);

    EXPECT_EQ(v.size(), 0);
    EXPECT_EQ(v.capacity(), 0);
    EXPECT_EQ(vec.size(), v_size);
    EXPECT_EQ(vec[2], 3);
    EXPECT_EQ(vec.data(), v_data);
}

TEST(VectorTest, MoveAssignmentTest){
    dev::vector<int>  v {1, 2, 3, 4, 5};
    dev::vector<int> v {3, 2, 1};

    auto* v_data {v.data()};
    auto v_size {v.size()};

    vec = std::move(v);
    EXPECT_EQ(v.size(), 0);
    EXPECT_EQ(v.capacity(), 0);
    EXPECT_EQ(vec.size(), v_size);
    EXPECT_EQ(vec.data(), v_data);
    for(int i{0}; i < v_size; ++i){
      EXPECT_EQ(vec[i], v_data[i]);
    }
}

// TODO: add Pushback and Iterator Test