#ifndef MAP_HPP
# define MAP_HPP

namespace ft
{
	template<
		class Key,
		class T,
		class Compare = std::less<Key>,
		// class Allocator = std::allocator<std::pair<const Key, T> >
	> class map;
}

template<
	class Key,
	class T,
	class Compare = std::less<Key>,
	// class Allocator = std::allocator<std::pair<const Key, T> >
> class map
{
	struct rb_tree_node
	{
		Color			m_color;
		rb_tree_node*	m_parent;
		rb_tree_node*	m_leftChild;
		rb_tree_node*	m_rightChild;
		int				m_value;
	};
	struct pair
	{
		Key const	first;
		T			second;

		// bool	value_compare(pair)
	};
	rb_tree_node	*d_root;
	size_t			d_size;

public:
	typedef	Key						key_type;
	typedef	T						mapped_type;
	typedef	pair					value_type;
	typedef	size_t					size_type;
	typedef	ptrdiff_t;				difference_type;
	typedef	Compare					key_compare;
	typedef	value_type&				reference;
	typedef	const value_type&		const_reference;
	typedef	value_type*				pointer;
	typedef	const value_type*		const_pointer;
	// typedef	iterator				iterator;
	// typedef	const iterator			const_iterator;
	// typedef	reverse_iterator		reverse_iterator;
	// typedef	const reverse_iterator	const_reverse_iterator;

//######################### CONSTRUCTORS #######################################
	// explicit map (const key_compare& comp = key_compare(),const allocator_type& alloc = allocator_type());
	// template <class InputIterator>
	// map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type());
	// map (const map& x);
	explicit map (const key_compare& comp = key_compare()){

	}
	template <class InputIterator>
	map (InputIterator first, InputIterator last, const key_compare& comp = key_compare()){

	}
	map (const map& x){

	}
	~map(){

	}
	map& operator= (const map& x){
		clear();
		map ret(x);
		d_root = x.d_root;
		d_size = x.d_size;
		ret.d_root = 0;
		return *this;
	}
	mapped_type& operator[] (const key_type& k);
//########################## ITERATORS #######################################
	iterator				begin();
	const_iterator			begin() const;
	iterator				end();
	const_iterator			end() const;
	reverse_iterator		rbegin();
	const_reverse_iterator	rbegin() const;
	reverse_iterator		rend();
	const_reverse_iterator	rend() const;
//########################### CAPACITY #######################################
	bool					empty() const;
	size_type				size() const;
	size_type				max_size() const;
//########################### INSERT #######################################
	pair<iterator,bool>		insert (const value_type& val);
	iterator				insert (iterator position, const value_type& val);
	template <class InputIterator>
	void					insert (InputIterator first, InputIterator last);
//########################### ERASE #######################################
	void					erase (iterator position);
	size_type				erase (const key_type& k);
	void					erase (iterator first, iterator last);
//########################### MODIFIERS #######################################
	void					swap (map& x);
	void					clear();
//########################### OBSERVERS #######################################
	key_compare				key_comp() const;
	value_compare			value_comp() const;
//########################### OPERATIONS #######################################
	iterator				find (const key_type& k);
	const_iterator			find (const key_type& k) const;
	size_type				count (const key_type& k) const;
	iterator				lower_bound (const key_type& k);
	const_iterator			lower_bound (const key_type& k) const;
	iterator				upper_bound (const key_type& k);
	const_iterator			upper_bound (const key_type& k) const;
	pair<const_iterator,const_iterator>	equal_range (const key_type& k) const;
	pair<iterator,iterator>	equal_range (const key_type& k);

private:
};

#endif
