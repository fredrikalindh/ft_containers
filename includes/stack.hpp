#ifndef STACK_HPP
#define STACK_HPP

#include "vector.hpp"

namespace ft
{
template <class T, class Container = vector<T> >
class stack
{
    Container d_ctnr;

public:
    typedef T value_type;
    typedef Container container_type;
    typedef size_t size_type;

    explicit stack(const container_type &ctnr = container_type()) : d_ctnr(ctnr) {}
    bool empty() const { return d_ctnr.empty(); }
    size_type size() const { return d_ctnr.size(); }
    value_type &top() { return d_ctnr.back(); }
    const value_type &top() const { return d_ctnr.back(); }
    void push(const value_type &val) { d_ctnr.push_back(val); }
    void pop() { d_ctnr.pop_back(); }

    friend void swap(stack &lhs, stack &rhs)
    {
        return lhs.d_ctnr.swap(rhs.d_ctnr);
    }
    template <typename _T, typename _Container>
    friend bool operator==(const stack<_T, _Container> &lhs, const stack<_T, _Container> &rhs);

    template <typename _T, typename _Container>
    friend bool operator<(const stack<_T, _Container> &lhs, const stack<_T, _Container> &rhs);
};

template <class T, class Container>
bool operator==(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
{
    return (lhs.d_ctnr == rhs.d_ctnr);
}
template <class T, class Container>
bool operator!=(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
{
    return !(lhs == rhs);
}
template <class T, class Container>
bool operator<(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
{
    return lhs.d_ctnr < rhs.d_ctnr;
}
template <class T, class Container>
bool operator<=(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
{
    return !(rhs < lhs);
}
template <class T, class Container>
bool operator>(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
{
    return rhs < lhs;
}
template <class T, class Container>
bool operator>=(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
{
    return !(lhs < rhs);
}
}  //namespace ft

// template <class T, class Container>
// bool operator==(const ft::stack<T, Container> &lhs, const ft::stack<T, Container> &rhs)
// {
// 	return lhs == rhs;
// }
// template <class T, class Container>
// bool operator!=(const ft::stack<T, Container> &lhs, const ft::stack<T, Container> &rhs)
// {
// 	return lhs != rhs;
// }
// template <class T, class Container>
// bool operator<(const ft::stack<T, Container> &lhs, const ft::stack<T, Container> &rhs)
// {
// 	return lhs < rhs;
// }
// template <class T, class Container>
// bool operator<=(const ft::stack<T, Container> &lhs, const ft::stack<T, Container> &rhs)
// {
// 	return lhs <= rhs;
// }
// template <class T, class Container>
// bool operator>(const ft::stack<T, Container> &lhs, const ft::stack<T, Container> &rhs)
// {
// 	return lhs > rhs;
// }
// template <class T, class Container>
// bool operator>=(const ft::stack<T, Container> &lhs, const ft::stack<T, Container> &rhs)
// {
// 	return lhs >= rhs;
// }

// template <class T, class Container>
// void swap(const ft::stack<T, Container> &lhs, const ft::stack<T, Container> &rhs)
// {
// 	return ft::swap(lhs, rhs);
// }

#endif
