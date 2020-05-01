#ifndef LIST_HPP
# define LIST_HPP

# include <iostream>
# include <string>

namespace ft
{
	template <class T, class Alloc = allocator<T> > class list;
}

template <class T, class Alloc = allocator<T> >
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

	friend void swap(list &a, list &b);
public:
// PREDEFINITION OF ITERATORS ##################################################
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
	// typedef Alloc							allocator_type;
//  ############################################################################

	explicit list (const allocator_type& alloc = allocator_type());
	explicit list (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type());
	template <class InputIterator>
	  list (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type());
	list (const list& x);
