#ifndef LIST_HPP
# define LIST_HPP

# include <iostream>
# include <string>

namespace ft
{
	template <class T>
	class list;
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

	Node	*first;
	Node	*last;
	size_t	lsize;
public:
//  ITERATOR ##################################################################
	class iterator
	{
	public:
		iterator(Node *node):curr(node), tail(0){}
		iterator(Node *node, Node *last):curr(node), tail(last){}
		iterator(iterator const &cpy):curr(cpy.curr), tail(cpy.tail){}
		virtual ~iterator(){}
		virtual iterator& operator=(Node *node){curr = node; tail = 0; return *this;}
		virtual iterator& operator=(iterator const &cpy){curr = cpy.curr; return *this;}
		virtual iterator& operator++(void){
			if (curr)
				curr = curr->next;
			else
				curr = tail;
			return *this;
		}
		virtual iterator operator++(int){
			Node *old = curr;
			if (curr)
				curr = curr->next;
			else
				curr = tail;
			return old;
		}
		virtual iterator& operator--(void){
			if (curr)
				curr = curr->prev;
			else
				curr = tail;
			return *this;
		}
		virtual iterator operator--(int){
			Node *old = curr;
			if (curr)
				curr = curr->prev;
			else
				curr = tail;
			return old;
		}
		T& 	operator*(void) const {return curr->value;}
		// T& 	operator->(void) const {return curr->value;}
		bool operator!=(iterator const &other) const {return curr != other.curr;}
		bool operator==(iterator const &other) const {return curr == other.curr;}
	protected:
		Node* curr;
		Node* tail;
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
	explicit list(){first = 0; last = 0; lsize = 0;}
	explicit list(size_t n, const T& val = T()):lsize(n){
		first = new Node(0, 0, val);
		Node *toAdd;
		Node *prev = first;
		for (size_t i = 0; i < n; i++)
		{
			toAdd = new Node(prev, 0, val);
			prev->next = toAdd;
			prev = toAdd;
		}
		last = toAdd;
		lsize = n;
	}
	// template <class InputIterator>
	list (iterator o_first, iterator o_last)
	{
		lsize = 1;
		first = new Node(0, 0, *o_first);
		Node *toAdd;
		Node *prev = first;
		for (o_first = ++o_first; o_first != o_last; o_first++)
		{
			toAdd = new Node(prev, 0, *o_first);
			prev->next = toAdd;
			prev = toAdd;
			lsize++;
		}
	}
	list(list const &cpy):lsize(cpy.lsize)
	{
		first = new Node(0, 0, cpy.first->value);
		Node *toAdd;
		Node *prev = first;
		Node *ctrav = cpy.first->next;
		while (ctrav)
		{
			toAdd = new Node(prev, 0, ctrav->value);
			prev->next = toAdd;
			prev = toAdd;
			ctrav = ctrav->next;
		}
		last = toAdd;
	}
	~list(){
		Node *prev;
		while (first && lsize)
		{
			prev = first;
			first = first->next;
			delete prev;
		}
		first = last = 0;
	}

	// list &operator=(list const &cpy){ //deep ??
	// 	if (lsize && first)
	// 		this->clear();
	// 	first = cpy.first;
	// 	last = cpy.last;
	// 	lsize = cpy.lsize;
	// 	return *this;
	// }

	list &operator=(list const &cpy){ //deep ??
		if (lsize && first)
			this->clear();
		list *ret = new list(cpy);
		return *ret;
	}
//############################# MEMBER FUNCTIONS ###############################
	size_t			size() const {return lsize;}
	size_t			max_size() const {return 768614336404564650;} // ?
	bool			empty() const {return lsize ? false : true;}// return first == 0}
	void 			resize(size_t n, T val = T())
	{
		Node *trav = first;
		if (this->empty()){
			list ret(n, val);
			first = ret.first;
			last = ret.last;
			lsize = ret.lsize;
			ret.first = 0;
		}else if (n < lsize)
		{
			lsize = n;
			while (--n > 0)
				trav = trav->next;
			last = trav;
			if (trav && trav->next){
			trav = trav->next;
			Node *del = trav;
			while (trav != 0)
			{
				trav = trav->next;
				delete del;
				del = trav;
			}}
			last->next = 0;
		}
		else if (n > lsize)
		{
			while (lsize++ < n)
			{
				trav = last;
				last = new Node(last, 0, val);
				trav->next = last;
			}
			lsize = n;
		}
	}
//############################## FOR ITERATOR ##################################
	T&				front() {return first->value;} //Calling this function on an empty container causes undefined behavior.
	T&				front() const {return first->value;}
	T&				back() {return last->value;}
	T&				back()const  {return last->value;}

	iterator			begin() {return iterator(first, last);}
	const_iterator		begin() const {return iterator(first, last);}
	iterator			end() {return iterator(0, last);} // 0?
	const_iterator		end() const {return iterator(0, last);} // 0?
	reverse_iterator 	rbegin() {return iterator(last, first);}
	const_reverse_iterator rbegin() const {return iterator(last, first);}
	reverse_iterator 	rend() {return iterator(0, first);}
	const_reverse_iterator rend() const {return iterator(0, first);}

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
			first = last = toAdd;
		}
		else if (index >= lsize)
			return ;
		else if (index == 0){
			toAdd = new Node(0, first, val);
			first->prev = toAdd;
			first = toAdd;
		}
		else if (index == lsize - 1){
			toAdd = new Node(last, 0, val);
			last->next = toAdd;
			last = toAdd;
		}
		else{
			Node *trav = first;
			for (int i = 0; i < index; i++)
				trav = trav->next;
			toAdd = new Node(trav->prev, trav, val);
			toAdd->prev->next = toAdd;
			trav->prev = toAdd;
		}
		lsize++;
	}
	iterator		insert (iterator position, const T& val){
		Node *toAdd;
		if (this->empty()) // EVEN POSSIBLE ?
		{
			toAdd = new Node(0, 0, val);
			first = last = toAdd;
		}
		else if (position.curr == first){
			toAdd = new Node(0, first, val);
			first->prev = toAdd;
			first = toAdd;
		}
		else if (!position.curr){
			toAdd = new Node(last, 0, val);
			last->next = toAdd;
			last = toAdd;
		}
		else {
			toAdd = new Node(position.curr->prev, position.curr, val);
			position.curr->prev->next = toAdd;
			position.curr->prev = toAdd;
		}
		lsize++;
	}
	void			insert (iterator position, size_t n, const T& val){
		Node *prev;
		size_t i = 0;
		if (position.curr == first){
			prev = first = new Node(0, first, val);
			i++;
		}
		else if (position.curr == 0)
			prev = last;
		else
			prev = position.curr->prev;
		Node *toAdd;
		while (i++ < n)
		{
			toAdd = new Node(prev, 0, val);
			prev->next = toAdd;
			prev = toAdd;
		}
		if (position.curr == 0)
			last = toAdd;
		else
			toAdd->next = position.curr;
		lsize += n;
	}
	template <class InputIterator>
	void			insert (iterator position, InputIterator ifirst, InputIterator ilast)
	{
		Node *prev;
		if (position.curr == first)
		{
			prev = first = new Node(0, first, *ifirst);
			ifirst++;
			lsize++;
		}
		else if (position.curr == 0)
			prev = last;
		else
			prev = position.curr->prev;
		Node *toAdd;
		while (ifirst != ilast)
		{
			toAdd = new Node(prev, 0, *ifirst);
			prev->next = toAdd;
			prev = toAdd;
			ifirst++;
			lsize++;
		}
		if (position.curr == 0)
			last = toAdd;
		else
			toAdd->next = position.curr;
	}
//################################ ERASE ######################################
	iterator 		erase(iterator position) {
		if (position.curr == first){
			first = first->next;
			first->prev = 0;
		}
		else if (position.curr == last){
			last = last->prev;
			last->next = 0;
		}
		else {
			position.curr->prev->next = position.curr->next;
			position.curr->next->prev = position.curr->prev;
		}
		lsize--;
		delete position.curr;
	}
	iterator 		erase(iterator ifirst, iterator ilast){
		if (ifirst == first && ilast.curr == 0)
			clear();
		else if (ifirst == first){
			first = ilast.curr;
			first->prev = 0;
		}
		else if (ilast.curr == 0){
			last = ifirst.curr->prev;
			last->next = 0;
		}
		else{
			ifirst.curr->prev->next = ilast.curr;
			ilast.curr->prev = ifirst.curr->prev;
		}
		while (ifirst != ilast){
			delete ifirst.curr;
			ifirst++;
		}
	}
//############################## PUSH & POP ###################################
	void			push_back(const T& val){
						last = new Node(last, 0, val);
						lsize++;
						if (last->prev)
							last->prev->next = last;
						else
							first = last;
					}
	void			pop_back() {
						if (last){
							last = last->prev;
							delete last->next;
							lsize--;
							last->next = 0;
					}}//T value = keep; delete keep; return value;}
	void			push_front(const T& val) {
						first = new Node(0, first, val);
						lsize++;
						if (first->next)
							first->next->prev = first;
						else
							last = first;
					}
	void			pop_front() {
						if (first){
							first = first->next;
							delete first->prev;
							lsize--;
							first->prev = 0;
					}}
	void			clear() {
						Node *prev;
						while (first)
						{
							prev = first;
							first = first->next;
							delete prev;
						}
						first = 0;
						last = 0;
						lsize = 0;
					} // ~
//################################ SPLICE ######################################
	void	splice (iterator position, list& x){
		if (position.curr == first){
			first->prev = x.last;
			x.last->next = first;
			first = x.first; // ADD first->prev = 0; ?
		}else if (position.curr){
			position.curr->prev->next = x.first;
			position.curr->prev = x.last;
			x.last->next = position.curr;
		}else {
			last->next = x.first;
			x.first->prev = last;
			last = x.last;
		}
		lsize += x.lsize;
		x.first = x.last = x.lsize = 0;
	}
	void	splice (iterator position, list& x, iterator i){ // remove from x
		//--- CHECK IF i IS PLACED IN CRITICAL POSITION ---
		if (i.curr == 0 && i.curr == x.first){
			x.last = x.last->prev;
			x.last->next = 0;
		}else if (i.curr == 0){
			x.last = x.last->prev;
			x.last->next = 0;
		}
		else if (i.curr == x.first){
			x.first = x.first->next;
			x.first->prev = 0;
		}
		else{
			i.curr->prev->next = i.curr->next;
			i.curr->next->prev = i.curr->prev;
		}
		//--------- INSERT-----------
		if(position.curr == first){
			first->prev = i.curr;
			i.curr->prev = 0;
			i.curr->next = first;
			first = i.curr;
		}else if (position.curr){
			position.curr->prev->next = x.first;
			position.curr->prev = x.last;
			x.last->next = position.curr;
		}else {
			last->next = i.curr;
			i.curr->next = 0;
			i.curr->prev = last;
			last = i.curr;
		}
		x.lsize--;
		lsize++;
	}
	void	splice (iterator position, list& x, iterator ifirst, iterator ilast){
		size_t change = 0;
		//--- CHECK IF i IS PLACED IN CRITICAL POSITION ---
		for (iterator it = ifirst; it != ilast; it++)
			change++;
		if (ilast.curr == 0 && ifirst.curr == x.first)
			x.first = x.last = 0;
		else if (ilast.curr == 0){
			x.last = ifirst.curr->prev;
			x.last->next = 0;
		}
		else if (ifirst.curr == x.first){
			x.first = ilast.curr;
			x.first->prev = 0;
		}
		else {
			ifirst.curr->prev->next = ilast.curr;
			ilast.curr->prev = ifirst.curr->prev;
		}
		//--------- INSERT-----------
		if(position.curr == first){
			ilast.curr->next = first;
			first = ifirst.curr;
			first->prev = 0;
		}else if (position.curr){
			position.curr->next->prev = ilast.curr;
			ilast.curr->next = position.curr;
		}else {
			last->next = ifirst.curr;
			ifirst.curr->prev = last;
			last = ilast.curr;
			last->next = 0;
		}
		lsize += change;
		x.lsize -= change;
	}
//################################ REMOVE ######################################
	void	remove (const T& val){
		Node *it = first;
		Node *toDel;
		while (it != 0)
		{
			if (it->value == val)
			{
				toDel = it;
				lsize--;
				if (lsize == 0)
					first = last = 0;
				else if (it == first){
					first = it->next;
					first->prev = 0;
				}if (it == last){
					last = it->prev;
					last->next = 0;
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
		Node *it = first;
		Node *toDel;
		while (it != 0)
		{
			if (pred(it->value))
			{
				toDel = it;
				lsize--;
				if (lsize == 0)
					first = last = 0;
				else if (it == first){
					first = it->next;
					first->prev = 0;
				}if (it == last){
					last = it->prev;
					last->next = 0;
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
		for (Node *it1 = first; it1 != 0; it1 = it1->next)
		{
			val = it1->value;
			Node *it2 = first->next;
			while (it2 != 0)
			{
				if (it2->value == val)
				{
					toDel = it2;
					lsize--;
					if (lsize == 0)
						first = last = 0;
					else if (it2 == first){
						first = it2->next;
						first->prev = 0;
					}if (it2 == last){
						last = it2->prev;
						last->next = 0;
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
	// 				lsize--;
	// 				if (lsize == 0)
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
		iterator it1 = first;
		iterator it2 = x.first;
		while (*it1 != 0)
		{
			if (*it1 > *it2)
				this->splice(it1, x, it2);
			else
				it1++;
		}
		if (!x.empty())
		{
			last->next = x.first;
			x.first->prev = last;
			last = x.last;
			lsize += x.lsize;
			x.first = x.last = x.lsize = 0;
		}
	}
	template <class Compare>
  	void	merge (list& x, Compare comp){
		iterator it1 = first;
		iterator it2 = x.first;
		while (*it1 != 0)
		{
			if (comp(*it1, *it2) < 0) // ?
				this->splice(it1, x, it2);
			else
				it1++;
		}
		if (!x.empty())
		{
			last->next = x.first;
			x.first->prev = last;
			last = x.last;
			lsize += x.lsize;
			x.first = x.last = x.lsize = 0;
		}
	}
	//############################## SORT #####################################
	void	sort(){
		if (lsize < 2)
			return ;
		for (Node *out = first; out != 0; out = out->next)
		{
			for (Node *in = first; in != 0; in = in->next)
			{
				if (out->value < in->value)
					std::swap(out->value, in->value);
			}
		}
	}

	template <class Compare>
	void	sort (Compare comp){
		if (lsize < 2)
			return ;
		for (Node *out = first; out != 0; out = out->next)
		{
			for (Node *in = first; in != 0; in = in->next)
			{
				if (comp(out->value, in->value))
					std::swap(out->value, in->value);
			}
		}
	}
	//############################## REVERSE ##################################
	void	reverse(){
		iterator front = first;
		iterator back = last;
		if (lsize > 1){
			while (front != back)
			{
				std::swap(*front, *back);
				front++;
				if (front == back)
					break;
				back--;
			}
		}
	}
	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	void print(){
		Node *it = first;
		while (lsize && it != 0){
			std::cout << it->value << ' ';
			it = it->next;
		}
		std::cout << '\n';
	}
};

#endif
