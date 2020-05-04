#ifndef ITERATOR_HPP
# define ITERATOR_HPP

namespace ft
{
	struct input_iterator_tag {};
	///  Marking output iterators.
	struct output_iterator_tag {};
	/// Forward iterators support a superset of input iterator operations.
	struct forward_iterator_tag : public input_iterator_tag {};
	/// Bidirectional iterators support a superset of forward iterator
	/// operations.
	struct bidirectional_iterator_tag : public forward_iterator_tag {};
	/// Random-access iterators support a superset of bidirectional iterator
	/// operations.
	struct random_access_iterator_tag : public bidirectional_iterator_tag {};

	template < class Iterator >
	struct iterator_traits {
	  typedef typename Iterator::value_type        value_type ;
	  typedef typename Iterator::difference_type   difference_type ;
	  typedef typename Iterator::pointer           pointer ;
	  typedef typename Iterator::reference         reference ;
	  typedef typename Iterator::iterator_category iterator_category ;
	};

	template < class T >
	struct iterator_traits <T* > {
	  typedef T                          value_type ;
	  typedef ptrdiff_t                  difference_type ;
	  typedef T*                         pointer ;
	  typedef T&                         reference ;
	  typedef random_access_iterator_tag iterator_category ;
	};
	template < class T >
	struct iterator_traits <const T* > {
	  typedef T                          value_type ;
	  typedef ptrdiff_t                  difference_type ;
	  typedef const T*                   pointer ;
	  typedef const T&                   reference ;
	  typedef random_access_iterator_tag iterator_category ;
	};


	template <class Iterator>
	class reverse_iterator
	{
		Iterator base_;
	public:
		typedef Iterator									iterator_type;
		typedef typename iterator_type::iterator_category	iterator_category;
		typedef typename iterator_type::value_type			value_type;
		typedef typename iterator_type::difference_type		difference_type;
		typedef typename iterator_type::pointer				pointer;
		typedef typename iterator_type::reference			reference;

		reverse_iterator():base_(0){}
		explicit reverse_iterator (iterator_type it):base_(--it){}
		template <class Iter>
		reverse_iterator (const reverse_iterator<Iter>& rev_it):base_(rev_it.base_){}

		iterator_type base() const {
			Iterator ret(base_);
			++ret;
			return ret;
		}
		reference operator*() const { return *base_; }
		pointer operator->() const { return &(operator*()); }
		reference operator[] (difference_type n) const { return base_[-n - 1];}

		reverse_iterator operator+ (difference_type n) const {
			reverse_iterator tmp(*this);
			tmp.base_ = tmp.base_ - n;
			return tmp;
		}
		reverse_iterator& operator+= (difference_type n){
			base_ = base_ - n;
			return *this;
		}
		reverse_iterator operator- (difference_type n) const{
			reverse_iterator tmp(*this);
			tmp.base_ = tmp.base_ + n;
			return tmp;
		}
		reverse_iterator& operator-= (difference_type n){
			base_ = base_ + n;
			return *this;
		}

		reverse_iterator& operator++(){
			--base_;
			return *this;
		}
		reverse_iterator  operator++(int){
			reverse_iterator tmp(*this);
			--base_;
			return tmp;
		}
		reverse_iterator& operator--(){
			++base_;
			return *this;
		}
		reverse_iterator  operator--(int){
			reverse_iterator tmp(*this);
			++base_;
			return tmp;
		}
	};

} // namespace ft

template <class Iterator>
bool operator== (const ft::reverse_iterator<Iterator>& lhs, const ft::reverse_iterator<Iterator>& rhs){
	return lhs.base() == rhs.base();
}
template <class Iterator>
bool operator!= (const ft::reverse_iterator<Iterator>& lhs, const ft::reverse_iterator<Iterator>& rhs){
	return lhs.base() != rhs.base();
}
template <class Iterator>
bool operator<  (const ft::reverse_iterator<Iterator>& lhs, const ft::reverse_iterator<Iterator>& rhs){
	return lhs.base() > rhs.base();
}
template <class Iterator>
bool operator<= (const ft::reverse_iterator<Iterator>& lhs, const ft::reverse_iterator<Iterator>& rhs){
	return lhs.base() >= rhs.base();
}
template <class Iterator>
bool operator>  (const ft::reverse_iterator<Iterator>& lhs, const ft::reverse_iterator<Iterator>& rhs){
	return lhs.base() < rhs.base();
}
template <class Iterator>
bool operator>= (const ft::reverse_iterator<Iterator>& lhs, const ft::reverse_iterator<Iterator>& rhs){
	return lhs.base() <= rhs.base();
}

template <class Iterator>
ft::reverse_iterator<Iterator> operator+ (
					typename ft::reverse_iterator<Iterator>::difference_type n,
							const ft::reverse_iterator<Iterator>& rev_it){
	return ft::reverse_iterator<Iterator>(rev_it + n);
}
template <class Iterator>
ft::reverse_iterator<Iterator> operator- (
					typename ft::reverse_iterator<Iterator>::difference_type n,
							const ft::reverse_iterator<Iterator>& rev_it){
	return ft::reverse_iterator<Iterator>(rev_it - n);
}


#endif
