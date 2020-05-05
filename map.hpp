#ifndef MAP_HPP
# define MAP_HPP

namespace ft
{

template<
	class Key,
	class T,
	class Compare = std::less<Key>,
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

		pair<Key, T>		pair_;
		rb_tree_node*		parent_;
		rb_tree_node*		leftChild_;
		rb_tree_node*		rightChild_;
		bool				isRed;
		bool				isLeft;

		rb_tree_node(pair<Key, T> pair, rb_tree_node* parent = 0, bool left = false):
			pair_(pair),
			parent_(parent),
			leftChild_(0),
			rightChild_(0),
			isRed(true),
			isLeftSide(left){}
		rb_tree_node(rb_tree_node const &x):
			pair_(x.pair_),
			parent_(0), // SHOULD I REALLY COPY POINTERS HERE
			leftChild_(0),
			rightChild_(0),
			isRed(x.isRed),
			isLeft(x.isLeft){}
	};
	rb_tree_node	*root_;
	size_t			size_;
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
	// typedef	reverse_iterator<iterator>		reverse_iterator;
	// typedef	reverse_iterator<const_iterator>	const_reverse_iterator;
	typedef	rb_tree_node			Node;

//######################### CONSTRUCTORS #######################################
	explicit map (const key_compare& comp = key_compare()):root_(0), size_(0), compare(comp){}
	template <class InputIterator>
	map (InputIterator first, InputIterator last, const key_compare& comp = key_compare()):
	root_(0),size_(0),compare(comp) {
		while (first != last) {
			add(*first);
		}
	}
	map (const map& x):root_(0), size(0), compare(x.compare){
		add_inOrder(x.root_);
	}
	~map(){
		removeNodes(root_);
		root_ = size_ = 0;
	}
	map& operator= (const map& x){
		map ret(x);
		swap(ret);
		return *this;
	}
	mapped_type& operator[] (const key_type& k){
		// Node *parent = find(k);
		// add(k);
		Node *trav = root;
		while (trav != 0){
			if (trav->pair_.key_ == k)
				return trav->pair_.value_;
			else if (trav.pair_.key_ < k)
				trav = trav->rightChild_;
			else
				trav = trav->leftChild_;
		}
		return mapped_type();
	}
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
	bool					empty() const {return !size_;}
	size_type				size() const {return size_;}
	size_type				max_size() const {return 576460752303423487;}
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
	void					swap (map& x) {
		char buffer[sizeof(map)];
		memcpy(buffer, &x, sizeof(map));
		memcpy(reinterpret_cast<char *>(&x), this, sizeof(map));
		memcpy(reinterpret_cast<char *>(this), &x, sizeof(map));
	}
	void					clear(){
		this->~map();
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
	void	add(Node &node, pair<Key, T> toAdd)){ // BETTER RECURSIVELY?
		if (comp(pair, node->pair_) < 0){
			if (node->leftChild_)
				return add(node->leftChild_);
			node->leftChild_ = new Node(pair, trav, true);
			node = node->leftChild_;
		}
		else {
			if (node->rightChild_)
				return add(node->rightChild_);
			node->rightChild_ = new Node(pair, trav, false);
			node = node->rightChild_;
		}
		size_++;
		checkColor(node);
	}
	void	checkColor(Node *node){
		if (node == root_){
			root_.isRed = black;
			return ;
		}
		if (node->isRed && node->parent_->isRed){
			correctTree(node);
		}
		checkColor(node->parent_);
	}
	bool AuntIsRed(Node *node){
		if (node->parent->isLeft){
			if (!node->parent->parent->rightChild_)
				return false;
			return node->parent->parent->rightChild_->isRed;
		}
		if (!node->parent->parent->leftChild_)
			return false;
		return node->parent->parent->leftChild_->isRed;
	}
	void correctTree(Node *node){
		if (AuntIsRed(node))
			colorFlip(node);
		else
			rotate(node);
	}
	void colorFlip(Node *node){
		node->parent->parent->isRed = true;
		if (node->parent->parent->leftChild_)
			node->parent->parent->leftChild_->isRed = false;
		if (node->parent->parent->rightChild_)
			node->parent->parent->rightChild_->isRed = false;
	}
	void rotate(Node *node){
		if (node->isLeft) {
			if (node->parent->isLeft) {
				rightRotate(node->parent->parent);
				node->isRed = true;
				node->parent->isRed = false;
				if (node->parent->leftChild_)
					node->parent->leftChild_->isRed = true;
			}
			else {
				rightLeftRotate(node->parent->parent);
				node->isRed = false;
				node->leftChild_->isRed = true;
				node->rightChild_->isRed = true;
			}
		}
		else {
			if (node->parent->isRight) {
				leftRotate(node->parent->parent);
				node->isRed = true;
				node->parent->isRed = false;
				if (node->parent->rightChild_)
					node->parent->rightChild_->isRed = true;
			}
			else {
				leftRightRotate(node->parent->parent);
				node->isRed = false;
				node->leftChild_->isRed = true;
				node->rightChild_->isRed = true;
			}
		}
	}
	void leftRotate(Node *gparent)
	{
		Node *tmp = gparent->rightChild_;
		gparent->rightChild_ = tmp->leftChild_;
		if (gparent->rightChild_) {
			gparent->rightChild_->parent = gparent;
			gparent->rightChild_->isLeft = false;
		}
		tmp->parent = gparent->parent;
		tmp->isLeft = gparent->isLeft;
		if (gparent->parent == 0)
			root_ = tmp;
		else if (gparent.isLeft)
			tmp->parent->leftChild_ = tmp;
		else
			tmp->parent->rightChild_ = tmp;
		tmp->leftChild_ = gparent;
		tmp->leftChild_->parent = tmp;
		tmp->leftChild_->isLeft = true;
	}
	void rightRotate(Node *gparent)
	{
		Node *tmp = gparent->leftChild_;
		gparent->leftChild_ = tmp->rightChild_;
		if (gparent->leftChild_) {
			gparent->leftChild_->parent = gparent;
			gparent->leftChild_->isLeft = true;
		}
		tmp->parent = gparent->parent;
		tmp->isLeft = gparent->isLeft;
		if (gparent->parent == 0)
			root_ = tmp;
		else if (gparent.isLeft)
			tmp->parent->rightChild_ = tmp;
		else
			tmp->parent->leftChild_ = tmp;
		tmp->rightChild_ = gparent;
		tmp->rightChild_->parent = tmp;
		tmp->rightChild_->isLeft = false;
	}
	void leftRightRotate(Node *node){
		leftRotate(node->leftChild_);
		rightRotate(node);
	}
	void rightLeftRotate(Node *node){
		rightRotate(node->rightChild_);
		leftRotate(node);
	}
	size_t heigth(){
		if (!root_)
			return 0;
		return height(root_) - 1;
	}
	size_t heigth(Node *node){
		if (node == 0)
			return 0;
		size_t left = height(node->leftChild_);
		size_t right = height(node->rightChild_);
		if (left > right)
			return left + 1;
		return right + 1;
	}
	int blackNodes(Node *node){
		if (node == 0)
			return 1;
		int left = blackNodes(node->leftChild_);
		int right = blackNodes(node->rightChild_);
		if (left != right)
			fixTree(node);
		if (node->isRed)
			return left + right;
		return left + right + 1;
	}
};

} //namespace ft

#endif
