#ifndef MAP_HPP
# define MAP_HPP

namespace ft
{
	template <class Key, class T>
	struct pair
	{
		Key const	first;
		T			second;
		pair(Key first, T second = T()):first(first), second(second){}
		// bool	value_compare(pair)
	};
template <
	class Key,
	class T,
	class Compare = std::less<Key> >
class map
{
	struct Node
	{
		ft::pair<Key, T>	pair_;
		Node*				parent_;
		Node*				left_;
		Node*				right_;
		bool				isRed_, isLeft;
		// ‎enum color_type{red=false,black=true};

		Node(ft::pair<Key, T> pair, Node* parent_ = 0, bool left = true, bool red = true):
			pair_(pair),
			parent_(parent_),
			left_(0),
			right_(0),
			isRed_(red),
			isLeft(left){}
		Node(Node const &x, Node *parent = 0):
			pair_(x.pair_),
			parent_(parent),
			left_(0),
			right_(0),
			isRed_(x.isRed_),
			isLeft(x.isLeft){}
	};
	bool	isRed(Node *n){
		if (n == 0)
			return false;
		return n->isRed_;
	}
public:
	Node*			root_;
	size_t			size_;
	Compare			comp;
public:
// ############################## ITERATOR #####################################
	class bidirectional_iterator
	{
		Node*	node_;
		map*	container_;
	public:
		typedef ft::bidirectional_iterator_tag	iterator_category; // CHANGE TO FT AND MAKE OWN DISTANCE + ADVANCE
		typedef	ft::pair<Key, T>				value_type;
		typedef std::ptrdiff_t					difference_type;
		typedef value_type*						pointer;
		typedef value_type&						reference;

		explicit bidirectional_iterator(Node *node = 0):node_(node), container_(0){}
		bidirectional_iterator(Node *node, map *container):node_(node), container_(container){}
		bidirectional_iterator(bidirectional_iterator const &cpy):node_(cpy.node_), container_(cpy.container_){}
		bidirectional_iterator& operator=(bidirectional_iterator const &cpy){
			bidirectional_iterator tmp(cpy);
			swap(tmp);
			return *this;
		}
		bidirectional_iterator& operator++(void){
			if (node_ == 0){
				node_ = container_->lowest().base();
			}else if (node_->isLeft && !node_->right_){
				node_ = node_->parent_;
			}else if (!node_->right_){
				Key store(node_->pair_.first);
				node_ = node_->parent_;
				while (node_ && !(container_->comp(store, node_->pair_.first)))
					node_ = node_->parent_;
			}else {
				node_ = node_->right_;
				while (node_ && node_->left_)
					node_ = node_->left_;
			}
			return *this;
		}
		bidirectional_iterator operator++(int){
			bidirectional_iterator old(*this);
			this->operator++();
			return old;
		}
		bidirectional_iterator& operator--(void){
			if (node_ == 0)
				node_ = container_->upper_bound().base();
			else if (!node_->isLeft && !node_->left_)
				node_ = node_->parent_;
			else if (!node_->left_){
				Key store(node_->pair_.first);
				node_ = node_->parent_;
				while (node_ && container_->comp(store, node_->pair_.first))
					node_ = node_->parent_;
			}else {
				node_ = node_->left_;
				while (node_ && node_->right_)
					node_ = node_->right_;
			}
			return *this;
		}
		bidirectional_iterator operator--(int){
			bidirectional_iterator old(*this);
			this->operator--();
			return old;
		}
		inline Node			*base(){return node_;}
		inline reference	operator*(void) {return node_->pair_;}
		inline pointer		operator->(void) {return &(node_->pair_);}
		inline reference	operator*(void) const {return node_->pair_;}
		inline pointer		operator->(void) const {return &(node_->pair_);}
		inline bool			operator!=(bidirectional_iterator const &other) const {return node_ != other.node_;}
		inline bool			operator==(bidirectional_iterator const &other) const {return node_ == other.node_;}

		void swap(bidirectional_iterator &other){  // PRIVATE?
			char buffer[sizeof(bidirectional_iterator)];
			memcpy(buffer, &other, sizeof(bidirectional_iterator));
			memcpy(reinterpret_cast<char *>(&other), this,   sizeof(bidirectional_iterator));
			memcpy(reinterpret_cast<char *>(this),   buffer, sizeof(bidirectional_iterator));
		}
	};
	class const_bidirectional_iterator
	{
		Node*		node_;
		const map*	container_;
	public:
		typedef ft::bidirectional_iterator_tag	iterator_category; // CHANGE TO FT AND MAKE OWN DISTANCE + ADVANCE
		typedef	const ft::pair<Key, T>			value_type;
		typedef std::ptrdiff_t					difference_type;
		typedef const value_type*				pointer;
		typedef const value_type&				reference;

		explicit const_bidirectional_iterator(Node *node = 0):node_(node), container_(0){}
		const_bidirectional_iterator(Node *node, map *container):node_(node), container_(container){}
		const_bidirectional_iterator(bidirectional_iterator const &cpy):node_(cpy.node_), container_(cpy.container_){}
		const_bidirectional_iterator& operator=(bidirectional_iterator const &cpy){
			const_bidirectional_iterator tmp(cpy);
			swap(tmp);
			return *this;
		}
		const_bidirectional_iterator& operator++(void){
			if (node_ == 0)
				node_ = container_->lowest().base();
			else if (!node_->right_ && node_->isLeft)
				node_ = node_->parent_;
			else if (!node_->right_){
				while (node_ && !node_->right_){
					node_ = node_->parent_;
				}
			}else {
				node_ = node_->right_;
				while (node_ && node_->left_)
					node_ = node_->left_;
			}
			return *this;
		}
		const_bidirectional_iterator operator++(int){
			const_bidirectional_iterator old(*this);
			this->operator++();
			return old;
		}
		const_bidirectional_iterator& operator--(void){
			if (node_ == 0)
				node_ = container_->upper_bound().base();
			else if (!node_->isLeft && !node_->left_)
				node_ = node_->parent_;
			else if (!node_->left_){
				Key store(node_->pair_.first);
				node_ = node_->parent_;
				while (node_ && container_->comp(store, node_->pair_.first))
					node_ = node_->parent_;
			}else {
				node_ = node_->left_;
				while (node_ && node_->right_)
					node_ = node_->right_;
			}
			return *this;
		}
		const_bidirectional_iterator operator--(int){
			const_bidirectional_iterator old(*this);
			this->operator--();
			return old;
		}
		inline Node			*base(){return node_;}
		inline reference	operator*(void) const {return node_->pair_;}
		inline pointer		operator->(void) const {return &(node_->pair_);}
		inline bool			operator!=(const_bidirectional_iterator const &other) const {return node_ != other.node_;}
		inline bool			operator==(const_bidirectional_iterator const &other) const {return node_ == other.node_;}

		void swap(const_bidirectional_iterator &other){  // PRIVATE?
			char buffer[sizeof(const_bidirectional_iterator)];
			memcpy(buffer, &other, sizeof(const_bidirectional_iterator));
			memcpy(reinterpret_cast<char *>(&other), this,   sizeof(const_bidirectional_iterator));
			memcpy(reinterpret_cast<char *>(this),   buffer, sizeof(const_bidirectional_iterator));
		}
	};
// ########################### TYPEDEFS ########################################
	typedef	Key										key_type;
	typedef	T										mapped_type;
	typedef ft::pair<Key, T>						value_type;
	typedef	size_t									size_type;
	typedef	ptrdiff_t								difference_type;
	typedef	Compare									key_compare;
	typedef	value_type&								reference;
	typedef	const value_type&						const_reference;
	typedef	value_type*								pointer;
	typedef	const value_type*						const_pointer;
	typedef	bidirectional_iterator					iterator;
	typedef	const_bidirectional_iterator			const_iterator;
	typedef	ft::reverse_iterator<iterator>			reverse_iterator;
	typedef	ft::reverse_iterator<const_iterator>	const_reverse_iterator;
	class value_compare : public std::binary_function<value_type, value_type, bool> // REMOVE INHERITANCE ?
	{
	public:
		bool operator()(const value_type& x, const value_type& y) const
			{return (comp(x.first, y.first)); }
	protected:
		value_compare(key_compare pr):comp(pr) {}
		key_compare comp;
	};
//######################### CONSTRUCTORS #######################################
	explicit map (const key_compare& comp = key_compare()):root_(0), size_(0), comp(comp){}
	template <class InputIterator>
	map (InputIterator first, InputIterator last, const key_compare& comp = key_compare()):
	root_(0),size_(0),comp(comp) {
		while (first != last) {
			if (!find(first->first)) //STUPID SOLUTION
				add(*first++);
		}
	} /* Maybe contrary to intuition, the map constructor only enters NEW keys.*/
	map (const map& x):root_(0), size_(x.size_), comp(x.comp){
		if (size_ > 0){
			root_ = new Node(*x.root_);
			copyTree(root_, x.root_);
		}
	}
	~map(){
		deleteTree(root_);
		root_ = 0;
		size_ = 0;
	}
	map& operator= (const map& x){
		map ret(x);
		swap(ret);
		return *this;
	}
	mapped_type& operator[] (const key_type& k){ // find node or parent to where it should be?
		add(k);
		return find(root_, k)->pair_.second;
	}
//########################## ITERATORS #######################################
	iterator				begin() {return lowest();}
	const_iterator			begin() const {return lowest();}
	iterator				end() { return iterator(0, this); }
	const_iterator			end() const { return iterator(0, this); }
	reverse_iterator		rbegin() { return reverse_iterator(uppest()); }
	const_reverse_iterator	rbegin() const { return reverse_iterator(uppest()); }
	reverse_iterator		rend() { return reverse_iterator(end()); }
	const_reverse_iterator	rend() const { return reverse_iterator(end()); }
//########################### CAPACITY #######################################
	bool					empty() const {return !size_;}
	size_type				size() const {return size_;}
	size_type				max_size() const {return 576460752303423487;}
//########################### INSERT #######################################
	ft::pair<iterator,bool>	insert (const value_type& val){
		add(val);
	}
	iterator				insert (iterator position, const value_type& val){
		add(val);
		position = iterator(find(val), this);
		return	position;
	}
	template <class InputIterator>
	void					insert (InputIterator first, InputIterator last){
		for ( ; first != last; first++)
			add(*first);
	}
//########################### ERASE #######################################
	void					erase (iterator position){
		Node *node(position.base());
		if (!size_)
			clear();
		if (!node->right_ && !node_->left_){
			if (node->isLeft)
				node->parent_->left_ = 0;
			else
				node->parent_->right_ = 0;
		}
		else if (node->right_){
			while (node->right_){
				swap(node->pair_, node->right_->pair);
				node = node->right_;
			}
			node->parent_->right_ = 0;
			delete node;
		}

	}
	size_type				erase (const key_type& k){
		Node *toErase;
		if (!(toErase = find(k)))
			return false;
		erase(iterator(toErase, this));
		return true;
	}
	void					erase (iterator first, iterator last){
		for ( ; first != last; first++)
			erase(first);
	}
//########################### MODIFIERS #######################################
	void					swap (map& x) {
		char buffer[sizeof(map)];
		memcpy(buffer, &x, sizeof(map));
		memcpy(reinterpret_cast<char *>(&x), this, sizeof(map));
		memcpy(reinterpret_cast<char *>(this), buffer, sizeof(map));
	}
	void					clear(){
		deleteTree(root_);
		root_ = 0;
		size_ = 0;
	}
//########################### OBSERVERS #######################################
	key_compare				key_comp() const {
		return comp;
	}
	value_compare			value_comp() const {
		return value_comp(comp);
	}
//########################### OPERATIONS #######################################
	iterator				find (const key_type& k) {
		return iterator(find(root_, k), this);
	}
	const_iterator			find (const key_type& k) const {
		return const_iterator(find(root_, k), this);
	}
	size_type				count (const key_type& k) const {
		if (find(root_, k))
			return 1;
		return 0;
	}
	iterator				lower_bound (const key_type& k) {
		return iterator(find(root_, k), this);
	}
	const_iterator			lower_bound (const key_type& k) const {
		return const_iterator(find(root_, k), this);
	}
	iterator				upper_bound (const key_type& k) {
		return iterator(find(root_, k), this);
	}
	const_iterator			upper_bound (const key_type& k) const {
		return const_iterator(find(root_, k), this);
	}

	ft::pair<const_iterator,const_iterator>	equal_range (const key_type& k) const{
		 return ft::pair<const_iterator,const_iterator>(lower_bound(k), upper_bound(k));
	}
	ft::pair<iterator,iterator>				equal_range (const key_type& k){
		 return ft::pair<iterator,iterator>(lower_bound(k), upper_bound(k));;
	}


//#################################################################################
	void printTree(){
		int level = 1;
	    while (printLevel(root_, level))
	        level++;
	}

	// Function to print all nodes of a given level from left to right
	bool printLevel(Node* root, int level)
	{
	    if (root == nullptr)
	        return false;

	    if (level == 1)
	    {
	        std::cout << "[" << root->pair_.first << "][" << root->isRed_ << "]";
	        // std::cout << "[" << root->pair_.first << "][" << root->pair_.second << "][" << root->isRed_ << "]";

	        // return true if at-least one node is present at given level
	        return true;
	    }

		if (level == 2)
			std::cout << "\n";
		// if (root->left_ && root->left_->left_)
		// 	std::cout << "	";
	    bool left = printLevel(root->left_, level - 1);
		// if (level == 2)
		// 	std::cout << "		";
	    bool right = printLevel(root->right_, level - 1);

	    return left || right;
	}
	bool addLevel(Node* root, int level)
	{
	    if (root == 0)
	        return false;
	    if (level == 1)
	    {
			add(root->pair_);
	        return true;
	    }
	    bool left = addLevel(root->left_, level - 1);
	    bool right = addLevel(root->right_, level - 1);
	    return left || right;
	}
	void levelOrderTraversal(Node* root)
	{
	    int level = 1;
	    while (addLevel(root, level))
	        level++;
	}
	// void printTree(Node *node, int lvl = 0){
	// 	if (node == 0)
	// 		return ;
	// 	for (int i = 5 - lvl * 2; i > 0; i--)
	// 		std::cout << '	';
	// 	std::cout << "LVL: " << lvl << " [" <<node->pair_.first << "] ["<< node->pair_.second << "]\n";
	// 	// if (node->isLeft)
	// 	// 	std::cout << "(left)" << '\n';
	// 	// else
	// 	// 	std::cout << "(right)" << '\n';
	// 	// if (lvl != 0 || !node->isLeft)
	// 	// 	for (int i = 4 - lvl; i > 0; i--)
	// 	// 		std::cout << '	';
	// 		// std::cout << "/		\\" << '\n';}
	// 	printTree(node->left_, lvl + 1);
	// 	printTree(node->right_, lvl + 1);
	// }
// ######################## HELPER FUNCTIONS ###################################
private:
	void add(ft::pair<Key, T> toAdd){
		root_ = put(0, root_, toAdd, true);
		if (root_->isRed_)
			root_->isRed_ = false;
	}
	ft::pair<Node*, Node*> put(Node *parent, Node *h, ft::pair<Key, T> toPut, bool left){
		if (h == 0){
			++size_;
			return new Node(toPut, parent, left);
		}
		if (h->pair_.first == toPut.first)
			h->pair_.second = toPut.second; // if keys equal -> replace value
		else if (!comp(h->pair_.first, toPut.first))
			 h->left_ = put(h, h->left_, toPut, true); // if comp gives false
		 else
			h->right_ = put(h, h->right_, toPut, false);

		if (isRed(h->right_) && !isRed(h->left_)) h = rotateLeft(h);
		if (isRed(h->left_) && isRed(h->left_->left_)) h = rotateRight(h);
		if (isRed(h->left_) && isRed(h->right_)) colorFlip(h);

		return ft::pair(h,);
	}
	// Node	*put(Node *parent, Node *h, ft::pair<Key, T> toPut, bool left){
	// 	if (h == 0){
	// 		++size_;
	// 		return new Node(toPut, parent, left);
	// 	}
	// 	if (h->pair_.first == toPut.first)
	// 		h->pair_.second = toPut.second; // if keys equal -> replace value
	// 	else if (!comp(h->pair_.first, toPut.first))
	// 		 h->left_ = put(h, h->left_, toPut, true); // if comp gives false
	// 	 else
	// 		h->right_ = put(h, h->right_, toPut, false);
	//
	// 	if (isRed(h->right_) && !isRed(h->left_)) h = rotateLeft(h);
	// 	if (isRed(h->left_) && isRed(h->left_->left_)) h = rotateRight(h);
	// 	if (isRed(h->left_) && isRed(h->right_)) colorFlip(h);
	//
	// 	return h;
	// }

	void colorFlip(Node *node){
		node->isRed_ = true;
		node->left_->isRed_ = false;
		node->right_->isRed_ = false;
	}
	Node* rotateLeft(Node *h)
	{
		assert (isRed(h->right_));

		Node *x = h->right_;
		h->right_ = x->left_;
		if (h->right_){
			h->right_->parent_ = h;
			h->right_->isLeft = false;
		}
		x->parent_ = h->parent_;
		x->isLeft = h->isLeft;
		x->isRed_ = h->isRed_;
		if (x->parent_ == 0)
			root_ = x;
		else if (x->isLeft)
			x->parent_->left_ = x;
		else
			x->parent_->right_ = x;
		x->left_ = h;
		h->isLeft = true;
		h->parent_ = x;
		h->isRed_ = true;
		return x;
	}
	Node* rotateRight(Node *h)
	{
		assert (isRed(h->left_));

		Node *x = h->left_;
		h->left_ = x->right_;
		if (h->left_){
			h->left_->parent_ = h;
			h->left_->isLeft = true;
		}
		x->parent_ = h->parent_;
		x->isLeft = h->isLeft;
		x->isRed_ = h->isRed_;
		if (x->parent_ == 0)
			root_ = x;
		else if (x->isLeft)
			x->parent_->left_ = x;
		else
			x->parent_->right_ = x;
		x->right_ = h;
		h->isLeft = false;
		h->parent_ = x;
		h->isRed_ = true;
		return x;
	}
	size_t heigth(){
		if (!root_)
			return 0;
		return height(root_) - 1;
	}
	size_t heigth(Node *node){
		if (node == 0)
			return 0;
		size_t left = height(node->left_);
		size_t right = height(node->right_);
		if (left > right)
			return left + 1;
		return right + 1;
	}
	// int blackNodes(Node *node){
	// 	if (node == 0)
	// 		return 1;
	// 	int left = blackNodes(node->left_);
	// 	int right = blackNodes(node->right_);
	// 	if (left < right)
	// 		fixUnevenBlack(node);
	// 	if (node->isRed_)
	// 		return left + right;
	// 	return left + right + 1;
	// }
	void	deleteTree(Node *node){
		if (node == 0)
			return ;
		deleteTree(node->left_);
		deleteTree(node->right_);
		delete node;
	}
	Node	*find(Node *node, const key_type& k){
		if (node == 0 || node->pair_.first == k)
			return node;
		if (!comp(node->pair_.first, k))
			return find(node->left_, k);
		return find(node->right_, k);
	}
	iterator				lowest (){
		Node *trav;
		for (trav = root_; trav->left_ ; trav = trav->left_)
			;
		return iterator(trav, this);
	}
	const_iterator			lowest () const {
		Node *trav;
		for (trav = root_; trav->left_; trav = trav->left_)
			;
		return iterator(trav, this);
	}
	iterator				uppest (){
		Node *trav;
		for (trav = root_; trav->right_; trav = trav->right_)
			;
		return iterator(trav, this);
	}
	const_iterator			uppest () const{
		Node *trav;
		for (trav = root_; trav->right_; trav = trav->right_)
			;
		return iterator(trav, this);
	}
	void	copyTree(Node *dest, Node *src){
		if (src->left_){
			dest->left_ = new Node(*src->left_, dest);
			copyTree(dest->left_, src->left_);
		}
		if (src->right_){
			dest->right_ = new Node(*src->right_, dest);
			copyTree(dest->right_, src->right_);
		}
	}
};

} //namespace ft

template <class Key, class T, class Compare>
bool operator== (const ft::map<Key, T, Compare>& lhs, const ft::map<Key, T, Compare>& rhs){
	if (lhs.size() != rhs.size())
		return false;
	typename ft::map<Key, T, Compare>::const_iterator l_it = lhs.begin();
	typename ft::map<Key, T, Compare>::const_iterator r_it = rhs.begin();
	while (l_it != lhs.end() && r_it != rhs.end()) {
		if (*l_it != *r_it){
			return false;
		}l_it++;
		r_it++;
	}
	return true;
}
template <class Key, class T, class Compare>
bool operator!= (const ft::map<Key, T, Compare>& lhs, const ft::map<Key, T, Compare>& rhs){
	return !(lhs == rhs);
}
template <class Key, class T, class Compare>
bool operator<  (const ft::map<Key, T, Compare>& lhs, const ft::map<Key, T, Compare>& rhs){
	typename ft::map<Key, T, Compare>::const_iterator l_it = lhs.begin();
	typename ft::map<Key, T, Compare>::const_iterator r_it = rhs.begin();
	while (l_it != lhs.end() && r_it != rhs.end()) {
		if (*l_it < *r_it)
			return true;
		if (*l_it > *r_it)
			return false;
		l_it++;
		r_it++;
	}
	if (r_it != rhs.end()) /// ??
		return true;
	return false;
}
template <class Key, class T, class Compare>
bool operator<= (const ft::map<Key, T, Compare>& lhs, const ft::map<Key, T, Compare>& rhs){
	return !(rhs < lhs);
}
template <class Key, class T, class Compare>
bool operator>  (const ft::map<Key, T, Compare>& lhs, const ft::map<Key, T, Compare>& rhs){
	return rhs < lhs;
}
template <class Key, class T, class Compare>
bool operator>= (const ft::map<Key, T, Compare>& lhs, const ft::map<Key, T, Compare>& rhs){
	return !(lhs < rhs);
}
template <class Key, class T, class Compare>
void swap(ft::map<Key, T, Compare> &a, ft::map<Key, T, Compare> &b){
	a.swap(b);
}

#endif
