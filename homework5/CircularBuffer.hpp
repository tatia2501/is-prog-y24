#include <iostream>
#include <iterator>
#include <algorithm>
#include <string>

using namespace std;
//fixed warnings
template <class T>
class CircularBuffer {
private:
    size_t buf_size = 0;
    size_t capacity = 0;
    size_t head = 0;
    size_t tail = 0;
    T* buffer;

public:
    class Iterator {
    private:
        T* ptr;
        T* buf;
        size_t position{};
        size_t ending{};
        int tonnage{};
    public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = value_type*;
        using reference = value_type&;

        Iterator(T* ptr, T* b, size_t p, size_t t, int c)
            : ptr(ptr), buf(b), position(p), ending(t), tonnage(c) {}

        Iterator() : buf(nullptr) {}

        T& operator*() {
            return buf[(ending - position) % tonnage];
        }

        T* operator-> () const {
            return &(operator*());
        }

        Iterator& operator+= (int num) {
            ptr += num;
            position += num;
            return *this;
        }

        Iterator& operator-= (int num) {
            ptr -= num;
            position -= num;
            return *this;
        }

        Iterator operator+ (int num) {
            return Iterator(ptr + num, buf, position + num, ending, tonnage);
        }

        Iterator operator- (int num) {
            return Iterator(ptr - num, buf, position - num, ending, tonnage);
        }

        difference_type operator- (Iterator it) {
            return ptr - it.ptr;
        }

        Iterator& operator++ () {
            ptr++;
            position++;
            return *this;
        }

        Iterator& operator--() {
            ptr--;
            position--;
            return *this;
        }

        bool operator< (const Iterator& t) const {
            return position < t.position;
        }

        bool operator> (const Iterator& t) const {
            return position > t.position;
        }

        bool operator>= (const Iterator& t) const {
            return position >= t.position;
        }

        bool operator<= (const Iterator& t) const {
            return position <= t.position;
        }

        bool operator== (const Iterator& t) const {
            return position == t.position;
        }

        bool operator!= (const Iterator& t) const {
            return position != t.position;
        }

    };

    explicit CircularBuffer(T num) {
        capacity = num;
        buffer = new T[capacity];
    }

    //fixed information of index and size in exceptions
    T& operator[](int i) {
        int size2 = buf_size;
        if (i >= size2) {
            string info = "Index " + std::to_string(i) + " is out of range. Max index -  " + std::to_string(size2 - 1);
            throw std::out_of_range(info);
        }
        return buffer[(tail - 1 - i) % capacity];
    }

    T operator[](int i) const {
        int size2 = buf_size;
        if (i >= size2) {
            string info = "Index " + std::to_string(i) + " is out of range. Max index -  " + std::to_string(size2 - 1);
            throw std::out_of_range(info);
        }
        return buffer[(tail - 1 - i) % capacity];
    }

    void addFirst(T num) {
        buffer[tail] = num;
        if (buf_size == capacity) {
            if (head < capacity - 1) {
                head++;
            }
            else head = 0;
        }
        else buf_size++;
        if (tail < capacity - 1) {
            tail++;
        }
        else tail = 0;
    }

    void delFirst() {
        if (buf_size == 0) {
            throw std::out_of_range("CircularBuffer's without elements");
        }
        buf_size--;
        if (tail > 0) {
            tail--;
        }
        else tail = capacity - 1;
    }

    void addLast(T num) {
        if (buf_size == capacity) {
            buffer[head] = num;
        }
        else {
            buf_size++;
            if (head > 0) {
                head--;
            }
            else head = capacity - 1;
            buffer[head] = num;
        }
    }

    void delLast() {
        if (buf_size == capacity) {
            throw std::out_of_range("CircularBuffer's without elements");
        }
        buf_size--;
        if (head < capacity - 1) {
            head++;
        }
        else head = 0;
    }

    void changeCapacity(int new_capacity) {
        int count = 0;
        int capacity2 = capacity;
        T* tmp = new T[capacity];
        for (int i = head; i < capacity2; i++) {
            tmp[count] = buffer[i];
            count++;
        }
        int tail2 = tail;
        for (int i = 0; i < tail2; i++) {
            tmp[count] = buffer[i];
            count++;
        }
        head = 0;
        tail = buf_size;
        capacity = new_capacity;
        delete[] buffer;
        buffer = tmp;
    }

    Iterator begin() const {
        if (tail != 0) {
            return Iterator(buffer, buffer, 0, tail - 1, capacity);
        }
        return Iterator(buffer, buffer, 0, capacity - 1, capacity);
    }

    Iterator end() const {
        if (tail != 0) {
            return Iterator(&buffer[buf_size], buffer, buf_size, tail - 1, capacity);
        }
        return Iterator(&buffer[buf_size], buffer, buf_size, capacity - 1, capacity);
    }

    T first() const {
        if (buf_size == 0) {
            throw std::out_of_range("CircularBuffer's without elements");
        }
        if (tail != 0) {
            return buffer[tail - 1];
        }
        else return buffer[capacity - 1];
    }

    T last() const {
        if (buf_size == 0) {
            throw std::out_of_range("CircularBuffer's without elements");
        }
        return buffer[head];
    }
};
