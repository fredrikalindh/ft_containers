#ifndef DEQUE_HPP
#define DEQUE_HPP

#include "iterator.hpp"
#include "utility.hpp"
namespace ft
{
template <class T, bool isconst = false>
class deque_iterator;

template <class T>
class deque_array;

/**
 * DEQUE - double ended queue with a structure similar to a vector 
 * but optimised for pushing and popping both ends. Unlike a vector
 * it therefore doesn't guarantee that the data will be stored 
 * continously. 
 *  [ ]
 *  [x] ---> [ ][ ][ ][x][x][x]
 *  [x] ---> [x][x][x][x][x][x]
 *  [x] ---> [x][x][x][x][ ][ ]
 *  [ ]
 */
template <class T, class Alloc = std::allocator<T> >
class deque
{
	template <class U, bool isconst>
	friend class deque_iterator;

	static const int ARRAY_SIZE = 1024;

	deque_array<deque_array<T> > arrays_;

public:
	typedef T value_type;
	typedef Alloc allocator_type;
	typedef value_type &reference;
	typedef const value_type &const_reference;
	typedef value_type *pointer;
	typedef const value_type *const_pointer;
	typedef ft::deque_iterator<T> iterator;
	typedef ft::deque_iterator<T, true> const_iterator;
	typedef ft::reverse_iterator<iterator> reverse_iterator;
	typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
	typedef typename iterator_traits<iterator>::difference_type difference_type;
	typedef size_t size_type;

	explicit deque(const allocator_type & = allocator_type()) {}
	explicit deque(size_type n, const value_type &val = value_type(),
				   const allocator_type & = allocator_type()) : arrays_(n ? ARRAY_SIZE % n + 1 : 1, 0)
	{
		for (size_type i = 0; i < n; ++i)
		{
			if (arrays_.size_ <= 0 || !arrays_.back().space_back())
				arrays_.push_back(deque_array<T>(ARRAY_SIZE, 0));
			arrays_.back().push_back(val);
		}
	}
	template <class InputIterator>
	deque(InputIterator first, InputIterator last,
		  const allocator_type & = allocator_type(),
		  typename std::enable_if<!std::is_integral<InputIterator>::value>::type * = 0)
	{
		while (first != last)
		{
			if (arrays_.size_ <= 0 || !arrays_.back().space_back())
				arrays_.push_back(deque_array<T>(ARRAY_SIZE, 0));
			arrays_.back().push_back(*first++);
		}
	}
	deque(const deque &x) : arrays_(x.arrays_) {}
	~deque() {}
	deque &operator=(const deque &x)
	{
		arrays_ = x.arrays_;
		return *this;
	}
	iterator begin() { return iterator(0, 0, &arrays_); }
	const_iterator begin() const { return const_iterator(0, 0, &arrays_); }
	iterator end() { return iterator(arrays_.size_, 0, &arrays_); }
	const_iterator end() const { return const_iterator(arrays_.size_, 0, &arrays_); }
	reverse_iterator rbegin() { return reverse_iterator(end()); }
	const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
	reverse_iterator rend() { return reverse_iterator(begin()); }
	const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }

	size_type size() const
	{
		size_type size = 0;
		for (int i = 0; i < arrays_.size_; ++i)
			size += arrays_[i].size_;
		return size;
	}
	size_type max_size() const
	{
		return std::numeric_limits<difference_type>::max() / ((sizeof(T) / 2) < 1 ? 1 : (sizeof(T) / 2));
	}
	void resize(size_type n, value_type val = value_type())
	{
		size_type sz = size();
		if (n < sz)
			erase(begin() + n, end());
		else if (n > sz)
			insert(end(), size_t(n - sz), val);
	}
	bool empty() const { return !size(); }
	void swap(deque &x)
	{
		char buffer[sizeof(deque)];
		memcpy(buffer, &x, sizeof(deque));
		memcpy(reinterpret_cast<char *>(&x), this, sizeof(deque));
		memcpy(reinterpret_cast<char *>(this), buffer, sizeof(deque));
	}
	void clear()
	{
		deque tmp;
		swap(tmp);
	}
	reference operator[](size_type n)
	{
		return *get_position(n);
	}
	const_reference operator[](size_type n) const
	{
		return *get_position(n);
	}
	reference at(size_type n)
	{
		pointer p = get_position(n);
		if (!p)
			throw std::out_of_range("deque");
		return *p;
	}
	const_reference at(size_type n) const
	{
		pointer p = get_position(n);
		if (!p)
			throw std::out_of_range("deque");
		return *p;
	}
	reference front()
	{
		return arrays_.front().front();
	}
	const_reference front() const
	{
		return arrays_.front().front();
	}
	reference back()
	{
		return arrays_.back().back();
	}
	const_reference back() const
	{
		return arrays_.back().back();
	}
	template <class InputIterator>
	void assign(InputIterator first, InputIterator last)
	{
		deque tmp(first, last);
		swap(tmp);
	}
	void assign(size_type n, const value_type &val)
	{
		deque tmp(n, val);
		swap(tmp);
	}
	void push_back(const value_type &val)
	{
		if (arrays_.size_ <= 0 || !arrays_.back().space_back())
			arrays_.push_back(deque_array<T>(ARRAY_SIZE, 0));
		arrays_.back().push_back(val);
	}
	void push_front(const value_type &val)
	{
		if (arrays_.size_ <= 0 || !arrays_.front().space_front())
			arrays_.push_front(deque_array<T>(ARRAY_SIZE, ARRAY_SIZE - 1));
		arrays_.front().push_front(val);
	}
	void pop_back()
	{
		arrays_.back().pop_back();
		if (!arrays_.back().size_)
			--arrays_.size_;
	}
	void pop_front()
	{
		arrays_.front().pop_front();
		if (!arrays_.front().size_)
		{
			++arrays_.index_first;
			--arrays_.size_;
		}
	}
	iterator insert(iterator position, const value_type &val)
	{
		insert(position, 1, val);
		if (!position.i_in && position.i_out)
			--position;
		return position;
	}
	void insert(iterator position, size_type n2, const value_type &val)
	{
		int n = n2;
		if (!n2)
			return;
		if (!position.i_in)
		{  // position == end()
			for (int i = 0; i < n; ++i)
				push_back(val);
			return;
		}
		// if there is space for insertion in current array
		if (arrays_[position.i_out].size_ + n < arrays_[position.i_out].capacity_)
			arrays_[position.i_out].insert(position.i_in, n, val);
		else
		{
			// N_TO_ARR, ELEMENTS AFTER POSITION THAT WILL BE COPIED TO A NEW ARRAY TMP
			deque_array<T> tmp;
			int n_to_arr = (ARRAY_SIZE - position.i_in < n) ? ARRAY_SIZE - position.i_in : n;
			if (int afterPos = arrays_[position.i_out].size_ - position.i_in)
			{
				int startPos = ARRAY_SIZE - position.i_in - n;
				startPos < 0 ? startPos = 0 : 0;
				tmp = deque_array<T>(ARRAY_SIZE, &(*position) + startPos, &(*position) + afterPos);
			}  // N_TO_ARR, ELEMENTS THAT NOW FIT IN CURRENT ARRAY,
			n -= n_to_arr;
			arrays_[position.i_out].insert(position.i_in, n_to_arr, val);
			// UNTIL ALL ELEMENTS ARE ADDED NEW ARRAYS WILL BE FILLED WITH MAX ARRAY_SIZE VAL
			while (n)
			{
				n_to_arr = (n < ARRAY_SIZE) ? n : ARRAY_SIZE;
				if (!arrays_.space_back())
					arrays_ = deque_array<deque_array<T> >(arrays_, arrays_.capacity_ + 2);
				arrays_.insert(++position.i_out + 1, 1, deque_array<T>(ARRAY_SIZE, n_to_arr, val));
				n -= n_to_arr;
			}
			int spaceInLast = ARRAY_SIZE - arrays_[position.i_out].size_;
			if (tmp.size_)
			{
				int elementsToInsert = (spaceInLast < tmp.size_) ? spaceInLast : tmp.size_;
				for (int i = 0; i < elementsToInsert; ++i)
					arrays_[position.i_out].push_back(tmp[i]);
				if (elementsToInsert != tmp.size_)
				{
					tmp.erase(0, elementsToInsert);
					if (!arrays_.space_back())
						arrays_ = deque_array<deque_array<T> >(arrays_, arrays_.capacity_ + 2);
					arrays_.insert(++position.i_out + 1, 1, tmp);
				}
			}
		}
	}
	template <class InputIterator>
	void insert(iterator position, InputIterator first, InputIterator last,
				typename std::enable_if<!std::is_integral<InputIterator>::value>::type * = 0)
	{
		while (first != last)
		{
			position = insert(position, *first++);
			++position;
		}
	}
	iterator erase(iterator position)
	{
		if (position == end() - 1)
			pop_back();
		else if (position == begin())
			pop_front();
		else
			arrays_[position.i_out].erase(position.i_in);
		return position;
	}
	iterator erase(iterator first, iterator last)
	{
		if (last == end())
		{
			arrays_.size_ = first.i_out + 1;
			arrays_[first.i_out].size_ = first.i_in;
		}
		else if (first == begin())
		{
			arrays_.size_ -= (last.i_out - arrays_.index_first);
			arrays_.index_first = last.i_out;
			arrays_[0].size_ -= (last.i_in - arrays_[0].index_first);
			arrays_[0].index_first = last.i_in;
		}
		else if (first.i_out == last.i_out)
		{
			arrays_[first.i_out].erase(first.i_in, last.i_in);
		}
		else
		{
			arrays_[first.i_out].erase(first.i_in, arrays_[first.i_out].size_);
			arrays_[last.i_out].erase(0, last.i_in);
			if (last.i_out - first.i_out > 0)
				arrays_.erase(first.i_out + 1, last.i_out);
			first.i_in = 0;
			first.i_out++;
		}
		return first;
	}

private:
	pointer get_position(int n) const
	{
		for (int i = 0; n >= 0 && i < arrays_.size_; ++i)
		{
			if (n < arrays_[i].size_)
				return &arrays_[i][n];
			n -= arrays_[i].size_;
		}
		return nullptr;
	}
};

template <class T>
class deque_array;

/**
 * DEQUE_ARRAY is what recursively builds up the deque by using the class 
 * first for the outer array< array<T> > - of varying capacity - and then 
 * the inner array<T> that has a fixed size set inside the deque class.
 * by standard the new deque_array starts at capacity/2, filling up using 
 * push_front/back, but can be set to start at specific index such as 0 or 
 * capacity for example. 
 */
template <class T>
class deque_array
{
	template <class U, class Alloc>
	friend class deque;
	template <class U, bool isconst>
	friend class deque_iterator;

	int capacity_;
	T *array_;
	int size_;
	int index_first;

public:
	typedef T value_type;

	deque_array() : capacity_(0),
					array_(nullptr),
					size_(0),
					index_first(0) {}
	deque_array(int capacity,
				int start_index = -1) : capacity_(capacity),
										array_(new T[capacity_]),
										size_(0),
										index_first(start_index == -1 ? capacity_ / 2 : start_index) {}
	deque_array(deque_array const &x) : capacity_(x.capacity_),
										array_(new T[capacity_]),
										size_(x.size_),
										index_first(x.index_first)
	{
		for (int i = index_first; i < size_ + index_first; ++i)
			array_[i] = x.array_[i];
	}
	template <class InputIterator>
	deque_array(int capacity, InputIterator first, InputIterator last,
				typename std::enable_if<!std::is_integral<InputIterator>::value>::type * = 0) : capacity_(capacity),
																								array_(new T[capacity_]),
																								index_first(0)
	{
		int i = 0;
		while (first != last)
			array_[i++] = *first++;
		size_ = i;
	}
	deque_array(int capacity, int n, value_type const &val) : capacity_(capacity),
															  array_(new T[capacity_]),
															  size_(n),
															  index_first(0)
	{
		for (int i = 0; i < size_; ++i)
			array_[i] = val;
	}
	deque_array(deque_array const &x, int new_size) : capacity_(new_size),
													  array_(new T[capacity_]),
													  size_(x.size_),
													  index_first((new_size - x.size_) / 2)
	{
		int j = x.index_first;
		for (int i = index_first; i < size_ + index_first; ++i)
			array_[i] = x.array_[j++];
	}
	~deque_array() { delete[] array_; }
	deque_array &operator=(deque_array const &x)
	{
		deque_array tmp(x);
		swap(tmp);
		return *this;
	}
	T &operator[](int n) { return array_[index_first + n]; }
	T &operator[](int n) const { return array_[index_first + n]; }
	bool full() const { return size_ >= capacity_; }
	bool space_back() const { return (index_first + size_) < capacity_; }
	bool space_front() const { return index_first > 0; }
	T &front() { return array_[index_first]; }
	T const &front() const { return array_[index_first]; }
	T &back() { return array_[index_first + size_ - 1]; }
	T const &back() const { return array_[index_first + size_ - 1]; }
	void push_front(T const &x)
	{
		if (index_first == 0)
		{
			int new_capacity = (capacity_ == 0) ? 2 : capacity_ * 2;
			deque_array tmp(*this, new_capacity);
			swap(tmp);
		}
		array_[--index_first] = x;
		++size_;
	}
	void push_back(T const &x)
	{
		if (index_first + size_ >= capacity_)
		{
			int new_capacity = (capacity_ == 0) ? 1 : capacity_ * 2;
			deque_array tmp(*this, new_capacity);
			swap(tmp);
		}
		array_[index_first + size_] = x;
		++size_;
	}
	void pop_front()
	{
		++index_first;
		--size_;
	}
	void pop_back() { --size_; }
	void swap(deque_array &x)
	{
		char buffer[sizeof(deque_array)];
		memcpy(buffer, &x, sizeof(deque_array));
		memcpy(reinterpret_cast<char *>(&x), this, sizeof(deque_array));
		memcpy(reinterpret_cast<char *>(this), buffer, sizeof(deque_array));
	}
	void erase(int position)
	{
		for (int i = position + index_first; i + 1 < index_first + size_; ++i)
			array_[i] = array_[i + 1];
		--size_;
	}
	void erase(int first, int last)
	{
		int dif = last - first;
		for (int i = first + index_first; i + dif < index_first + size_; ++i)
			array_[i] = array_[i + dif];
		size_ -= dif;
	}
	void insert(int position, const value_type &val)
	{
		insert(position, 1, val);
	}
	void insert(int position, int n, const value_type &val)
	{
		position += index_first;
		// IF POSITION IS NOT IN THE END, WE HAVE TO MOVE TO MAKE SPACE
		// IF N + SIZE_ > CAPACITY_ MOVING ELEMENTS IS TAKEN CARE OF IN OUTER LAYER
		if (position < size_)
		{
			size_ = (size_ + n < capacity_) ? size_ + n : capacity_;
			int i;
			for (i = size_ - 1; i >= position + n; --i)
				array_[i] = array_[i - n];
			while (i >= position)
				array_[i--] = val;
		}
		// OTHERWISE WE JUST PUSH BACK
		else
		{
			if (n > capacity_ - size_)
				n = capacity_ - size_;
			for (int i = 0; i < n; ++i)
				push_back(val);
		}
	}
};

/*
	* DEQUE_ITERATOR: a double layered array_, index for the outer array and 
	* index for the inner. It will try to do all operations on the inner index
	* if fail it will go out one layer
	*/
template <class T, bool isconst>
class deque_iterator
{
	friend class deque<T>;
	friend class deque_iterator<T, false>;
	friend class deque_iterator<T, true>;

	typedef typename choose<isconst,
							const deque_array<deque_array<T> > *,
							deque_array<deque_array<T> > *>::type dequeptr;

	int i_out;		  // index for array
	int i_in;		  // index inside array
	dequeptr array_;  // pointer to the container

public:
	typedef ft::random_access_iterator_tag iterator_category;
	typedef std::ptrdiff_t difference_type;
	typedef T value_type;
	typedef typename choose<isconst, const T &, T &>::type reference;
	typedef typename choose<isconst, const T *, T *>::type pointer;

	deque_iterator() : i_out(0),
					   i_in(0),
					   array_(0) {}
	deque_iterator(int out, int in, dequeptr d) : i_out(out),
												  i_in(in),
												  array_(d) {}
	deque_iterator(deque_iterator<T, false> const &x) : i_out(x.i_out),
														i_in(x.i_in),
														array_(x.array_) {}
	~deque_iterator() {}
	deque_iterator &operator=(deque_iterator<T, false> const &x)
	{
		deque_iterator tmp(x);
		swap(tmp);
		return *this;
	}
	reference operator*() const { return (*array_)[i_out][i_in]; }
	pointer operator->() const { return &(operator*()); }
	reference operator[](difference_type n) const { return *(*this + n); }
	deque_iterator operator+(difference_type n) const
	{
		deque_iterator tmp(*this);

		tmp += n;
		return tmp;
	}
	deque_iterator &operator+=(difference_type n)
	{
		while (n)
		{
			if (n + i_in < (*array_)[i_out].size_)
			{
				i_in += n;
				break;
			}
			n -= ((*array_)[i_out++].size_ - i_in);
			i_in = 0;
		}
		return *this;
	}
	deque_iterator operator-(difference_type n) const
	{
		deque_iterator tmp(*this);
		tmp -= n;
		return tmp;
	}
	deque_iterator &operator-=(difference_type n)
	{
		while (n)
		{
			if (i_in - n >= 0)
			{
				i_in -= n;
				break;
			}
			n -= i_in;
			--i_out;
			i_in = (*array_)[i_out].size_;
		}
		return *this;
	}
	deque_iterator &operator++()
	{
		++i_in;
		if (i_in && i_in == (*array_)[i_out].size_)
		{
			i_in = 0;
			++i_out;
		}

		return *this;
	}
	deque_iterator operator++(int)
	{
		deque_iterator tmp(*this);
		operator++();
		return tmp;
	}
	deque_iterator &operator--()
	{
		if (i_in == 0 && i_out > 0)
		{
			--i_out;
			i_in = (*array_)[i_out].size_;
		}
		--i_in;
		return *this;
	}
	deque_iterator operator--(int)
	{
		deque_iterator tmp(*this);
		operator--();
		return tmp;
	}
	void swap(deque_iterator &x)
	{
		char buffer[sizeof(deque_iterator)];
		memcpy(buffer, &x, sizeof(deque_iterator));
		memcpy(reinterpret_cast<char *>(&x), this, sizeof(deque_iterator));
		memcpy(reinterpret_cast<char *>(this), buffer, sizeof(deque_iterator));
	}
	difference_type operator-(deque_iterator const &x) const
	{
		if (i_out == x.i_out)
			return i_in - x.i_in;
		if (i_out > x.i_out)
			return -(x - *this);
		difference_type ret = (*array_)[i_out].size_ - i_in + x.i_in;
		for (int i = i_out + 1; i < x.i_out; ++i)
			ret += (*array_)[i].size_;
		return -ret;
	}
	friend deque_iterator operator+(difference_type value, const deque_iterator &x)
	{
		deque_iterator tmp(x);
		return tmp += value;
	}
	friend bool operator==(deque_iterator const &lhs, deque_iterator const &rhs)
	{
		return lhs.i_out == rhs.i_out && lhs.i_in == rhs.i_in && lhs.array_ == rhs.array_;
	}
	friend bool operator!=(deque_iterator const &lhs, deque_iterator const &rhs)
	{
		return !(lhs == rhs);
	}
	friend bool operator<(deque_iterator const &lhs, deque_iterator const &rhs)
	{
		return lhs.i_out < rhs.i_out || lhs.i_in < rhs.i_in || lhs.array_ < rhs.array_;
	}
	friend bool operator<=(deque_iterator const &lhs, deque_iterator const &rhs)
	{
		return !(rhs < lhs);
	}
	friend bool operator>(deque_iterator const &lhs, deque_iterator const &rhs)
	{
		return rhs < lhs;
	}
	friend bool operator>=(deque_iterator const &lhs, deque_iterator const &rhs)
	{
		return !(lhs < rhs);
	}
};

template <class T, class Alloc>
void swap(ft::deque<T, Alloc> &a, ft::deque<T, Alloc> &b)
{
	a.swap(b);
}
template <class T, class Alloc>
bool operator==(ft::deque<T, Alloc> const &lhs, ft::deque<T, Alloc> const &rhs)
{
	if (lhs.size() != rhs.size())
		return false;
	return equal(lhs.begin(), lhs.end(), rhs.begin());
}
template <class T, class Alloc>
bool operator!=(const ft::deque<Alloc, T> &lhs, const ft::deque<Alloc, T> &rhs)
{
	return !(lhs == rhs);
}
template <class T, class Alloc>
bool operator<(const ft::deque<T, Alloc> &lhs, const ft::deque<T, Alloc> &rhs)
{
	ft::less<T> less;
	return lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end(), less);
}
template <class T, class Alloc>
bool operator<=(const ft::deque<T, Alloc> &lhs, const ft::deque<T, Alloc> &rhs)
{
	return !(rhs < lhs);
}
template <class T, class Alloc>
bool operator>(const ft::deque<T, Alloc> &lhs, const ft::deque<T, Alloc> &rhs)
{
	return rhs < lhs;
}
template <class T, class Alloc>
bool operator>=(const ft::deque<T, Alloc> &lhs, const ft::deque<T, Alloc> &rhs)
{
	return !(lhs < rhs);
}

}  //namespace ft

#endif
