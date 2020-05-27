#ifndef LIST_HPP
# define LIST_HPP

# include <iostream>
# include <string>

# include "iterator.hpp"

namespace ft
{

template <class T>
class list
{
protected:
//  NODE ######################################################################
	struct Node
	{
		Node		*prev;
		Node		*next;
		T			value;

		Node(T value = T()):next(0), prev(0), value(value){}
		Node(Node *prev, Node *next, T value):prev(prev), next(next), value(value){}
		Node(Node const &cpy):prev(cpy.prev), next(cpy.next), value(cpy.value){}
	};
	Node*	first_;
	Node*	last_;
	size_t	size_;

public:
//  ITERATOR ##################################################################
	class bidirectional_iterator
	{
	protected:
		Node*	node_;
		list*	container_;
	public:
		typedef ft::bidirectional_iterator_tag	iterator_category; // CHANGE TO FT AND MAKE OWN DISTANCE + ADVANCE
		typedef T								value_type;
		typedef std::ptrdiff_t					difference_type;
		typedef T*								pointer;
		typedef T&								reference;

		explicit bidirectional_iterator(Node *node = 0):node_(node), container_(0){}
		bidirectional_iterator(Node *node, list *container):node_(node), container_(container){}
		bidirectional_iterator(bidirectional_iterator const &cpy):node_(cpy.node_), container_(cpy.container_){}
		// ~bidirectional_iterator(){}
		bidirectional_iterator& operator=(bidirectional_iterator const &cpy){
			bidirectional_iterator tmp(cpy);
			swap(tmp);
			return *this;
		}
		bidirectional_iterator& operator++(void){
			if (node_)
				node_ = node_->next;
			else
				node_ = container_->first_;
			return *this;
		}
		bidirectional_iterator operator++(int){
			bidirectional_iterator old(*this);
			if (node_)
				node_ = node_->next;
			else
				node_ = container_->first_;
			return old;
		}
		bidirectional_iterator& operator--(void){
			if (node_)
				node_ = node_->prev;
			else
				node_ = container_->last_;
			return *this;
		}
		bidirectional_iterator operator--(int){
			bidirectional_iterator old(*this);
			if (node_)
				node_ = node_->prev;
			else
				node_ = container_->last_;
			return old;
		}
		inline Node *base(){return node_;}
		inline reference	operator*(void) {return node_->value;}
		inline pointer		operator->(void) {return &(node_->value);}
		inline reference	operator*(void) const {return node_->value;}
		inline pointer		operator->(void) const {return &(node_->value);}
		inline bool			operator!=(bidirectional_iterator const &other) const {return node_ != other.node_;}
		inline bool			operator==(bidirectional_iterator const &other) const {return node_ == other.node_;}

		void swap(bidirectional_iterator &other){  // PRIVATE?
			char buffer[sizeof(bidirectional_iterator)];
			memcpy(buffer, &other, sizeof(bidirectional_iterator));
			memcpy(reinterpret_cast<char *>(&other), this,   sizeof(bidirectional_iterator));
			memcpy(reinterpret_cast<char *>(this),   buffer, sizeof(bidirectional_iterator));
		}
	};
	class const_bidirectional_iterator : public bidirectional_iterator
	{
	protected:
		Node*	node_;
		const list*	container_;
	public:
		// typedef ft::bidirectional_iterator_tag			iterator_category; // CHANGE TO FT AND MAKE OWN DISTANCE + ADVANCE
		typedef const T									value_type;
		// typedef std::ptrdiff_t							difference_type;
		typedef const T*								pointer;
		typedef const T&								reference;

		const_bidirectional_iterator(Node *node = 0):node_(node), container_(0){}
		const_bidirectional_iterator(Node *node, list const *container):node_(node), container_(container){}
		const_bidirectional_iterator(bidirectional_iterator const &cpy):node_(cpy.node_), container_(cpy.container_){}
		// ~bidirectional_iterator(){}
		// const_bidirectional_iterator& operator=(bidirectional_iterator const &cpy){
		// 	const_bidirectional_iterator tmp(cpy);
		// 	swap(tmp);
		// 	return *this;
		// }
		// const_bidirectional_iterator& operator++(void){
		// 	if (node_)
		// 		node_ = node_->next;
		// 	else
		// 		node_ = container_->first_;
		// 	return *this;
		// }
		// const_bidirectional_iterator operator++(int){
		// 	const_bidirectional_iterator old(*this);
		// 	if (node_)
		// 		node_ = node_->next;
		// 	else
		// 		node_ = container_->first_;
		// 	return old;
		// }
		// const_bidirectional_iterator& operator--(void){
		// 	if (node_)
		// 		node_ = node_->prev;
		// 	else
		// 		node_ = container_->last_;
		// 	return *this;
		// }
		// const_bidirectional_iterator operator--(int){
		// 	const_bidirectional_iterator old(*this);
		// 	if (node_)
		// 		node_ = node_->prev;
		// 	else
		// 		node_ = container_->last_;
		// 	return old;
		// }
		// inline Node *base(){return node_;}
		// inline reference	operator*(void) {return node_->value;}
		// inline pointer		operator->(void) {return &(node_->value);}
		// inline reference	operator*(void) const {return node_->value;}
		// inline pointer		operator->(void) const {return &(node_->value);}
		// inline bool			operator!=(const_bidirectional_iterator const &other) const {return node_ != other.node_;}
		// inline bool			operator==(const_bidirectional_iterator const &other) const {return node_ == other.node_;}
		//
		// void swap(const_bidirectional_iterator &other){  // PRIVATE?
		// 	char buffer[sizeof(const_bidirectional_iterator)];
		// 	memcpy(buffer, &other, sizeof(const_bidirectional_iterator));
		// 	memcpy(reinterpret_cast<char *>(&other), this,   sizeof(const_bidirectional_iterator));
		// 	memcpy(reinterpret_cast<char *>(this),   buffer, sizeof(const_bidirectional_iterator));
		// }
	};
// TYPEDEFS ####################################################################
	typedef T										value_type;
	typedef value_type&								reference;
	typedef const value_type&						const_reference;
	typedef value_type*								pointer;
	typedef const value_type*						const_pointer;
	typedef bidirectional_iterator					iterator;
	typedef const_bidirectional_iterator			const_iterator;
	typedef ft::reverse_iterator<iterator>			reverse_iterator;
	typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;
	typedef size_t									size_type;
	typedef ptrdiff_t								difference_type;

// ############################ CONSTRUCTORS ###################################
	explicit list():first_(0), last_(0), size_(0){}
	explicit list(size_t n, const T& val = T()):first_(0), last_(0),size_(n){
		if (n) {
			first_ = new Node(0, 0, val);
			Node *toAdd;
			Node *prev = first_;
			while (--n)
			{
				toAdd = new Node(prev, 0, val);
				prev->next = toAdd;
				prev = toAdd;
			}
			last_ = prev;
		}
	}
	template <class InputIterator>
	list (InputIterator first, InputIterator last,
	typename std::enable_if<!std::is_integral<InputIterator>::value>::type* = 0):
	first_(0), last_(0), size_(0) {
		if (first != last) {
			size_ = 1;
			first_ = new Node(0, 0, *first);
			Node *toAdd;
			Node *prev = first_;
			for (first = ++first; first != last; first++)
			{
				toAdd = new Node(prev, 0, *first);
				prev->next = toAdd;
				prev = toAdd;
				size_++;
			}
			last_ = prev;
		}
	}
	list(list const &cpy):first_(0), last_(0), size_(cpy.size_)
	{
		if (size_)
		{
			first_ = new Node(0, 0, cpy.first_->value);
			Node *toAdd;
			Node *prev = first_;
			Node *ctrav = cpy.first_->next;
			while (ctrav)
			{
				toAdd = new Node(prev, 0, ctrav->value);
				prev->next = toAdd;
				prev = toAdd;
				ctrav = ctrav->next;
			}
			last_ = prev;
		}
	}
	~list(){
		Node *prev;
		while (first_ && size_)
		{
			prev = first_;
			first_ = first_->next;
			delete prev;
		}
		first_ = last_ = 0;
		size_ = 0;
	}
	list &operator=(list const &x){
		list cpy(x);
		swap(cpy);
		return *this;
	}
//############################# MEMBER FUNCTIONS ###############################
	inline size_type		size() const {return size_;}
	inline size_type		max_size() const {return 768614336404564650;} // ?
	inline bool				empty() const {return !first_;} // return first == 0}
	void 					resize(size_t n, T val = T())
	{
		Node *trav;
		if (!n)
			clear();
		else if (empty()){
			list tmp(n, val);
			swap(tmp);
		}else if (n < size_){
			trav = first_;
			while (n-- > 0)
				trav = trav->next;
			erase(iterator(trav, this), iterator(0, this));
		}
		else if (n > size_){
			insert(0, n - size_, val);
		}
	}
	void swap(list &other){
		char buffer[sizeof(list)];
		memcpy(buffer, &other, sizeof(list));
		memcpy(reinterpret_cast<char *>(&other), this,   sizeof(list));
		memcpy(reinterpret_cast<char *>(this),   buffer, sizeof(list));
	}
//############################## FOR ITERATOR ##################################
	inline reference			front() {return first_->value;} //Calling this function on an empty container causes undefined behavior.
	inline const_reference		front() const {return first_->value;}
	inline reference			back() {return last_->value;}
	inline const_reference		back() const  {return last_->value;}

	inline iterator				begin() {return iterator(first_, this);}
	inline const_iterator		begin() const {return const_iterator(first_, this);}
	inline iterator				end() {return iterator(0, this);}
	inline const_iterator		end() const {return const_iterator(0, this);}
	inline reverse_iterator		rbegin() {return reverse_iterator(end());}
	inline const_reverse_iterator rbegin() const {return const_reverse_iterator(end());}
	inline reverse_iterator 	rend() {return reverse_iterator(begin());}
	inline const_reverse_iterator rend() const {return const_reverse_iterator(begin());}

//################################ ASSIGN ######################################
	template 		<class InputIterator>
	void 			assign (InputIterator first, InputIterator last){
		list tmp(first, last);
		swap(tmp);
	}
	void 			assign (size_t n, const T& val){
		list tmp(n, val);
		swap(tmp);
	}
//################################ INSERT ######################################
	iterator		insert (iterator position, const T& val){
		Node *toAdd;
		if (this->empty()) // EVEN POSSIBLE ?
		{
			toAdd = new Node(0, 0, val);
			first_ = last_ = toAdd;
		}
		else if (position.base() == first_){
			toAdd = new Node(0, first_, val);
			first_->prev = toAdd;
			first_ = toAdd;
		}
		else if (!position.base()){
			toAdd = new Node(last_, 0, val);
			last_->next = toAdd;
			last_ = toAdd;
		}
		else {
			toAdd = new Node(position.base()->prev, position.base(), val);
			position.base()->prev->next = toAdd;
			position.base()->prev = toAdd;
		}
		size_++;
		return iterator(toAdd, this);
	}
	void			insert (iterator position, size_type n, const T& val){
		Node *prev;
		size_t i = 0;
		if (position.base() == first_){
			prev = first_ = new Node(0, first_, val);
			i++;
		}
		else if (position.base() == 0)
			prev = last_;
		else
			prev = position.base()->prev;
		Node *toAdd;
		while (i++ < n)
		{
			toAdd = new Node(prev, 0, val);
			prev->next = toAdd;
			prev = toAdd;
		}
		if (position.base() == 0){
			last_ = toAdd;
		}else{
			position.base()->prev = toAdd;
			toAdd->next = position.base();
		}size_ += n;
	}
	template <class InputIterator>
	void			insert (iterator position, InputIterator first, InputIterator last,
	typename std::enable_if<!std::is_integral<InputIterator>::value>::type* = 0){
		Node *prev;
		if (position.base() == first_)
		{
			prev = first_ = new Node(0, first_, *first);
			first++;
			size_++;
		}
		else if (position.base() == 0)
			prev = last_;
		else
			prev = position.base()->prev;
		Node *toAdd;
		while (first != last){
			toAdd = new Node(prev, 0, *first);
			prev->next = toAdd;
			prev = toAdd;
			first++;
			size_++;
		}
		if (position.base() == 0){
			last_ = toAdd;
		}else{
			position.base()->prev = toAdd;
			toAdd->next = position.base();
		}
	}
//################################ ERASE ######################################
	iterator 		erase(iterator position){
		if (position == 0)
			return position;
		iterator ret(position);
		ret++;
		unlink_node(position.base());
		delete position.base();
		return ret;
	}
	iterator 		erase(iterator first, iterator last){
		Node* toDel;
		unlink_range(first.base(), last.base());
		while (first != 0 && first != last){
			toDel = first.base();
			first++;
			delete toDel;
		}
		return last;
	}
//############################## PUSH & POP ###################################
	void			push_back(const T& val){
						last_ = new Node(last_, 0, val);
						size_++;
						if (last_->prev)
							last_->prev->next = last_;
						else
							first_ = last_;
					}
	void			pop_back() {
						Node *toDel = last_;
						unlink_node(last_);
						delete toDel;
					}
	void			push_front(const T& val) {
						first_ = new Node(0, first_, val);
						size_++;
						if (first_->next)
							first_->next->prev = first_;
						else
							last_ = first_;
					}
	void			pop_front() {
						Node *toDel = first_;
						unlink_node(first_);
						delete toDel;
					}
	void			clear() {
						Node *prev;
						while (first_)
						{
							prev = first_;
							first_ = first_->next;
							delete prev;
						}
						first_ = last_ = 0;
						size_ = 0;
					} // ~
//################################ SPLICE ######################################
	void	splice (iterator position, list& x){
		if (x.empty())
			return ;
		if (position.base() == first_){
			first_->prev = x.last_;
			x.last_->next = first_;
			first_ = x.first_;
		}else if (position.base() == 0){
			last_->next = x.first_;
			x.first_->prev = last_;
			last_ = x.last_;
		}else {
			position.base()->prev->next = x.first_;
			x.first_->prev = position.base()->prev;
			position.base()->prev = x.last_;
			x.last_->next = position.base();
		}
		size_ += x.size_;
		x.first_ = x.last_ = 0;
		x.size_ = 0;
	}
	void	splice (iterator position, list& x, iterator i){ // remove from x
		x.unlink_node(i.base());
		//--------- INSERT-----------
		if (empty()){
			first_ = last_ = i.base();
		}else if(position.base() == first_){
			first_->prev = i.base();
			i.base()->next = first_;
			first_ = i.base();
		}else if (position.base() == 0){
			last_->next = i.base();
			i.base()->prev = last_;
			last_ = i.base();
		}else {
			i.base()->next = position.base();
			i.base()->prev = position.base()->prev;
			i.base()->prev->next = i.base();
			i.base()->next->prev = i.base();
		}
		size_++;
	}
	void	splice (iterator position, list& x, iterator first, iterator last){
		if (!x.first_ || first == last)
			return ;
		Node *nlast = (last.base()) ? last.base()->prev : x.last_;
		size_ += x.unlink_range(first.base(), last.base());
		if (empty()){
			first_ = first.base();
			last_ = nlast;
		}else if(position.base() == first_){
			first_->prev = nlast;
			nlast->next = first_;
			first_ = first.base();
		}else if (position.base() == 0){
			last_->next = first.base();
			first.base()->prev = last_;
			last_ = nlast;
		}else {
			position.base()->prev->next = first.base();
			first.base()->prev = position.base()->prev;
			position.base()->prev = nlast;
			last.base()->next = position.base();
		}
	}
//################################ REMOVE ######################################
	void	remove (const T& val){
		iterator it = first_;
		while (it != 0)
		{
			if (*it == val)
				it = erase(it);
			else
				it++;
		}
	}
	template <class Predicate>
	void	remove_if (Predicate pred){
		iterator it = first_;
		while (it.base() != 0)
		{
			if (pred(*it))
				it = erase(it);
			else
				it++;
		}
	}
//################################ UNIQUE ######################################
	void	unique(){
		iterator it2;
		for (Node *it1 = first_; it1->next != 0; it1 = it1->next)
		{
			it2 = it1->next;
			while (it2 != 0 && *it2 == it1->value)
				it2 = erase(it2);
		}
	}
	template <class BinaryPredicate>
	void	unique (BinaryPredicate binary_pred){
		iterator it2;
		for (Node *it1 = first_; it1 != 0; it1 = it1->next)
		{
			it2 = it1->next;
			while (it2 != 0 && binary_pred(*it2, it1->value))
				it2 = erase(it2);
		}
	}

//################################ MERGE ######################################
// A subtlety is that merge doesn't alter the list if the list itself is used as
//argument: object.merge(object) won't change the list `object'. !!!!!!!

	void	merge (list& x){ //sorted merge
		iterator a(first_);
		iterator b(x.first_);
		Node *insert;
		while (a != 0 && b != 0){
			if (*b < *a){
				insert = b.base();
				b++;
				splice(a, x, insert);
			}
			else
				a++;
		}
		if (!x.empty()){
			last_->next = x.first_;
			x.first_->prev = last_;
		}
		x.first_ = x.last_ = 0;
		x.size_ = 0;
	}
	template <class Compare>
  	void	merge (list& x, Compare comp){
		iterator a(first_);
		iterator b(x.first_);
		Node *insert;
		while (a != 0 && b != 0){
			if (comp(*b, *a) > 0) {
				insert = b.base();
				b++;
				splice(a, x, insert);
			}
			else
				a++;
		}
		if (!x.empty()){
			last_->next = x.first_;
			x.first_->prev = last_;
		}
		x.first_ = x.last_ = 0;
		x.size_ = 0;
	}
//############################## SORT ##########################################
	void	sort(){
		if (size_ < 2)
			return ;
		mergesort(&first_, std::less<value_type>());
	}

	template <class Compare>
	void	sort (Compare comp){
		if (size_ < 2)
			return ;
		mergesort(&first_, comp);
	}
//############################## REVERSE #######################################
	void	reverse(){
		iterator front = first_;
		iterator back = last_;
		while (front != back){
			std::swap(*front, *back);
			front++;
			if (front == back)
				break ;
			back--;
		}
	}
protected:
	void unlink_node(Node* position){
		if (!position)
			return ;
		size_--;
		if (size_ < 1){
			first_ = last_ = 0;
		}
		else if (position == first_){
			first_ = first_->next;
			first_->prev = 0;
		}
		else if (position == last_){
			last_ = last_->prev;
			last_->next = 0;
		}
		else {
			position->prev->next = position->next;
			position->next->prev = position->prev;
		}
		position->prev = position->next = 0;
	}
	size_t unlink_range(Node* first, Node* last){
		size_t range_size = 0;
		for (Node *trav = first; trav != last; trav = trav->next){
			range_size++;
		}
		if (range_size == size_ || (first == first_ && last == 0)){
			first_ = last_ = 0;
		}
		else if (first == first_){
			first_ = last;
			last->prev->next = 0;
			first_->prev = 0;
		}
		else if (last == 0){
			last_ = first->prev;
			last_->next = 0;
		}
		else {
			first->prev->next = last;
			last->prev->next = 0;
			last->prev = first->prev;
		}
		first->prev = 0;
		size_ -= range_size;
		return range_size;
	}

// MERGE SORT UTILS ###########################################################
	Node *split_list(Node *first){
		if (first->next != 0){
			for (Node *fast = first; fast != 0; fast = fast->next){
				if (fast && fast->next){
					fast = fast->next;
					first = first->next;
				}
		}}
		if (first->prev)
			first->prev->next = 0;
		return first;
	}
	template <typename Comp>
	Node *sort_merge(Node *a, Node *c, Comp comp){
		if (!a) {last_ = c; return c;}
		if (!c) {last_ = a; return a;}
		if (comp(a->value, c->value)){
			a->next = sort_merge(a->next,c, comp);
			a->next->prev = a;
			a->prev = 0;
			return a;
		}else{
			c->next = sort_merge(a,c->next, comp);
			c->next->prev = c;
			c->prev = 0;
			return c;
		}
	}
	template <typename Comp>
	void mergesort(Node **first, Comp comp){
		if (!*first || !(*first)->next)
			return ;
		Node *middle = split_list(*first);
		mergesort(first, comp);
		mergesort(&middle, comp);
		*first = sort_merge(*first, middle, comp);
	}
};
} // namespace ft

template <class T>
bool operator== (const ft::list<T>& lhs, const ft::list<T>& rhs){
	if (lhs.size() != rhs.size())
		return false;
	typename ft::list<T>::const_iterator l_it = lhs.begin();// #########################   WHY TYPENAME?
	typename ft::list<T>::const_iterator r_it = rhs.begin();
	while (l_it != lhs.end() && r_it != rhs.end()) {
		if (*l_it != *r_it){
			return false;
		}
		l_it++;
		r_it++;
	}
	return true;
}
template <class T>
bool operator!= (const ft::list<T>& lhs, const ft::list<T>& rhs){
	return !(lhs == rhs);
}
template <class T>
bool operator<  (const ft::list<T>& lhs, const ft::list<T>& rhs){
	typename ft::list<T>::const_iterator l_it = lhs.begin();// #########################   WHY TYPENAME?
	typename ft::list<T>::const_iterator r_it = rhs.begin();
	while (l_it != lhs.end() && r_it != rhs.end()) {
		if (*l_it < *r_it)
			return true;
		if (*l_it > *r_it)
			return false;
		l_it++;
		r_it++;
	}
	return false;
}
template <class T>
bool operator<= (const ft::list<T>& lhs, const ft::list<T>& rhs){
	return !(rhs < lhs);
}
template <class T>
bool operator>  (const ft::list<T>& lhs, const ft::list<T>& rhs){
	return rhs < lhs;
}
template <class T>
bool operator>= (const ft::list<T>& lhs, const ft::list<T>& rhs){
	return !(lhs < rhs);
}
template <class T>
void swap(ft::list<T> &a, ft::list<T> &b){
	a.swap(b);
}


#endif
