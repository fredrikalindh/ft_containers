#ifndef STACK_HPP
# define STACK_HPP

# include "list.hpp"
namespace ft
{

template <class T, class Container = list<T> >
class stack
{
	Container d_ctnr;
public:
	typedef	T			value_type;
	typedef	Container	container_type;
	typedef size_t		size_type;

	explicit stack (const container_type& ctnr = container_type()):d_ctnr(ctnr){}
	bool				empty() const {return d_ctnr.empty();}
	size_type 			size() const {return d_ctnr.size();}
	value_type& 		top() {return d_ctnr.back();}
	const value_type&	top() const {return d_ctnr.back();}
	void				push (const value_type& val) {d_ctnr.push_back(val);}
	void				pop() {d_ctnr.pop_back();}

	friend
	bool operator== (const stack& lhs, const stack& rhs){
		return lhs.d_ctnr == rhs.d_ctnr;
	}
	friend
	bool operator!= (const stack& lhs, const stack& rhs){
		return lhs.d_ctnr != rhs.d_ctnr;
	}
	friend
	bool operator<  (const stack& lhs, const stack& rhs){
		return lhs.d_ctnr < rhs.d_ctnr;
	}
	friend
	bool operator<= (const stack& lhs, const stack& rhs){
		return lhs.d_ctnr <= rhs.d_ctnr;
	}
	friend
	bool operator>  (const stack& lhs, const stack& rhs){
		return lhs.d_ctnr > rhs.d_ctnr;
	}
	friend
	bool operator>= (const stack& lhs, const stack& rhs){
		return lhs.d_ctnr >= rhs.d_ctnr;
	}
};

} //namespace ft



// template <class T, class Container>
// friend bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs){
// 	return lhs.d_ctnr == rhs.d_ctnr;
// }
// template <class T, class Container>
// friend bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs){
// 	return lhs.d_ctnr != rhs.d_ctnr;
// }
// template <class T, class Container>
// friend bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs){
// 	return lhs.d_ctnr < rhs.d_ctnr;
// }
// template <class T, class Container>
// friend bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs){
// 	return lhs.d_ctnr <= rhs.d_ctnr;
// }
// template <class T, class Container>
// friend bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs){
// 	return lhs.d_ctnr > rhs.d_ctnr;
// }
// template <class T, class Container>
// friend bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs){
// 	return lhs.d_ctnr >= rhs.d_ctnr;
// }


#endif
