#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iostream>

namespace ft
{
	template <class T>
	class vector;
}

template <class T>
class ft::vector
{
protected:
	T		*arr;
	size_t	vsize;
	size_t	maxsize;
public:
	class iterator
	{
		T* curr;
		T* last; // ? size - 1
	public:
		iterator();

		virtual iterator& operator++(int){}
		virtual iterator& operator++(){}
		virtual iterator& operator--(int){}
		virtual iterator& operator--(){}
		bool operator==(iterator const &);
		bool operator!=(iterator const &);
	};
	class reverse_iterator : public iterator
	{
		iterator& operator++(int){}
		iterator& operator++(){}
		iterator& operator--(int){}
		iterator& operator--(){}
	};

	using size_type = size_t;
	using value_type = T;
	using iterator = iterator;
	// using iterator = iterator;
	using const_iterator = iterator const;
	// using reverse_iterator = reverse_iterator;
	using const_reverse_iterator = reverse_iterator const;
	using difference_type = ptrdiff_t;


	// explicit vector (const allocator_type& alloc = allocator_type()){}
	// explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type());
	// template <class InputIterator>
	// vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type());
	explicit vector ()vsize(0), maxsize(0){} // maxsize ??
	explicit vector (size_type n, const value_type& val = value_type()):vsize(n){
		arr = new T[n](val);
	}
	template <class InputIterator>
	vector (InputIterator first, InputIterator last){

	}
	vector (const vector& x){

	}
	~vector(){delete []arr;}
	vector& operator= (const vector& x){

	}

	iterator begin();
	const_iterator begin() const;
	iterator end();
	const_iterator end() const;
	reverse_iterator rbegin();
	const_reverse_iterator rbegin() const;
	reverse_iterator rend();
	const_reverse_iterator rend() const;
	size_type size() const;
	size_type max_size() const;// 4611686018427387903
	void resize (size_type n, value_type val = value_type());
	size_type capacity() const;
	bool empty() const;
	void reserve (size_type n);

	reference operator[] (size_type n);
	const_reference operator[] (size_type n) const;
	reference at (size_type n);
	const_reference at (size_type n) const;
	reference front();
	const_reference front() const;
	reference back();
	const_reference back() const;

	template <class InputIterator>
	void assign (InputIterator first, InputIterator last);
	void assign (size_type n, const value_type& val);

	void push_back (const value_type& val);
	void pop_back();

	iterator insert (iterator position, const value_type& val);
	void insert (iterator position, size_type n, const value_type& val);
	template <class InputIterator>
	void insert (iterator position, InputIterator first, InputIterator last);

	iterator erase (iterator position);
	iterator erase (iterator first, iterator last);

	void swap (vector& x);
	void clear();
}
#endif
