#ifndef MULTIMAP_HPP
# define MULTIMAP_HPP

#include "RBTree.hpp"
#include "utility.hpp"

namespace ft
{
template <
	class Key,
	class T,
	class Compare = std::less<Key> >
class multimap
{
public:
	typedef	Key										key_type;
	typedef	T										mapped_type;
	typedef ft::pair<Key, T>						value_type;
	typedef	size_t									size_type;
	typedef	std::ptrdiff_t								difference_type;
	typedef	Compare									key_compare;
	typedef	value_type&								reference;
	typedef	const value_type&						const_reference;
	typedef	value_type*								pointer;
	typedef	const value_type*						const_pointer;
	class value_compare : public std::binary_function<value_type, value_type, bool> // REMOVE INHERITANCE ?
	{
	protected:
		Compare comp;
		value_compare (Compare c) : comp(c) {}	// constructed with map's comparison object
	public:
		friend class multimap;

		typedef bool result_type;
		typedef value_type first_argument_type;
		typedef value_type second_argument_type;
		bool operator() (const value_type& x, const value_type& y) const
		{
			return comp(x.first, y.first);
		}
	};
private:
	typedef ft::RB_Tree<ft::pair<Key, T>, value_compare> RBT;

	RBT			tree_;
	Compare		comp;
public:
// ########################### TYPEDEFS ########################################
typedef	typename RBT::iterator					iterator;
typedef	typename RBT::const_iterator			const_iterator;
typedef	ft::reverse_iterator<iterator>			reverse_iterator;
typedef	ft::reverse_iterator<const_iterator>	const_reverse_iterator;
//######################### CONSTRUCTORS #######################################
	explicit multimap (const key_compare& comp = key_compare()):tree_(comp, true), comp(comp){}
	template <class InputIterator>
	multimap (InputIterator first, InputIterator last, const key_compare& comp = key_compare()):
	tree_(comp, true), comp(comp){
		for ( ; first != last; first++)
			tree_.add(*first);
	}
	multimap (const multimap& x):tree_(x.tree_), comp(x.comp){}
	~multimap(){}
	multimap& operator= (const multimap& x){
		multimap tmp(x);
		swap(tmp);
		return *this;
	}
//########################## ITERATORS #######################################
	iterator				begin() {return iterator(tree_.min(), &tree_);}
	const_iterator			begin() const {return const_iterator(tree_.min(), &tree_);}
	iterator				end() { return iterator(0, &tree_); }
	const_iterator			end() const { return const_iterator(0, &tree_); }
	reverse_iterator		rbegin() { return reverse_iterator(end());}
	const_reverse_iterator	rbegin() const { return reverse_iterator(end());}
	reverse_iterator		rend() { return reverse_iterator(begin()); }
	const_reverse_iterator	rend() const { return reverse_iterator(begin()); }
//########################### CAPACITY #######################################
	bool					empty() const {return !tree_.size();}
	size_type				size() const {return tree_.size();}
	size_type				max_size() const {return 461168601842738790;}
//########################### INSERT #######################################
	iterator	insert (const value_type& val) {
		return iterator(tree_.add(val), &tree_);
	}
	iterator				insert (iterator, const value_type& val){
		return iterator(tree_.add(val), &tree_);
	}
	template <class InputIterator>
	void					insert (InputIterator first, InputIterator last){
		while (first != last) tree_.add(*first++);
	}
//########################### ERASE #######################################
	void					erase (iterator position){
		tree_.deleteKey(position);
	}
	size_type				erase (const key_type& k) {
		return tree_.deleteKey(k);
	}
	void					erase (iterator first, iterator last){ // CAN MAKE MORE EFFICIENT
		size_t size = 0;
		for (iterator trav = first; trav != last; trav++)
			size++;
		Key *keys = new Key[size];
		for (size_t i = 0; i < size; i++){
			keys[i] = first->first;
			++first;
		}
		for (size_t i = 0 ; i < size; i++){
			tree_.deleteKey(keys[i]);
		}
		delete [] keys;
	}
//########################### MODIFIERS #######################################
	void					swap (multimap& x) {
		char buffer[sizeof(multimap)];
		memcpy(buffer, &x, sizeof(multimap));
		memcpy(reinterpret_cast<char *>(&x), this, sizeof(multimap));
		memcpy(reinterpret_cast<char *>(this), buffer, sizeof(multimap));
	}
	void					clear(){
		tree_.clear();
	}
//########################### OBSERVERS #######################################
	key_compare				key_comp() const {return comp;}
	value_compare			value_comp() const {return value_compare(comp);}
//########################### OPERATIONS #######################################
	iterator				find (const key_type& k) {
		return iterator(tree_.find(k), &tree_);
	}
	const_iterator			find (const key_type& k) const {
		return const_iterator(tree_.find(k), &tree_);
	}
	size_type				count (const key_type& k) const {
		size_type n = 0;
		for (iterator i(tree_.find(k), &tree_);
			i.node_ && !comp(i->first, k) && !comp(k, i->first);
			++i ) ++n;
		return n;
	}
	iterator				lower_bound (const key_type& k) {
		return iterator(tree_.find(k), &tree_);
	}
	const_iterator			lower_bound (const key_type& k) const {
		return const_iterator(tree_.find(k), &tree_);
	}
	iterator				upper_bound (const key_type& k) {
		return iterator(tree_.find_upper(k), &tree_);
	}
	const_iterator			upper_bound (const key_type& k) const {
		return const_iterator(tree_.find_upper(k), &tree_);
	}
	ft::pair<const_iterator,const_iterator>	equal_range (const key_type& k) const{
		 return ft::pair<const_iterator,const_iterator>(lower_bound(k), upper_bound(k));
	}
	ft::pair<iterator,iterator>				equal_range (const key_type& k){
		 return ft::pair<iterator,iterator>(lower_bound(k), upper_bound(k));
	}
	friend bool operator== (const multimap &lhs, const multimap &rhs) {
	return lhs.tree_.equal(rhs.tree_, key_compare());
	}
	friend bool operator!= (const multimap &lhs, const multimap &rhs) {
	return !(lhs == rhs);
	}
	friend bool operator<  (const multimap &lhs, const multimap &rhs) {
	return rhs.tree_.lesser(lhs.tree_, key_compare());
	}
	friend bool operator>= (const multimap &lhs, const multimap &rhs) {
	return !(lhs < rhs);
	}
	friend bool operator>  (const multimap &lhs, const multimap &rhs) {
	return rhs < lhs;
	}
	friend bool operator<= (const multimap &lhs, const multimap &rhs) {
	return !(rhs < lhs);
	}
};

} // namespace ft

template <class Key, class T, class Compare>
void swap(ft::multimap<Key, T, Compare> &a, ft::multimap<Key, T, Compare> &b){
	a.swap(b);
}

#endif