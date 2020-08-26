#ifndef DEQUE_HPP
#define DEQUE_HPP

namespace ft
{
	template <class T>
	class deque_iterator;

	/*
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
		template <class U>
		friend class deque;
		// template <class U>
		friend class deque_iterator<T>;

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
		deque_array(deque_array const &x, int new_size) : capacity_(new_size),
														  array_(new T[capacity_]),
														  size_(x.size_),
														  index_first((new_size - x.size_) / 2)
		{
			for (int i = index_first; i < size_ + index_first; ++i)
				array_[i] = x.array_[i];
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
			while (index_first == 0)
			{
				int new_capacity = (capacity_ == 0) ? 2 : capacity_ * 2;
				deque_array tmp(*this, new_capacity); // JUST CHANGE TO ALWAYS MAKE SURE IT'S NEVER 0 ?
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
			for (int i = position; i + 1 < index_first + size_; ++i)
				array_[i] = array_[i + 1];
			--size_;
		}
		void erase(int first, int last)
		{
			int dif = last - first;
			for (int i = first; i + dif < index_first + size_; ++i)
				array_[i] = array_[i + dif];
			size_ -= dif;
		}
		void insert(int position, const value_type &val)
		{
			insert(position, 1, val);
		}
		void insert(int position, int n, const value_type &val)
		{
			int i = std::min(size_ + n, capacity_);
			for (; i >= position + n; --i)
				array_[i] = array_[i - n];
			while (i >= position)
				array_[i--] = val;
			size_ += n;
		}
	};

	/*
	* DEQUE - double ended queue with a structure similar to a vector 
	* but optimised for pushing and popping both ends. Unlike a vector
	* it therefore doesn't guarantee that the data will be stored 
	* continously. 
	*  [ ]
	*  [x] ---> [ ][ ][ ][x][x][x]
	*  [x] ---> [ ][x][x][x][x][x]
	*  [x] ---> [x][x][x][x][ ][ ]
	*  [ ]
	*/
	template <class T>
	class deque
	{
	protected:
		static const size_t ARRAY_SIZE = 1024;

		deque_array<deque_array<T> > arrays_;

	public:
		typedef size_t size_type;
		typedef T value_type;
		typedef std::ptrdiff_t difference_type;
		typedef value_type &reference;
		typedef const value_type &const_reference;
		typedef value_type *pointer;
		typedef const value_type *const_pointer;
		typedef deque_iterator<T> iterator;
		typedef deque_iterator<T> const_iterator; // #########################################
		typedef ft::reverse_iterator<iterator> reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

		explicit deque() {}
		explicit deque(size_type n, const value_type &val = value_type()) : arrays_(ARRAY_SIZE % n + 1, 0)
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
		iterator end() { return iterator(arrays_.size_ - 1, arrays_.back().size_, &arrays_); }
		const_iterator end() const { return const_iterator(arrays_.size_ - 1, arrays_.back().size_, &arrays_); }
		reverse_iterator rbegin() { return reverse_iterator(end()); }
		const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
		reverse_iterator rend() { return reverse_iterator(begin()); }
		const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }

		size_type size() const
		{
			size_type size = 0;
			for (int i = arrays_.index_first; i < arrays_.index_first + arrays_.size_; ++i)
				size += arrays_[i].size_;
			return size;
		}
		size_type max_size() const { return 4611686018427387903; }
		void resize(size_type n, value_type val = value_type())
		{
			size_type sz = size();
			if (n < sz)
				erase(begin() + n, end());
			else if (n > sz)
				insert(end(), n - sz, val);
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
		}
		void pop_front()
		{
			arrays_.front().pop_front();
		}
		iterator insert(iterator position, const value_type &val)
		{
			insert(position, 1, val);
			return position;
		}
		void insert(iterator position, size_type n, const value_type &val)
		{
			if (arrays_[position.i_out].size_ >= arrays_[position.i_out].capacity_)
			{
				deque_array<T> tmp(arrays_[position.i_out]);
				arrays_[position.i_out].erase(position.i_in + 1, arrays_[position.i_out].size_);
				tmp.erase(0, position.i_in + 1);
				arrays_.insert(position.i_out, tmp);
			}
			arrays_[position.i_out].insert(position.i_in, n, val);
		}
		template <class InputIterator>
		void insert(iterator position, InputIterator first, InputIterator last, typename std::enable_if<!std::is_integral<InputIterator>::value>::type * = 0)
		{
			while (first != last)
				position = insert(position, *first++);
		}
		iterator erase(iterator position)
		{
			arrays_[position.i_out].erase(position.i_in);
			return position;
		}
		iterator erase(iterator first, iterator last)
		{
			if (first.i_out == last.i_out)
			{
				arrays_[first.i_out].erase(first.i_in, last.i_in);
			}
			else
			{
				arrays_[first.i_out].erase(first.i_in, arrays_[first.i_out].size_);
				arrays_[last.i_out].erase(0, last.i_in);
				arrays_.erase(first.i_out + 1, last.i_out);
			}
			return last; /// DON'T REMEMBER
		}

	private:
		pointer get_position(int n) const
		{
			for (int i = arrays_.index_first; i < arrays_.index_first + arrays_.size_; ++i)
			{
				if (n < arrays_[i].size_)
					return &arrays_[i][n];
				n -= arrays_[i].size_;
			}
			return nullptr;
		}
	};

	/*
	* DEQUE_ITERATOR: a double layered array_, index for the outer array and 
	* index for the inner. It will try to do all operations on the inner index
	* if fail it will go out one layer
	*/
	template <class T>
	class deque_iterator
	{
		friend class deque<T>;

		int i_out;								   // index for array
		int i_in;								   // index inside array
		const deque_array<deque_array<T> > *array_; // pointer to the container

	public:
		typedef ft::random_access_iterator_tag iterator_category;
		typedef std::ptrdiff_t difference_type;
		typedef T value_type;
		typedef T *pointer;
		typedef T &reference;

		deque_iterator() : i_out(0),
						   i_in(0),
						   array_(0) {}
		deque_iterator(int out, int in, const deque_array<deque_array<T> > *d) : i_out(out),
																				i_in(in),
																				array_(d) {}
		deque_iterator(deque_iterator const &x) : i_out(x.i_out),
												  i_in(x.i_in),
												  array_(x.array_) {}
		~deque_iterator() {}
		deque_iterator &operator=(deque_iterator const &x)
		{
			deque_iterator tmp(x);
			swap(tmp);
			return *this;
		}
		reference operator*() const { return (*array_)[i_out][i_in]; }
		pointer operator->() const { return &(operator*()); }
		reference operator[](difference_type n) const
		{
			for (int i = array_->i_out; i < array_->index_first + array_->size_; ++i)
			{
				if (n < (*array_)[i].size_)
					return (*array_)[i][n];
				n -= (*array_)[i].size_;
			}
		}
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
				n -= i_in + (*array_)[i_out++].size_;
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
				if (i_in - n > 0)
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
			if (i_in == (*array_)[i_out].size_)
			{
				i_in = 0;
				++i_out;
			}
			else
			{
				++i_in;
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
			else
			{
				--i_in;
			}
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
		template <class it>
		friend bool operator==(const ft::deque_iterator<it> &lhs, const ft::deque_iterator<it> &rhs)
		{
			return lhs.i_out == rhs.i_out && lhs.i_in == rhs.i_in && lhs.array_ == rhs.array_;
		}
		template <class it>
		friend bool operator!=(const ft::deque_iterator<it> &lhs, const ft::deque_iterator<it> &rhs)
		{
			return !(lhs == rhs);
		}
		template <class it>
		friend bool operator<(const ft::deque_iterator<it> &lhs, const ft::deque_iterator<it> &rhs)
		{
			return lhs.i_out < rhs.i_out || lhs.i_in < rhs.i_in || lhs.array_ < rhs.array_;
		}
		template <class it>
		friend bool operator<=(const ft::deque_iterator<it> &lhs, const ft::deque_iterator<it> &rhs)
		{
			return !(lhs < rhs);
		}
		template <class it>
		friend bool operator>(const ft::deque_iterator<it> &lhs, const ft::deque_iterator<it> &rhs)
		{
			return rhs < lhs;
		}
		template <class it>
		friend bool operator>=(const ft::deque_iterator<it> &lhs, const ft::deque_iterator<it> &rhs)
		{
			return !(rhs < lhs);
		}
	};
	template <class T>
	void swap(ft::deque<T> &a, ft::deque<T> &b)
	{
		a.swap(b);
	}
	template <class T>
	bool operator==(deque<T> const &lhs, deque<T> const &rhs)
	{
		if (lhs.size() != rhs.size())
			return false;
		typename ft::deque<T>::const_iterator l_it = lhs.begin();
		typename ft::deque<T>::const_iterator r_it = rhs.begin();
		while (l_it != lhs.end() && r_it != rhs.end())
		{
			if (*l_it != *r_it)
				return false;
			l_it++;
			r_it++;
		}
		return true;
	}
	template <class T>
	bool operator!=(const ft::deque<T> &lhs, const ft::deque<T> &rhs)
	{
		return !(lhs == rhs);
	}
	template <class T>
	bool operator<(const ft::deque<T> &lhs, const ft::deque<T> &rhs)
	{
		typename ft::deque<T>::const_iterator l_it = lhs.begin();
		typename ft::deque<T>::const_iterator r_it = rhs.begin();
		while (l_it != lhs.end() && r_it != rhs.end())
		{
			if (*l_it < *r_it)
				return true;
			if (*l_it > *r_it)
				return false;
			l_it++;
			r_it++;
		}
		return true; // ?????
	}
	template <class T>
	bool operator<=(const ft::deque<T> &lhs, const ft::deque<T> &rhs)
	{
		return !(rhs < lhs);
	}
	template <class T>
	bool operator>(const ft::deque<T> &lhs, const ft::deque<T> &rhs)
	{
		return rhs < lhs;
	}
	template <class T>
	bool operator>=(const ft::deque<T> &lhs, const ft::deque<T> &rhs)
	{
		return !(lhs < rhs);
	}

} //namespace ft

#endif
