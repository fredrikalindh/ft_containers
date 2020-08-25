#ifndef DEQUE_HPP
#define DEQUE_HPP

namespace ft
{

	template <class T>
	class deque_iterator;

	template <class T>
	class deque
	{
	protected:
		T *arrays_; // array + how full
		size_t size_;
		size_t n_;
		size_t first_;
		size_t last_;

	public:
		typedef size_t size_type;
		typedef T value_type;
		typedef std::ptrdiff_t difference_type;
		typedef value_type &reference;
		typedef const value_type &const_reference;
		typedef value_type *pointer;
		typedef const value_type *const_pointer;
		typedef deque_iterator<T> iterator;
		typedef deque_iterator<const T> const_iterator;
		typedef ft::reverse_iterator<iterator> reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

		explicit deque() : arrays_(0), size_(0), n_(0), {}
		explicit deque(size_type n, const value_type &val = value_type()) : arrays_(new *T[n_]),
																			size_(n),
																			first_(0),
																			last_(n_ - 1)
		{
			// mallocing all the arrays
			for (size_t i = 0; i < n; ++i)
				arrays_[i] = new T[ARRAY_SIZE];
			size_t offset = (n % ARRAY_SIZE) / 2;
			// n < ARRAY_SIZE
			if (first_ == last_)
			{
				first_index = 500 - offset;
				last_index = 500 + offset;
				for (size_t i = first_; i < last_index; ++i)
					arrays_[first_][i] = val;
			}
			else
			{ // n > ARRAY_SIZE
				first_index = ARRAY_SIZE - offset;
				last_index = offset;
				// filling first array from the end
				for (size_t i = first_index; i < ARRAY_SIZE; ++i)
					arrays_[first_][i] = val;
				// filling last array from beginning
				for (size_t i = 0; i < last_index; ++i)
					arrays_[last_][i] = val;
			}
			// filling up all arrays in between
			for (size_t a_num = first_ + 1; a_num < last_; ++a_num)
			{
				for (size_t i = 0; i < ARRAY_SIZE; ++i)
					arrays_[a_num][i] = val;
			}
		}
		template <class InputIterator>
		deque(InputIterator first, InputIterator last) : arrays_(new *T[1]), n_(1),
														 size_(0),
														 first_(0),
														 last_(1),
														 first_index(0),
														 last_index(1)
		{
			while (first != last)
			{
				push_back(*first++);
			}
		}
		deque(const deque &x) : n_(x.n_), arrays_(new *T[n_]), size_(x.size_), first_(x.first_),
								last_(x.last_), first_index(x.first_index), last_index(x.last_index)
		{
			for (size_t i = x.first_; i < x.last_; ++i)
			{
				arrays_[i] = new T[ARRAY_SIZE];
				for (size_t j = 0; j < ARRAY_SIZE; ++j)
					arrays_[i][j] = x.arrays_[i][j];
			}
		}
		~deque()
		{
			for (size_t i = 0; i < n_; ++i)
				delete[] arrays_[i];
			delete[] arrays_;
		}
		deque &operator=(const deque &x)
		{
			deque tmp(x);
			swap(tmp);
			return *this;
		}

		iterator begin() { return iterator(first_, first_index, *this); }
		const_iterator begin() const { return iterator(first_, first_index, *this); }
		iterator end() { return iterator(last_, last_index, *this); }
		const_iterator end() const { return iterator(last_, last_index, *this); }
		reverse_iterator rbegin() { return reverse_iterator(end()); }
		const_reverse_iterator rbegin() const { return reverse_iterator(end()); }
		reverse_iterator rend() { return reverse_iterator(begin()); }
		const_reverse_iterator rend() const { return reverse_iterator(begin()); }

		size_type size() const { return size_; }
		size_type max_size() const { return 4611686018427387903; }
		void resize(size_type n, value_type val = value_type());
		bool empty() const { return !size_; }
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
			return arrays_[n / ARRAY_SIZE][n % ARRAY_SIZE];
		}
		const_reference operator[](size_type n) const
		{
			return arrays_[n / ARRAY_SIZE][n % ARRAY_SIZE];
		}
		reference at(size_type n)
		{
			if (n >= size)
				throw std::out_of_range("deque");
			return arrays_[n / ARRAY_SIZE][n % ARRAY_SIZE];
		}
		const_reference at(size_type n) const
		{
			if (n >= size)
				throw std::out_of_range("deque");
			return arrays_[n / ARRAY_SIZE][n % ARRAY_SIZE];
		}
		reference front()
		{
			return arrays_[first_][first_index];
		}
		const_reference front() const
		{
			return arrays_[first_][first_index];
		}
		reference back()
		{
			return arrays_[last_][last_index - 1];
		}
		const_reference back() const
		{
			return arrays_[last_][last_index - 1];
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
			if (last_ == n_ - 1 && last_index == ARRAY_SIZE)
			{
				T **tmp = new *T[n_ * 2];
				for (size_t i = 0; i < n_; ++i)
				{
					tmp[i + n_ / 2] = arrays_[i];
				}
				n_ += n;
				delete[] arrays_;
				arrays_ = tmp;
			}
			if (last_index == ARRAY_SIZE)
			{
				arrays_[++last_] = new T[ARRAY_SIZE];
				last_index = 0;
			}
			arrays_[last_][last_index++] = val;
		}
		void push_front(const value_type &val)
		{
			if (first_ == 0 && first_index == 0)
			{
				T **tmp = new *T[n_ * 2];
				for (size_t i = 0; i < n_; ++i)
				{
					tmp[i + n_ / 2] = arrays_[i];
				}
				n_ += n_;
				delete[] arrays_;
				arrays_ = tmp;
			}
			if (first_index == 0)
			{
				arrays_[--first_] = new T[ARRAY_SIZE];
				first_index = ARRAY_SIZE;
			}
			arrays_[first_][--first_index] = val;
		}
		void pop_back()
		{
			if (last_ && last_index == 1)
			{
				--last_;
				last_index = ARRAY_SIZE;
			}
			else
				--last_index;
		}
		void pop_front()
		{
			if (first_index == ARRAY_SIZE - 1)
			{
				++first_;
				first_index = 0;
			}
			else
				++first_index;
		}
		iterator insert(iterator position, const value_type &val)
		{
			position = shift(1, position, n_ - position.arr_n < position.arr_n); // SHIFTS FORWARD OR BACK DEPENDING ON WHATS CLOSEST
			*position = val;
		}
		void insert(iterator position, size_type n, const value_type &val)
		{
			position = shift(n, position, n_ - position.arr_n < position.arr_n); // SHIFTS FORWARD OR BACK DEPENDING ON WHATS CLOSEST
			while (n--)
				position++ = val;
		}
		template <class InputIterator>
		void insert(iterator position, InputIterator first, InputIterator last)
		{
			while (first != last)
				position = insert(position, *first);
		}
		iterator erase(iterator position)
		{
		}
		iterator erase(iterator first, iterator last);

	private:
		iterator shift(size_t steps, iterator start, bool back)
		{
		}
	};

	template <class T>
	class deque_iterator
	{
		template <class U>
		friend class deque;

		size_t a_;		 // index for array
		size_t i_;		 // index inside array
		deque const *d_; // pointer to the container

		deque_iterator(size_t a, size_t i, deque const *d) : a_(a), i_(i), d_(d) {}

	public:
		typedef ft::random_access_iterator_tag iterator_category;
		typedef std::ptrdiff_t difference_type;
		typedef T value_type;
		typedef T *pointer;
		typedef T &reference;

		explicit deque_iterator(deque_iterator const &x) : a_(x.a_), i_(x.i_), d_(x.d_) {}
		~deque_iterator() { d_ = 0; }
		deque_iterator &operator=(deque_iterator const &x)
		{
			a_(x.a_);
			i_(x.i_);
			d_(x.d_);
		}
		reference operator*() const { return *i_; }
		pointer operator->() const { return &(operator*()); }
		reference operator[](difference_type n) const {
			return d_.arrays[]}

		deque_iterator
		operator+(difference_type n) const
		{
			deque_iterator tmp(*this);
			if (n > i_)
				tmp.a_ -= n / deque::ARRAY_SIZE;
			tmp.i_ -= n % i_;
			return tmp;
		}
		deque_iterator &operator+=(difference_type n)
		{
			if (n > i_)
				tmp.a_ -= (n - i_) / deque::ARRAY_SIZE;
			i_ -= n % i_;
			return *this;
		}
		deque_iterator operator-(difference_type n) const
		{
			deque_iterator tmp(*this);
			tmp.a_ += n / i_;
			tmp.i_ += n % i_;
			return tmp;
		}
		deque_iterator &operator-=(difference_type n)
		{
			base_ = base_ + n;
			return *this;
		}
		deque_iterator &operator++()
		{
			if (i_ >= deque::ARRAY_SIZE - 1)
			{
				i_ = 0;
				++a_;
			}
			else
			{
				++i_;
			}
			return *this;
		}
		deque_iterator operator++(int)
		{
			deque_iterator tmp(*this);
			if (i_ >= deque::ARRAY_SIZE - 1)
			{
				i_ = 0;
				++a_;
			}
			else
			{
				++i_;
			}
			return tmp;
		}
		deque_iterator &operator--()
		{
			if (i_ == 0)
			{
				i_ = deque::ARRAY_SIZE - 1;
				--a_;
			}
			else
			{
				--i_;
			}
			return *this;
		}
		deque_iterator operator--(int)
		{
			deque_iterator tmp(*this);
			if (i_ == 0)
			{
				i_ = deque::ARRAY_SIZE - 1;
				--a_;
			}
			else
			{
				--i_;
			}
			return tmp;
		}
		template <class it>
		friend bool operator==(const ft::deque_iterator<it> &lhs, const ft::deque_iterator<it> &rhs)
		{
			return lhs.i_ == rhs.i_;
		}
		template <class it>
		friend bool operator!=(const ft::deque_iterator<it> &lhs, const ft::deque_iterator<it> &rhs)
		{
			return lhs.i_ != rhs.i_;
		}
		template <class it>
		friend bool operator<(const ft::deque_iterator<it> &lhs, const ft::deque_iterator<it> &rhs)
		{
			return lhs.i_ > rhs.i_;
		}
		template <class it>
		friend bool operator<=(const ft::deque_iterator<it> &lhs, const ft::deque_iterator<it> &rhs)
		{
			return lhs.i_ >= rhs.i_;
		}
		template <class it>
		friend bool operator>(const ft::deque_iterator<it> &lhs, const ft::deque_iterator<it> &rhs)
		{
			return lhs.i_ < rhs.i_;
		}
		template <class it>
		friend bool operator>=(const ft::deque_iterator<it> &lhs, const ft::deque_iterator<it> &rhs)
		{
			return lhs.i_ <= rhs.i_;
		}
	};

	template <class T>
	bool operator==(const ft::deque<T> &lhs, const ft::deque<T> &rhs);
	template <class T>
	bool operator!=(const ft::deque<T> &lhs, const ft::deque<T> &rhs);
	template <class T>
	bool operator<(const ft::deque<T> &lhs, const ft::deque<T> &rhs);
	template <class T>
	bool operator<=(const ft::deque<T> &lhs, const ft::deque<T> &rhs);
	template <class T>
	bool operator>(const ft::deque<T> &lhs, const ft::deque<T> &rhs);
	template <class T>
	bool operator>=(const ft::deque<T> &lhs, const ft::deque<T> &rhs);

} //namespace ft

#endif
