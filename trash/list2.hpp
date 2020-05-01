#ifndef LIST_HPP
# define LIST_HPP

# include <iostream>
# include <string>

template <class T>
class ft::List
{
public:
	List();
	List(List const &cpy);
	~List();

	List &operator=(List const &cpy);

	unsigned int	size();
	unsigned int	max_size();
	bool			empty();
	unsigned int	resize();

	T				front();
	T				back();

	ListElement		*begin();
	ListElement		*rend();
	ListElement		*end();
	ListElement		*rbegin();
	void			assign();
	void			insert(int ?);
	void			erase();

	void			push_back();
	void			pop_back();
	void			push_front();
	void			pop_front();
	void			clear();

	void			splice();
	void			remove();
	void			remove_if();
	void			unique();
	void			merge();
	void			sort();
	void			reverse();

	class iterator
	{
	public:
		iterator();
		iterator();
		~iterator();
		iterator &operator=(ListElement *ret);

		iterator &operator==(iterator const &i2);
		iterator &operator!=(iterator const &i2);
		iterator &operator++(iterator const &i2);
		iterator &operator--(iterator const &i2);
	private:
		ListElement *curr;
	};

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
	T			value_type; //	defaults to: allocator<value_type>
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
