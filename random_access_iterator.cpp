
template <class T>
class random_access_iterator
{
	T*	d_p;
public:
	iterator (T* d_p = 0);
	iterator (iterator const &x);

	iterator &operator++();
	iterator &operator++(int);
	iterator &operator--();
	iterator &operator--(int);

	iterator &operator+(int); // only random_access_iterator
	iterator &operator-(int); // only random_access_iterator
	iterator &operator+=(int); // only random_access_iterator
	iterator &operator-=(int); // only random_access_iterator

	T&		operator*();
	T&		operator->();
	T&		operator[](int); // only random_access_iterator

	bool operator==(iterator const &x) const;
	bool operator!=(iterator const &x) const;
	bool operator<(iterator const &x) const; // only random_access_iterator
	bool operator<=(iterator const &x) const; // only random_access_iterator
	bool operator>(iterator const &x) const; // only random_access_iterator
	bool operator>=(iterator const &x) const; // only random_access_iterator
};

template <class InputIterator, class Distance>
void advance (InputIterator& it, Distance n);

template<class InputIterator>
typename iterator_traits<InputIterator>::difference_type
distance (InputIterator first, InputIterator last);

template <class Container>
back_insert_iterator<Container> back_inserter (Container& x);

template <class Container>
  front_insert_iterator<Container> front_inserter (Container& x);

template <class Container, class Iterator>
insert_iterator<Container> inserter (Container& x, Iterator it);
