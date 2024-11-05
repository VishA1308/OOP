#include <gtest/gtest.h>
#include "CircularBuffer.cpp"
TEST(CircularBuffer, Constuctor)
{
    // Тестирование конструктора по умолчанию
    CircularBuffer cb;
    EXPECT_EQ((int)cb.size(), 0);
    EXPECT_EQ(cb.empty(), true);

    CircularBuffer cb1(10);
    EXPECT_EQ((int)cb1.capacity(), 10);
    EXPECT_EQ((int)cb1.size(), 0);
    EXPECT_EQ(cb1.empty(), true);

    const int a = 10;
    CircularBuffer cb2(10, a);
    EXPECT_EQ((int)cb2.size(), 10);
    EXPECT_EQ(cb2.empty(), false);
}

TEST(CircularBuffer, Capacity)
{
    // Тестирование конструктора по умолчанию
    CircularBuffer cb(10);
    EXPECT_EQ((int)cb.capacity(), 10);
    EXPECT_EQ((int)cb.size(), 0);
    EXPECT_EQ(cb.empty(), true);
}

// Тест на добавление элементов 
TEST(CircularBuffer, PushBackAndFront) 
{
    CircularBuffer buffer(5);
    EXPECT_EQ(buffer.size(), 0);
    buffer.push_back('a');
    buffer.push_back('b');
    EXPECT_EQ(buffer.size(), 2);
    EXPECT_EQ(buffer.front(), 'a');
    EXPECT_EQ(buffer.back(), 'b');
    
}



//// Тест на извлечение элементов
TEST(CircularBuffer, PopFront)
{
    CircularBuffer buffer(5);
    buffer.push_back('a');
    buffer.push_back('b');
    buffer.pop_front();
    EXPECT_EQ(buffer.front(), 'b');
    EXPECT_EQ(buffer.size(), 1);
}
TEST(CircularBuffer, index)
{
    CircularBuffer buffer(5);
    buffer.push_back('a');
    buffer.push_back('b');
    EXPECT_EQ(buffer[0], 'a');
    EXPECT_EQ(buffer[1], 'b');
    EXPECT_EQ(buffer.size(), 2);
}
// Тест на проверку метода at()
TEST(CircularBuffer, AtMethod) {
    CircularBuffer buffer(5);
    buffer.push_back('a');
    buffer.push_back('b');
    EXPECT_EQ(buffer.at(0), 'a');
    EXPECT_EQ(buffer.at(1), 'b');
}

// Тест на проверку метода linearize()
TEST(CircularBuffer, LinearizeMethod) {
    CircularBuffer buffer(5);
    buffer.push_back('a');
    buffer.push_back('b');
    buffer.linearize();
    EXPECT_TRUE(buffer.is_linearized());
}

// Тест на изменение емкости
TEST(CircularBuffer, SetCapacity) {
    CircularBuffer buffer(5);
    EXPECT_EQ(buffer.capacity(), 5);
    buffer.push_back('a');
    buffer.push_back('b');
    buffer.set_capacity(10);
    EXPECT_EQ(buffer.capacity(), 10);
    EXPECT_EQ(buffer.reserve(), 8);
}

TEST(CircularBuffer, swap) {
    CircularBuffer buffer(5);
    EXPECT_EQ(buffer.capacity(), 5);
    CircularBuffer buffer1(10);
    EXPECT_EQ(buffer != buffer1, false);
    buffer.swap(buffer1);
    EXPECT_EQ(buffer.capacity(), 10);
    EXPECT_EQ(buffer == buffer1, true);
}



