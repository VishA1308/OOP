#include <iostream>
#include <stdexcept>
#include <algorithm>
#include "CircularBuffer.cpp"

int main() {
    // Тестирование конструктора по умолчанию
    CircularBuffer cb;
    std::cout << "Initial size: " << (int)cb.size() << " (Expected: 0)" << std::endl;
    std::cout << "Is empty: " << (cb.empty() ? "true" : "false") << " (Expected: true)" << std::endl;

    // Тестирование конструктора с заданной емкостью
    CircularBuffer cb1(10);
    std::cout << "Capacity of cb1: " << (int)cb1.capacity() << " (Expected: 10)" << std::endl;

    // Тестирование конструктора с заполнением
    const int a = 10;
    CircularBuffer cb2(10, a);
    std::cout << "Size of cb2 after initialization: " << (int)cb2.size() << " (Expected: 10)" << std::endl;

    // Тестирование копирующего конструктора
    CircularBuffer cb3(cb2);
    std::cout << "Size of cb3 (copy of cb2): " << (int)cb3.size() << " (Expected: 10)" << std::endl;

    // Тестирование установки ёмкости
    cb.set_capacity(10);
    std::cout << "Capacity after set_capacity: " << (int)cb.capacity() << " (Expected: 10)" << std::endl;

    // Тестирование добавления элементов
    cb.push_front(1);
    cb.push_back(2);
    std::cout << "Front: " << (int)cb[0] << " (Expected: 1)" << std::endl;
    std::cout << "Back: " << (int)cb[1] << " (Expected: 2)" << std::endl;

    // Тестирование push_front
    cb.push_front(0);
    std::cout << "Front after push_front: " << (int)cb[0] << " (Expected: 0)" << std::endl;

    // Тестирование pop_back
    cb.pop_back();
    std::cout << "Size after pop_back: " << (int)cb.size() << " (Expected: 2)" << std::endl;

    // Тестирование pop_front
    cb.pop_front();
    std::cout << "Front after pop_front: " << (int)cb[0] << " (Expected: 1)" << std::endl;

    // Тестирование resize
    cb.resize(5, -1);
    std::cout << "Size after resize to larger: " << (int)cb.size() << " (Expected: 5)" << std::endl;

    // Тестирование insert
    cb.insert(2, 42);
    std::cout << "Element at position 2 after insert: " << (int)cb[2] << " (Expected: 42)" << std::endl;

    // Тестирование clear
    cb.clear();
    std::cout << "Size after clear: " << (int)cb.size() << " (Expected: 0)" << std::endl;
    std::cout << "Is empty after clear: " << ((int)cb.empty() ? "true" : "false") << " (Expected: true)" << std::endl;

    return 0;
}
