#ifndef MULTIMAP_HPP
#define MULTIMAP_HPP

#include "RBTree.hpp"
#include "iterator.hpp"
#include "utility.hpp"

namespace ft
{
template <
	class Key,
	class T,
	class Compare = less<Key>,
	class Alloc = std::allocator<pair<const Key, T> > >
class multimap
{
public:
	// ########################### TYPEDEFS ########################################
	typedef Key key_type;
	typedef T mapped_type;
	typedef Alloc allocator_type;
	typedef pair<const key_type, mapped_type> value_type;
	typedef size_t size_type;
	typedef Compare key_compare;
	typedef value_type& reference;
	typedef const value_type& const_reference;
	typedef value_type* pointer;
	typedef const value_type* const_pointer;
	class value_compare : public std::binary_function<value_type, value_type, bool>
	{
	protected:
		Compare comp;
		value_compare(Compare c) : comp(c) {}  // constructed with map's comparison object
	public:
		friend class multimap;

		typedef bool result_type;
		typedef value_type first_argument_type;
		typedef value_type second_argument_type;
		bool operator()(const value_type& x, const value_type& y) const
		{
			return comp(x.first, y.first);
		}
	};
	typedef typename RB_Tree<ft::pair<Key, T>, value_compare>::iterator iterator;
	typedef typename RB_Tree<ft::pair<Key, T>, value_compare>::const_iterator const_iterator;
	typedef ft::reverse_iterator<iterator> reverse_iterator;
	typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
	typedef typename iterator_traits<iterator>::difference_type difference_type;

	//######################### CONSTRUCTORS #######################################
	explicit multimap(const key_compare& comp = key_compare(),
					  const allocator_type& = allocator_type()) : tree_(comp, true),
																  comp(comp) {}
	template <class InputIterator>
	multimap(InputIterator first, InputIterator last,
			 const key_compare& comp = key_compare(),
			 const allocator_type& = allocator_type()) : tree_(comp, true),
														 comp(comp)
	{
		while (first != last)
			tree_.add(*first++);
	}
	multimap(const multimap& x) : tree_(x.tree_),
								  comp(x.comp) {}
	~multimap() {}
	multimap& operator=(const multimap& x)
	{
		multimap tmp(x);
		swap(tmp);
		return *this;
	}
	//########################## ITERATORS #######################################
	iterator begin() { return iterator(tree_.min(), &tree_); }
	const_iterator begin() const { return const_iterator(tree_.min(), &tree_); }
	iterator end() { return iterator(0, &tree_); }
	const_iterator end() const { return const_iterator(0, &tree_); }
	reverse_iterator rbegin() { return reverse_iterator(end()); }
	const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
	reverse_iterator rend() { return reverse_iterator(begin()); }
	const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }
	//########################### CAPACITY #######################################
	bool empty() const { return !tree_.size(); }
	size_type size() const { return tree_.size(); }
	size_type max_size() const { return tree_.max_size(); }
	//########################### INSERT #######################################
	iterator insert(const value_type& val)
	{
		return iterator(tree_.add(val), &tree_);
	}
	iterator insert(iterator position, const value_type& val)
	{
		return iterator(tree_.add(position, val), &tree_);
	}
	template <class InputIterator>
	void insert(InputIterator first, InputIterator last)
	{
		while (first != last)
			tree_.add(*first++);
	}
	//########################### ERASE #######################################
	void erase(iterator position)
	{
		tree_.deleteKey(position);
	}
	size_type erase(const key_type& k)
	{
		size_type i = 0;
		while (tree_.deleteKey(k))
			i++;
		return i;
	}
	void erase(iterator first, iterator last)
	{  // CAN MAKE MORE EFFICIENT
		while (first != end() && first != last &&
			   (last == end() || !comp(last->first, first->first)))
			first = tree_.deleteKey(first);
	}
	//########################### MODIFIERS #######################################
	void swap(multimap& x)
	{
		char buffer[sizeof(multimap)];
		memcpy(buffer, &x, sizeof(multimap));
		memcpy(reinterpret_cast<char*>(&x), this, sizeof(multimap));
		memcpy(reinterpret_cast<char*>(this), buffer, sizeof(multimap));
	}
	void clear() { tree_.clear(); }
	//########################### OBSERVERS #######################################
	key_compare key_comp() const { return comp; }
	value_compare value_comp() const { return value_compare(comp); }
	//########################### OPERATIONS #######################################
	iterator find(const key_type& k)
	{
		return iterator(tree_.find(k), &tree_);
	}
	const_iterator find(const key_type& k) const
	{
		return const_iterator(tree_.find(k), &tree_);
	}
	size_type count(const key_type& k) const
	{
		return tree_.count(k);
	}
	iterator lower_bound(const key_type& k)
	{
		return iterator(tree_.lower_bound(k), &tree_);
	}
	const_iterator lower_bound(const key_type& k) const
	{
		return const_iterator(tree_.lower_bound(k), &tree_);
	}
	iterator upper_bound(const key_type& k)
	{
		return iterator(tree_.upper_bound(k), &tree_);
	}
	const_iterator upper_bound(const key_type& k) const
	{
		return const_iterator(tree_.upper_bound(k), &tree_);
	}
	pair<const_iterator, const_iterator> equal_range(const key_type& k) const
	{
		return pair<const_iterator, const_iterator>(lower_bound(k), upper_bound(k));
	}
	pair<iterator, iterator> equal_range(const key_type& k)
	{
		return pair<iterator, iterator>(lower_bound(k), upper_bound(k));
	}

private:
	RB_Tree<pair<Key, T>, value_compare> tree_;
	Compare comp;
};

template <class Key, class T, class Compare, class Alloc>
bool operator==(const multimap<Key, T, Compare, Alloc>& lhs, const multimap<Key, T, Compare, Alloc>& rhs)
{
	if (lhs.size() != rhs.size())
		return false;
	return equal(lhs.begin(), lhs.end(), rhs.begin());
}
template <class Key, class T, class Compare, class Alloc>
bool operator!=(const multimap<Key, T, Compare, Alloc>& lhs,
				const multimap<Key, T, Compare, Alloc>& rhs)
{
	return !(lhs == rhs);
}
template <class Key, class T, class Compare, class Alloc>
bool operator<(const multimap<Key, T, Compare, Alloc>& lhs,
			   const multimap<Key, T, Compare, Alloc>& rhs)
{
	ft::less<ft::pair<Key, T> > less;
	return lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end(), less);
}
template <class Key, class T, class Compare, class Alloc>
bool operator>=(const multimap<Key, T, Compare, Alloc>& lhs,
				const multimap<Key, T, Compare, Alloc>& rhs)
{
	return !(lhs < rhs);
}
template <class Key, class T, class Compare, class Alloc>
bool operator>(const multimap<Key, T, Compare, Alloc>& lhs,
			   const multimap<Key, T, Compare, Alloc>& rhs)
{
	return rhs < lhs;
}
template <class Key, class T, class Compare, class Alloc>
bool operator<=(const multimap<Key, T, Compare, Alloc>& lhs,
				const multimap<Key, T, Compare, Alloc>& rhs)
{
	return !(rhs < lhs);
}
template <class Key, class T, class Compare, class Alloc>
void swap(multimap<Key, T, Compare, Alloc>& a, multimap<Key, T, Compare, Alloc>& b)
{
	a.swap(b);
}
}  // namespace ft

#endif
