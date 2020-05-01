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
		void swap(Node &b){
			char buffer[sizeof(T)];
			memcpy(buffer, &b.value, sizeof(T));
			memcpy(reinterpret_cast<char *>(&b.value), &value,   sizeof(T));
			memcpy(reinterpret_cast<char *>(&value),   buffer, sizeof(T));
		}

	};

	Node*	d_first;
	Node*	d_last;
	size_t	d_size;

public:
	friend	void swap(list &a, list &b){
		char buffer[sizeof(ft::list<T>)];
		memcpy(buffer, &b, sizeof(ft::list<T>));
		memcpy(reinterpret_cast<char *>(&b), &a,   sizeof(ft::list<T>));
		memcpy(reinterpret_cast<char *>(&a),   buffer, sizeof(ft::list<T>));
	}
	class	bidirectional_iterator;
	class	reverse_iterator;
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
	list (InputIterator first, InputIterator last):d_first(0), d_last(0), d_size(0)
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
			list tmp(n, val);
			swap(tmp);
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
	void swap(list &other){
		char buffer[sizeof(list)];
		memcpy(buffer, &other, sizeof(list));
		memcpy(reinterpret_cast<char *>(&other), this,   sizeof(list));
		memcpy(reinterpret_cast<char *>(this),   buffer, sizeof(list));
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
	reverse_iterator	rbegin() {return reverse_iterator(d_last, d_first);}
	const_reverse_iterator rbegin() const {return reverse_iterator(d_last, d_first);}
	reverse_iterator 	rend() {return reverse_iterator(0, d_first);}
	const_reverse_iterator rend() const {return reverse_iterator(0, d_first);}

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
			d_first = d_last = toAdd;
		}
		else if (position.base() == d_first){
			toAdd = new Node(0, d_first, val);
			d_first->prev = toAdd;
			d_first = toAdd;
		}
		else if (!position.base()){
			toAdd = new Node(d_last, 0, val);
			d_last->next = toAdd;
			d_last = toAdd;
		}
		else {
			toAdd = new Node(position.base()->prev, position.base(), val);
			position.base()->prev->next = toAdd;
			position.base()->prev = toAdd;
		}
		d_size++;
		return iterator(toAdd, d_last);
	}
	void			insert (iterator position, size_type n, const T& val){
		Node *prev;
		size_t i = 0;
		if (position.base() == d_first){
			prev = d_first = new Node(0, d_first, val);
			i++;
		}
		else if (position.base() == 0)
			prev = d_last;
		else
			prev = position.base()->prev;
		Node *toAdd;
		while (i++ < n)
		{
			toAdd = new Node(prev, 0, val);
			prev->next = toAdd;
			prev = toAdd;
		}
		if (position.base() == 0)
			d_last = toAdd;
		else
			toAdd->next = position.base();
		d_size += n;
	}
	template <class InputIterator>
	void			insert (iterator position, InputIterator first, InputIterator last){
		Node *prev;
		if (position.base() == d_first)
		{
			prev = d_first = new Node(0, d_first, *first);
			first++;
			d_size++;
		}
		else if (position.base() == 0)
			prev = d_last;
		else
			prev = position.base()->prev;
		Node *toAdd;
		while (first != last){
			toAdd = new Node(prev, 0, *first);
			prev->next = toAdd;
			prev = toAdd;
			first++;
			d_size++;
		}
		if (position.base() == 0)
			d_last = toAdd;
		else
			toAdd->next = position.base();
	}
//################################ ERASE ######################################
	iterator 		erase(iterator position){
		if (position == 0)
			return position;
		iterator ret = position;
		ret++;
		unlink_node(position.base());
		delete position.base();
		return ret;
	}
	iterator 		erase(iterator first, iterator last){
		iterator toDel;
		unlink_range(first.base(), last.base());
		while (first != 0 && first != last){
			toDel = first;
			first++;
			delete toDel.base();
		}
		return last;
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
						Node *toDel = d_last;
						unlink_node(d_last);
						delete toDel;
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
						Node *toDel = d_first;
						unlink_node(d_first);
						delete toDel;
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
		if (x.empty())
			return ;
		if (position.base() == d_first){
			d_first->prev = x.d_last;
			x.d_last->next = d_first;
			d_first = x.d_first;
		}else if (position.base() == 0){
			d_last->next = x.d_first;
			x.d_first->prev = d_last;
			d_last = x.d_last;
		}else {
			position.base()->prev->next = x.d_first;
			x.d_first->prev = position.base()->prev;
			position.base()->prev = x.d_last;
			x.d_last->next = position.base();
		}
		d_size += x.d_size;
		x.d_first = x.d_last = 0;
		x.d_size = 0;
	}
	void	splice (iterator position, list& x, iterator i){ // remove from x
		x.unlink_node(i.base());
		//--------- INSERT-----------
		if (empty()){
			d_first = d_last = i.base();
		}else if(position.base() == d_first){
			d_first->prev = i.base();
			i.base()->next = d_first;
			d_first = i.base();
		}else if (position.base() == 0){
			d_last->next = i.base();
			i.base()->prev = d_last;
			d_last = i.base();
		}else {
			i.base()->next = position.base();
			i.base()->prev = position.base()->prev;
			i.base()->prev->next = i.base();
			i.base()->next->prev = i.base();
		}
		d_size++;
	}
	void	splice (iterator position, list& x, iterator first, iterator last){
		if (!x.d_first || first == last)
			return ;
		Node *nlast = (last.base()) ? last.base()->prev : x.d_last;
		d_size += x.unlink_range(first.base(), last.base());
		if (empty()){
			d_first = first.base();
			d_last = nlast;
		}else if(position.base() == d_first){
			d_first->prev = nlast;
			nlast->next = d_first;
			d_first = first.base();
		}else if (position.base() == 0){
			d_last->next = first.base();
			first.base()->prev = d_last;
			d_last = nlast;
		}else {
			position.base()->prev->next = first.base();
			first.base()->prev = position.base()->prev;
			position.base()->prev = nlast;
			last.base()->next = position.base();
		}
	}

//################################ REMOVE ######################################
	void	remove (const T& val){
		iterator it = d_first;
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
		iterator it = d_first;
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
		for (Node *it1 = d_first; it1->next != 0; it1 = it1->next)
		{
			it2 = it1->next;
			while (it2 != 0 && *it2 == it1->value)
				it2 = erase(it2);
		}
	}
	template <class BinaryPredicate>
	void	unique (BinaryPredicate binary_pred){
		iterator it2;
		for (Node *it1 = d_first; it1 != 0; it1 = it1->next)
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
		iterator a(d_first);
		iterator b(x.d_first);
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
			d_last->next = x.d_first;
			x.d_first->prev = d_last;
		}
		x.d_first = x.d_last = 0;
		x.d_size = 0;
	}
	template <class Compare>
  	void	merge (list& x, Compare comp){
		iterator a(d_first);
		iterator b(x.d_first);
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
			d_last->next = x.d_first;
			x.d_first->prev = d_last;
		}
		x.d_first = x.d_last = 0;
		x.d_size = 0;
	}
//############################## SORT ##########################################
	void	sort(){
		if (d_size < 2)
			return ;
		mergesort(&d_first, std::less<value_type>());
	}

	template <class Compare>
	void	sort (Compare comp){
		if (d_size < 2)
			return ;
		mergesort(&d_first, comp);
	}
//############################## REVERSE #######################################
	void	reverse(){
		iterator front = d_first;
		iterator back = d_last;
		while (front != back){
			std::swap(*front, *back);
			front++;
			if (front == back)
				break ;
			back--;
		}
	}
//  ITERATOR ##################################################################
	class bidirectional_iterator
	{
	protected:
		Node* d_node;
		Node* d_tail;
	public:
		bidirectional_iterator(Node *node = 0, Node *last = 0):d_node(node), d_tail(0){}
		bidirectional_iterator(bidirectional_iterator const &cpy):d_node(cpy.d_node), d_tail(cpy.d_tail){}
		~bidirectional_iterator(){}
		bidirectional_iterator& operator=(bidirectional_iterator const &cpy){
			d_node = cpy.d_node;
			d_tail = cpy.d_tail;
			return *this;
		}
		bidirectional_iterator& operator++(void){
			if (d_node)
				d_node = d_node->next;
			else
				d_node = d_tail;
			return *this;
		}
		bidirectional_iterator operator++(int){
			bidirectional_iterator old(d_node);
			if (d_node)
				d_node = d_node->next;
			else
				d_node = d_tail;
			return old;
		}
		bidirectional_iterator& operator--(void){
			if (d_node)
				d_node = d_node->prev;
			else
				d_node = d_tail;
			return *this;
		}
		bidirectional_iterator operator--(int){
			bidirectional_iterator old(d_node);
			if (d_node)
				d_node = d_node->prev;
			else
				d_node = d_tail;
			return old;
		}
		Node *base(){return d_node;}
		void swap(bidirectional_iterator &other){
			char buffer[sizeof(bidirectional_iterator)];
			memcpy(buffer, &other, sizeof(bidirectional_iterator));
			memcpy(reinterpret_cast<char *>(&other), this,   sizeof(bidirectional_iterator));
			memcpy(reinterpret_cast<char *>(this),   buffer, sizeof(bidirectional_iterator));
		}
		T& 	operator*(void) const {return d_node->value;}
		T* 	operator->(void) const {return &(d_node->value);}
		bool operator!=(bidirectional_iterator const &other) const {return d_node != other.d_node;}
		bool operator==(bidirectional_iterator const &other) const {return d_node == other.d_node;}
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

protected:
	void unlink_node(Node* position){
		if (!position)
			return ;
		d_size--;
		if (d_size < 1){
			d_first = d_last = 0;
		}
		else if (position == d_first){
			d_first = d_first->next;
			d_first->prev = 0;
		}
		else if (position == d_last){
			d_last = d_last->prev;
			d_last->next = 0;
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
		if (range_size == d_size || (first == d_first && last == 0)){
			d_first = d_last = 0;
		}
		else if (first == d_first){
			d_first = last;
			last->prev->next = 0;
			d_first->prev = 0;
		}
		else if (last == 0){
			d_last = first->prev;
			d_last->next = 0;
		}
		else {
			first->prev->next = last;
			last->prev->next = 0;
			last->prev = first->prev;
		}
		first->prev = 0;
		d_size -= range_size;
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
		if (!a) {d_last = c; return c;}
		if (!c) {d_last = a; return a;}
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
template <class InsertIterator>
void advance(InsertIterator &it, size_t n){
	while (n--)
		it++;
}


// template <class T>
// void swap(ft::list<T> &a, ft::list<T> &b){
// 	char buffer[sizeof(ft::list<T>)];
// 	memcpy(buffer, &b, sizeof(ft::list<T>));
// 	memcpy(reinterpret_cast<char *>(&b), &a,   sizeof(ft::list<T>));
// 	memcpy(reinterpret_cast<char *>(&a),   buffer, sizeof(ft::list<T>));
// }

#endif
