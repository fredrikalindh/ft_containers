#ifndef QUEUE_HPP
# define QUEUE_HPP

namespace ft
{
	template <class T, class Container = list<T> > class queue;
}

template <class T, class Container = list<T> >
class queue
{
public:
	typedef	T			value_type;
	typedef	Container	container_type;
	typedef size_t		size_type;

	explicit queue (const container_type& ctnr = container_type());

	bool				empty() const;
	size_type 			size() const;
	value_type&			front();
	const value_type&	front() const;
	value_type&			back();
	const value_type&	back() const;
	void				push (const value_type& val);
	void				pop();
};
	template <class T, class Container>
	bool operator== (const queue<T,Container>& lhs, const queue<T,Container>& rhs);
	template <class T, class Container>
	bool operator!= (const queue<T,Container>& lhs, const queue<T,Container>& rhs);
	template <class T, class Container>
	bool operator<  (const queue<T,Container>& lhs, const queue<T,Container>& rhs);
	template <class T, class Container>
	bool operator<= (const queue<T,Container>& lhs, const queue<T,Container>& rhs);
	template <class T, class Container>
	bool operator>  (const queue<T,Container>& lhs, const queue<T,Container>& rhs);
	template <class T, class Container>
	bool operator>= (const queue<T,Container>& lhs, const queue<T,Container>& rhs);
#endif
