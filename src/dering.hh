#ifndef SKVY_DERING_DERING_H
#define SKVY_DERING_DERING_H

#include <cstddef>

namespace skvy {
namespace dering {

/* ********** Base Class ********** */

template <typename T, size_t CAP> class Base {
  public:
    Base() : head(0), tail(0) {}

    virtual size_t len() const = 0;
    size_t cap() const { return CAP; }
    bool is_empty() const;
    virtual bool is_full() const = 0;
    void clear();
    bool push_back(T val);
    bool pop_back(T *ptr);
    bool push_front(T val);
    bool pop_front(T *ptr);
    virtual bool value_at(size_t index, T **pptr) = 0;
    virtual bool value_at(size_t index, T const **pptr) const = 0;
    T &front();
    T const &front() const;
    virtual T &back() = 0;
    virtual T const &back() const = 0;
    virtual T &operator[](size_t index) = 0;
    virtual T const &operator[](size_t index) const = 0;

  protected:
    T data[CAP + 1];
    size_t head;
    size_t tail;

    virtual void push_back_uncheck(T val) = 0;
    virtual void pop_back_uncheck(T *ptr) = 0;
    virtual void push_front_uncheck(T val) = 0;
    virtual void pop_front_uncheck(T *ptr) = 0;
};

template <typename T, size_t CAP> bool Base<T, CAP>::is_empty() const {
    return this->head == this->tail;
}

template <typename T, size_t CAP> void Base<T, CAP>::clear() {
    this->tail = this->head;
}

template <typename T, size_t CAP> bool Base<T, CAP>::push_back(T val) {
    if (this->is_full()) {
        return false;
    }
    this->push_back_uncheck(val);
    return true;
}

template <typename T, size_t CAP> bool Base<T, CAP>::pop_back(T *ptr) {
    if (this->is_empty()) {
        return false;
    }
    this->pop_back_uncheck(ptr);
    return true;
}

template <typename T, size_t CAP> bool Base<T, CAP>::push_front(T val) {
    if (this->is_full()) {
        return false;
    }
    this->push_front_uncheck(val);
    return true;
}

template <typename T, size_t CAP> bool Base<T, CAP>::pop_front(T *ptr) {
    if (this->is_empty()) {
        return false;
    }
    this->pop_front_uncheck(ptr);
    return true;
}

template <typename T, size_t CAP> T &Base<T, CAP>::front() {
    return this->data[this->head];
}

template <typename T, size_t CAP> T const &Base<T, CAP>::front() const {
    return this->data[this->head];
}

template <typename T, size_t CAP, bool IS_POWER_OF_2 = (0 == ((CAP + 1) & CAP))>
class Dering;

/* ********** power of 2 ********** */

template <typename T, size_t CAP>
class Dering<T, CAP, true> : public Base<T, CAP> {
  public:
    size_t len() const;
    bool is_full() const;
    bool value_at(size_t index, T **pptr);
    bool value_at(size_t index, T const **pptr) const;
    T &back();
    T const &back() const;
    T &operator[](size_t index);
    T const &operator[](size_t index) const;

  protected:
    void push_back_uncheck(T val);
    void pop_back_uncheck(T *ptr);
    void push_front_uncheck(T val);
    void pop_front_uncheck(T *ptr);
};

template <typename T, size_t CAP> size_t Dering<T, CAP, true>::len() const {
    return CAP & (this->tail - this->head);
}

template <typename T, size_t CAP> bool Dering<T, CAP, true>::is_full() const {
    return (CAP & (this->tail + 1)) == this->head;
}

template <typename T, size_t CAP>
bool Dering<T, CAP, true>::value_at(size_t index, T **pptr) {
    if (this->len() <= index) {
        return false;
    }

    if (nullptr != pptr) {
        *pptr = this->data + (CAP & (this->head + index));
    }

    return true;
}

template <typename T, size_t CAP>
bool Dering<T, CAP, true>::value_at(size_t index, T const **pptr) const {
    if (this->len() <= index) {
        return false;
    }

    if (nullptr != pptr) {
        *pptr = this->data + (CAP & (this->head + index));
    }

    return true;
};

template <typename T, size_t CAP> T &Dering<T, CAP, true>::back() {
    return this->data[CAP & (this->tail - 1)];
}

template <typename T, size_t CAP> T const &Dering<T, CAP, true>::back() const {
    return this->data[CAP & (this->tail - 1)];
}

template <typename T, size_t CAP>
T &Dering<T, CAP, true>::operator[](size_t index) {
    return this->data[CAP & (this->head + index)];
}

template <typename T, size_t CAP>
T const &Dering<T, CAP, true>::operator[](size_t index) const {
    return this->data[CAP & (this->head + index)];
}

template <typename T, size_t CAP>
void Dering<T, CAP, true>::push_back_uncheck(T val) {
    this->data[this->tail] = val;
    this->tail = CAP & (this->tail + 1);
}

template <typename T, size_t CAP>
void Dering<T, CAP, true>::pop_back_uncheck(T *ptr) {
    this->tail = CAP & (this->tail - 1);
    if (nullptr != ptr) {
        *ptr = this->data[this->tail];
    }
}

template <typename T, size_t CAP>
void Dering<T, CAP, true>::push_front_uncheck(T val) {
    this->head = CAP & (this->head - 1);
    this->data[this->head] = val;
}

template <typename T, size_t CAP>
void Dering<T, CAP, true>::pop_front_uncheck(T *ptr) {
    if (nullptr != ptr) {
        *ptr = this->data[this->head];
    }
    this->head = CAP & (this->head + 1);
}

/* ********** not power of 2 ********** */

template <typename T, size_t CAP>
class Dering<T, CAP, false> : public Base<T, CAP> {
  public:
    size_t len() const;
    bool is_full() const;
    bool value_at(size_t index, T **pptr);
    bool value_at(size_t index, T const **pptr) const;
    T &back();
    T const &back() const;
    T &operator[](size_t index);
    T const &operator[](size_t index) const;

  protected:
    void push_back_uncheck(T val);
    void pop_back_uncheck(T *ptr);
    void push_front_uncheck(T val);
    void pop_front_uncheck(T *ptr);
};

template <typename T, size_t CAP> size_t Dering<T, CAP, false>::len() const {
    return this->head > this->tail ? ((CAP + 1) - (this->head - this->tail))
                                   : (this->tail - this->head);
}

template <typename T, size_t CAP> bool Dering<T, CAP, false>::is_full() const {
    return (CAP == this->tail ? 0 : (this->tail + 1)) == this->head;
}

template <typename T, size_t CAP>
bool Dering<T, CAP, false>::value_at(size_t index, T **pptr) {
    if (this->len() <= index) {
        return false;
    }

    if (nullptr != pptr) {
        *pptr = this->data
                + (CAP < (this->head + index) ? (this->head + index) - (CAP + 1)
                                              : (this->head + index));
    }

    return true;
}

template <typename T, size_t CAP>
bool Dering<T, CAP, false>::value_at(size_t index, T const **pptr) const {
    if (this->len() <= index) {
        return false;
    }

    if (nullptr != pptr) {
        *pptr = this->data
                + (CAP < (this->head + index) ? (this->head + index) - (CAP + 1)
                                              : (this->head + index));
    }

    return true;
};

template <typename T, size_t CAP> T &Dering<T, CAP, false>::back() {
    return this->data[0 == this->tail ? CAP : (this->tail - 1)];
}

template <typename T, size_t CAP> T const &Dering<T, CAP, false>::back() const {
    return this->data[0 == this->tail ? CAP : (this->tail - 1)];
}

template <typename T, size_t CAP>
T &Dering<T, CAP, false>::operator[](size_t index) {
    return this
        ->data[CAP < (this->head + index) ? (this->head + index) - (CAP + 1)
                                          : (this->head + index)];
}

template <typename T, size_t CAP>
T const &Dering<T, CAP, false>::operator[](size_t index) const {
    return this
        ->data[CAP < (this->head + index) ? (this->head + index) - (CAP + 1)
                                          : (this->head + index)];
}

template <typename T, size_t CAP>
void Dering<T, CAP, false>::push_back_uncheck(T val) {
    this->data[this->tail] = val;
    this->tail = CAP == this->tail ? 0 : (this->tail + 1);
}

template <typename T, size_t CAP>
void Dering<T, CAP, false>::pop_back_uncheck(T *ptr) {
    this->tail = 0 == this->tail ? CAP : (this->tail - 1);
    if (nullptr != ptr) {
        *ptr = this->data[this->tail];
    }
}

template <typename T, size_t CAP>
void Dering<T, CAP, false>::push_front_uncheck(T val) {
    this->head = 0 == this->head ? CAP : (this->head - 1);
    this->data[this->head] = val;
}

template <typename T, size_t CAP>
void Dering<T, CAP, false>::pop_front_uncheck(T *ptr) {
    if (nullptr != ptr) {
        *ptr = this->data[this->head];
    }
    this->head = CAP == this->head ? 0 : (this->head + 1);
}

} // namespace dering
} // namespace skvy

#endif
