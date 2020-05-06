#ifndef MAP_HPP
# define MAP_HPP

namespace ft
{
	template <class First, class Second>
	struct pair
	{
		First const	key;
		Second		value;
		pair(First first, Second second = Second()):key(first), value(second){}
		// bool	value_compare(pair)
	};
template<
	class Key,
	class T,
	class Compare = std::less<Key> >
class map
{
	struct Node
	{

		ft::pair<Key, T>	pair_;
		Node*				parent_;
		Node*				leftChild_;
		Node*				rightChild_;
		bool				isRed;
		bool				isLeft;

		Node(ft::pair<Key, T> pair, Node* parent_ = 0, bool left = false, bool red = true):
			pair_(pair),
			parent_(parent_),
			leftChild_(0),
			rightChild_(0),
			isRed(red),
			isLeft(left){}
		Node(Node const &x, Node *parent = 0):
			pair_(x.pair_),
			parent_(parent),
			leftChild_(0),
			rightChild_(0),
			isRed(x.isRed),
			isLeft(x.isLeft){}
	};
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
			if (node_ == 0)
				node_ = container_->lowest().base();
			else if (!node_->rightChild_ && node_->isLeft)
				node_ = node_->parent_;
			else if (!node_->rightChild_ && node_->parent_->parent_)
				node_ = node_->parent_->parent_;
			else {
				node_ = node_->rightChild_;
				while (node_ && node_->leftChild_)
					node_ = node_->leftChild_;
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
			else if (!node_->leftChild_ && !node_->isLeft)
				node_ = node_->parent_;
			else if (!node_->leftChild_ && node_->parent_->parent_)
				node_ = node_->parent_->parent_;
			else {
				node_ = node_->leftChild_;
				while (node_ && node_->rightChild_)
					node_ = node_->rightChild_;
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
			else if (!node_->rightChild_ && node_->isLeft)
				node_ = node_->parent_;
			else if (!node_->rightChild_ && node_->parent_->parent_)
				node_ = node_->parent_->parent_;
			else {
				node_ = node_->rightChild_;
				while (node_ && node_->leftChild_)
					node_ = node_->leftChild_;
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
				node_ = container_->uppest().base();
			else if (!node_->leftChild_ && !node_->isLeft)
				node_ = node_->parent_;
			else if (!node_->leftChild_ && node_->parent_->parent_)
				node_ = node_->parent_->parent_;
			else {
				node_ = node_->leftChild_;
				while (node_ && node_->rightChild_)
					node_ = node_->rightChild_;
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
//######################### CONSTRUCTORS #######################################
	explicit map (const key_compare& comp = key_compare()):root_(0), size_(0), comp(comp){}
	template <class InputIterator>
	map (InputIterator first, InputIterator last, const key_compare& comp = key_compare()):
	root_(0),size_(0),comp(comp) {
		while (first != last) {
			add(*first++);
		}
	}
	map (const map& x):root_(0), size_(x.size_), comp(x.comp){
		if (size_ > 0){
			root_ = new Node(*x.root_);
			size_++;
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
		Node *node;
		if (!(node = find_node(root_, k)))
			node = add(pair<Key, T>(k));
		return node->pair_.value;
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
	ft::pair<iterator,bool>	insert (const value_type& val);
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
		memcpy(reinterpret_cast<char *>(this), buffer, sizeof(map));
	}
	void					clear(){
		deleteTree(root_);
		root_ = 0;
		size_ = 0;
	}
//########################### OBSERVERS #######################################
	key_compare				key_comp() const;
	// value_compare			value_comp() const;
//########################### OPERATIONS #######################################
	iterator				find (const key_type& k);
	const_iterator			find (const key_type& k) const;
	size_type				count (const key_type& k) const;

	iterator				lower_bound (const key_type& k) ;
	const_iterator			lower_bound (const key_type& k) const ;
	iterator				upper_bound (const key_type& k) ;
	const_iterator			upper_bound (const key_type& k) const ;

	ft::pair<const_iterator,const_iterator>	equal_range (const key_type& k) const{

	}
	ft::pair<iterator,iterator>				equal_range (const key_type& k){

	}

	// void printTree(){
	// 	levelOrderTraversal(root_);
	// }
	//
	// // Function to print all nodes of a given level from left to right
	// bool printLevel(Node* root, int level)
	// {
	//     if (root == nullptr)
	//         return false;
	//
	//     if (level == 1)
	//     {
	//         std::cout << "[" << root->pair_.key << "][" << root->pair_.value << "]";
	//
	//         // return true if at-least one node is present at given level
	//         return true;
	//     }
	//
	// 	if (level == 2)
	// 		std::cout << "\n";
	// 	if (root->leftChild_ && root->leftChild_->leftChild_)
	// 		std::cout << "	";
	//     bool left = printLevel(root->leftChild_, level - 1);
	// 	if (level == 2)
	// 		std::cout << "		";
	//     bool right = printLevel(root->rightChild_, level - 1);
	//
	//     return left || right;
	// }
	bool addLevel(Node* root, int level)
	{
	    if (root == 0)
	        return false;
	    if (level == 1)
	    {
			add(root->pair_);
	        return true;
	    }
	    bool left = addLevel(root->leftChild_, level - 1);
	    bool right = addLevel(root->rightChild_, level - 1);
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
	// 	std::cout << "LVL: " << lvl << " [" <<node->pair_.key << "] ["<< node->pair_.value << "]\n";
	// 	// if (node->isLeft)
	// 	// 	std::cout << "(left)" << '\n';
	// 	// else
	// 	// 	std::cout << "(right)" << '\n';
	// 	// if (lvl != 0 || !node->isLeft)
	// 	// 	for (int i = 4 - lvl; i > 0; i--)
	// 	// 		std::cout << '	';
	// 		// std::cout << "/		\\" << '\n';}
	// 	printTree(node->leftChild_, lvl + 1);
	// 	printTree(node->rightChild_, lvl + 1);
	// }
// ######################## HELPER FUNCTIONS ###################################
private:
	Node 	*add(ft::pair<Key, T> toAdd){
		Node *added;
		if (root_ == 0){
			root_ = new Node(toAdd, 0, false, false);
			added = root_;
			++size_;
		}else {
			added = add(root_, toAdd);
			if (root_->isRed)
				root_->isRed = false;
			// blackNodes(root_);
		}
		return added;
	}
	Node	*add(Node *node, ft::pair<Key, T> toAdd){ // BETTER RECURSIVELY?
		if (comp(toAdd.key, node->pair_.key) < 0){
			if (node->leftChild_)
				return add(node->leftChild_, toAdd);
			node->leftChild_ = new Node(toAdd, node, true);
			node = node->leftChild_;
		}
		else {
			if (node->rightChild_)
				return add(node->rightChild_, toAdd);
			node->rightChild_ = new Node(toAdd, node, false);
			node = node->rightChild_;
		}
		size_++;
		checkColor(node);
		return node;
	}
	void	checkColor(Node *node){
		if (node == root_)
			return ;
		if (node->isRed && node->parent_->isRed){
			correctTree(node);
		}
		checkColor(node->parent_);
	}
	bool AuntIsRed(Node *node){
		if (node->parent_->isLeft){
			if (!node->parent_->parent_->rightChild_)
				return false;
			return node->parent_->parent_->rightChild_->isRed;
		}
		if (!node->parent_->parent_->leftChild_)
			return false;
		return node->parent_->parent_->leftChild_->isRed;
	}
	void correctTree(Node *node){
		if (AuntIsRed(node))
			colorFlip(node);
		else
			rotate(node);
	}
	void colorFlip(Node *node){
		node->parent_->parent_->isRed = true;
		if (node->parent_->parent_->leftChild_)
			node->parent_->parent_->leftChild_->isRed = false;
		if (node->parent_->parent_->rightChild_)
			node->parent_->parent_->rightChild_->isRed = false;
	}
	void rotate(Node *node){
		if (node->isLeft) {
			if (node->parent_->isLeft) {
				rightRotate(node->parent_->parent_);
				node->isRed = true;
				node->parent_->isRed = false;
				if (node->parent_->leftChild_)
					node->parent_->leftChild_->isRed = true;
			}
			else {
				rightLeftRotate(node->parent_->parent_);
				node->isRed = false;
				node->leftChild_->isRed = true;
				node->rightChild_->isRed = true;
			}
		}
		else {
			if (!node->parent_->isLeft) {
				leftRotate(node->parent_->parent_);
				node->isRed = true;
				node->parent_->isRed = false;
				if (node->parent_->rightChild_)
					node->parent_->rightChild_->isRed = true;
			}
			else {
				leftRightRotate(node->parent_->parent_);
				node->isRed = false;
				node->leftChild_->isRed = true;
				node->rightChild_->isRed = true;
			}
		}
	}
	void leftRotate(Node *gparent_)
	{
		Node *tmp = gparent_->rightChild_;
		gparent_->rightChild_ = tmp->leftChild_;
		if (gparent_->rightChild_) {
			gparent_->rightChild_->parent_ = gparent_;
			gparent_->rightChild_->isLeft = false;
		}
		tmp->parent_ = gparent_->parent_;
		tmp->isLeft = gparent_->isLeft;
		if (gparent_->parent_ == 0)
			root_ = tmp;
		else if (gparent_->isLeft)
			tmp->parent_->leftChild_ = tmp;
		else
			tmp->parent_->rightChild_ = tmp;
		tmp->leftChild_ = gparent_;
		tmp->leftChild_->parent_ = tmp;
		tmp->leftChild_->isLeft = true;
	}
	void rightRotate(Node *gparent_)
	{
		Node *tmp = gparent_->leftChild_;
		gparent_->leftChild_ = tmp->rightChild_;
		if (gparent_->leftChild_) {
			gparent_->leftChild_->parent_ = gparent_;
			gparent_->leftChild_->isLeft = true;
		}
		tmp->parent_ = gparent_->parent_;
		tmp->isLeft = gparent_->isLeft;
		if (gparent_->parent_ == 0)
			root_ = tmp;
		else if (gparent_->isLeft)
			tmp->parent_->rightChild_ = tmp;
		else
			tmp->parent_->leftChild_ = tmp;
		tmp->rightChild_ = gparent_;
		tmp->rightChild_->parent_ = tmp;
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
	void	deleteTree(Node *node){
		if (node == 0)
			return ;
		deleteTree(node->leftChild_);
		deleteTree(node->rightChild_);
		delete node;
	}
	Node	*find_node(Node *node, const key_type& k){
		if (node == 0 || comp(node->pair_.value, k) == 0)
			return node;
		if (comp(node->pair_.value, k) < 0)
			return find_node(node->leftChild_, k);
		return find_node(node->rightChild_, k);
	}
	iterator				lowest (){
		Node *trav;
		for (trav = root_; trav->leftChild_; trav = trav->leftChild_)
			;
		return iterator(trav, this);
	}
	const_iterator			lowest () const{
		Node *trav;
		for (trav = root_; trav->leftChild_; trav = trav->leftChild_)
			;
		return iterator(trav, this);
	}
	iterator				uppest (){
		Node *trav;
		for (trav = root_; trav->rightChild_; trav = trav->rightChild_)
			;
		return iterator(trav, this);
	}
	const_iterator			uppest () const{
		Node *trav;
		for (trav = root_; trav->rightChild_; trav = trav->rightChild_)
			;
		return iterator(trav, this);
	}
	void	copyTree(Node *dest, Node *src){
		if (src->leftChild_){
			dest->leftChild_ = new Node(*src->leftChild_, dest);
			copyTree(dest->leftChild_, src->leftChild_);
		}
		if (src->rightChild_){
			dest->rightChild_ = new Node(*src->rightChild_, dest);
			copyTree(dest->rightChild_, src->rightChild_);
		}
	}
};

} //namespace ft

#endif
