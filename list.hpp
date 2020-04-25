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
		Node(T value = T()):next(0), prev(0), value(value){}
		Node(Node *prev, Node *next, T value):prev(prev), next(next), value(value){}
		Node(Node const &cpy):prev(cpy.prev), next(cpy.next), value(cpy.value){}
		Node		*prev;
		Node		*next;
		T			value;
	};

	Node	*d_first;
	Node	*d_last;
	size_t	d_size;
public:
//  ITERATOR ##################################################################
	class iterator
	{
	public:
		iterator(Node *node = 0, Node *last = 0):d_node(node), d_tail(0){}
		iterator(iterator const &cpy):d_node(cpy.d_node), d_tail(cpy.d_tail){}
		virtual ~iterator(){}
		virtual iterator& operator=(Node *node){d_node = node; d_tail = 0; return *this;}
		virtual iterator& operator=(iterator const &cpy){d_node = cpy.d_node; return *this;}
		virtual iterator& operator++(void){
			if (d_node)
				d_node = d_node->next;
			else
				d_node = d_tail;
			return *this;
		}
		virtual iterator operator++(int){
			Node *old = d_node;
			if (d_node)
				d_node = d_node->next;
			else
				d_node = d_tail;
			return old;
		}
		virtual iterator& operator--(void){
			if (d_node)
				d_node = d_node->prev;
			else
				d_node = d_tail;
			return *this;
		}
		virtual iterator operator--(int){
			Node *old = d_node;
			if (d_node)
				d_node = d_node->prev;
			else
				d_node = d_tail;
			return old;
		}
		T& 	operator*(void) const {return d_node->value;}
		// T& 	operator->(void) const {return d_node->value;}
		bool operator!=(iterator const &other) const {return d_node != other.d_node;}
		bool operator==(iterator const &other) const {return d_node == other.d_node;}
	// protected:
		Node* d_node;
		Node* d_tail;
	};
	class reverse_iterator : public iterator
	{
		reverse_iterator operator++(void){this->iterator::operator--();}
		reverse_iterator operator++(int){this->iterator::operator--(1);}
		reverse_iterator operator--(void){this->iterator::operator++();}
		reverse_iterator operator--(int){this->iterator::operator++(1);}
	};
	typedef const reverse_iterator const_reverse_iterator;
	typedef const iterator const_iterator;

// LIST FUNCTIONS ##############################################################

// ############################ CONSTRUCTORS ###################################
	explicit list():d_first(0), d_last(0), d_size(0){}
	explicit list(size_t n, const T& val = T()):d_size(n), d_first(0), d_last(0){
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
	list (InputIterator first, InputIterator last):d_size(0), d_first(0), d_last(0)
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
	list(list const &cpy):d_size(cpy.d_size), d_first(0), d_last(0)
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

	list &operator=(list const &cpy){
		if (d_size && d_first)
			this->clear();
		list ret(cpy);
		d_size = ret.d_size;
		d_first = ret.d_first;
		d_last = ret.d_last;
		ret.d_first = 0;
		return *this;
	}
//############################# MEMBER FUNCTIONS ###############################
	size_t			size() const {return d_size;}
	size_t			max_size() const {return 768614336404564650;} // ?
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
			while (trav != 0)
			{
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
			d_size = n;
		}
	}
//############################## FOR ITERATOR ##################################
	T&				front() {return d_first->value;} //Calling this function on an empty container causes undefined behavior.
	T&				front() const {return d_first->value;}
	T&				back() {return d_last->value;}
	T&				back()const  {return d_last->value;}

	iterator			begin() {return iterator(d_first, d_last);}
	const_iterator		begin() const {return iterator(d_first, d_last);}
	iterator			end() {return iterator(0, d_last);} // 0?
	const_iterator		end() const {return iterator(0, d_last);} // 0?
	reverse_iterator 	rbegin() {return iterator(d_last, d_first);}
	const_reverse_iterator rbegin() const {return iterator(d_last, d_first);}
	reverse_iterator 	rend() {return iterator(0, d_first);}
	const_reverse_iterator rend() const {return iterator(0, d_first);}

//################################ ASSIGN ######################################
	template 		<class InputIterator>
	void 			assign (InputIterator first, InputIterator last){
		this->clear();
		*this = list(first, last);
	}
	void 			assign (size_t n, const T& val){
		this->clear();
		*this = list(n, val);
	}
//################################ INSERT ######################################
	void			insert(int index, T val){
		Node *toAdd;
		if (this->empty()) {
			toAdd = new Node(0, 0, val);
			d_first = d_last = toAdd;
		}
		else if (index >= d_size)
			return ;
		else if (index == 0){
			toAdd = new Node(0, d_first, val);
			d_first->prev = toAdd;
			d_first = toAdd;
		}
		else if (index == d_size - 1){
			toAdd = new Node(d_last, 0, val);
			d_last->next = toAdd;
			d_last = toAdd;
		}
		else{
			Node *trav = d_first;
			for (int i = 0; i < index; i++)
				trav = trav->next;
			toAdd = new Node(trav->prev, trav, val);
			toAdd->prev->next = toAdd;
			trav->prev = toAdd;
		}
		d_size++;
	}
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
		return iterator(toAdd, dlast);
	}
	void			insert (iterator position, size_t n, const T& val){
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
		if (position.d_node == d_first){
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
		delete position.d_node;
	}
	iterator 		erase(iterator first, iterator last){
		if (first == d_first && last.d_node == 0)
			clear();
		else if (first == d_first){
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
						if (d_last->prev){
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
					}//T value = keep; delete keep; return value;}
	void			push_front(const T& val) {
						d_first = new Node(0, d_first, val);
						d_size++;
						if (d_first->next)
							d_first->next->prev = d_first;
						else
							d_last = d_first;
					}
	void			pop_front() {
						if (d_first->next) {
							d_first = d_first->next;
							delete d_first->prev;
							d_size--;
							d_first->prev = 0;
						}
						else{
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
				}if (it == d_last){
					d_last = it->prev;
					d_last->next = 0;
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
			if (pred(it->value))
			{
				toDel = it;
				d_size--;
				if (d_size == 0)
					d_first = d_last = 0;
				else if (it == d_first){
					d_first = it->next;
					d_first->prev = 0;
				}if (it == d_last){
					d_last = it->prev;
					d_last->next = 0;
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
	// 	T val;
	// 	Node *it2;
	// 	Node *toDel = 0;
	// 	for (Node *it1 = first; it1 != 0; it1 = it1->next)
	// 	{
	// 		val = it1->value;
	// 		Node *it2 = first->next;
	// 		while (it2 != 0)
	// 		{
	// 			if (it2->value == val)
	// 			{
	// 				toDel = it2;
	// 				d_size--;
	// 				if (d_size == 0)
	// 					first = last = 0;
	// 				else if (it2 == first){
	// 					first = it2->next;
	// 					first->prev = 0;
	// 				}if (it2 == last){
	// 					last = it2->prev;
	// 					last->next = 0;
	// 				}
	// 				it2 = it2->next;
	// 				delete toDel;
	// 			}
	// 			else
	// 				it2 = it2->next;
	// 		}
	// 	}
	// }
//################################ MERGE ######################################
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
		for (Node *out = d_first; out != 0; out = out->next)
		{
			for (Node *in = d_first; in != 0; in = in->next)
			{
				if (out->value < in->value)
					std::swap(out->value, in->value);
			}
		}
	}

	template <class Compare>
	void	sort (Compare comp){
		if (d_size < 2)
			return ;
		for (Node *out = d_first; out != 0; out = out->next)
		{
			for (Node *in = d_first; in != 0; in = in->next)
			{
				if (comp(out->value, in->value))
					std::swap(out->value, in->value);
			}
		}
	}
	//############################## REVERSE ##################################
	void	reverse(){
		Node *temp = d_first;
		d_first = d_last;
		d_last = temp;
		// iterator front = d_first;
		// iterator back = last;
		// if (d_size > 1){
		// 	while (front != back)
		// 	{
		// 		std::swap(*front, *back);
		// 		front++;
		// 		if (front == back)
		// 			break;
		// 		back--;
		// 	}
		// }
	}
	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	void print(){
		Node *it = d_first;
		while (d_size && it != 0){
			std::cout << it->value << ' ';
			it = it->next;
		}
		std::cout << '\n';
	}
};

#endif
