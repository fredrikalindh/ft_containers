#ifndef SET_HPP
#define SET_HPP

#include "RBTree.hpp"
#include "utility.hpp"

namespace ft
{
template <class T,
		  class Compare = less<T>,
		  class Alloc = std::allocator<T> >
class set
{
public:
	typedef T key_type;
	typedef T value_type;
	typedef Compare key_compare;
	typedef Compare value_compare;
	typedef Alloc allocator_type;
	typedef typename allocator_type::reference reference;
	typedef typename allocator_type::const_reference const_reference;
	typedef typename allocator_type::pointer pointer;
	typedef typename allocator_type::const_pointer const_pointer;
	// typedef value_type &reference;
	// typedef const value_type &const_reference;
	// typedef value_type *pointer;
	// typedef const value_type *const_pointer;
	typedef typename RB_Tree<T, value_compare>::iterator iterator;
	typedef typename RB_Tree<T, value_compare>::const_iterator const_iterator;
	typedef ft::reverse_iterator<iterator> reverse_iterator;
	typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
	typedef typename iterator_traits<iterator>::difference_type difference_type;
	typedef size_t size_type;

	explicit set(const key_compare &comp = key_compare(),
				 const allocator_type & = allocator_type()) : tree_(value_compare(comp)),
															  comp(comp) {}
	template <class InputIterator>
	set(InputIterator first, InputIterator last,
		const key_compare &comp = key_compare(),
		const allocator_type & = allocator_type()) : tree_(value_compare(comp)),
													 comp(comp)
	{
		while (first != last)
			tree_.add(*first++);
	}
	set(const set &x) : tree_(x.tree_),
						comp(x.comp) {}
	~set() {}
	set &operator=(const set &x)
	{
		set ret(x);
		swap(ret);
		return *this;
	}

	iterator begin() { return iterator(tree_.min(), &tree_); }
	const_iterator begin() const { return const_iterator(tree_.min(), &tree_); }
	iterator end() { return iterator(0, &tree_); }
	const_iterator end() const { return const_iterator(0, &tree_); }
	reverse_iterator rbegin() { return reverse_iterator(end()); }
	const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
	reverse_iterator rend() { return reverse_iterator(begin()); }
	const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }

	bool empty() const { return !tree_.size(); }
	size_type size() const { return tree_.size(); }
	size_type max_size() const
	{
		size_type div = (sizeof(T) / 4 + sizeof(T) % 4) * 4;
		return std::numeric_limits<difference_type>::max() / (div + 12);
	}

	pair<iterator, bool> insert(const value_type &val)
	{
		iterator ret(tree_.add(val), &tree_);
		return pair<iterator, bool>(ret, (*ret == val));
	}
	/**
	 * @param[in] position
	 * 		Hint for the position where the element can be inserted.
	 */
	iterator insert(iterator position, const value_type &val)
	{
		return iterator(tree_.add(position, val), &tree_);
	}
	template <class InputIterator>
	void insert(InputIterator first, InputIterator last)
	{
		while (first != last)
			tree_.add(*first++);
	}
	void erase(iterator position)
	{
		tree_.deleteKey(*position);
	}
	size_type erase(const value_type &val)
	{
		return tree_.deleteKey(val);
	}
	void erase(iterator first, iterator last)
	{
		while (first != end() && first != last &&
			   (last == end() || !comp(*last, *first)))
			first = tree_.deleteKey(first);
	}
	void swap(set &x)
	{
		char buffer[sizeof(set)];
		memcpy(buffer, &x, sizeof(set));
		memcpy(reinterpret_cast<char *>(&x), this, sizeof(set));
		memcpy(reinterpret_cast<char *>(this), buffer, sizeof(set));
	}
	void clear()
	{
		tree_.clear();
	}

	key_compare key_comp() const { return comp; }
	value_compare value_comp() const { return comp; }

	iterator find(const value_type &val) const
	{
		return iterator(tree_.find(val), &tree_);
	}
	size_type count(const value_type &val) const
	{
		return (tree_.find(val)) ? 1 : 0;
	}
	iterator lower_bound(const value_type &val) const
	{
		return iterator(tree_.lower_bound(val), &tree_);
	}
	iterator upper_bound(const value_type &val) const
	{
		return iterator(tree_.upper_bound(val), &tree_);
	}
	pair<iterator, iterator> equal_range(const value_type &val) const
	{
		return pair<iterator, iterator>(tree_.lower_bound(val), tree_.upper_bound(val));
	}

private:
	RB_Tree<T, value_compare> tree_;
	Compare comp;
};

template <class T, class Compare, class Alloc>
bool operator==(const set<T, Compare, Alloc> &lhs, const set<T, Compare, Alloc> &rhs)
{
	if (lhs.size() != rhs.size())
		return false;
	return equal(lhs.begin(), lhs.end(), rhs.begin());
}
template <class T, class Compare, class Alloc>
bool operator!=(const set<T, Compare, Alloc> &lhs, const set<T, Compare, Alloc> &rhs)
{
	return !(lhs == rhs);
}
template <class T, class Compare, class Alloc>
bool operator<(const set<T, Compare, Alloc> &lhs, const set<T, Compare, Alloc> &rhs)
{
	ft::less<T> less;
	return lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end(), less);
}
template <class T, class Compare, class Alloc>
bool operator>=(const set<T, Compare, Alloc> &lhs, const set<T, Compare, Alloc> &rhs)
{
	return !(lhs < rhs);
}
template <class T, class Compare, class Alloc>
bool operator>(const set<T, Compare, Alloc> &lhs, const set<T, Compare, Alloc> &rhs)
{
	return rhs < lhs;
}
template <class T, class Compare, class Alloc>
bool operator<=(const set<T, Compare, Alloc> &lhs, const set<T, Compare, Alloc> &rhs)
{
	return !(rhs < lhs);
}
template <class T, class Compare, class Alloc>
void swap(set<T, Compare, Alloc> &a, set<T, Compare, Alloc> &b)
{
	a.swap(b);
}

}  // namespace ft

#endif
