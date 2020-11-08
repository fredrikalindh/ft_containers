#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <stdexcept>

#include "iterator.hpp"
#include "utility.hpp"

namespace ft
{
template <class T, bool isconst = false>
class vector_iterator;
/**
 * VECTOR: dynamic array optimized for insertion in the back.
 */
template <class T, class Alloc = std::allocator<T> >
class vector
{
	T *array_;
	size_t size_;
	size_t capacity_;

	vector(const vector &x, size_t capacity) : array_(capacity ? new T[capacity] : nullptr),
											   capacity_(capacity)
	{
		size_type i = 0;
		while (i < capacity_ && i < x.size_)
		{
			array_[i] = x.array_[i];
			++i;
		}
		size_ = i;
	}

public:
	typedef size_t size_type;
	typedef T value_type;
	typedef Alloc allocator_type;
	typedef value_type &reference;
	typedef const value_type &const_reference;
	typedef value_type *pointer;
	typedef const value_type *const_pointer;
	typedef vector_iterator<T> iterator;
	typedef vector_iterator<T, true> const_iterator;
	typedef ft::reverse_iterator<iterator> reverse_iterator;
	typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
	typedef typename iterator_traits<iterator>::difference_type difference_type;

	explicit vector(const allocator_type & = allocator_type()) : array_(0),
																 size_(0),
																 capacity_(0)
	{
	}
	explicit vector(size_type n, const value_type &val = value_type(),
					const allocator_type & = allocator_type()) : array_(new T[n]),
																 size_(n),
																 capacity_(n)
	{
		for (size_type i = 0; i < n; i++)
			array_[i] = val;
	}
	template <class InputIterator>
	vector(InputIterator first, InputIterator last,
		   const allocator_type & = allocator_type(),
		   typename std::enable_if<!std::is_integral<InputIterator>::value>::type * = 0) : array_(0),
																						   size_(0),
																						   capacity_(0)
	{
		while (first != last)
			push_back(*first++);
	}
	vector(const vector &x) : array_(new T[x.capacity_]),
							  size_(x.size_),
							  capacity_(x.capacity_)
	{
		for (size_type i = 0; i < size_; i++)
			array_[i] = x.array_[i];
	}
	~vector()
	{
		delete[] array_;
	}
	vector &operator=(const vector &x)
	{
		vector ret(x);
		swap(ret);
		return *this;
	}
	iterator begin() { return array_; }
	const_iterator begin() const { return array_; }
	iterator end() { return &array_[size_]; }
	const_iterator end() const { return &array_[size_]; }
	reverse_iterator rbegin() { return reverse_iterator(end()); }
	const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
	reverse_iterator rend() { return reverse_iterator(begin()); }
	const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }
	size_type size() const { return size_; }
	size_type max_size() const
	{
		return std::numeric_limits<difference_type>::max() / ((sizeof(T) / 2) < 1 ? 1 : (sizeof(T) / 2));
	}
	void resize(size_type n, value_type val = value_type())
	{
		if (n > max_size())
			throw std::length_error("max_size(size_t n) 'n' exceeds maximum supported size");
		vector tmp(*this, n);
		swap(tmp);
		for (size_type i = size_; i < capacity_; ++i)
			array_[i] = val;
		size_ = n;
	}
	size_type capacity() const { return capacity_; }
	bool empty() const { return !size_; }
	void reserve(size_type n)
	{
		if (n > capacity_)
		{
			if (n > max_size())
				throw std::length_error("reserve(size_t n) 'n' exceeds maximum supported size");
			vector tmp(*this, n);
			swap(tmp);
		}
	}
	reference operator[](size_type n) { return array_[n]; }
	const_reference operator[](size_type n) const { return array_[n]; }
	reference at(size_type n)
	{
		if (n >= size_)
			throw std::out_of_range("vector");
		return array_[n];
	}
	const_reference at(size_type n) const
	{
		if (n >= size_)
			throw std::out_of_range("vector");
		return array_[n];
	}
	reference front() { return array_[0]; }
	const_reference front() const { return array_[0]; }
	reference back() { return array_[size_ - 1]; }
	const_reference back() const { return array_[size_ - 1]; }
	template <class InputIterator>
	void assign(InputIterator first, InputIterator last)
	{
		vector tmp(first, last);
		swap(tmp);
	}
	void assign(size_type n, const value_type &val)
	{
		vector tmp(n, val);
		swap(tmp);
	}
	void push_back(const value_type &val)
	{
		if (size_ >= capacity_)
		{
			vector tmp(*this, !capacity_ ? 1 : capacity_ * 2);
			swap(tmp);
		}
		array_[size_++] = val;
	}
	void pop_back()
	{
		if (size_ > 0)
			size_--;
	}
	iterator insert(iterator position, const value_type &val)
	{
		size_type n = position - array_;
		insert(position, 1, val);
		return array_ + n;
	}
	void insert(iterator position, size_type n, const value_type &val)
	{
		if (size_ + n >= capacity_)
		{
			vector tmp(*this, capacity_ + n);
			position = tmp.array_ + (position - array_);
			swap(tmp);
		}
		for (iterator back = &array_[size_ - 1]; back >= position; --back)
			back[n] = *back;
		for (size_type i = 0; i < n; i++)
			*position++ = val;
		size_ += n;
	}
	template <class InputIterator>
	void insert(iterator position, InputIterator first, InputIterator last,
				typename std::enable_if<!std::is_integral<InputIterator>::value>::type * = 0)
	{
		while (first != last)
			position = insert(position, *first++) + 1;
	}
	iterator erase(iterator position)
	{
		for (iterator it = position; it + 1 < end(); ++it)
			*it = *(it + 1);
		if (size_)
			size_--;
		return position;
	}
	iterator erase(iterator first, iterator last)
	{
		size_type dif = last - first;
		for (iterator it = first; last < end(); ++last)
			*it++ = *last;
		size_ -= dif;
		return first;
	}
	void swap(vector &x)
	{
		char buffer[sizeof(vector)];
		memcpy(buffer, reinterpret_cast<char *>(&x), sizeof(vector));
		memcpy(reinterpret_cast<char *>(&x), this, sizeof(vector));
		memcpy(reinterpret_cast<char *>(this), buffer, sizeof(vector));
	}
	void clear()
	{
		vector tmp;
		swap(tmp);
	}
};
template <class T, bool isconst>
class vector_iterator
{
	friend class vector_iterator<T, false>;
	friend class vector_iterator<T, true>;

public:
	typedef ft::random_access_iterator_tag iterator_category;
	typedef T value_type;
	typedef typename choose<isconst, const T &, T &>::type reference;
	typedef typename choose<isconst, const T *, T *>::type pointer;
	typedef std::ptrdiff_t difference_type;

protected:
	pointer p;

public:
	vector_iterator() : p(nullptr) {}
	vector_iterator(pointer p) : p(p) {}
	vector_iterator(vector_iterator<T, false> const &x) : p(x.p) {}
	virtual ~vector_iterator() {}

	vector_iterator &operator=(vector_iterator<T, false> const &x)
	{
		p = x.p;
		return *this;
	}
	reference operator*() const
	{
		return *p;
	}
	pointer operator->() const
	{
		return p;
	}
	reference operator[](int val) const
	{
		return p[val];
		// return *(p + val);
	}
	vector_iterator operator++(int)
	{
		vector_iterator tmp(*this);
		++p;
		return tmp;
	}
	vector_iterator &operator++()
	{
		++p;
		return *this;
	}
	vector_iterator operator--(int)
	{
		vector_iterator tmp(*this);
		--p;
		return tmp;
	}
	vector_iterator &operator--()
	{
		--p;
		return *this;
	}
	vector_iterator &operator+=(int value)
	{
		p += value;
		return *this;
	}
	vector_iterator operator+(int value) const
	{
		vector_iterator tmp(*this);
		return tmp += value;
	}
	vector_iterator &operator-=(int value)
	{
		p -= value;
		return *this;
	}
	vector_iterator operator-(int value) const
	{
		vector_iterator tmp(*this);
		return tmp -= value;
	}
	difference_type operator-(vector_iterator const &x) const
	{
		return p - x.p;
	}
	friend vector_iterator operator+(difference_type value, const vector_iterator &x)
	{
		vector_iterator tmp(x);
		return tmp += value;
	}
	friend bool operator==(const vector_iterator &lhs, const vector_iterator &rhs)
	{
		return lhs.p == rhs.p;
	}
	friend bool operator!=(const vector_iterator &lhs, const vector_iterator &rhs)
	{
		return lhs.p != rhs.p;
	}
	friend bool operator<(const vector_iterator &lhs, const vector_iterator &rhs)
	{
		return lhs.p < rhs.p;
	}
	friend bool operator<=(const vector_iterator &lhs, const vector_iterator &rhs)
	{
		return lhs.p <= rhs.p;
	}
	friend bool operator>(const vector_iterator &lhs, const vector_iterator &rhs)
	{
		return lhs.p > rhs.p;
	}
	friend bool operator>=(const vector_iterator &lhs, const vector_iterator &rhs)
	{
		return lhs.p >= rhs.p;
	}
};

template <class T>
void swap(ft::vector<T> &a, ft::vector<T> &b)
{
	a.swap(b);
}
template <class T>
bool operator==(const ft::vector<T> &lhs, const ft::vector<T> &rhs)
{
	if (lhs.size() != rhs.size())
		return false;
	return equal(lhs.begin(), lhs.end(), rhs.begin());
}
template <class T>
bool operator!=(const ft::vector<T> &lhs, const ft::vector<T> &rhs)
{
	return !(lhs == rhs);
}
template <class T>
bool operator<(const ft::vector<T> &lhs, const ft::vector<T> &rhs)
{
	ft::less<T> less;
	return lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end(), less);
}
template <class T>
bool operator<=(const ft::vector<T> &lhs, const ft::vector<T> &rhs)
{
	return !(rhs < lhs);
}
template <class T>
bool operator>(const ft::vector<T> &lhs, const ft::vector<T> &rhs)
{
	return rhs < lhs;
}
template <class T>
bool operator>=(const ft::vector<T> &lhs, const ft::vector<T> &rhs)
{
	return !(lhs < rhs);
}
}  //namespace ft

#endif
