#ifndef LIST_HPP
# define LIST_HPP

# include <iostream>
# include <string>

namespace ft
{
	template <class T> class list;
}

template <class T>
class ft::list
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

	Node*	d_first;
	Node*	d_last;
	size_t	d_size;

// move to friend function instead
	void swap(list &other){
		char buffer[sizeof(list)];
		memcpy(buffer, &other, sizeof(list));
		memcpy(reinterpret_cast<char *>(&other), this,   sizeof(list));
		memcpy(reinterpret_cast<char *>(this),   buffer, sizeof(list));
	}
public:
	class bidirectional_iterator;
	class reverse_iterator;

// TYPEDEFS ####################################################################
	typedef T								value_type;
	typedef value_type&						reference;
	typedef const value_type&				const_reference;
	typedef value_type*						pointer;
	typedef const value_type*				const_pointer;
	typedef bidirectional_iterator			iterator;
	typedef const bidirectional_iterator	const_iterator;
	typedef reverse_iterator				reverse_iterator;
	typedef const reverse_iterator			const_reverse_iterator;
	typedef size_t							size_type;
	typedef ptrdiff_t						difference_type;
//  ITERATOR ##################################################################
	class bidirectional_iterator
	{
	public:
		bidirectional_iterator(Node *node = 0, Node *last = 0):d_node(node), d_tail(0){}
		bidirectional_iterator(bidirectional_iterator const &cpy):d_node(cpy.d_node), d_tail(cpy.d_tail){}
		virtual ~bidirectional_iterator(){}
		virtual bidirectional_iterator& operator=(bidirectional_iterator const &cpy){
			d_node = cpy.d_node;
			d_tail = cpy.d_tail;
			return *this;
		}
		virtual bidirectional_iterator& operator++(void){
			if (d_node)
				d_node = d_node->next;
			else
				d_node = d_tail;
			return *this;
		}
		virtual bidirectional_iterator operator++(int){
			bidirectional_iterator old(d_node);
			if (d_node)
				d_node = d_node->next;
			else
				d_node = d_tail;
			return old;
		}
		virtual bidirectional_iterator& operator--(void){
			if (d_node)
				d_node = d_node->prev;
			else
				d_node = d_tail;
			return *this;
		}
		virtual bidirectional_iterator operator--(int){
			bidirectional_iterator old(d_node);
			if (d_node)
				d_node = d_node->prev;
			else
				d_node = d_tail;
			return old;
		}
		T& 	operator*(void) const {return d_node->value;}
		T* 	operator->(void) const {return &(d_node->value);}
		bool operator!=(bidirectional_iterator const &other) const {return d_node != other.d_node;}
		bool operator==(bidirectional_iterator const &other) const {return d_node == other.d_node;}
	// protected:
		Node* d_node;
		Node* d_tail;
	};
	class reverse_iterator
	{
		bidirectional_iterator d_base;
	public:
		reverse_iterator(Node *node = 0, Node *last = 0):d_base(node, last){}
		explicit reverse_iterator (bidirectional_iterator it);
		template <class Iter>
		// reverse_iterator (const reverse_iterator<Iter>& rev_it);

		reverse_iterator& operator=(reverse_iterator const &x){d_base = x.d_base; return *this;}
		reverse_iterator operator++(void){this->iterator::operator--();}
		reverse_iterator operator++(int){this->iterator::operator--(1);}
		reverse_iterator operator--(void){this->iterator::operator++();}
		reverse_iterator operator--(int){this->iterator::operator++(1);}

		bidirectional_iterator base() const {return bidirectional_iterator(d_base);}
		reference operator*(){return *d_base;}
		pointer operator->() const {
			return &(*d_base);
		}
	};

// CONSTRAINTS #################################################################

// ############################ CONSTRUCTORS ###################################
	explicit list():d_first(0), d_last(0), d_size(0){}
	explicit list(size_t n, const T& val = T()):d_first(0), d_last(0),d_size(n){
		if (n) {
			d_first = new Node(0, 0, val);
			Node *toAdd;
			Node *prev = d_first;
			while (--n)
			{
				toAdd = new Node(prev, 0, val);
				prev->next = toAdd;
				prev = toAdd;
			}
			d_last = prev;
		}
	}
	template <class InputIterator>
	list (InputIterator first, InputIterator last):d_first(0), d_last(0),d_size(0)
	{
		if (first != last) {
			d_size = 1;
			d_first = new Node(0, 0, *first);
			Node *toAdd;
			Node *prev = d_first;
			for (first = ++first; first != last; first++)
			{
				toAdd = new Node(prev, 0, *first);
				prev->next = toAdd;
				prev = toAdd;
				d_size++;
			}
			d_last = prev;
		}
	}
	list(list const &cpy):d_first(0), d_last(0), d_size(cpy.d_size)
	{
		if (d_size)
		{
			d_first = new Node(0, 0, cpy.d_first->value);
			Node *toAdd;
			Node *prev = d_first;
			Node *ctrav = cpy.d_first->next;
			while (ctrav)
			{
				toAdd = new Node(prev, 0, ctrav->value);
				prev->next = toAdd;
				prev = toAdd;
				ctrav = ctrav->next;
			}
			d_last = prev;
		}
	}
	~list(){
		Node *prev;
		while (d_first && d_size)
		{
			prev = d_first;
			d_first = d_first->next;
			delete prev;
		}
		d_first = d_last = 0;
		d_size = 0;
	}

	list &operator=(list const &x){
		list cpy(x);
		swap(cpy);
		return *this;
		// cpy is destructed
	}
//############################# MEMBER FUNCTIONS ###############################
	size_type		size() const {return d_size;}
	size_type		max_size() const {return 768614336404564650;} // ?
	bool			empty() const {return !d_first;} // return first == 0}
	void 			resize(size_t n, T val = T())
	{
		Node *trav;
		if (!n)
			clear();
		else if (empty()){
			list ret(n, val);
			d_first = ret.d_first;
			d_last = ret.d_last;
			d_size = ret.d_size;
			ret.d_first = 0;
		}else if (n < d_size)
		{
			trav = d_first;
			d_size = n;
			while (--n > 0)
				trav = trav->next;
			d_last = trav;
			if (trav && trav->next){
				trav = trav->next;
				Node *del = trav;
				while (trav != 0){
					trav = trav->next;
					delete del;
					del = trav;
				}}
			d_last->next = 0;
		}
		else if (n > d_size)
		{
			while (d_size++ < n)
			{
				trav = d_last;
				d_last = new Node(d_last, 0, val);
				trav->next = d_last;
			}
		}
	}
//############################## FOR ITERATOR ##################################
	reference			front() {return d_first->value;} //Calling this function on an empty container causes undefined behavior.
	const_reference		front() const {return d_first->value;}
	reference			back() {return d_last->value;}
	const_reference		back() const  {return d_last->value;}

	iterator			begin() {return iterator(d_first, d_last);}
	const_iterator		begin() const {return iterator(d_first, d_last);}
	iterator			end() {return iterator(0, d_last);}
	const_iterator		end() const {return iterator(0, d_last);}
	reverse_iterator 	rbegin() {return iterator(d_last, d_first);}
	const_reverse_iterator rbegin() const {return iterator(d_last, d_first);}
	reverse_iterator 	rend() {return iterator(0, d_first);}
	const_reverse_iterator rend() const {return iterator(0, d_first);}

//################################ ASSIGN ######################################
	template 		<class InputIterator>
	void 			assign (InputIterator first, InputIterator last){
		this->clear();
		list ret(first, last);
		d_first = ret.d_first;
		d_last = ret.d_last;
		d_size = ret.d_size;
		ret.d_first = 0;
	}
	void 			assign (size_t n, const T& val){
		this->clear();
		list ret(n, val);
		d_first = ret.d_first;
		d_last = ret.d_last;
		d_size = ret.d_size;
		ret.d_first = 0;
	}
//################################ INSERT ######################################
	iterator		insert (iterator position, const T& val){
		Node *toAdd;
		if (this->empty()) // EVEN POSSIBLE ?
		{
			toAdd = new Node(0, 0, val);
			d_first = d_last = toAdd;
		}
		else if (position.d_node == d_first){
			toAdd = new Node(0, d_first, val);
			d_first->prev = toAdd;
			d_first = toAdd;
		}
		else if (!position.d_node){
			toAdd = new Node(d_last, 0, val);
			d_last->next = toAdd;
			d_last = toAdd;
		}
		else {
			toAdd = new Node(position.d_node->prev, position.d_node, val);
			position.d_node->prev->next = toAdd;
			position.d_node->prev = toAdd;
		}
		d_size++;
		return iterator(toAdd, d_last);
	}
	void			insert (iterator position, size_type n, const T& val){
		Node *prev;
		size_t i = 0;
		if (position.d_node == d_first){
			prev = d_first = new Node(0, d_first, val);
			i++;
		}
		else if (position.d_node == 0)
			prev = d_last;
		else
			prev = position.d_node->prev;
		Node *toAdd;
		while (i++ < n)
		{
			toAdd = new Node(prev, 0, val);
			prev->next = toAdd;
			prev = toAdd;
		}
		if (position.d_node == 0)
			d_last = toAdd;
		else
			toAdd->next = position.d_node;
		d_size += n;
	}
	template <class InputIterator>
	void			insert (iterator position, InputIterator first, InputIterator last)
	{
		Node *prev;
		if (position.d_node == d_first)
		{
			prev = d_first = new Node(0, d_first, *first);
			first++;
			d_size++;
		}
		else if (position.d_node == 0)
			prev = d_last;
		else
			prev = position.d_node->prev;
		Node *toAdd;
		while (first != last)
		{
			toAdd = new Node(prev, 0, *first);
			prev->next = toAdd;
			prev = toAdd;
			first++;
			d_size++;
		}
		if (position.d_node == 0)
			d_last = toAdd;
		else
			toAdd->next = position.d_node;
	}
//################################ ERASE ######################################
	iterator 		erase(iterator position) {
		if (d_size == 1){
			d_first = d_last = 0;
		}
		else if (position.d_node == d_first){
			d_first = d_first->next;
			d_first->prev = 0;
		}
		else if (position.d_node == d_last){
			d_last = d_last->prev;
			d_last->next = 0;
		}
		else {
			position.d_node->prev->next = position.d_node->next;
			position.d_node->next->prev = position.d_node->prev;
		}
		d_size--;
		iterator ret(position.d_node->next, d_last);
		delete position.d_node;
		return ret;
	}
	iterator 		erase(iterator first, iterator last){
		if (first == d_first && last.d_node == 0){
			clear();
		}
		if (first == d_first){
			d_first = last.d_node;
			d_first->prev = 0;
		}
		else if (last.d_node == 0){
			d_last = first.d_node->prev;
			d_last->next = 0;
		}
		else{
			first.d_node->prev->next = last.d_node;
			last.d_node->prev = first.d_node->prev;
		}
		while (first != last){
			delete first.d_node;
			first++;
		}
		return (last.d_node) ? iterator(last.d_node->next, d_last) : iterator(0, d_last);
	}
//############################## PUSH & POP ###################################
	void			push_back(const T& val){
						d_last = new Node(d_last, 0, val);
						d_size++;
						if (d_last->prev)
							d_last->prev->next = d_last;
						else
							d_first = d_last;
					}
	void			pop_back() {
						if (d_size > 1){
							d_last = d_last->prev;
							delete d_last->next;
							d_size--;
							d_last->next = 0;
						}
						else {
							delete d_last;
							d_last = d_first = 0;
							d_size = 0;
						}
					}
	void			push_front(const T& val) {
						d_first = new Node(0, d_first, val);
						d_size++;
						if (d_first->next)
							d_first->next->prev = d_first;
						else
							d_last = d_first;
					}
	void			pop_front() {
						if (d_size > 1) {
							d_first = d_first->next;
							delete d_first->prev;
							d_size--;
							d_first->prev = 0;
						}
						else {
							delete d_first;
							d_first = d_last = 0;
							d_size = 0;
						}
					}
	void			clear() {
						Node *prev;
						while (d_first)
						{
							prev = d_first;
							d_first = d_first->next;
							delete prev;
						}
						d_first = d_last = 0;
						d_size = 0;
					} // ~
//################################ SPLICE ######################################
	void	splice (iterator position, list& x){
		if (position.d_node == d_first){
			d_first->prev = x.d_last;
			x.d_last->next = d_first;
			d_first = x.d_first; // ADD d_first->prev = 0; ?
		}else if (position.d_node){
			position.d_node->prev->next = x.d_first;
			position.d_node->prev = x.d_last;
			x.d_last->next = position.d_node;
		}else {
			d_last->next = x.d_first;
			x.d_first->prev = d_last;
			d_last = x.d_last;
		}
		d_size += x.d_size;
		x.d_first = x.d_last = x.d_size = 0;
	}
	void	splice (iterator position, list& x, iterator i){ // remove from x
		//--- CHECK IF i IS PLACED IN CRITICAL POSITION ---
		if (i.d_node == 0 && i.d_node == x.d_first){
			x.d_last = x.d_last->prev;
			x.d_last->next = 0;
		}else if (i.d_node == 0){
			x.d_last = x.d_last->prev;
			x.d_last->next = 0;
		}
		else if (i.d_node == x.d_first){
			x.d_first = x.d_first->next;
			x.d_first->prev = 0;
		}
		else{
			i.d_node->prev->next = i.d_node->next;
			i.d_node->next->prev = i.d_node->prev;
		}
		//--------- INSERT-----------
		if(position.d_node == d_first){
			d_first->prev = i.d_node;
			i.d_node->prev = 0;
			i.d_node->next = d_first;
			d_first = i.d_node;
		}else if (position.d_node){
			position.d_node->prev->next = x.d_first;
			position.d_node->prev = x.d_last;
			x.d_last->next = position.d_node;
		}else {
			d_last->next = i.d_node;
			i.d_node->next = 0;
			i.d_node->prev = d_last;
			d_last = i.d_node;
		}
		x.d_size--;
		d_size++;
	}
	void	splice (iterator position, list& x, iterator itf, iterator ifl){
		size_t change = 0;
		//--- CHECK IF i IS PLACED IN CRITICAL POSITION ---
		for (iterator it = itf; it != ifl; it++)
			change++;
		if (ifl.d_node == 0 && itf.d_node == x.d_first)
			x.d_first = x.d_last = 0;
		else if (ifl.d_node == 0){
			x.d_last = itf.d_node->prev;
			x.d_last->next = 0;
		}
		else if (itf.d_node == x.d_first){
			x.d_first = ifl.d_node;
			x.d_first->prev = 0;
		}
		else {
			itf.d_node->prev->next = ifl.d_node;
			ifl.d_node->prev = itf.d_node->prev;
		}
		//--------- INSERT-----------
		if(position.d_node == d_first){
			ifl.d_node->next = d_first;
			d_first = itf.d_node;
			d_first->prev = 0;
		}else if (position.d_node){
			position.d_node->next->prev = ifl.d_node;
			ifl.d_node->next = position.d_node;
		}else {
			d_last->next = itf.d_node;
			itf.d_node->prev = d_last;
			d_last = ifl.d_node;
			d_last->next = 0;
		}
		d_size += change;
		x.d_size -= change;
	}
//################################ REMOVE ######################################
	void	remove (const T& val){
		Node *it = d_first;
		Node *toDel;
		while (it != 0)
		{
			if (it->value == val)
			{
				toDel = it;
				d_size--;
				if (d_size == 0)
					d_first = d_last = 0;
				else if (it == d_first){
					d_first = it->next;
					d_first->prev = 0;
				}else if (it == d_last){
					d_last = it->prev;
					d_last->next = 0;
				} else {
					it->prev->next = it->next;
					it->next->prev = it->prev;
				}
				it = it->next;
				delete toDel;
			}
			else
				it = it->next;
		}
	}
	template <class Predicate>
	void	remove_if (Predicate pred){
		Node *it = d_first;
		Node *toDel;
		while (it != 0)
		{
			if (pred(it->value)){
				toDel = it;
				d_size--;
				if (d_size == 0)
					d_first = d_last = 0;
				else if (it == d_first){
					d_first = it->next;
					d_first->prev = 0;
				}else if (it == d_last){
					d_last = it->prev;
					d_last->next = 0;
				}else {
					it->prev->next = it->next;
					it->next->prev = it->prev;
				}
				it = it->next;
				delete toDel;
			}
			else
				it = it->next;
		}
	}
//################################ UNIQUE ######################################
	void	unique(){
		T val;
		Node *it2;
		Node *toDel = 0;
		for (Node *it1 = d_first; it1 != 0; it1 = it1->next)
		{
			val = it1->value;
			Node *it2 = d_first->next;
			while (it2 != 0)
			{
				if (it2->value == val)
				{
					toDel = it2;
					d_size--;
					if (d_size == 0)
						d_first = d_last = 0;
					else if (it2 == d_first){
						d_first = it2->next;
						d_first->prev = 0;
					}if (it2 == d_last){
						d_last = it2->prev;
						d_last->next = 0;
					}
					it2 = it2->next;
					delete toDel;
				}
				else
					it2 = it2->next;
			}
		}
	}
	// template <class BinaryPredicate>
	// void	unique (BinaryPredicate binary_pred){
	// }
//################################ MERGE ######################################
// A subtlety is that merge doesn't alter the list if the list itself is used as
//argument: object.merge(object) won't change the list `object'. !!!!!!!

	void	merge (list& x){ //sorted merge
		iterator it1 = d_first;
		iterator it2 = x.d_first;
		while (*it1 != 0)
		{
			if (*it1 > *it2)
				this->splice(it1, x, it2);
			else
				it1++;
		}
		if (!x.empty())
		{
			d_last->next = x.d_first;
			x.d_first->prev = d_last;
			d_last = x.d_last;
			d_size += x.d_size;
			x.d_first = x.d_last = x.d_size = 0;
		}
	}
	template <class Compare>
  	void	merge (list& x, Compare comp){
		iterator it1 = d_first;
		iterator it2 = x.d_first;
		while (*it1 != 0)
		{
			if (comp(*it1, *it2) < 0) // ?
				this->splice(it1, x, it2);
			else
				it1++;
		}
		if (!x.empty())
		{
			d_last->next = x.d_first;
			x.d_first->prev = d_last;
			d_last = x.d_last;
			d_size += x.d_size;
			x.d_first = x.d_last = x.d_size = 0;
		}
	}
	//############################## SORT #####################################
	void	sort(){
		if (d_size < 2)
			return ;

	}

	template <class Compare>
	void	sort (Compare comp){
		if (d_size < 2)
			return ;

	}
	//############################## REVERSE ##################################
	void	reverse(){
		Node *temp = d_first;
		d_first = d_last;
		d_last = temp;
	}
};

// friend
// template <class T>
//    void swap (ft::list<T>& x, ft::list<T>& y){
// 	  size_t temp_size =
//   }

#endif
