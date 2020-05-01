#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iostream>
# include <stdexcept>

namespace ft
{
	template <class T> class vector;
}

template <class T>
class ft::vector
{
protected:
	T		*arr;
	size_t	d_size;
	size_t	d_capacity;
	size_t	d_multi;
public:
	class reverse_iterator
	{
		T* p;
	public:
		reverse_iterator(T* p):p(p){}
		reverse_iterator(reverse_iterator const &other):p(other.p){}

		reverse_iterator operator++(int){T* old = p; p--; return old;}
		reverse_iterator operator++(){p--; return *this;}
		reverse_iterator operator--(int){T* old = p; p++; return old;}
		reverse_iterator operator--(){p++; return *this;}

		T& operator*(){return *p;}

		bool operator==(reverse_iterator const &other){return p == other.p;}
		bool operator!=(reverse_iterator const &other){return p != other.p;}
	};

	typedef size_t size_type;
	typedef T value_type;
	typedef value_type& reference;
	typedef const value_type& const_reference;
	typedef value_type* pointer;
	typedef const value_type* const_pointer;
	typedef T* iterator;
	typedef const T* const_iterator;
	// typedef reverse_iterator = reverse_iterator;
	typedef const reverse_iterator const_reverse_iterator;
	typedef ptrdiff_t difference_type;


	// explicit vector (const allocator_type& alloc = allocator_type()){}
	// explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type());
	// template <class InputIterator>
	// vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type());
	explicit vector ():arr(0), d_size(0), d_capacity(0), d_multi(0){} // maxsize ??
	explicit vector (size_type n, const value_type& val = value_type()):d_size(n), d_capacity(n), d_multi(n){
		arr = new T[n];
		for (size_type i = 0; i < n; i++)
			arr[i] = val;
	}
	template <class InputIterator>
	vector (InputIterator first, InputIterator last):arr(0), d_size(0), d_capacity(0), d_multi(0){
		for (InputIterator getSize = first; getSize != last; getSize++)
			d_size++;
		arr = new T[d_size];
		int i = 0;
		while (first != last)
		{
			arr[i] = *first;
			i++;
			first++;
		}
		d_capacity = d_multi = d_size;
	}
	vector (const vector& x):arr(0), d_size(x.d_size), d_capacity(x.d_capacity), d_multi(x.d_multi){
		arr = new T[d_capacity];
		for (size_type i = 0; i < d_size; i++)
			arr[i] = x.arr[i];
	}
	~vector(){delete []arr;}
	vector& operator= (const vector& x){
		vector ret(x);

		delete arr;
		arr = ret.arr;
		d_size = ret.d_size;
		d_capacity = ret.d_capacity;
		d_multi = ret.d_multi;
		ret.arr = 0;
		return *this;
	}

	iterator begin() {return arr;}
	const_iterator begin() const {return arr;}
	iterator end() {return &arr[d_size];}
	const_iterator end() const {return &arr[d_size];}
	reverse_iterator rbegin() {return &arr[d_size - 1];}
	const_reverse_iterator rbegin() const {if (d_size > 0){return &arr[d_size - 1];}return 0;}
	reverse_iterator rend(){return arr - 1;}
	const_reverse_iterator rend() const{return arr - 1;}

	size_type size() const {return d_size;}
	size_type max_size() const {return 4611686018427387903;}
	void resize (size_type n, value_type val = value_type());
	size_type capacity() const {return d_capacity;}
	bool empty() const {return d_size == 0 ? true : false;}
	void reserve (size_type n){
		if (n > max_size())
			throw std::length_error("max_size(size_t n) 'n' exceeds maximum supported size"); //allocator<T>::allocate(size_t n) 'n' exceeds maximum supported size
		if (n > d_capacity){
			T* newArr = new T[n];
			for (size_type i = 0; i < d_size; i++)
				newArr[i] = arr[i];
			delete []arr;
			arr = newArr;
			d_capacity = n;
		}
		else if (n == 0){
			clear();
		}
		else if (n > 0 && n < d_capacity){

			for (size_type i = n; i < d_size; i++)
				arr[i] = T();
			d_multi = d_size = d_capacity = n;
		}
	}

	reference operator[] (size_type n){return arr[n];}
	const_reference operator[] (size_type n) const {return arr[n];};
	reference at (size_type n){
		if (n >= d_size)
			throw std::out_of_range("vector");
		return arr[n];
	}
	const_reference at (size_type n) const{
		if (n >= d_size)
			throw std::out_of_range("vector");
		return arr[n];
	}
	reference front(){return arr[0];}
	const_reference front() const{return arr[0];}
	reference back(){return arr[d_size - 1];}
	const_reference back() const{return arr[d_size - 1];}

	template <class InputIterator>
	void assign (InputIterator first, InputIterator last){
		delete []arr;

		d_size = 0;
		for (InputIterator getSize = first; getSize != last; getSize++)
			d_size++;
		d_capacity = d_multi = d_size;
		arr = new T[d_capacity];
		for (size_type i = 0; first != last; i++){
			arr[i] = *first;
			first++;
		}
	}
	void assign (size_type n, const value_type& val){
		delete []arr;

		d_capacity = d_multi = d_size = n;
		arr = new T[d_capacity];
		for (size_type i = 0; i < n; i++)
			arr[i] = val;
	}

	void push_back (const value_type& val){
		if (d_size + 1 < d_capacity)
			arr[d_size++] = val;
		else {
			if (d_capacity == 0)
				d_multi = ++d_capacity;
			else {
				d_capacity += d_multi;
				d_multi *= 2;
			}
			T* newArr = new T[d_capacity];
			for (size_t i = 0; i < d_size; i++)
				newArr[i] = arr[i];
			newArr[d_size] = val;
			delete []arr;
			arr = newArr;
			d_size++;
		}
	}
	void pop_back(){
		if (d_size > 0){
			d_size--;
			arr[d_size] = T();
		}
	}

	iterator insert (iterator position, const value_type& val){
		if (d_size < d_capacity){ // if there's space: just add at position
			T forNext = *position;
			T curr;
			*position = val;
			while (++position < &arr[d_size]){ // and shift everything 1
				curr = *position;
				*position = forNext;
				forNext = curr;
			}
		}
		else { // create new array of double size
			d_capacity += d_multi;
			T *newArr = new T[d_capacity];
			d_multi *= 2;
			size_type i = 0;
			for (iterator start = arr; start != position; start++){ // copy normally until position
				newArr[i] = arr[i];
				i++;
			}
			newArr[i++] = val; // insert value
			while (position < &arr[d_size]) // and copy the rest
				newArr[i++] = *position++;
			delete []arr;
			arr = newArr;
		}
		d_size++;
	}
	void insert (iterator position, size_type n, const value_type& val){
		if (d_size + n < d_capacity){ // if there's space: just add at position
			iterator back = &arr[d_size - 1];
			while (back >= position){ // shift everything after pos n -> right
				back[n] = *back;
				back--;
			}
			for (size_type i = 0; i < n; i++){ // insert val
				*back = val;
				back++;
			}
		}
		else { // create new array of double size
			d_capacity += n;
			d_multi = d_capacity;
			T *newArr = new T[d_capacity];
			size_type i = 0;
			for (iterator start = arr; start != position; start++){ // copy normally until position
				newArr[i] = arr[i];
				i++;
			}
			for (size_type k = 0; k < n; k++) // insert values
				newArr[i++] = val;
			while (position < &arr[d_size]) // and copy the rest
				newArr[i++] = *position++;
			delete []arr;
			arr = newArr;
		}
		d_size += n;
	}
	template <class InputIterator>
	void insert (iterator position, InputIterator first, InputIterator last){
		size_type n = 0;
		for (InputIterator getSize = first; getSize != last; getSize++)
			n++;
		if (d_size + n < d_capacity){ // if there's space: just add at position
			iterator back = &arr[d_size - 1];
			while (back >= position){ // shift everything after pos n -> right
				back[n] = *back;
				back--;
			}
			while (first != last){ // insert val
				*back++ = *first++;
			}
		}
		else { // create new array of double size
			d_capacity += n;
			d_multi = d_capacity;
			T *newArr = new T[d_capacity];
			size_type i = 0;
			for (iterator start = arr; start != position; start++){ // copy normally until position
				newArr[i] = arr[i];
				i++;
			}
			while (first != last){
				newArr[i++] = *first++;
			}// insert values
			while (position < &arr[d_size]) // and copy the rest
				newArr[i++] = *position++;
			delete []arr;
			arr = newArr;
		}
		d_size += n;
	}

	iterator erase (iterator position){
		iterator next = position;
		next++;
		while (next < &arr[d_size]){
			*position = *next;
			position++;
			next++;
		}
		if (d_size)
			d_size--;
	}
	iterator erase (iterator first, iterator last){
		iterator getVal = last;
		while (first != last)
		{
			if (getVal < &arr[d_size]){
				*first++ = *getVal++;
			}else{
				*first++ = T();
			}
			if (d_size)
				d_size--;
		}
	}

	void swap (vector& x){
		vector temp;
		temp.arr = x.arr;
		temp.d_size = x.d_size;
		temp.d_capacity = x.d_capacity;
		x.arr = arr;
		x.d_size = d_size;
		x.d_capacity = d_capacity;
		arr = temp.arr;
		d_size = temp.d_size;
		d_capacity = temp.d_capacity;
		temp.arr = 0;
	}

	void clear(){
		delete []arr;
		arr = d_size = d_capacity = d_multi = 0;
	}
};
#endif
