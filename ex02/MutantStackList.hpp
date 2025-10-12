#ifndef MUTANTSTACK_LIST_HPP
# define MUTANTSTACK_LIST_HPP

# define RED "\033[31m"
# define GREEN "\033[32m"
# define BLUE "\033[34m"
# define YELLOW "\033[33m"
# define CYAN "\033[36m"
# define MAGENTA "\033[35m"
# define WHITE "\033[37m"
# define RESET "\033[0m"

# include <iostream>
# include <stack>
# include <list>

/*
	std::stack<T, Container> is an adapter over an underlying container.
	std::stack<T> default underlying container is std::deque<T>

	Why still choose std::deque<T>?
	1. Standard default underlying container of std::stack<T> is std::deque<T>.
		- std::stack<T> is originally wrapped over a deque, changing to different underlying container may cause odd behaviours/accidental slowdown
	
	2. Performance and Locality 
		- deque is good cache locality for iteration , has cheaper push_back/pop_back
		- no massive reallocation like vector, no per-element heap node like list
	 # Locality ---> How fast the CPU read the elements. When the elements near each other : Good locality; Elements far from each other: Poor locality
	3. Iterator invalidation and value access
		- deque: push_back/pop_back may invalidate end iterators, 
			but overall most iterators remain valid when capacity doesn’t shift across blocks. 
			Iterating is still fast due to locality
		- list: insert/erase does not invalidate iterators
			but only have bidirectional iterators but does not have "random access"

	4. 
*/

template <typename T, typename Container = std::list<T> >
class	MutantStack: public std::stack<T, Container>
{
	private:

	public:
		MutantStack();
		MutantStack(const MutantStack &other);
		MutantStack &operator=(const MutantStack &other);
		~MutantStack();

		typedef typename std::stack<T, Container>::container_type				container_type;
		typedef typename container_type::iterator								iterator;
		typedef typename container_type::const_iterator							const_iterator;
		typedef typename container_type::reverse_iterator						reverse_iterator;
		typedef typename container_type::const_reverse_iterator					const_reverse_iterator;

		iterator				begin(void);
		iterator				end(void);

		const_iterator			begin(void) const;
		const_iterator			end(void) const;

		reverse_iterator		rbegin(void);
		reverse_iterator		rend(void);

		const_reverse_iterator	rbegin(void) const;
		const_reverse_iterator	rend(void) const;
};

// =============================================================================
// Ctors & Dtors
// =============================================================================

template <typename T, typename Container>
MutantStack<T, Container>::MutantStack():
	std::stack<T, Container>()
{
	std::cout << "Default Constructor is called\n";
}

template <typename T, typename Container>
MutantStack<T, Container>::MutantStack(const MutantStack &other):
	std::stack<T, Container>(other)
{
	std::cout << "Copy Constructor is called\n";
}

template <typename T, typename Container>
MutantStack<T, Container>::~MutantStack()
{
	std::cout << "Default Destructor is called\n";
}

// =============================================================================
// Copy Assignment Operator
// =============================================================================
template <typename T, typename Container>
MutantStack<T, Container>	&MutantStack<T, Container>::operator=(const MutantStack &other)
{
	if (this != &other)
		std::stack<T, Container>::operator=(other);
	return (*this);
}

// =============================================================================
// Iterators
// =============================================================================
/*
	- c is the protected member underlying container inside std::stack.
	- Expose its iterators so MutantStack can be iterated like the underlying container.
*/
template <typename T, typename Container>
typename MutantStack<T, Container>::iterator MutantStack<T, Container>::begin(void)
{
	return (this->c.begin());
}

template <typename T, typename Container>
typename MutantStack<T, Container>::iterator MutantStack<T, Container>::end(void)
{
	return (this->c.end());
}

// =============================================================================
// Const_iterators
// =============================================================================
template <typename T, typename Container>
typename MutantStack<T, Container>::const_iterator MutantStack<T, Container>::begin(void) const
{
	return (this->c.begin());
}

template <typename T, typename Container>
typename MutantStack<T, Container>::const_iterator MutantStack<T, Container>::end(void) const
{
	return (this->c.end());
}

// =============================================================================
// Reverse_iterators
// =============================================================================
template <typename T, typename Container>
typename MutantStack<T, Container>::reverse_iterator MutantStack<T, Container>::rbegin(void)
{
	return (this->c.rbegin());
}

template <typename T, typename Container>
typename MutantStack<T, Container>::reverse_iterator MutantStack<T, Container>::rend(void)
{
	return (this->c.rend());
}

// =============================================================================
// Const_reverse_iterators
// =============================================================================
template <typename T, typename Container>
typename MutantStack<T, Container>::const_reverse_iterator MutantStack<T, Container>::rbegin(void) const
{
	return (this->c.rbegin());
}

template <typename T, typename Container>
typename MutantStack<T, Container>::const_reverse_iterator MutantStack<T, Container>::rend(void) const
{
	return (this->c.rend());
}

#endif
