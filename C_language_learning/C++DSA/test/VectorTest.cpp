#include "../include/vector.h"
#include <gtest/gtest.h>

using namespace dev;
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
    dev::Vector<int> v;
    EXPECT_EQ(v.empty(), true);
}

TEST(VectorTest, InitializerListTest)
{
    AllocCounter::reset();
    dev::Vector<int> v{1, 2, 3, 4, 5};
    EXPECT_EQ(!v.empty(), true);
    EXPECT_EQ(v.size() == 5, true);
    EXPECT_EQ(v.capacity() > 0, true);
    for (int i{0}; i < v.size(); ++i)
    {
        EXPECT_EQ(v[i], i + 1);
    }

    dev::Vector vec{AllocCounter(), AllocCounter(), AllocCounter()};
    EXPECT_EQ(!vec.empty(), true);
    EXPECT_EQ(vec.size() == 3, true);
    EXPECT_EQ(AllocCounter::default_ctor_count == 3, true);
    EXPECT_EQ(AllocCounter::copy_ctor_count == 3, true);
}

TEST(VectorTest, ParametrizedConstructorTest)
{
    dev::Vector v(7, 3.4);
    EXPECT_EQ(v.size(), 7);
    EXPECT_EQ(v[0], 3.4);

    AllocCounter::reset();
    AllocCounter allocCounter;
    dev::Vector v1 (10, allocCounter);
    EXPECT_EQ(AllocCounter::default_ctor_count, 1);
    EXPECT_EQ(AllocCounter::copy_ctor_count, 10);
}

TEST(VectorTest, CopyConstructorTest)
{
    dev::Vector<int> v {1, 2, 3, 4 , 5};
    dev::Vector<int> vec(v);
    EXPECT_EQ(vec.size(), v.size());
    EXPECT_EQ(vec.capacity() > 0, true);
    for(int i {0}; i < v.size(); ++i){
        EXPECT_EQ(vec[i], v[i]);
    }
}

TEST(VectorTest, CopyAssignementTest){
    dev::Vector<int> v {1, 2, 3, 4 , 5};
    dev::Vector<int> vec;
    vec = v;
    EXPECT_EQ(vec.size(), v.size());
    EXPECT_EQ(vec.capacity() > 0, true);

    for(int i {0}; i < v.size(); ++i){
      EXPECT_EQ(vec[i], v[i]);
    }
}

TEST(VectorTest, MoveConstructorTest)
{
    dev::Vector<int> v {1,2,3,4,5};
    dev::Vector<int> vec;

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
    dev::Vector<int>  v {1, 2, 3, 4, 5};
    dev::Vector<int> vec {3, 2, 1};

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

// 1. ACCESSORS AND EXCEPTION HANDLING
TEST(VectorTest, AccessorsAndExceptionTest)
{
    dev::Vector<int> v{10, 20, 30, 40};

    EXPECT_EQ(v.front(), 10);
    EXPECT_EQ(v.back(), 40);
    EXPECT_EQ(v[1], 20);
    EXPECT_EQ(v.at(2), 30);

    // Const accessors
    const auto& const_v = v;
    EXPECT_EQ(const_v.front(), 10);
    EXPECT_EQ(const_v.back(), 40);
    EXPECT_EQ(const_v[1], 20);
    EXPECT_EQ(const_v.at(2), 30);

    // Bounds checking exception
    EXPECT_THROW(v.at(4), std::out_of_range);
    EXPECT_THROW(v.at(100), std::out_of_range);

    // Raw data access
    EXPECT_NE(v.data(), nullptr);
    EXPECT_EQ(*v.data(), 10);
}

// 2. PUSH_BACK AND EMPLACE_BACK
TEST(VectorTest, PushBackAndEmplaceBackTest)
{
    dev::Vector<std::pair<int, std::string>> v;

    // Lvalue push_back
    std::pair<int, std::string> p1{1, "one"};
    v.push_back(p1);

    // Rvalue push_back
    v.push_back({2, "two"});

    // Perfect forwarding with emplace_back (in-place construction)
    v.emplace_back(3, "three");

    EXPECT_EQ(v.size(), 3);
    EXPECT_EQ(v[0].second, "one");
    EXPECT_EQ(v[1].second, "two");
    EXPECT_EQ(v[2].second, "three");
}

// 3. POP_BACK AND CLEAR (DESTRUCTOR TRACKING)
TEST(VectorTest, PopBackAndClearTest)
{
    AllocCounter::reset();
    {
        dev::Vector<AllocCounter> v;
        v.emplace_back(10);
        v.emplace_back(20);
        v.emplace_back(30);

        EXPECT_EQ(v.size(), 3);

        // pop_back should invoke destructor of the last element
        v.pop_back();
        EXPECT_EQ(v.size(), 2);
        EXPECT_EQ(v.back().value, 20);

        // clear should destroy remaining elements but retain capacity
        auto old_capacity = v.capacity();
        v.clear();
        EXPECT_EQ(v.size(), 0);
        EXPECT_EQ(v.capacity(), old_capacity);
    }
    // Vector went out of scope; all constructed elements must be destroyed
}

// 4. RESERVE, RESIZE, AND SHRINK_TO_FIT
TEST(VectorTest, MemoryManagementTest)
{
    dev::Vector<int> v;

    // Reserve memory
    v.reserve(50);
    EXPECT_EQ(v.size(), 0);
    EXPECT_GE(v.capacity(), 50);

    // Resize expansion
    v.resize(10);
    EXPECT_EQ(v.size(), 10);
    EXPECT_EQ(v[0], 0); // Default-initialized elements

    // Resize shrinkage
    v.resize(3);
    EXPECT_EQ(v.size(), 3);

    // Shrink capacity to match size
    v.shrink_to_fit();
    EXPECT_EQ(v.capacity(), v.size());
}

// 5. ITERATOR OPERATIONS AND STL ALGORITHMS
TEST(VectorTest, IteratorAndSTLAlgorithmsTest)
{
    dev::Vector<int> v{5, 2, 8, 1, 9};

    // Range-based for loop
    int sum = 0;
    for (int x : v)
    {
        sum += x;
    }
    EXPECT_EQ(sum, 25);

    // Compatibility with std::sort
    std::sort(v.begin(), v.end());
    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 2);
    EXPECT_EQ(v[4], 9);

    // Compatibility with std::find
    auto it = std::find(v.begin(), v.end(), 8);
    EXPECT_NE(it, v.end());
    EXPECT_EQ(*it, 8);

    // Const iterators
    const auto& const_v = v;
    auto c_it = const_v.cbegin();
    EXPECT_EQ(*c_it, 1);
}

// TODO: add Pushback and Iterator Test

int main (int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}