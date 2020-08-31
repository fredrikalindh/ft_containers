#ifndef RBTREE_HPP
#define RBTREE_HPP

#include "iterator.hpp"

namespace ft
{
	template <class T, class Compare>
	class rb_tree_iterator;

	template <class T, class Compare>
	class RB_Tree
	{
		template <class U, class Cmp>
		friend class rb_tree_iterator;

		static const bool RED = true;
		static const bool BLACK = false;

		struct Node
		{
			T value_;
			Node *parent_;
			Node *left_;
			Node *right_;
			bool color_, isLeft;

			Node(T value, Node *parent_ = 0, bool left = true, bool color = RED) : value_(value),
																				   parent_(parent_),
																				   left_(0),
																				   right_(0),
																				   color_(color),
																				   isLeft(left) {}
			Node(Node const &x, Node *parent = 0) : value_(x.value_),
													parent_(parent),
													left_(0),
													right_(0),
													color_(x.color_),
													isLeft(x.isLeft) {}
		};
		bool isRed(Node *n)
		{
			if (n == 0)
				return false;
			return n->color_ == RED;
		}

		Node *root_;
		size_t size_;
		Compare comp;
		const bool allowMulti;

	public:
		// ########################### TYPEDEFS ########################################
		typedef T value_type;
		typedef size_t size_type;
		typedef std::ptrdiff_t difference_type;
		typedef value_type &reference;
		typedef const value_type &const_reference;
		typedef value_type *pointer;
		typedef const value_type *const_pointer;
		typedef rb_tree_iterator<T, Compare> iterator;
		typedef rb_tree_iterator<T, Compare> const_iterator;
		// typedef	rb_tree_iterator<const T, Compare>		const_iterator; ???????????????????????????????????
		//######################### CONSTRUCTORS #######################################
		explicit RB_Tree(const Compare &comp, bool allow = false) : root_(0),
																	size_(0),
																	comp(comp),
																	allowMulti(allow) {}
		RB_Tree(const RB_Tree &x) : root_(0),
									size_(x.size_),
									comp(x.comp),
									allowMulti(x.allowMulti)
		{
			if (size_)
			{
				root_ = new Node(*x.root_);
				copyTree(root_, x.root_);
			}
		}
		~RB_Tree()
		{
			deleteTree(root_);
			root_ = 0;
			size_ = 0;
		}
		RB_Tree &operator=(const RB_Tree &x)
		{
			RB_Tree ret(x);
			swap(ret);
			return *this;
		}
		//########################### MODIFIERS #######################################
		void swap(RB_Tree &x)
		{
			char buffer[sizeof(RB_Tree)];
			memcpy(buffer, &x, sizeof(RB_Tree));
			memcpy(reinterpret_cast<char *>(&x), this, sizeof(RB_Tree));
			memcpy(reinterpret_cast<char *>(this), buffer, sizeof(RB_Tree));
		}
		void clear()
		{
			deleteTree(root_);
			root_ = 0;
			size_ = 0;
		}
		size_t size() const
		{
			return size_;
		}
		// ########################## MAIN FUNCTIONS ###################################
		Node *find(const value_type &k) const
		{
			return find(root_, k);
		}
		// Node *find(Node *node, const value_type &k) const
		// {
		// 	  std::cout << "FIND " << k << "###########################" << std::endl;

		// 	if (!node)
		// 		return node;
		// 	rb_tree_iterator<T, Compare> it(min(root_), this);
		// 	while (it.node_ && (comp(*it, k) || comp(k, *it))) {
		// 		std::cout << *it << std::endl;
		// 		++it;
		// 	 }std::cout << "FIND ###########################" << std::endl;
		// 	return it.node_;
		// }
		Node *find(Node *node, const value_type &k) const
		{
			while (node)
			{
				if (!comp(node->value_, k) && !comp(k, node->value_))
					break;
				if (!comp(node->value_, k))
					node = node->left_;
				else
					node = node->right_;					
			}
			iterator it(node, this);
			while (it.node_ && (!comp(*it, k) && !comp(k, *it)))
				--it;
			if (it.node_)
				++it;
			return it.node_;
		}
		// Node *find(Node *node, const value_type &k) const
		// {
		// 	while (node)
		// 	{
		// 		if (!comp(node->value_, k) && !comp(k, node->value_) && (!node->left_  || 
		// 		!(!comp(node->left_->value_, k) && !comp(k, node->left_->value_)))) // --> IF LEFT IS NOT ALSO EQUAL
		// 			return node;
		// 		if (!comp(node->value_, k))
		// 			node = node->left_;
		// 		else
		// 			node = node->right_;					
		// 	}
		// 	return 0;
		// }
		Node *find_upper(const value_type k) const
		{
			rb_tree_iterator<T, Compare> it(find(root_, k), this);
			while (it.node_ && !comp(*it, k) && !comp(k, *it))
				++it;
			return it.node_;
		}
		size_type count(const value_type &k) const
		{
			size_type count = 0;

			for (rb_tree_iterator<T, Compare> it(find(root_, k), this);
			 it.node_ && !comp(*it, k) && !comp(k, *it); ++it)
				++count;
			return count;
		}
		Node *add(value_type toAdd)
		{
			Node *added; // sending address to this pointer so that I can select it even with the recursive

			root_ = add(0, root_, toAdd, true, &added);
			root_->color_ = BLACK;
			return added;
		}
		Node *add(Node *preceding, value_type value)
		{
			bool first = false;
			iterator it(preceding, this);
			while (it.node_) {
				if (comp(value, *it)) { // --> value < it
					first = true;
					--it;
				}else if (comp(*it, value)){ // --> value > it
					if (first) break;
					++it;
				}else
				{
					Node *added = new Node(value, it.node_->parent_, it.node_->isLeft);
					if (added->parent_)
						added->isLeft ? added->parent_->left_ = added : added->parent_->right_ = added;
					else
						root_ = added;
					added->left_ = it.node_->left_;
					if (added->left_)
						added->left_->parent_ = added;
					it.node_->left_ = 0;
					it.node_->isLeft = false;
					added->right_ = it.node_;
					it.node_->parent_ = added;
					++size_;
					return added;
				}
			}
			return add(value);
		}
		Node *add(Node *parent, Node *x, value_type &value, bool left, Node **added)
		{
			if (x == 0)
			{
				std::cout << "ADDING " << value;
				if (parent) 
					std::cout << " PARENT :  " << parent->value_;
				std::cout << std::endl;
				++size_;
				*added = new Node(value, parent, left);
				return *added;
			}
			if (!comp(x->value_, value) && !comp(value, x->value_) && allowMulti == false) // ---> EQUAL
				*added = x;
			else if (!comp(value, x->value_)) {
				x->right_ = add(x, x->right_, value, false, added);
				x->right_->parent_ = x;
			}else{
				x->left_ = add(x, x->left_, value, true, added); // if comp gives false
				x->left_->parent_ = x;
			}

			if (isRed(x->right_) && !isRed(x->left_))
				x = rotateLeft(x);
			if (isRed(x->left_) && isRed(x->left_->left_))
				x = rotateRight(x);
			if (isRed(x->left_) && isRed(x->right_))
				colorFlip(x);
			std::cout << "ADDING " << value;
			if (parent) 
				std::cout << " PARENT :  " << parent->value_;
			std::cout << std::endl;
			return x;
		}
		bool deleteKey(value_type value)
		{
			if (!find(root_, value)){
				std::cout << "not found :)" << std::endl;
				return false;
			}if (size_ < 2)
			{
				size_ = 0;
				root_ = nullptr;
				return true;
			}
			if (!isRed(root_->left_) && !isRed(root_->right_))
				root_->color_ = RED;
			root_ = deleteKey(root_, value);
			std::cout << "###########################" << std::endl;
			if (root_)
				root_->color_ = BLACK;
			return true;
		}
		Node *deleteKey(Node *x, value_type &value)
		{
			if (comp(value, x->value_))
			{
				if (!isRed(x->left_) && x->left_ && !isRed(x->left_->left_))
					x = moveRedLeft(x);
				x->left_ = deleteKey(x->left_, value);
			}
			else
			{
				if (isRed(x->left_))
					x = rotateRight(x);
				if (!comp(x->value_, value) && !x->right_)
				{ // EQUAL
					--size_;
					delete x;
					return 0;
				}
				if (!isRed(x->right_) && x->right_ && !isRed(x->right_->left_))
					x = moveRedRight(x);
				if (!comp(x->value_, value) && !comp(value, x->value_))
				{
					Node *h = min(x->right_);
					x->value_ = h->value_;
					x->right_ = deleteMin(x->right_);
				}
				else
					x->right_ = deleteKey(x->right_, value);
			}
			return balance(x);
		}
		void deleteKey(Node *x)
		{
			// std::cout << "DELETING : " << x->value_ << " LEFT : ";
			// (x->left_) ? std::cout << x->left_->value_ : std::cout << "no child ";
			// std::cout << " RIGHT : ";
			// (x->right_) ? std::cout << x->right_->value_ : std::cout << "no child ";
			// std::cout << " PARENT : ";
			// (x->parent_) ? std::cout << x->parent_->value_ : std::cout << "no parent";
			// std::cout << std::endl;

			if (!x)
				return ; 
			if (size_ == 1)
			{
				delete x;
				size_ = 0;
				root_ = 0;
			}
			else if (x && !x->right_)
			{
				std::cout << "no right child" << std::endl;
				if (x == root_) {
					std::cout << "1" << std::endl;
					root_ = x->left_;
					root_->parent_ = 0;
				}else {
					std::cout << "2" << std::endl;
					(x->isLeft) ? x->parent_->left_ = x->left_ : x->parent_->right_ = 0;
					x->left_ ? x->left_->parent_ = x->parent_ : 0;
				}
				--size_;
				delete x;
			}
			else
			{
				std::cout << "right child" << std::endl;
				Node *h = min(x->right_);
				if (x == root_) 
					root_ = h;
				else
					x->isLeft ? x->parent_->left_ = h : x->parent_->right_ = h;
				h->isLeft ? h->parent_->left_ = 0 : h->parent_->right_ = 0;
				h->parent_ = x->parent_;
				h->left_ = x->left_;
				h->right_ = x->right_;
				h->color_ = x->color_;
				h->isLeft = x->isLeft;
				delete x;
				--size_;
			}
		}
		// void deleteKey(Node *x)
		// {
		// 	std::cout << "DELETING : " << x->value_ << " LEFT : ";
		// 	(x->left_) ? std::cout << x->left_->value_ : std::cout << "no child ";
		// 	std::cout << " RIGHT : ";
		// 	(x->right_) ? std::cout << x->right_->value_ : std::cout << "no child ";
		// 	std::cout << " PARENT : ";
		// 	(x->parent_) ? std::cout << x->parent_->value_ : std::cout << "no parent";
		// 	std::cout << std::endl;

		// 	if (!x)
		// 		return ; 
		// 	if (size_ == 1)
		// 	{
		// 		delete x;
		// 		size_ = 0;
		// 		root_ = 0;
		// 	}
		// 	else if (x && !x->right_)
		// 	{
		// 		std::cout << "no right child" << std::endl;
		// 		if (x == root_) {
		// 			root_ = x->left_;
		// 			root_->parent_ = 0;
		// 		}else {
		// 			(x->isLeft) ? x->parent_->left_ = x->left_ : x->parent_->right_ = 0;
		// 			x->left_ ? x->left_->parent_ = x->parent_ : 0;
		// 		}
		// 		--size_;
		// 		// delete x;
		// 	}
		// 	else
		// 	{
		// 		Node *h = min(x->right_);
		// 		x->value_ = h->value_;
		// 		x->right_ = deleteMin(x->right_);
		// 		if (x->right_) 
		// 			x->right_->parent_ = x;
		// 		else
		// 			std::cout << "no rightttt" << std::endl;
		// 	}
		// }
		// void deleteKey(Node *x)
		// {
		// 	std::cout << "DELETING : " << x->value_ << " LEFT : ";
		// 	(x->left_) ? std::cout << x->left_->value_ : std::cout << "no child ";
		// 	std::cout << " RIGHT : ";
		// 	(x->right_) ? std::cout << x->right_->value_ : std::cout << "no child ";
		// 	std::cout << " PARENT : ";
		// 	(x->parent_) ? std::cout << x->parent_->value_ : std::cout << "no parent";
		// 	std::cout << std::endl;

		// 	if (!x)
		// 		return ; 
		// 	if (size_ == 1)
		// 	{
		// 		delete x;
		// 		size_ = 0;
		// 		root_ = 0;
		// 	}
		// 	else if (x && !x->right_)
		// 	{
		// 		if (x == root_) {
		// 			root_ = x->left_;
		// 			root_->parent_ = 0;
		// 		}else{
		// 			(x->isLeft) ? x->parent_->left_ = x->left_ : x->parent_->right_ = 0;
		// 			x->left_ ? x->left_->parent_ = x->parent_ : 0;
		// 		}
		// 		--size_;
		// 		// delete x;
		// 	}
		// 	else
		// 	{
		// 		Node *h = min(x->right_);
		// 		x->value_ = h->value_;
		// 		x->right_ = deleteMin(x->right_);
		// 	}
		// }	
		// ######################## HELPER FUNCTIONS ###################################
		void deleteMin()
		{
			if (root_ == 0) return ;
			if (!isRed(root_->left_ && !isRed(root_->right_)))
				root_->color_ = RED;
			root_ = deleteMin(root_);
			if (root_)
				root_->color_ = BLACK;
		}

		Node *deleteMin(Node *h)
		{
			if (!h->left_)
			{
				std::cout << "delete no left child "  << h->value_ << std::endl;
				--size_;
				delete h;
				return 0;
			}
			if (!isRed(h->left_) && !isRed(h->left_->left_))
				h = moveRedLeft(h);
			h->left_ = deleteMin(h->left_);
			return balance(h);
		}
		void deleteMax()
		{
			// if (root_ == 0) throw
			if (root_ == 0) return ;
			if (!isRed(root_->left_ && !isRed(root_->right_)))
				root_->color_ = RED;

			root_ = deleteMax(root_);
			if (root_)
				root_->color_ = BLACK;
		}

		Node *deleteMax(Node *h)
		{
			if (isRed(h->left_))
				h = rotateRight(h);
			if (h->right_ == 0)
			{
				--size_;
				delete h;
				return 0;
			}
			if (!isRed(h->right_) && !isRed(h->right_->left_))
				h = moveRedRight(h->right_);

			h->right_ = deleteMax(h->right_);
			return balance(h);
		}
		void colorFlip(Node *node)
		{
			node->color_ = !node->color_;
			node->left_->color_ = !node->left_->color_;
			node->right_->color_ = !node->right_->color_;
		}
		Node *rotateLeft(Node *h)
		{
			assert(isRed(h->right_));

			Node *x = h->right_;
			h->right_ = x->left_;
			if (h->right_)
			{
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
		Node *rotateRight(Node *h)
		{
			assert(isRed(h->left_));

			Node *x = h->left_;
			h->left_ = x->right_;
			if (h->left_)
			{
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
		Node *moveRedLeft(Node *h)
		{
			colorFlip(h);
			if (isRed(h->right_->left_))
			{
				h->right_ = rotateRight(h->right_);
				h = rotateLeft(h);
				colorFlip(h);
			}
			return h;
		}
		Node *moveRedRight(Node *h)
		{
			colorFlip(h);
			if (isRed(h->left_->left_))
			{
				h = rotateRight(h);
				colorFlip(h);
			}
			return h;
		}
		Node *balance(Node *h)
		{
			if (isRed(h->right_))
				h = rotateLeft(h);
			if (isRed(h->left_) && isRed(h->left_->left_))
				h = rotateRight(h);
			if (isRed(h->left_) && isRed(h->right_))
				colorFlip(h);

			return h;
		}
		void deleteTree(Node *node)
		{
			if (node == 0)
				return;
			deleteTree(node->left_);
			deleteTree(node->right_);
			delete node;
		}
		void copyTree(Node *dest, Node *src)
		{
			if (src->left_)
			{
				dest->left_ = new Node(*src->left_, dest);
				copyTree(dest->left_, src->left_);
			}
			if (src->right_)
			{
				dest->right_ = new Node(*src->right_, dest);
				copyTree(dest->right_, src->right_);
			}
		}
		inline Node *min() const
		{
			return min(root_);
		}
		inline Node *min(Node *trav) const
		{
			while (trav->left_)
				trav = trav->left_;
			return trav;
		}
		inline Node *max() const
		{
			return max(root_);
		}
		inline Node *max(Node *trav) const
		{
			while (trav->right_)
				trav = trav->right_;
			return trav;
		}
		size_t heigth()
		{
			if (!root_)
				return 0;
			return height(root_) - 1;
		}
		size_t heigth(Node *node)
		{
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
		bool equal(const RB_Tree &x, Compare comp) const
		{
			if (size() != x.size())
				return false;
			const_iterator l_it(min(), this);
			const_iterator r_it(x.min(), &x);
			while (l_it.node_ && r_it.node_)
			{
				if (comp(*l_it, *r_it) || comp(*r_it, *l_it))
					return false;
				l_it++;
				r_it++;
			}
			return true;
		}
		bool lesser(const RB_Tree &x, Compare comp) const
		{
			const_iterator l_it(min(), this);
			const_iterator r_it(x.min(), &x);
			while (l_it.node_ && r_it.node_)
			{
				if (comp(*l_it, *r_it))
					return true;
				if (comp(*r_it, *l_it))
					return false;
				l_it++;
				if (!l_it.node_)
					return true;
				r_it++;
			}
			return false;
		}
	};
	// ############################## ITERATOR #####################################
	template <class T, class Compare>
	class rb_tree_iterator
	{
	public:
		friend class RB_Tree<T, Compare>;

		typedef typename RB_Tree<T, Compare>::Node Node;
		typedef RB_Tree<T, Compare> Tree;

		Node *node_;
		Tree const *tree_;

		// public:
		typedef ft::bidirectional_iterator_tag iterator_category;
		typedef std::ptrdiff_t difference_type;
		typedef T value_type;
		typedef T *pointer;
		typedef T &reference;

		rb_tree_iterator(Node *node = 0, Tree const *tree = 0) : node_(node), tree_(tree) {}
		rb_tree_iterator(rb_tree_iterator const &cpy) : node_(cpy.node_), tree_(cpy.tree_) {}
		rb_tree_iterator &operator=(rb_tree_iterator const &cpy)
		{
			node_ = cpy.node_;
			return *this;
		}
		rb_tree_iterator &operator++(void)
		{
			if (node_ == 0)
			{
				node_ = tree_->min();
			}
			if (node_->right_)
			{
				node_ = node_->right_;
				while (node_ && node_->left_)
					node_ = node_->left_;
			}
			else
			{
				while (node_ && node_->parent_ && !node_->isLeft)
					node_ = node_->parent_;
				node_ = node_->parent_;
			}
			return *this;
		}
		rb_tree_iterator operator++(int)
		{
			rb_tree_iterator old(*this);
			operator++();
			return old;
		}
		rb_tree_iterator &operator--(void)
		{
			if (node_ == 0)
				node_ = tree_->max();
			else if (node_->left_)
			{
				node_ = node_->left_;
				while (node_ && node_->right_)
					node_ = node_->right_;
			}
			else
			{
				while (node_ && node_->parent_ && node_->isLeft)
					node_ = node_->parent_;
				node_ = node_->parent_;
			}
			return *this;
		}
		rb_tree_iterator operator--(int)
		{
			rb_tree_iterator old(*this);
			operator--();
			return old;
		}
		inline reference operator*(void) const { return node_->value_; }
		inline pointer operator->(void) const { return &(node_->value_); }
		inline bool operator!=(rb_tree_iterator const &other) const { return node_ != other.node_; }
		inline bool operator==(rb_tree_iterator const &other) const { return node_ == other.node_; }
	};

} //namespace ft

template <class T, class Compare>
void swap(ft::RB_Tree<T, Compare> &a, ft::RB_Tree<T, Compare> &b)
{
	a.swap(b);
}

#endif