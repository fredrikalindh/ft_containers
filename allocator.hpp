#ifndef ALLOCATOR_HPP
# define ALLOCATOR_HPP

namespace ft
{
	template <class T>
	class Allocator;
}

template <class T>
class Allocator
{

public:
	typedef T value_type;

	Allocator();
	Allocator(Allocator const &other);
	~Allocator(); // deallocate everything?
	value_type *address(value_type &object);
	value_type *allocate(size_t count);
	void construct(value_type *object, Arg &&...args);
	void destroy(value_type *object);
	void deallocate(value_type *object, size_t count);
	size_t max_size();
};

#endif

/*
- `value_type *address(value_type &object)`
> returns the address of object.

- `value_type *allocate(size_t count)`
> allocates raw memory for holding count values of the container's value_type.

- `void construct(value_type *object, Arg &&...args)`
> using placement new, uses the arguments following object to install a value at object.

- `void destroy(value_type *object)`
> calls object's destructor (but doesn't deallocate object's own memory).

- `void deallocate(value_type *object, size_t count)`
> calls operator delete to delete object's memory, previously allocated by allocate.

- `size_t max_size()`
> returns the maximum number of elements that allocate can allocate.
*/
