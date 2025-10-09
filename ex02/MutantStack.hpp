#ifndef MUTANTSTACK_HPP
# define MUTANTSTACK_HPP

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


/*
	std::stack<T> is an adapter over an underlying container (by default std::deque<T>).

	typedef :
		what? :creates a type alias (a new name for an existing type)
		when? :whenever you want a shorter/clearer name for a type
	
	typename :
		what? : tells the compiler that a dependent(depends on template param) name is a type, by default compiler thinks it as a "value" (static data/member) rather than a "type"
		why need?: In templates, a qualified name that depends on a template parameter (e.g. T::container_type) could be a type or a static member. 
					The compiler assumes “not a type” unless you say typename
		when no need?
			1) Not dependent: if the name doesn’t depend on a template parameter.
				std::vector<int>::iterator it;   // OK, no 'typename' here (not dependent)
			2) Base class lists and constructor initializer lists (grammar already expects a type):
				template <typename T>
				struct D : T::Base {        // no 'typename' allowed here
					D() : T::Base() {}      // no 'typename' here either
				};
			3) Before template parameter lists or ordinary type names:
				template <typename T> struct X {};   // 'typename' used correctly here (template params)
				long x;                               // obviously no 'typename'

*/
template <typename T>
class	MutantStack: public std::stack<T>
{
	private:


	public:
		MutantStack();
		MutantStack(const MutantStack &other);
		MutantStack &operator=(const MutantStack &other);
		~MutantStack();

		typedef typename std::stack<T>::container_type::iterator				iterator;
		typedef typename std::stack<T>::container_type::const_iterator			const_iterator;
		typedef typename std::stack<T>::container_type::reverse_iterator		reverse_iterator;
		typedef typename std::stack<T>::container_type::const_reverse_iterator	const_reverse_iterator;

		iterator	begin(void);
		iterator	end(void);

		const_iterator	begin(void) const;
		const_iterator	end(void) const;

		reverse_iterator	rbegin(void);
		reverse_iterator	rend(void);

		const_reverse_iterator	rbegin(void) const;
		const_reverse_iterator	rend(void) const;
};

// =============================================================================
// Ctors & Dtors
// =============================================================================

template <typename T>
MutantStack<T>::MutantStack():
	std::stack<T>()
{
	std::cout << "Default Constructor is called\n";
}

template <typename T>
MutantStack<T>::MutantStack(const MutantStack &other):
	std::stack<T>(other)
{
	std::cout << "Copy Constructor is called\n";
}

template <typename T>
MutantStack<T>::~MutantStack()
{
	std::cout << "Default Destructor is called\n";
}

// =============================================================================
// Copy Assignment Operator
// =============================================================================
template <typename T>
MutantStack<T>	&MutantStack<T>::operator=(const MutantStack &other)
{
	if (this != &other)
		std::stack<T>::operator=(other);
	return (*this);
}

// =============================================================================
// Iterators
// =============================================================================
/*
	- c is the protected member underlying container inside std::stack.
	- std::stack is just an adapter; it forwards to a real container it keeps as a member named c (type container_type). By default that’s a std::deque<T>.
	- c is protected, so a class derived from std::stack<T> can access it and thus expose its iterators
		like : this->c.begin(); this->c.end()
*/
template <typename T>
typename MutantStack<T>::iterator MutantStack<T>::begin(void)
{
	return (this->c.begin());
}

template <typename T>
typename MutantStack<T>::iterator MutantStack<T>::end(void)
{
	return (this->c.end());
}

// =============================================================================
// Const_iterators
// =============================================================================

template <typename T>
typename MutantStack<T>::const_iterator MutantStack<T>::begin(void) const
{
	return (this->c.begin());
}

template <typename T>
typename MutantStack<T>::const_iterator MutantStack<T>::end(void) const
{
	return (this->c.end());
}


// =============================================================================
// Reverse_iterators
// =============================================================================

template <typename T>
typename MutantStack<T>::reverse_iterator MutantStack<T>::rbegin(void)
{
	return (this->c.rbegin());
}

template <typename T>
typename MutantStack<T>::reverse_iterator MutantStack<T>::rend(void)
{
	return (this->c.rend());
}

// =============================================================================
// Const_reverse_iterators
// =============================================================================

template <typename T>
typename MutantStack<T>::const_reverse_iterator MutantStack<T>::rbegin(void) const
{
	return (this->c.rbegin());
}

template <typename T>
typename MutantStack<T>::const_reverse_iterator MutantStack<T>::rend(void) const
{
	return (this->c.rend());
}

#endif