#pragma once
#include <iterator>
#include <exception>

struct MyIteratorDirection
{
    static short int const DIRECT = 0;
    static short int const REVERSE = 1;
};

template<typename ValueType>
class CMyIterator : public std::iterator<std::input_iterator_tag, ValueType>
{
public:
    CMyIterator(ValueType* ptr) : m_valuePtr(ptr)
    {}

    CMyIterator(const CMyIterator& it) : m_valuePtr(it.m_valuePtr)
    {}

    bool operator!=(CMyIterator const& other) const
    {
        return m_valuePtr != other.m_valuePtr;
    }

    typename CMyIterator<ValueType>::reference operator*() const
    {
        return *m_valuePtr;
    }

    CMyIterator& operator++()
    {
        ++m_valuePtr;
        return *this;
    }
    CMyIterator& operator++(int)
    {
        m_valuePtr++;
        return *this;
    }

    CMyIterator& operator--()
    {
        --m_valuePtr;
        return *this;
    }
    CMyIterator& operator--(int)
    {
        m_valuePtr--;
        return *this;
    }

    const int operator-(const CMyIterator& other)
    {
        return (int)(m_valuePtr - other.m_valuePtr);
    }

    CMyIterator const operator+(const int number)
    {
        m_valuePtr += number;
        return *this;
    }

    CMyIterator const friend operator+(const int number, const CMyIterator& other)
    {
        ValueType* value = other.m_valuePtr + number;
        CMyIterator<ValueType> it(value);
        return it;
    }

private:
    ValueType* m_valuePtr;
};
