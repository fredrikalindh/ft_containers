#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <stdexcept>

#include "iterator.hpp"

namespace ft
{
	/*
	* VECTOR: dynamic array optimized for insertion in the back.
	*/
	template <class T>
	class vector
	{
	protected:
		T *array_;
		size_t size_;
		size_t capacity_;
		size_t multi_;

		vector(const vector &x, size_t capacity) : array_(capacity ? new T[capacity] : nullptr),
												   capacity_(capacity),
												   multi_(x.multi_)
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
		typedef value_type &reference;
		typedef const value_type &const_reference;
		typedef value_type *pointer;
		typedef const value_type *const_pointer;
		typedef T *iterator;
		typedef const T *const_iterator;
		typedef ft::reverse_iterator<iterator> reverse_iterator;
		typedef ft::reverse_iterator<const T *> const_reverse_iterator;
		typedef std::ptrdiff_t difference_type;

		explicit vector() : array_(0),
							size_(0),
							capacity_(0),
							multi_(1) {}
		explicit vector(size_type n, const value_type &val = value_type()) : array_(new T[n]),
																			 size_(n),
																			 capacity_(n),
																			 multi_(n)
		{
			for (size_type i = 0; i < n; i++)
				array_[i] = val;
		}
		template <class InputIterator>
		vector(InputIterator first, InputIterator last,
			   typename std::enable_if<!std::is_integral<InputIterator>::value>::type * = 0) : array_(0),
																							   size_(0),
																							   capacity_(0),
																							   multi_(1)
		{
			while (first != last)
				push_back(*first++);
		}
		vector(const vector &x) : array_(new T[x.capacity_]),
								  size_(x.size_),
								  capacity_(x.capacity_),
								  multi_(x.multi_)
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
		const_reverse_iterator rbegin() const { return reverse_iterator(end()); }
		reverse_iterator rend() { return reverse_iterator(begin()); }
		const_reverse_iterator rend() const { return reverse_iterator(begin()); }
		size_type size() const { return size_; }
		size_type max_size() const { return 4611686018427387903; }
		void resize(size_type n, value_type val = value_type())
		{
			if (n > max_size())
				throw std::length_error("max_size(size_t n) 'n' exceeds maximum supported size"); //allocator<T>::allocate(size_t n) 'n' exceeds maximum supported size
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
		inline reference operator[](size_type n) { return array_[n]; }
		inline const_reference operator[](size_type n) const { return array_[n]; }
		inline reference at(size_type n)
		{
			if (n >= size_)
				throw std::out_of_range("vector");
			return array_[n];
		}
		inline const_reference at(size_type n) const
		{
			if (n >= size_)
				throw std::out_of_range("vector");
			return array_[n];
		}
		inline reference front() { return array_[0]; }
		inline const_reference front() const { return array_[0]; }
		inline reference back() { return array_[size_ - 1]; }
		inline const_reference back() const { return array_[size_ - 1]; }
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
				vector tmp(*this, capacity_ + multi_);
				tmp.multi_ = multi_ * 2;
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
		{ // OWN ENABLE_IF ?
			while (first != last)
				position = insert(position, *first++);
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
			size_ -= (last - first);
			for (iterator it = first; last < end(); ++last)
				*it++ = *last;
			return first;
		}
		void swap(vector &x)
		{
			char buffer[sizeof(vector)];
			memcpy(buffer, &x, sizeof(vector));
			memcpy(reinterpret_cast<char *>(&x), this, sizeof(vector));
			memcpy(reinterpret_cast<char *>(this), buffer, sizeof(vector));
		}
		void clear()
		{
			vector tmp;
			swap(tmp);
		}
	}; // namespace ft

} //namespace ft

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
	typename ft::vector<T>::const_iterator l_it = lhs.begin(); // #########################   WHY TYPENAME?
	typename ft::vector<T>::const_iterator r_it = rhs.begin();
	while (l_it != lhs.end() && r_it != rhs.end())
	{
		if (*l_it != *r_it)
		{
			std::cout << *l_it << " != " << *r_it << '\n';
			return false;
		}
		l_it++;
		r_it++;
	}
	return true;
}
template <class T>
bool operator!=(const ft::vector<T> &lhs, const ft::vector<T> &rhs)
{
	return !(lhs == rhs);
}
template <class T>
bool operator<(const ft::vector<T> &lhs, const ft::vector<T> &rhs)
{
	typename ft::vector<T>::const_iterator l_it = lhs.begin(); // #########################   WHY TYPENAME?
	typename ft::vector<T>::const_iterator r_it = rhs.begin();
	while (l_it != lhs.end() && r_it != rhs.end())
	{
		if (*l_it < *r_it)
			return true;
		if (*l_it > *r_it)
			return false;
		l_it++;
		r_it++;
	}
	return true;
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

#endif
