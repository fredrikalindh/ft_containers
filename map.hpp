#ifndef MAP_HPP
# define MAP_HPP

namespace ft
{

template<
	class Key,
	class T,
	class Compare = std::less<Key>,
	// class Allocator = std::allocator<std::pair<const Key, T> >
> class map
{
	struct pair
	{
		Key const	first;
		T			second;

		pair(Key key, T val = T()):first(key), second(val){}
		// bool	value_compare(pair)
	};
	struct rb_tree_node
	{

		pair<Key, T>		m_pair;
		rb_tree_node*		m_parent;
		rb_tree_node*		m_leftChild;
		rb_tree_node*		m_rightChild;
		bool				isRed;
		bool				isLeftSide;

		rb_tree_node(pair<Key, T> pair, rb_tree_node* parent = 0, bool side = false):
			m_pair(pair),
			m_parent(parent),
			m_leftChild(0),
			m_rightChild(0),
			isRed(true),
			isLeftSide(side){}
		rb_tree_node(rb_tree_node const &x):
			m_pair(x.m_pair),
			m_parent(0), // SHOULD I REALLY COPY POINTERS HERE
			m_leftChild(0),
			m_rightChild(0),
			isRed(x.isRed),
			isLeftSide(x.isLeftSide){}


	};
	rb_tree_node	*d_root;
	size_t			d_size;
	key_compare		compare;

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
	typedef	rb_tree_node			Node;

//######################### CONSTRUCTORS #######################################
	explicit map (const key_compare& comp = key_compare()):d_root(0), d_size(0), compare(comp){}
	template <class InputIterator>
	map (InputIterator first, InputIterator last, const key_compare& comp = key_compare()):
		d_root(0),
		d_size(0),
		compare(comp){}{
		while (first != last)
			insert(*first);
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
	void					swap (map& x){
		char buffer[sizeof(map)];
		memcpy(buffer, &x, sizeof(map));
		memcpy(reinterpret_cast<char *>(&x), this, sizeof(map));
		memcpy(reinterpret_cast<char *>(this), &x, sizeof(map));
	}
	void					clear(){
		~map();
	}
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
	void	add_node(pair<Key, T> pair){ // BETTER RECURSIVELY?
		if (!d_root){
			d_root = new Node(pair);
		}
		else{
			Node *trav = d_root;
			while (1) {
				if (comp(pair, trav->m_pair) < 0){
					if (trav->m_leftChild)
						trav = trav->m_leftChild;
					else{
						trav->m_leftChild = new Node(pair, trav, true);
						return (checkBalance(trav->m_leftChild));
					}
				}
				else {
					if (trav->m_rightChild)
						trav = trav->m_rightChild;
					else{
						trav->m_rightChild = new Node(pair, trav, false);
						return (checkBalance(trav->m_rightChild));
					}
				}
			}
		}
	}
	bool	checkBalance(Node *inserted){
		if (d_root.isRed){
			d_root.isRed = black;
		}
		// bool PrevWasRed = inserted.isRed;
		for (Node *trav = inserted; trav.parent != 0; trav = trav->parent){
			if (trav.isRed && trav.parent.isRed)
				trav.isRed = false;
		}
	}
};

} //namespace ft

#endif
