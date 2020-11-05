#ifndef LIST_HPP
#define LIST_HPP

#include <functional>
#include <limits>

#include "iterator.hpp"

namespace ft
{
template <class T, bool isconst = false>
class list_iterator;

/*
	* NODE: structure that builds up the doubly linked list. Stores the previous and next
	* node along with the data.
	*/
template <class T>
struct list_node
{
    list_node *prev;
    list_node *next;
    T value;

    list_node(T value = T()) : next(0), prev(0), value(value) {}
    list_node(list_node *prev, list_node *next, T value) : prev(prev), next(next), value(value) {}
    list_node(list_node const &cpy) : prev(cpy.prev), next(cpy.next), value(cpy.value) {}
};
template <class T>
class list
{
    template <class U, bool isconst>
    friend class list_iterator;

    typedef ft::list_node<T> Node;

protected:
    Node *first_;
    Node *last_;
    size_t size_;

public:
    // TYPEDEFS ####################################################################
    typedef T value_type;
    typedef value_type &reference;
    typedef const value_type &const_reference;
    typedef value_type *pointer;
    typedef const value_type *const_pointer;
    typedef list_iterator<T> iterator;
    typedef list_iterator<T, true> const_iterator;
    typedef ft::reverse_iterator<iterator> reverse_iterator;
    typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;

    // ############################ CONSTRUCTORS ###################################
    explicit list() : first_(0), last_(0), size_(0) {}
    explicit list(size_t n, const T &val = T()) : first_(0), last_(0), size_(n)
    {
        if (n)
        {
            first_ = new Node(0, 0, val);
            Node *toAdd;
            Node *prev = first_;
            while (--n)
            {
                toAdd = new Node(prev, 0, val);
                prev->next = toAdd;
                prev = toAdd;
            }
            last_ = prev;
        }
    }
    template <class InputIterator>
    list(InputIterator first, InputIterator last,
         typename std::enable_if<!std::is_integral<InputIterator>::value>::type * = 0) : first_(0), last_(0), size_(0)
    {
        if (first != last)
        {
            size_ = 1;
            first_ = new Node(0, 0, *first);
            Node *toAdd;
            Node *prev = first_;
            for (first = ++first; first != last; first++)
            {
                toAdd = new Node(prev, 0, *first);
                prev->next = toAdd;
                prev = toAdd;
                size_++;
            }
            last_ = prev;
        }
    }
    list(list const &cpy) : first_(0), last_(0), size_(cpy.size_)
    {
        if (size_)
        {
            first_ = new Node(0, 0, cpy.first_->value);
            Node *toAdd;
            Node *prev = first_;
            Node *ctrav = cpy.first_->next;
            while (ctrav)
            {
                toAdd = new Node(prev, 0, ctrav->value);
                prev->next = toAdd;
                prev = toAdd;
                ctrav = ctrav->next;
            }
            last_ = prev;
        }
    }
    ~list()
    {
        Node *prev;
        while (first_ && size_)
        {
            prev = first_;
            first_ = first_->next;
            delete prev;
        }
        first_ = last_ = 0;
        size_ = 0;
    }
    list &operator=(list const &x)
    {
        list cpy(x);
        swap(cpy);
        return *this;
    }
    //############################# MEMBER FUNCTIONS ###############################
    inline size_type size() const { return size_; }
    inline size_type max_size() const { return std::numeric_limits<difference_type>::max() / (sizeof(Node) / 2); }  // ?
    inline bool empty() const { return !size_; }
    void resize(size_t n, T val = T())
    {
        Node *trav;
        if (!n)
            clear();
        else if (empty())
        {
            list tmp(n, val);
            swap(tmp);
        }
        else if (n < size_)
        {
            trav = first_;
            while (n-- > 0)
                trav = trav->next;
            erase(iterator(trav), iterator(0));
        }
        else if (n > size_)
        {
            insert(iterator(0), n - size_, val);
        }
    }
    void swap(list &other)
    {
        char buffer[sizeof(list)];
        memcpy(buffer, &other, sizeof(list));
        memcpy(reinterpret_cast<char *>(&other), this, sizeof(list));
        memcpy(reinterpret_cast<char *>(this), buffer, sizeof(list));
    }
    //############################## FOR ITERATOR ##################################
    inline reference front() { return first_->value; }  //Calling this function on an empty container causes undefined behavior.
    inline const_reference front() const { return first_->value; }
    inline reference back() { return last_->value; }
    inline const_reference back() const { return last_->value; }

    inline iterator begin() { return iterator(first_, this); }
    inline const_iterator begin() const { return const_iterator(first_, this); }
    inline iterator end() { return iterator(0, this); }
    inline const_iterator end() const { return const_iterator(0, this); }
    inline reverse_iterator rbegin() { return reverse_iterator(end()); }
    inline const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
    inline reverse_iterator rend() { return reverse_iterator(begin()); }
    inline const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }

    //################################ ASSIGN ######################################
    template <class InputIterator>
    void assign(InputIterator first, InputIterator last)
    {
        list tmp(first, last);
        swap(tmp);
    }
    void assign(size_t n, const T &val)
    {
        list tmp(n, val);
        swap(tmp);
    }
    //################################ INSERT ######################################
    iterator insert(iterator position, const T &val)
    {
        Node *toAdd;
        if (empty())
        {
            toAdd = new Node(0, 0, val);
            first_ = last_ = toAdd;
        }
        else if (position.node_ == first_)
        {
            toAdd = new Node(0, first_, val);
            first_->prev = toAdd;
            first_ = toAdd;
        }
        else if (!position.node_)
        {
            toAdd = new Node(last_, 0, val);
            last_->next = toAdd;
            last_ = toAdd;
        }
        else
        {
            toAdd = new Node(position.node_->prev, position.node_, val);
            position.node_->prev->next = toAdd;
            position.node_->prev = toAdd;
        }
        size_++;
        position.node_ = toAdd;
        return position;
        // return iterator(toAdd, this);
    }
    void insert(iterator position, size_type n, const T &val)
    {
        while (n--)
        {
            position = insert(position, val);
            ++position;
        }
    }
    template <class InputIterator>
    void insert(iterator position, InputIterator first, InputIterator last,
                typename std::enable_if<!std::is_integral<InputIterator>::value>::type * = 0)
    {
        while (first != last)
        {
            position = insert(position, *first++);
            ++position;
        }
    }
    //################################ ERASE ######################################
    iterator erase(iterator position)
    {
        if (position.node_ == 0)
            return position;
        iterator ret(position);
        ret++;
        unlink(position.node_);
        delete position.node_;
        return ret;
    }
    iterator erase(iterator first, iterator last)
    {
        if (first == last)
            return first;
        Node *toDel;
        unlink(first.node_, last.node_);
        while (first.node_ != 0 && first != last)
        {
            toDel = first.node_;
            first++;
            delete toDel;
        }
        return last;
    }
    //############################## PUSH & POP ###################################
    void push_back(const T &val)
    {
        last_ = new Node(last_, 0, val);
        size_++;
        if (last_->prev)
            last_->prev->next = last_;
        else
            first_ = last_;
    }
    void pop_back()
    {
        Node *toDel = last_;
        unlink(last_);
        delete toDel;
    }
    void push_front(const T &val)
    {
        first_ = new Node(0, first_, val);
        size_++;
        if (first_->next)
            first_->next->prev = first_;
        else
            last_ = first_;
    }
    void pop_front()
    {
        Node *toDel = first_;
        unlink(first_);
        delete toDel;
    }
    void clear()
    {
        Node *prev;
        while (first_)
        {
            prev = first_;
            first_ = first_->next;
            delete prev;
        }
        first_ = last_ = 0;
        size_ = 0;
    }
    //################################ SPLICE ######################################
    void splice(iterator position, list &x)
    {
        if (x.empty())
            return;
        if (empty())
        {
            swap(x);
            return;
        }
        if (position.node_ == first_)
        {
            first_->prev = x.last_;
            x.last_->next = first_;
            first_ = x.first_;
        }
        else if (position.node_ == 0)
        {
            last_->next = x.first_;
            x.first_->prev = last_;
            last_ = x.last_;
        }
        else
        {
            position.node_->prev->next = x.first_;
            x.first_->prev = position.node_->prev;
            position.node_->prev = x.last_;
            x.last_->next = position.node_;
        }
        size_ += x.size_;
        x.first_ = x.last_ = 0;
        x.size_ = 0;
    }
    void splice(iterator position, list &x, iterator i)
    {  // remove from x
        x.unlink(i.node_);
        //--------- INSERT-----------
        if (empty())
        {
            first_ = last_ = i.node_;
        }
        else if (position.node_ == first_)
        {
            first_->prev = i.node_;
            i.node_->next = first_;
            first_ = i.node_;
        }
        else if (position.node_ == 0)
        {
            last_->next = i.node_;
            i.node_->prev = last_;
            last_ = i.node_;
        }
        else
        {
            i.node_->next = position.node_;
            i.node_->prev = position.node_->prev;
            i.node_->prev->next = i.node_;
            i.node_->next->prev = i.node_;
        }
        size_++;
    }
    void splice(iterator position, list &x, iterator first, iterator last)
    {
        if (!x.first_ || first == last)
            return;
        Node *nlast = (last.node_) ? last.node_->prev : x.last_;
        size_ += x.unlink(first.node_, last.node_);
        if (empty())
        {
            first_ = first.node_;
            last_ = nlast;
        }
        else if (position.node_ == first_)
        {
            first_->prev = nlast;
            nlast->next = first_;
            first_ = first.node_;
        }
        else if (position.node_ == 0)
        {
            last_->next = first.node_;
            first.node_->prev = last_;
            last_ = nlast;
        }
        else
        {
            position.node_->prev->next = first.node_;
            first.node_->prev = position.node_->prev;
            position.node_->prev = nlast;
            nlast->next = position.node_;
        }
    }
    //################################ REMOVE ######################################
    void remove(const T &val)
    {
        iterator it(first_);
        while (it.node_ != 0)
        {
            if (*it == val)
                it = erase(it);
            else
                it++;
        }
    }
    template <class Predicate>
    void remove_if(Predicate pred)
    {
        iterator it(first_);
        while (it.node_ != 0)
        {
            if (pred(*it))
                it = erase(it);
            else
                it++;
        }
    }
    //################################ UNIQUE ######################################
    void unique()
    {
        iterator it2;
        for (Node *it1 = first_; it1 && it1->next != 0; it1 = it1->next)
        {
            for (it2 = iterator(it1->next); it2 != end() && *it2 == it1->value;)
                it2 = erase(it2);
        }
    }

    template <class BinaryPredicate>
    void unique(BinaryPredicate binary_pred)
    {
        iterator it2;
        for (Node *it1 = first_; it1 && it1->next != 0; it1 = it1->next)
        {
            for (it2 = iterator(it1->next); it2 != end() && binary_pred(*it2, it1->value);)
                it2 = erase(it2);
        }
    }
    //################################ MERGE ######################################
    // A subtlety is that merge doesn't alter the list if the list itself is used as
    //argument: object.merge(object) won't change the list `object'. !!!!!!!

    void merge(list &x)
    {  //sorted merge
        iterator a(first_, this);
        iterator b(x.first_, &x);
        if (this == &x || x.empty())
            return;
        if (empty())
        {
            swap(x);
            return;
        }
        while (a.node_ != 0 && b.node_ != 0)
        {
            if (*b < *a)
                splice(a, x, b++);
            else
                a++;
        }
        if (!x.empty())
            splice(a, x, b, x.end());
    }
    template <class Compare>
    void merge(list &x, Compare comp)
    {
        iterator a(first_, this);
        iterator b(x.first_, &x);
        if (this == &x || x.empty())
            return;
        if (empty())
        {
            swap(x);
            return;
        }
        while (a.node_ != 0 && b.node_ != 0)
        {
            if (comp(*b, *a) > 0)
                splice(a, x, b++);
            else
                a++;
        }
        if (!x.empty())
            splice(a, x, b, x.end());
    }
    //############################## SORT ##########################################
    void sort()
    {
        if (size_ < 2)
            return;
        mergesort(&first_, std::less<value_type>());
        Node *trav;
        for (trav = last_; trav && trav->next; trav = trav->next)
            ;
        last_ = trav;
    }

    template <class Compare>
    void sort(Compare comp)
    {
        if (size_ < 2)
            return;
        mergesort(&first_, comp);
        Node *trav;
        for (trav = last_; trav && trav->next; trav = trav->next)
            ;
        last_ = trav;
    }
    //############################## REVERSE #######################################
    void reverse()
    {
        iterator front(first_);
        iterator back(last_);
        while (front != back)
        {
            std::swap(*front, *back);
            front++;
            if (front == back)
                break;
            back--;
        }
    }

protected:
    void unlink(Node *position)
    {
        if (!position)
            return;
        size_--;
        if (size_ < 1)
        {
            first_ = last_ = 0;
        }
        else if (position == first_)
        {
            first_ = first_->next;
            first_->prev = 0;
        }
        else if (position == last_)
        {
            last_ = last_->prev;
            last_->next = 0;
        }
        else
        {
            position->prev->next = position->next;
            position->next->prev = position->prev;
        }
        position->prev = position->next = 0;
    }
    size_t unlink(Node *first, Node *last)
    {
        size_t range_size = 0;
        for (Node *trav = first; trav != last; trav = trav->next)
        {
            range_size++;
        }
        if (range_size == size_ || (first == first_ && last == 0))
        {
            first_ = last_ = 0;
        }
        else if (first == first_)
        {
            first_ = last;
            last->prev->next = 0;
            first_->prev = 0;
        }
        else if (last == 0)
        {
            last_ = first->prev;
            last_->next = 0;
        }
        else
        {
            first->prev->next = last;
            last->prev->next = 0;
            last->prev = first->prev;
        }
        first->prev = 0;
        size_ -= range_size;
        return range_size;
    }

    // MERGE SORT UTILS ###########################################################
    Node *split_list(Node *first)
    {
        if (first->next != 0)
        {
            for (Node *fast = first; fast != 0; fast = fast->next)
            {
                if (fast && fast->next)
                {
                    fast = fast->next;
                    first = first->next;
                }
            }
        }
        if (first->prev)
            first->prev->next = 0;
        return first;
    }
    template <typename Comp>
    Node *sort_merge(Node *a, Node *c, Comp comp)
    {
        if (!a)
        {
            last_ = c;
            return c;
        }
        if (!c)
        {
            last_ = a;
            return a;
        }
        if (comp(a->value, c->value))
        {
            a->next = sort_merge(a->next, c, comp);
            a->next->prev = a;
            a->prev = 0;
            return a;
        }
        else
        {
            c->next = sort_merge(a, c->next, comp);
            c->next->prev = c;
            c->prev = 0;
            return c;
        }
    }
    template <typename Comp>
    void mergesort(Node **first, Comp comp)
    {
        if (!*first || !(*first)->next)
            return;
        Node *middle = split_list(*first);
        mergesort(first, comp);
        mergesort(&middle, comp);
        *first = sort_merge(*first, middle, comp);
    }
};
/*
	* BIDIRECTIONAL ITERATOR: 
	*/
template <class T, bool isconst>
class list_iterator
{
    friend class list<T>;
    friend class list_iterator<T, false>;
    friend class list_iterator<T, true>;
    typedef typename choose<isconst, const list_node<T>, list_node<T> >::type Node;
    typedef typename choose<isconst, const list<T> *, list<T> *>::type listptr;

    Node *node_;
    listptr container_;

public:
    typedef ft::bidirectional_iterator_tag iterator_category;
    typedef T value_type;
    typedef std::ptrdiff_t difference_type;
    typedef typename choose<isconst, const T &, T &>::type reference;
    typedef typename choose<isconst, const T *, T *>::type pointer;

    list_iterator(Node *node = 0) : node_(node),
                                    container_(0) {}
    list_iterator(Node *node, listptr container) : node_(node),
                                                   container_(container) {}
    // list_iterator(list_iterator const &cpy) : node_(cpy.node_),
    // 										  container_(cpy.container_) {}
    list_iterator(list_iterator<T, false> const &cpy) : node_(cpy.node_),
                                                        container_(cpy.container_) {}
    ~list_iterator() {}

    list_iterator &operator=(list_iterator const &cpy)
    {
        list_iterator tmp(cpy);
        swap(tmp);
        return *this;
    }
    list_iterator &operator++(void)
    {
        if (node_)
            node_ = node_->next;
        else if (container_)
            node_ = container_->first_;
        return *this;
    }
    list_iterator operator++(int)
    {
        list_iterator old(*this);
        if (node_)
            node_ = node_->next;
        else if (container_)
            node_ = container_->first_;
        return old;
    }
    list_iterator &operator--(void)
    {
        if (node_)
            node_ = node_->prev;
        else if (container_)
            node_ = container_->last_;
        return *this;
    }
    list_iterator operator--(int)
    {
        list_iterator old(*this);
        if (node_)
            node_ = node_->prev;
        else if (container_)
            node_ = container_->last_;
        return old;
    }
    inline reference operator*(void) { return node_->value; }
    inline pointer operator->(void) { return &(node_->value); }
    inline reference operator*(void) const { return node_->value; }
    inline pointer operator->(void) const { return &(node_->value); }
    inline bool operator!=(list_iterator const &other) const { return node_ != other.node_; }
    inline bool operator==(list_iterator const &other) const { return node_ == other.node_; }

    void swap(list_iterator &other)
    {
        char buffer[sizeof(list_iterator)];
        memcpy(buffer, &other, sizeof(list_iterator));
        memcpy(reinterpret_cast<char *>(&other), this, sizeof(list_iterator));
        memcpy(reinterpret_cast<char *>(this), buffer, sizeof(list_iterator));
    }
};

template <class T>
bool operator==(const ft::list<T> &lhs, const ft::list<T> &rhs)
{
    if (lhs.size() != rhs.size())
        return false;
    typename ft::list<T>::const_iterator l_it = lhs.begin();
    typename ft::list<T>::const_iterator r_it = rhs.begin();
    while (l_it != lhs.end() && r_it != rhs.end())
    {
        if (*l_it != *r_it)
            return false;
        l_it++;
        r_it++;
    }
    if (l_it == lhs.end() && r_it == rhs.end())
        return true;
    return false;
}
template <class T>
bool operator!=(const ft::list<T> &lhs, const ft::list<T> &rhs)
{
    return !(lhs == rhs);
}
template <class T>
bool operator<(const ft::list<T> &lhs, const ft::list<T> &rhs)
{
    typename ft::list<T>::const_iterator l_it = lhs.begin();
    typename ft::list<T>::const_iterator r_it = rhs.begin();
    while (l_it != lhs.end() && r_it != rhs.end())
    {
        if (*l_it < *r_it)
            return true;
        if (*r_it < *l_it)
            return false;
        l_it++;
        r_it++;
    }
    if (r_it != rhs.end())
        return true;
    return false;
}
template <class T>
bool operator<=(const ft::list<T> &lhs, const ft::list<T> &rhs)
{
    return !(rhs < lhs);
}
template <class T>
bool operator>(const ft::list<T> &lhs, const ft::list<T> &rhs)
{
    return rhs < lhs;
}
template <class T>
bool operator>=(const ft::list<T> &lhs, const ft::list<T> &rhs)
{
    return !(lhs < rhs);
}
template <class T>
void swap(ft::list<T> &a, ft::list<T> &b)
{
    a.swap(b);
}
}  // namespace ft

#endif
