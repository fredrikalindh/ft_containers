#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <functional>
namespace ft
{
template <class T1, class T2>
struct pair
{
    typedef T1 first_type;
    typedef T2 second_type;

    T1 first;
    T2 second;

    pair() : first(T1()), second(T2()) {}
    pair(const T1& x, const T2& y = T2()) : first(x), second(y) {}

    template <class U1, class U2>
    pair(const pair<U1, U2>& p) : first(p.first), second(p.second)
    {
    }

    pair(const pair& p) : first(p.first), second(p.second){};

    pair& operator=(pair const& x)
    {
        first = x.first;
        second = x.second;
        return *this;
    }
};

template <class T1, class T2>
bool operator==(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
{
    return (lhs.first == rhs.first && lhs.second == rhs.second);
}
template <class T1, class T2>
bool operator!=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
{
    return !(lhs == rhs);
}
template <class T1, class T2>
bool operator<(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
{
    if (lhs.first < rhs.first)
        return true;
    else if (lhs.first == rhs.first && lhs.second < rhs.second)
        return true;
    return false;
}
template <class T1, class T2>
bool operator<=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
{
    return !(rhs < lhs);
}
template <class T1, class T2>
bool operator>(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
{
    return rhs < lhs;
}
template <class T1, class T2>
bool operator>=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
{
    return !(lhs < rhs);
}

template <class T1, class T2>
pair<T1, T2> make_pair(T1 a, T2 b)
{
    return pair<T1, T2>(a, b);
}
}  //namespace ft

#endif
