#include <iostream>
#include <iterator>
#include <algorithm>

using namespace std;

template <class T>
class CircularBuffer {
private:
    T* buffer;
    size_t capacity = 0;
    size_t buf_size = 0;
    size_t head = 0;
    size_t tail = 0;

public:
    class Iterator {
    private:
        T* buf;
        T* point;
        int capacity{};
        size_t position{};
        size_t tail{};
    public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = value_type*;
        using reference = value_type&;

        Iterator(T* point, T* b, size_t p, size_t t, int c)
            : point(point), buf(b), position(p), tail(t), capacity(c) {}

        Iterator() : buf(nullptr) {}

        T& operator*() {
            return buf[(tail - position) % capacity];
        }

        T* operator-> () const {
            return &(operator*());
        }

        Iterator& operator+= (int num) {
            point += num;
            position += num;
            return *this;
        }

        Iterator& operator-= (int num) {
            point -= num;
            position -= num;
            return *this;
        }

        Iterator operator+ (int num) {
            return Iterator(point + num, buf, position + num, tail, capacity);
        }

        Iterator operator- (int num) {
            return Iterator(point - num, buf, position - num, tail, capacity);
        }

        difference_type operator- (Iterator it) {
            return point - it.point;
        }

        Iterator& operator++ () {
            point++;
            position++;
            return *this;
        }

        Iterator& operator--() {
            point--;
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

    T& operator[](int i) {
        int size2 = buf_size;
        if (i >= size2) {
            throw std::out_of_range("Index out of range");
        }
        return buffer[(tail - 1 - i) % capacity];
    }

    T operator[](int i) const {
        int size2 = buf_size;
        if (i >= size2) {
            throw std::out_of_range("Index out of range");
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
        int c = 0;
        int capacity2 = capacity;
        T* tmp = new T[capacity];
        for (int i = head; i < capacity2; i++) {
            tmp[c] = buffer[i];
            c++;
        }
        int tail2 = tail;
        for (int i = 0; i < tail2; i++) {
            tmp[c] = buffer[i];
            c++;
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
