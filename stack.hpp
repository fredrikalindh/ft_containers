#ifndef STACK_HPP
# define STACK_HPP

namespace ft
{
	template <class T, class Container = list<T> > class stack;
}

template <class T, class Container = list<T> >
class stack
{

public:
	typedef	T			value_type;
	typedef	Container	container_type;
	typedef size_t		size_type;

	explicit stack (const container_type& ctnr = container_type());
	~stack();

	bool				empty() const;
	size_type 			size() const;
	value_type& 		top();
	const value_type&	top() const;
	void				push (const value_type& val);
	void				pop();
};

template <class T, class Container>
  bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs);
template <class T, class Container>
  bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs);
template <class T, class Container>
  bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs);
template <class T, class Container>
  bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs);
template <class T, class Container>
  bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs);
template <class T, class Container>
  bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs);

#endif
