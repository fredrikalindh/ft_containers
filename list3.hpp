#ifndef LIST_HPP
# define LIST_HPP

# include <iostream>
# include <string>
# include "ft.hpp"

template <class T>
class ft::List
{
public:
	// using key_type                  = StringT;
    // using mapped_type               = MappedT;
    // using value_type                = std::pair<const key_type, mapped_type>;
    // using char_type                 = typename key_type::value_type;
    // using size_type                 = std::size_t;
    // using allocator_type            = AllocatorT;
    // using reference                 = mapped_type&;
    // using const_reference           = const mapped_type&;
    // using pointer                   = typename std::allocator_traits<allocator_type>::pointer;
    // using const_pointer             = typename std::allocator_traits<allocator_type>::const_pointer;
    // using iterator                  = prefix_tree_iterator<key_type, char_type, mapped_type>;
    // using const_iterator            = prefix_tree_const_iterator<key_type, char_type, mapped_type>;
    // using reverse_iterator          = std::reverse_iterator<iterator>;
    // using const_reverse_iterator    = std::reverse_iterator<const_iterator>;

	using value_type				= 	T;
	// using allocator_type			= 	Allocator; // Not sure if we need?
	using size_type				 	= 	unsigned int; // type (usually std::size_t)
	using difference_type			= 	std::ptrdiff_t; //Signed integer type (usually std::ptrdiff_t)
	// using reference	 				= 	Allocator::reference;
	// using const_reference	 		= 	Allocator::const_reference//	(until C++11)	const value_type&	(since C++11)
	// using pointer	 				=	Allocator::pointer;//	(until C++11)	std::allocator_traits<Allocator>::pointer	(since C++11)
	// using const_pointer	 			=	Allocator::const_pointer;//	(until C++11)	std::allocator_traits<Allocator>::const_pointer	(since C++11)
	using iterator					=	LegacyBidirectionalIterator;
	using const_iterator			=	const LegacyBidirectionalIterator;
	using reverse_iterator			=	std::reverse_iterator<iterator>;
	using const_reverse_iterator	=	std::reverse_iterator<const_iterator>;


	List(){first = 0; last = 0; size = 0;}
	List(int n, T value);
	template <typename FwdIterT>
    prefix_tree(FwdIterT first, FwdIterT last);
	List(List const &cpy) // ------- MAYBE USE ITERATOR :)
	{
		first = new ListElement(*cpy.first);
		last = new ListElement(*cpy.last);

		ListElement *prev = 0;
		ListElement *trav = first;
		ListElement *travcpy = cpy.first;
		while (travcpy != cpy.last)
		{
			trav->prev = prev;
			trav->next = new ListElement(*travcpy.next);
			prev = trav;
			trav = trav->next;
			travcpy = travcpy->next;
		}
		last->prev = prev;
		last->next = 0; // if I initialize like this it's unneccessary
	}
	~List(){
		ListElement *prev = first;
		while (first)
		{
			first = first->next;
			delete prev;
			prev = first;
		}
	}

	List &operator=(List const &cpy);

	unsigned int	size() {return size} // or iterate and find, maybe easier
	unsigned int	max_size(); // ?
	bool			empty() {return size ? false : true;}
	unsigned int	resize(); // ?

	T				front() {return first->value}
	T				back() {return last->value} // or (last->prev)->value?

	ListElement		*begin() {return first}
	ListElement		*rend() {return first}
	ListElement		*end() {return last}
	ListElement		*rbegin() {return last}
	void			assign();
	void			insert(int index, T value);
	void			erase(ListElement del);

	void			push_back(T value) {last = new ListElement(value, last, 0); last->prev->next = last;}
	void			pop_back() {last = last->prev; delete last->next; last->next = 0; }//T value = keep; delete keep; return value;}
	void			push_front(T value) {first = new ListElement(value, 0, first); first->next->prev = first;}
	void			pop_front() {first = first->next; delete first->prev; first->prev = 0;}
	void			clear();

	void			splice();
	void			remove();
	void			remove_if();
	void			unique();
	void			merge();
	void			sort();
	void			reverse();


private:
	ListElement<T>	*first;
	ListElement<T>	*last;
	unsigned int	size;
};

template <class T>
class ListElement
{
public:

private:
	T			value; //	defaults to: allocator<value_type>
	ListElement	*next;
	ListElement	*prev;
};


// template <class T, class Alloc>
// class List
// {
// public:
//
// private:
// 	T		value_type; //	defaults to: allocator<value_type>
// 	Alloc	allocator_type; // for the default allocator: value_type&
// 	//Alloc & reference;
// 	//Alloc & const_reference;
// 	Alloc	*pointer;		//value_type*
// 	Alloc const	*const_pointer;		//const value_type*
// 	unsigned int	size_typer
// };

#endif
