#ifndef SPAN_HPP
# define SPAN_HPP

# define RED "\033[31m"
# define GREEN "\033[32m"
# define BLUE "\033[34m"
# define YELLOW "\033[33m"
# define CYAN "\033[36m"
# define MAGENTA "\033[35m"
# define WHITE "\033[37m"
# define RESET "\033[0m"

# include <iostream>
# include <algorithm> 
# include <vector>
# include <stdexcept>
# include <limits>
# include <iterator>

class Span
{
	private:
		unsigned int _n;
		std::vector<int>	_intStorage;

		Span();
	public:
		Span(unsigned int n);
		~Span();
		Span(const Span &other);
		Span	&operator=(const Span &other);

		// Members Fx
		void	addNumber(int num);
		long	shortestSpan() const;
		long	longestSpan() const;

		template <typename T>
		void	addRange(T first, T last);


		// Helper
		bool	checkFullStorage() const;
		bool	insufficientElement() const;
		void	printAllElements() const;

		class	StorageIsFullException : public std::exception
		{
			public:
				virtual const char *what() const throw();
		};

		class	InsufficientElementException : public std::exception
		{
			public:
				virtual const char *what() const throw();
		};

		class	EmptyElementToAddException : public std::exception
		{
			public:
				virtual const char *what() const throw();
		};
};

// Add a range of number from another container to current container
template <typename T>
void	Span::addRange(T first, T last)
{
	// Count number of incoming elements
	size_t	incoming = static_cast<size_t>(std::distance(first, last));
	if (incoming == 0)
		throw (Span::EmptyElementToAddException());

	// Count space left in intStorage
	size_t	leftoverSpaces = 0;
	if (static_cast<size_t>(_n) > _intStorage.size())
		leftoverSpaces = static_cast<size_t>(_n) - _intStorage.size();
	
	// Check if the spaces left enough to store incomingElements
	if (incoming > leftoverSpaces)
		throw (Span::StorageIsFullException());
	
	// Insert the incoming Elements
	this->_intStorage.insert(this->_intStorage.end(), first, last);
}

#endif