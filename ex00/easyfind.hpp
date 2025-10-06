#ifndef EASYFIND_HPP
# define EASYFIND_HPP

# include <algorithm> // std::find
# include <stdexcept> 
# include <iostream>
# include <vector>

# define RED "\033[31m"
# define GREEN "\033[32m"
# define BLUE "\033[34m"
# define YELLOW "\033[33m"
# define CYAN "\033[36m"
# define MAGENTA "\033[35m"
# define WHITE "\033[37m"
# define RESET "\033[0m"

// Defining Exception if no match found
class	ElementNotFoundException : public std::exception
{
	public:
		virtual const char *what() const throw()
		{
			return ("[EasyFind Exception]: Element is not found in the container!");
		}
};

/*
	T is a container of integers

	easyfind() takes two parameters
		- Type T (means integers containers)
		- Integers

	Returns iterator to first match, or throws exception if not found
*/
// Non-const version
template <typename T>
typename T::iterator easyfind(T &container, int value)
{
	typename	T::iterator it = std::find(container.begin(), container.end(), value);
	if (it == container.end())
		throw (ElementNotFoundException());
	return (it);
}

// Const version
template <typename T>
typename T::const_iterator easyfind(const T &container, int value)
{
	typename	T::const_iterator it = std::find(container.begin(), container.end(), value);
	if (it == container.end())
		throw (ElementNotFoundException());
	return (it);
}

#endif