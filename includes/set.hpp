#ifndef SET_HPP
#define SET_HPP

#include "RBTree.hpp"
#include "utility.hpp"

namespace ft
{
	template <class T, class Compare = std::less<T> >
	class set
	{
	public:
		typedef T key_type;
		typedef T value_type;
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;
		typedef Compare key_compare;
		typedef Compare value_compare;
		typedef value_type &reference;
		typedef const value_type &const_reference;
		typedef value_type *pointer;
		typedef const value_type *const_pointer;

	private:
		typedef ft::RB_Tree<T, value_compare> RBT;

		RBT tree_;
		Compare comp;

	public:
		typedef typename RBT::iterator iterator;
		typedef typename RBT::const_iterator const_iterator;
		typedef ft::reverse_iterator<iterator> reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

		explicit set(const key_compare &comp = key_compare()) : tree_(value_compare(comp)), comp(comp) {}
		template <class InputIterator>
		set(InputIterator first, InputIterator last, const key_compare &comp = key_compare()) : tree_(value_compare(comp)), comp(comp)
		{
			for (; first != last; first++)
				tree_.add(*first);
		}
		set(const set &x) : tree_(x.tree_), comp(x.comp) {}
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
		size_type max_size() const { 
			size_type div = (sizeof(T) / 4 + sizeof(T) % 4) * 4;
			return std::numeric_limits<difference_type>::max() / (div + 12); 
		}

		ft::pair<iterator, bool> insert(const value_type &val)
		{
			iterator ret(tree_.add(val), &tree_);
			return ft::pair<iterator, bool>(ret, (*ret == val));
		}
		iterator insert(iterator, const value_type &val)
		{
			return iterator(tree_.add(val), &tree_);
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
		{ // CAN MAKE MORE EFFICIENT
			size_t size = 0;
			for (iterator trav = first; trav != last; trav++)
				size++;
			T *keys = new T[size];
			for (size_t i = 0; i < size; i++)
			{
				keys[i] = *first;
				++first;
			}
			for (size_t i = 0; i < size; i++)
			{
				tree_.deleteKey(keys[i]);
			}
			delete[] keys;
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
		ft::pair<iterator, iterator> equal_range(const value_type &val) const
		{
			return ft::pair<iterator, iterator>(lower_bound(val), upper_bound(val));
		}

		friend bool operator==(const set &lhs, const set &rhs)
		{
			return lhs.tree_ == rhs.tree_;
		}
		friend bool operator!=(const set &lhs, const set &rhs)
		{
			return !(lhs == rhs);
		}
		friend bool operator<(const set &lhs, const set &rhs)
		{
			return lhs.tree_ < rhs.tree_;
		}
		friend bool operator>=(const set &lhs, const set &rhs)
		{
			return !(lhs < rhs);
		}
		friend bool operator>(const set &lhs, const set &rhs)
		{
			return rhs < lhs;
		}
		friend bool operator<=(const set &lhs, const set &rhs)
		{
			return !(rhs < lhs);
		}
	};

	template <class T, class Compare>
	void swap(set<T, Compare> &a, set<T, Compare> &b)
	{
		a.swap(b);
	}

} // namespace ft

#endif
