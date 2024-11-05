#include <iostream>
#include <stdexcept>
#include <algorithm>

typedef char value_type;
using namespace std;

class CircularBuffer
{
private:
    value_type* buffer;
    int head;
    int tail;
    int capacity_;
    int size_;
    bool linearized;

public:

    CircularBuffer() : buffer(nullptr), head(0), tail(0), capacity_(10), size_(0), linearized(false) {}

    CircularBuffer(const CircularBuffer& cb)
    {

        buffer = new value_type[cb.capacity()];
        head = 0;
        tail = cb.size() - 1;
        capacity_ = cb.capacity();
        size_ = cb.size();
        linearized = cb.linearized;
        for (int i = 0; i < cb.size(); i++)
        {
            buffer[i] = cb[i];
        }
    }

    explicit CircularBuffer(int capacity)
    {
        capacity_ = capacity;
        buffer = new value_type[capacity_];
        head = 0;
        tail = 0;
        size_ = 0;
        linearized = false;
    }

    CircularBuffer(int capacity, const value_type& elem)
    {
        capacity_ = capacity;
        buffer = new value_type[capacity_];
        head = 0;
        for (int i = 0; i < capacity; i++)
        {
            buffer[i] = elem;
        }
        tail = capacity;
        size_ = capacity;
        linearized = false;
    }

    ~CircularBuffer()
    {
        delete[] buffer;
    }

    value_type& operator[](int i)
    {
        return buffer[(head + i) % capacity_];
    }

    const value_type& operator[](int i) const
    {
        return buffer[(head + i) % capacity_];
    }


    value_type& at(int i)
    {
        if (i < 0 || i >= size_)
        {
            cout << ("Index out of range");
        }
        else
        {
            return (*this)[i];
        }

    }
    const value_type& at(int i) const
    {
        return const_cast<CircularBuffer&>(*this).at(i);
    }

    value_type& front()
    {
        if (empty())
        {
            cout << ("Buffer is empty");
        }
        return buffer[head];
    }

    value_type& back()
    {
        if (empty())
        {
            cout << ("Buffer is empty");
        }
        return buffer[(tail - 1 + capacity_) % capacity_];
    }

    const value_type& front() const
    {
        return const_cast<CircularBuffer&>(*this).front();
    }

    const value_type& back() const
    {
        return const_cast<CircularBuffer&>(*this).back();
    }
    void swap(CircularBuffer& cb)
    {
        std::swap(buffer, cb.buffer);
        std::swap(head, cb.head);
        std::swap(tail, cb.tail);
        std::swap(capacity_, cb.capacity_);
        std::swap(size_, cb.size_);
        std::swap(linearized, cb.linearized);
    }
    value_type* linearize()
    {
        if (!is_linearized())
        {
            if (size_ > 0)
            {
                std::rotate(buffer, buffer + head, buffer + head + size_);
                head = 0;
                tail = size_;
            }
            linearized = true;
        }
        return buffer;
    }


    bool is_linearized() const
    {
        return linearized;
    }


    void rotate(int new_begin)
    {
        if (new_begin < 0 || new_begin >= size_) throw std::out_of_range("Invalid rotation index");
        head = (head + new_begin) % capacity_;
        tail = (head + size_) % capacity_;
    }
    int size() const
    {
        return size_;
    }

    bool empty() const
    {
        return size_ == 0;
    }

    bool full() const
    {
        return size_ == capacity_;
    }

    int reserve() const
    {
        return capacity_ - size_;
    }

    int capacity() const
    {
        return capacity_;
    }

    void set_capacity(int new_capacity)
    {
        if (new_capacity <= 0) throw std::invalid_argument("New capacity must be positive");
        value_type* new_buffer = new value_type[new_capacity];
        for (int i = 0; i < size_; ++i)
        {
            new_buffer[i] = (*this)[i];
        }
        delete[] buffer;
        buffer = new_buffer;
        capacity_ = new_capacity;
        head = 0;
        tail = size_;
        linearized = false;
    }

    void resize(int new_size, const value_type& item = value_type())
    {
        if (new_size < 0) throw std::invalid_argument("New size must be non-negative");

        if (new_size > capacity_)
        {
            set_capacity(new_size);
            std::fill(buffer + size_, buffer + new_size, item);
        }

        size_ = new_size > size_ ? new_size : size_;
        tail = (head + size_) % capacity_;

        if (new_size < size_)
        {

            for (int i = new_size; i < size_; ++i)
            {
                pop_back();
            }
        }

        linearized = false;
    }

    CircularBuffer& operator=(const CircularBuffer& cb)
    {
        if (this != &cb)
        {
            delete[] buffer;
            head = cb.head;
            tail = cb.tail;
            capacity_ = cb.capacity_;
            size_ = cb.size_;
            linearized = cb.linearized;

            buffer = new value_type[capacity_];
            std::copy(cb.buffer, cb.buffer + capacity_, buffer);
        }
        return *this;
    }

    void push_back(const value_type& item = value_type())
    {
        if (capacity_ == 0)
        {
            return;
        }
        if (full()) 
            pop_front();
        buffer[tail] = item;
        tail = (tail + 1) % capacity_;
        size_++;
    }

    void push_front(const value_type& item = value_type())
    {
        if (capacity_ == 0)
        {
            return;
        }
        if (full())
        {
            if (capacity_ < 5)
            {
                set_capacity(5);
            }
            else
            {
                set_capacity((capacity_ + capacity_) / 2);
            }

        }

        head = (head - 1 + capacity_) % capacity_;
        buffer[head] = item;
        size_++;


    }

    void insert(int pos, const value_type& item = value_type())
    {
        if (pos < 0 || pos > size_) throw std::out_of_range("Invalid position for insert");

        if (full()) pop_front(); // Overwrite the oldest element

        for (int i = size_; i > pos; --i)
        {
            (*this)[i] = (*this)[i - 1];
        }

        (*this)[pos] = item;

        tail = (tail + 1) % capacity_;
        size_++;
    }

    void erase(int first, int last)
    {

        if (first < 0 || last > size_ || first >= last) {
            throw std::out_of_range("Invalid erase range");
        }

        int num_elements_to_erase = last - first;
        int new_size = size_ - num_elements_to_erase;

        for (int i = last; i < size_; ++i)
        {
            buffer[(head + first + i - last) % capacity_] = buffer[(head + i) % capacity_];
        }


        size_ = new_size;
        tail = (head + size_) % capacity_;


        if (new_size == 0) {
            head = 0;
        }

        linearized = false;
    }

    void clear()
    {
        head = tail = 0;
        size_ = 0;
    }

    void pop_back()
    {
        if (empty())
        {
            cout << ("Buffer is empty");
        }
        else
        {
            tail = (tail - 1 + capacity_) % capacity_;
            size_--;
        }
    }

    void pop_front()
    {
        if (empty())
        {
            cout << ("Buffer is empty");
        }
        else
        {
            head = (head + 1) % capacity_;
            size_--;
        }
    }

    bool operator ==(const CircularBuffer& b)
    {
        if (size_ != b.size()) return false;

        for (int i = 0; i < size_; i++)
        {
            if ((*this)[i] != b[i]) return false;
        }

        return true;
    }

    bool operator !=(const CircularBuffer& b)
    {
        return !(*this == b);
    }
};
