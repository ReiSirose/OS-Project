#include <vector>
#include <gtest/gtest.h>
#include <stdexcept>



TEST(StdVectorTest, Initialization) {
    std::vector<int> empty_vec;
    EXPECT_TRUE(empty_vec.empty());
    EXPECT_EQ(empty_vec.size(),0);

    std::vector<int> init_vec = {10, 20, 30};
    EXPECT_FALSE(init_vec.empty());
    EXPECT_EQ(init_vec.size(), 3);
    EXPECT_EQ(init_vec[0], 10);
}


TEST(StdVectorTest, PushAndPop) {
    std::vector<std::string> vec;
    vec.push_back("hello");
    vec.push_back("world");

    EXPECT_EQ(vec.size(), 2);
    EXPECT_EQ(vec.front(), "hello");
    EXPECT_EQ(vec.back(), "world");

    vec.pop_back();
    EXPECT_EQ(vec.size(), 1);
    EXPECT_EQ(vec.back(), "hello");
}

TEST(StdVectorTest, ElementAccess) {
    std::vector<int> vec = {1, 2, 3, 4, 5};

    EXPECT_EQ(vec[2], 3);
    EXPECT_EQ(vec.at(4), 5);

    // .at() throws std::out_of_range when index exceeds vector size
    EXPECT_THROW(vec.at(10), std::out_of_range);
}

TEST(StdVectorTest, ResizingAndClearing) {
    std::vector<int> vec = {1, 2, 3};
    
    vec.resize(5, 100); // Expands size to 5, filling new elements with 100
    EXPECT_EQ(vec.size(), 5);
    EXPECT_EQ(vec[3], 100);
    EXPECT_EQ(vec[4], 100);

    vec.clear();
    EXPECT_TRUE(vec.empty());
    EXPECT_EQ(vec.size(), 0);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}