#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iostream>
# include <stdexcept>

# include "iterator.hpp"

namespace ft
{

template <class T>
class vector
{
protected:
	T		*array_;
	size_t	size_;
	size_t	capacity_;
	size_t	multi_;
public:
	typedef size_t								size_type;
	typedef T 									value_type;
	typedef value_type& 						reference;
	typedef const value_type&					const_reference;
	typedef value_type* 						pointer;
	typedef const value_type*					const_pointer;
	typedef T*									iterator;
	typedef const T*							const_iterator;
	typedef ft::reverse_iterator<iterator>		reverse_iterator;
	typedef ft::reverse_iterator<const T*>		const_reverse_iterator;
	typedef std::ptrdiff_t						difference_type;

	explicit vector ():array_(0), size_(0), capacity_(0), multi_(0){}
	explicit vector (size_type n, const value_type& val = value_type()):size_(n), capacity_(n), multi_(n){
		array_ = new T[n];
		for (size_type i = 0; i < n; i++)
			array_[i] = val;
	}
	// template <class InputIterator>
	// vector (InputIterator first, InputIterator last,
	// typename std::enable_if<!std::is_integral<InputIterator>::value>::type* = 0):array_(0), size_(0), capacity_(0), multi_(0){
	// 	for (InputIterator getSize = first; getSize != last; getSize++)
	// 		size_++;
	// 	array_ = new T[size_];
	// 	int i = 0;
	// 	while (first != last)
	// 	{
	// 		array_[i] = *first;
	// 		i++;
	// 		first++;
	// 	}
	// 	capacity_ = multi_ = size_;
	// }
	template <class InputIterator>
	vector (InputIterator first, InputIterator last,
	typename std::enable_if<!std::is_integral<InputIterator>::value>::type* = 0):array_(0), size_(0), capacity_(0), multi_(0){
		while (first != last)
		{
			push_back(*first);
			first++;
		}
	}
	vector (const vector& x):array_(0), size_(x.size_), capacity_(x.capacity_), multi_(x.multi_){
		array_ = new T[capacity_];
		for (size_type i = 0; i < size_; i++)
			array_[i] = x.array_[i];
	}
	~vector(){
		delete []array_;
		array_ = 0;
		size_ = capacity_ = multi_ = 0;
	}
	vector& operator= (const vector& x){
		vector ret(x);
		swap(ret);
		return *this;
	}

	iterator				begin() {return array_;}
	const_iterator			begin() const {return array_;}
	iterator				end() {return &array_[size_];}
	const_iterator			end() const {return &array_[size_];}
	reverse_iterator		rbegin() {return reverse_iterator(end());}
	const_reverse_iterator	rbegin() const {return reverse_iterator(end());}
	reverse_iterator		rend(){return reverse_iterator(begin());}
	const_reverse_iterator	rend() const{return reverse_iterator(begin());}

	size_type	size() const {return size_;}
	size_type	max_size() const {return 4611686018427387903;}
	void		resize (size_type n, value_type val = value_type()){
		if (n > max_size())
			throw std::length_error("max_size(size_t n) 'n' exceeds maximum supported size"); //allocator<T>::allocate(size_t n) 'n' exceeds maximum supported size
		if (n > capacity_){
			T* newArr = new T[n]; // SET MULTI?
			size_type i;
			for (i = 0; i < size_; i++)
				newArr[i] = array_[i];
			for ( ; i < n; i++)
				newArr[i] = val;
			delete []array_;
			array_ = newArr;
		}
		else if (n == 0){
			clear();
		}
		multi_ = size_ = capacity_ = n;
	}
	size_type capacity() const {return capacity_;}
	bool empty() const {return !size_;}
	void reserve (size_type n){
		if (n > capacity_){
			if (n > max_size())
				throw std::length_error("reserve(size_t n) 'n' exceeds maximum supported size");
			T* newArr = new T[n];
			for (size_type i = 0; i < size_; i++)
				newArr[i] = array_[i];
			delete []array_;
			array_ = newArr;
			capacity_ = multi_ = n; // MULTI OR NOT ?
		}
	}
	inline reference		operator[] (size_type n) {return array_[n];}
	inline const_reference	operator[] (size_type n) const {return array_[n];}
	inline reference		at (size_type n) {
		if (n >= size_)
			throw std::out_of_range("vector");
		return array_[n];
	}
	inline const_reference	at (size_type n) const {
		if (n >= size_)
			throw std::out_of_range("vector");
		return array_[n];
	}
	inline reference 		front(){return array_[0];}
	inline const_reference	front() const{return array_[0];}
	inline reference		back(){return array_[size_ - 1];}
	inline const_reference	back() const{return array_[size_ - 1];}

	template <class InputIterator>
	void assign (InputIterator first, InputIterator last){
		vector tmp(first, last);
		swap(tmp);
	}
	void assign (size_type n, const value_type& val){
		vector tmp(n, val);
		swap(tmp);
	}
	void push_back (const value_type& val){
		if (size_ < capacity_)
			array_[size_++] = val;
		else {
			if (!multi_)
				capacity_ = ++multi_;
			else {
				capacity_ += multi_;
				multi_ *= 2;
			}
			T* newArr = new T[capacity_];
			for (size_t i = 0; i < size_; i++)
				newArr[i] = array_[i];
			newArr[size_] = val;
			delete []array_;
			array_ = newArr;
			size_++;
		}
	}
	void pop_back(){
		if (size_ > 0){
			size_--;
			// array_[size_] = T();
		}
	}
	iterator insert (iterator position, const value_type& val){
		iterator ret(position);
		if (size_ < capacity_){ // if there's space: just add at position
			T forNext = *position;
			T curr;
			*position = val;
			while (++position < &array_[size_]){ // and shift everything 1
				curr = *position;
				*position = forNext;
				forNext = curr;
			}
		}
		else { // create new array_ay of double size
			capacity_ += multi_;
			multi_ *= 2;
			T *newArr = new T[capacity_];
			size_type i = 0;
			for (iterator start = array_; start != position; start++){ // copy normally until position
				newArr[i] = array_[i];
				i++;
			}
			ret = &newArr[i];
			newArr[i++] = val; // insert value
			while (position < &array_[size_]) // and copy the rest
				newArr[i++] = *position++;
			delete []array_;
			array_ = newArr;
		}
		size_++;
		return ret;
	}
	void insert (iterator position, size_type n, const value_type& val){
		if (size_ + n < capacity_){ // if there's space: just add at position
			iterator back = &array_[size_ - 1];
			while (back >= position){ // shift everything after pos n -> right
				back[n] = *back;
				back--;
			}
			for (size_type i = 0; i < n; i++){ // insert val
				*back = val;
				back++;
			}
		}
		else {
			capacity_ += n;
			multi_ = capacity_;
			T *newArr = new T[capacity_];
			size_type i = 0;
			for (iterator start = array_; start != position; start++){ // copy normally until position
				newArr[i] = array_[i];
				i++;
			}
			for (size_type k = 0; k < n; k++) // insert values
				newArr[i++] = val;
			while (position < &array_[size_]) // and copy the rest
				newArr[i++] = *position++;
			delete []array_;
			array_ = newArr;
		}
		size_ += n;
	}
	template <class InputIterator>
	void insert (iterator position, InputIterator first, InputIterator last,
	typename std::enable_if<!std::is_integral<InputIterator>::value>::type* = 0){ // OWN ENABLE_IF ?
		for ( ; first != last; first++)
			position = insert(position, *first);
	}
	// template <class InputIterator>
	// void insert (iterator position, InputIterator first, InputIterator last,
	// typename std::enable_if<!std::is_integral<InputIterator>::value>::type* = 0){ // OWN ENABLE_IF ?
	// 	size_type n = 0;
	// 	for (InputIterator getSize = first; getSize != last; getSize++)
	// 		n++;
	// 	if (size_ + n < capacity_){ // if there's space: just add at position
	// 		iterator back = &array_[size_ - 1];
	// 		while (back >= position){ // shift everything after pos n -> right
	// 			back[n] = *back;
	// 			back--;
	// 		}
	// 		while (first != last){ // insert val
	// 			*back++ = *first++;
	// 		}
	// 	}
	// 	else {
	// 		capacity_ += n;
	// 		multi_ = capacity_;
	// 		T *newArr = new T[capacity_];
	// 		size_type i = 0;
	// 		for (iterator start = array_; start != position; start++){ // copy normally until position
	// 			newArr[i] = array_[i];
	// 			i++;
	// 		}
	// 		while (first != last){
	// 			newArr[i++] = *first++;
	// 		}// insert values
	// 		while (position < &array_[size_]) // and copy the rest
	// 			newArr[i++] = *position++;
	// 		delete []array_;
	// 		array_ = newArr;
	// 	}
	// 	size_ += n;
	// }

	iterator erase (iterator position){
		iterator ret(position);
		iterator next(position + 1);
		while (next < &array_[size_]){
			*position = *next;
			position++;
			next++;
		}
		if (size_)
			size_--;
		return ret;
	}
	iterator erase (iterator first, iterator last){
		iterator ret(first);
		size_type minus = 0;
		iterator getVal(last);
		while (getVal < &array_[size_])
		{
			*first++ = *getVal++;
			if (first <= last)
				minus++;
		}
		size_ -= minus;
		return ret;
	}
	void swap (vector& x){
		char buffer[sizeof(vector)];
		memcpy(buffer, &x, sizeof(vector));
		memcpy(reinterpret_cast<char *>(&x), this, sizeof(vector));
		memcpy(reinterpret_cast<char *>(this), buffer, sizeof(vector));
	}

	void clear(){
		delete []array_;
		array_ = 0;
		size_ = capacity_ = multi_ = 0;
	}
};

} //namespace ft

template <class T>
void swap(ft::vector<T> &a, ft::vector<T> &b) {
	a.swap(b);
}

template <class T>
bool operator== (const ft::vector<T>& lhs, const ft::vector<T>& rhs){
	if (lhs.size() != rhs.size())
		return false;
	typename ft::vector<T>::const_iterator l_it = lhs.begin();// #########################   WHY TYPENAME?
	typename ft::vector<T>::const_iterator r_it = rhs.begin();
	while (l_it != lhs.end() && r_it != rhs.end()) {
		if (*l_it != *r_it){
			std::cout << *l_it << " != " << *r_it << '\n';
			return false;
		}
		l_it++;
		r_it++;
	}
	return true;
}
template <class T>
bool operator!= (const ft::vector<T>& lhs, const ft::vector<T>& rhs){
	return !(lhs == rhs);
}
template <class T>
bool operator<  (const ft::vector<T>& lhs, const ft::vector<T>& rhs){
	typename ft::vector<T>::const_iterator l_it = lhs.begin();// #########################   WHY TYPENAME?
	typename ft::vector<T>::const_iterator r_it = rhs.begin();
	while (l_it != lhs.end() && r_it != rhs.end()) {
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
bool operator<= (const ft::vector<T>& lhs, const ft::vector<T>& rhs){
	return !(rhs < lhs);
}
template <class T>
bool operator>  (const ft::vector<T>& lhs, const ft::vector<T>& rhs){
	return rhs < lhs;
}
template <class T>
bool operator>= (const ft::vector<T>& lhs, const ft::vector<T>& rhs){
	return !(lhs < rhs);
}

#endif
