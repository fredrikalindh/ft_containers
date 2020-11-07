#ifndef QUEUE_HPP
#define QUEUE_HPP

#include "list.hpp"

namespace ft
{
template <class T, class Container = ft::list<T> >
class queue
{
    Container d_ctnr;

public:
    typedef T value_type;
    typedef Container container_type;
    typedef size_t size_type;

    explicit queue(const container_type& ctnr = container_type()) : d_ctnr(ctnr) {}

    bool empty() const { return d_ctnr.empty(); }
    size_type size() const { return d_ctnr.size(); }
    value_type& front() { return d_ctnr.front(); }
    const value_type& front() const { return d_ctnr.front(); }
    value_type& back() { return d_ctnr.back(); }
    const value_type& back() const { return d_ctnr.back(); }
    void push(const value_type& val) { d_ctnr.push_back(val); }
    void pop() { d_ctnr.pop_front(); }

    friend void swap(queue& lhs, queue& rhs)
    {
        return lhs.d_ctnr.swap(rhs.d_ctnr);
    }
    friend bool operator==(const queue& lhs, const queue& rhs)
    {
        return lhs.d_ctnr == rhs.d_ctnr;
    }
    friend bool operator!=(const queue& lhs, const queue& rhs)
    {
        return lhs.d_ctnr != rhs.d_ctnr;
    }
    friend bool operator<(const queue& lhs, const queue& rhs)
    {
        return lhs.d_ctnr < rhs.d_ctnr;
    }
    friend bool operator<=(const queue& lhs, const queue& rhs)
    {
        return lhs.d_ctnr <= rhs.d_ctnr;
    }
    friend bool operator>(const queue& lhs, const queue& rhs)
    {
        return lhs.d_ctnr > rhs.d_ctnr;
    }
    friend bool operator>=(const queue& lhs, const queue& rhs)
    {
        return lhs.d_ctnr >= rhs.d_ctnr;
    }
};

}  //namespace ft

// template <class T, class Container>
// void swap(const ft::queue<T, Container> &lhs, const ft::queue<T, Container> &rhs)
// {
// 	return ft::swap(lhs, rhs);
// }

#endif
