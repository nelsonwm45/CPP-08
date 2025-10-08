#include "Span.hpp"

// =============================================================================
// Ctors & Dtors
// =============================================================================

Span::Span()
{}

Span::Span(unsigned int n):
	_n(n)
{
	this->_intStorage.reserve(n); // preallocate memory
}

Span::Span(const Span &other):
	_n(other._n),
	_intStorage(other._intStorage)
{}

Span::~Span()
{}

// =============================================================================
// Copy Assignment Operator
// =============================================================================

Span	&Span::operator=(const Span &other)
{
	if (this != &other)
	{
		this->_n = other._n;
		this->_intStorage = other._intStorage;
	}
	return (*this);
}

// =============================================================================
// Member Functions
// =============================================================================
void	Span::addNumber(int num)
{
	if (this->checkFullStorage() == true)
		throw (Span::StorageIsFullException());
	this->_intStorage.push_back(num);
}

// Smallest distance between number
// Sort and Keep comparing to get the smallest
long	Span::shortestSpan() const
{
	if (this->insufficientElement() == true)
		throw (Span::InsufficientElementException());
	std::vector<int> sorted = this->_intStorage;
	std::sort(sorted.begin(), sorted.end());

	long	bestDistance = std::numeric_limits<long>::max();
	for (size_t	i = 1; i < sorted.size(); i++)
	{
		long distance = static_cast<long>(sorted[i] - sorted[i - 1]);
		if (distance < bestDistance)
			bestDistance = distance;
	}
	return (bestDistance);
}

// Biggest distance between numbers
// Biggest - smallest number
long	Span::longestSpan() const
{
	if (this->insufficientElement() == true)
		throw (Span::InsufficientElementException());
	std::vector<int>::const_iterator	largestIt = std::max_element(_intStorage.begin(), _intStorage.end());
	std::vector<int>::const_iterator	smallestIt = std::min_element(_intStorage.begin(), _intStorage.end());
	long longestSpan = static_cast<long>(*largestIt - *smallestIt);
	return (longestSpan);
}

// =============================================================================
// Helper
// =============================================================================
bool	Span::checkFullStorage() const
{
	if (this->_intStorage.size() >= this->_n)
		return (true);
	return (false);
}

bool	Span::insufficientElement() const
{
	if (this->_intStorage.size() <= 1)
		return (true);
	return (false);
}

void	Span::printAllElements() const
{
	std::cout << "\n====Elements Inside the IntStorage====\n";
	std::cout << "Number of Elements: " << _intStorage.size() << "\n";
	for (std::vector<int>::const_iterator it = _intStorage.begin(); it != _intStorage.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
}


// =============================================================================
// Exceptions
// =============================================================================
const char	*Span::StorageIsFullException::what() const throw ()
{
	return ("[SpanException]: Int Storage is Full!");
}

const char	*Span::InsufficientElementException::what() const throw()
{
	return ("[SpanException]: Insufficient Element in Storage!");
}

const char	*Span::EmptyElementToAddException::what() const throw()
{
	return ("[SpanException]: Empty Incoming Elements | Nothing to Add!");
}