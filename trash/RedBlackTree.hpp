#ifndef REDBLACKTREE_HPP
# define REDBLACKTREE_HPP

template < class Key, class T, class Compare = std::less<Key> >
class RedBlackTree
{
	static const bool RED   = true;
	static const bool BLACK = false;

	struct Node
	{
		ft::pair<Key, T>	pair_;
		Node*				parent_;
		Node*				left_;
		Node*				right_;
		bool				color_, isLeft;
		// ‎enum color_type{red=false,black=true};

		Node(ft::pair<Key, T> pair, Node* parent_ = 0, bool left = true, bool color = RED):
			pair_(pair),
			parent_(parent_),
			left_(0),
			right_(0),
			color_(color),
			isLeft(left){}
		Node(Node const &x, Node *parent = 0):
			pair_(x.pair_),
			parent_(parent),
			left_(0),
			right_(0),
			color_(x.color_),
			isLeft(x.isLeft){}
	};
	bool	isRed(Node *n){
		if (n == 0) return false;
		return n->color_ == RED;
	}
public:
	Node*			root_;
	size_t			size_;
	Compare			comp;
// ITERATORS ###################################################################
	class bidirectional_iterator
	{
		Node*	node_;
		map*	container_;
	public:
		typedef ft::bidirectional_iterator_tag	iterator_category;
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
				node_ = container_->min(container_->root_);
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
				node_ = container_->max(container_->root_);
			else if (!node_->isLeft && !node_->left_)
				node_ = node_->parent_;
			else if (!node_->left_){
				Key store(node_->pair_.first);
				node_ = node_->parent_;
				while (node_ && !container_->comp(node_->pair_.first, store))
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
		const_bidirectional_iterator(Node *node, map const *container):node_(node), container_(container){}
		const_bidirectional_iterator(bidirectional_iterator const &cpy):node_(cpy.node_), container_(cpy.container_){}
		const_bidirectional_iterator& operator=(bidirectional_iterator const &cpy){
			const_bidirectional_iterator tmp(cpy);
			swap(tmp);
			return *this;
		}
		const_bidirectional_iterator& operator++(void){
				if (node_ == 0){
					node_ = container_->min(container_->root_);
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
		const_bidirectional_iterator operator++(int){
			const_bidirectional_iterator old(*this);
			this->operator++();
			return old;
		}
		const_bidirectional_iterator& operator--(void){
			if (node_ == 0)
				node_ = container_->max(container_->root_);
			else if (!node_->isLeft && !node_->left_)
				node_ = node_->parent_;
			else if (!node_->left_){
				Key store(node_->pair_.first);
				node_ = node_->parent_;
				while (node_ && !container_->comp(node_->pair_.first, store))
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
		inline Node			*base() const {return node_;}
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
	protected:
		Compare comp;
		value_compare (Compare c) : comp(c) {}	// constructed with map's comparison object
	public:
		friend class map;

		typedef bool result_type;
		typedef value_type first_argument_type;
		typedef value_type second_argument_type;
		bool operator() (const value_type& x, const value_type& y) const
		{
			return comp(x.first, y.first);
		}
	};
protected:
	Node	*find(Node *node, const key_type& k) const {
		// if (k == 0) THROW SOMETHING ?
		while (node){
			if (node->pair_.first == k)
				return node;
			if (!comp(node->pair_.first, k))
				node = node->left_;
			else
				node = node->right_;
		}
		return 0;
	}
	Node* add(ft::pair<Key, T> toAdd){
		Node* added; // sending address to this pointer so that I can select it even with the recursive

		root_ = add(0, root_, toAdd, true, &added);
		if (root_->color_ == RED)
			root_->color_ = BLACK;
		return added;
	}
	Node	*add(Node *parent, Node *x, ft::pair<Key, T> value, bool left, Node **added){
		if (x == 0){
			++size_;
			*added = new Node(value, parent, left);
			return *added;
		}
		// std::cout << "WHAT IS comp(" << x->pair_.first << ','<< value.first << ")	"<< comp(x->pair_.first, value.first) << " / " << comp(value.first, x->pair_.first) << '\n';
		if (x->pair_.first == value.first) {
			// x->pair_.second = value.second; // if keys equal -> replace value
			*added = x;
		}else if (!comp(x->pair_.first, value.first))
			 x->left_ = add(x, x->left_, value, true, added); // if comp gives false
		else
			x->right_ = add(x, x->right_, value, false, added);
		if (isRed(x->right_) && !isRed(x->left_)) x = rotateLeft(x);
		if (isRed(x->left_) && isRed(x->left_->left_)) x = rotateRight(x);
		if (isRed(x->left_) && isRed(x->right_)) colorFlip(x);

		return x;
	}

	void deleteMin(){
		// if (root_ == 0) throw

		if (!isRed(root_->left_ && !isRed(root_->right_)))
			root_->color_ = RED;

		root_ = deleteMin(root_);
		if (root_) root_->color_ = BLACK;
	}

	Node *deleteMin(Node *h){
		if (h->left_ == 0){ // ADD DELETE ?
			--size_;
			delete h;
			return 0;
		}if (!isRed(h->left_) && !isRed(h->left_->left_))
			h = moveRedLeft(h);

		h->left_ = deleteMin(h->left_);
		return balance(h);
	}
	void deleteMax(){
		// if (root_ == 0) throw

		if (!isRed(root_->left_ && !isRed(root_->right_)))
			root_->color_ = RED;

		root_ = deleteMax(root_);
		if (root_) root_->color_ = BLACK;
	}

	Node *deleteMax(Node *h){
		if (isRed(h->left_))
			h = rotateRight(h);
		if (h->right_ == 0){
			--size_;
			delete h;
			return 0;
		}if (!isRed(h->right_) && !isRed(h->right_->left_))
			h = moveRedRight(h->right_);

		h->right_ = deleteMax(h->right_);
		return balance(h);
	}

	void deleteKey(Key key){
		// if (toDelete.first == 0) // error throw ?

		// if (!(count(toDelete)))
		if (!isRed(root_->left_) && !isRed(root_->right_))
			root_->color_ = RED;
		root_ = deleteKey(root_, key);
		if (root_)
			root_->color_ = BLACK;
	}
	Node	*deleteKey(Node *x, Key key){
		// std::cout << "WHAT IS comp(" << x->pair_.first << ','<< key << ')'<< comp(x->pair_.first, key) << '+' << comp(key, x->pair_.first) << '\n';
		if (comp(key, x->pair_.first)){
			if (!isRed(x->left_) && x->left_ && !isRed(x->left_->left_))
				x = moveRedLeft(x);
			x->left_ = deleteKey(x->left_, key);
		}
		else {
			if (isRed(x->left_))
				x = rotateRight(x);
			if (x->pair_.first == key && !x->right_){ //delete here
				--size_;
				delete x;
				return 0;
			}
			if (!isRed(x->right_) && x->right_ && !isRed(x->right_->left_))
				x = moveRedRight(x);
			if (x->pair_.first == key) {
				Node *h = min(x->right_);
				x->pair_ = h->pair_;
				x->right_ = deleteMin(x->right_);
			}
			else x->right_ = deleteKey(x->right_, key);
		}
		return balance(x);
	}
	void colorFlip(Node *node){
		node->color_ = !node->color_;
		node->left_->color_ = !node->left_->color_;
		node->right_->color_ = !node->right_->color_;
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
		x->color_ = h->color_;
		x->left_ = h;
		h->isLeft = true;
		h->parent_ = x;
		h->color_ = RED;
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
		x->color_ = h->color_;
		x->right_ = h;
		h->isLeft = false;
		h->parent_ = x;
		h->color_ = RED;
		return x;
	}
	Node *moveRedLeft(Node *h){
		colorFlip(h);
		if (isRed(h->right_->left_)){
			h->right_ = rotateRight(h->right_);
			h = rotateLeft(h);
			colorFlip(h);
		}
		return h;
	}
	Node *moveRedRight(Node *h){
		colorFlip(h);
		if (isRed(h->left_->left_)){
			h = rotateRight(h);
			colorFlip(h);
		}
		return h;
	}
	Node *balance(Node *h){
		if (isRed(h->right_))							h = rotateLeft(h);
		if (isRed(h->left_) && isRed(h->left_->left_))	h = rotateRight(h);
		if (isRed(h->left_) && isRed(h->right_))		colorFlip(h);

		return h;
	}
	void	deleteTree(Node *node){
		if (node == 0)
			return ;
		deleteTree(node->left_);
		deleteTree(node->right_);
		delete node;
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
	inline Node*		min (Node *trav) const {
		while (trav->left_)
			trav = trav->left_;
		return trav;
	}
	inline Node*		max (Node *trav) const {
		while (trav->right_)
			trav = trav->right_;
		return trav;
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
	// 	if (node->color_)
	// 		return left + right;
	// 	return left + right + 1;
	// }
};

#endif
