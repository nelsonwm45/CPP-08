#include "Span.hpp"
#include <list>

static void divider(std::string const & title, std::string const &colour)
{
	std::cout << colour << "\n// ===================================================================\n" << RESET;
	std::cout << colour << "// " << title << "\n" << RESET;
	std::cout << colour << "// ===================================================================\n" << RESET;
	return;
}

static void safeShortest(const Span& sp)
{
	try 
	{
		std::cout << "shortestSpan = " << sp.shortestSpan() << "\n";
	}
	catch (const std::exception& e)
	{
		std::cout << RED << e.what() << RESET << "\n";
	}
}
static void safeLongest(const Span& sp)
{
	try
	{
		std::cout << "longestSpan  = " << sp.longestSpan() << "\n";
	}
	catch (const std::exception& e)
	{
		std::cout << RED << e.what() << RESET << "\n";
	}
}

int main()
{
	{
		divider("From Subject PDF", GREEN);
		Span sp = Span(5);
		sp.addNumber(6);
		sp.addNumber(3);
		sp.addNumber(17);
		sp.addNumber(9);
		sp.addNumber(11);
		std::cout << sp.shortestSpan() << std::endl;
		std::cout << sp.longestSpan() << std::endl;
	}
	{
		divider("Exceptions: StorageIsFullException (addNumber)", BLUE);
		Span sp(3);
		sp.addNumber(1);
		sp.addNumber(2);
		sp.addNumber(3);
		try
		{
			sp.addNumber(4); // should throw
		}
		catch (const std::exception& e)
		{
			std::cout << RED << e.what() << RESET << "\n";
		}
	}
	{
		divider("Exceptions: InsufficientElementException (shortest/longest)", BLUE);
		Span empty(5);
		safeShortest(empty); // empty
		safeLongest(empty);  // empty

		Span one(5);
		one.addNumber(42);
		safeShortest(one); // 1 element
		safeLongest(one);  // 1 element
	}
	{
		divider("Exceptions: EmptyElementToAddException (addRange with empty range)", BLUE);
		Span sp(5);
		int arr[] = {1,2,3};
		// empty range: same begin==end
		try
		{
			sp.addRange(arr, arr);
		}
		catch (const std::exception& e)
		{
			std::cout << RED << e.what() << RESET << "\n";
		}
	}
	{
		divider("Exceptions: StorageIsFullException (addRange overflow)", BLUE);
		Span sp(4);
		int arr[] = {10, 20, 30, 40, 50};
		try
		{
			sp.addRange(arr, arr + 5); // too many for capacity 4
		}
		catch (const std::exception& e)
		{
			std::cout << RED << e.what() << RESET << "\n";
		}
	}
	{
		divider("addRange from C-array", CYAN);
		Span sp(6);
		int arr[] = {7, 1, 3};
		sp.addRange(arr, arr + 3);
		sp.addNumber(10);
		sp.addNumber(-4);
		sp.addNumber(8);
		safeShortest(sp);
		safeLongest(sp);
	}
	{
		divider("addRange from std::vector<int>", CYAN);
		Span sp(6);
		std::vector<int> v;
		v.push_back(100);
		v.push_back(101);
		v.push_back(150);
		sp.addRange(v.begin(), v.end());
		sp.addNumber(90);
		sp.addNumber(120);
		sp.addNumber(151);
		safeShortest(sp);
		safeLongest(sp);
	}
	{
		divider("addRange from std::list<int>", CYAN);
		Span sp(7);
		std::list<int> lst;
		lst.push_back(5);
		lst.push_back(6);
		lst.push_back(8);
		sp.addRange(lst.begin(), lst.end());
		sp.addNumber(100);
		sp.addNumber(1);
		sp.addNumber(50);
		sp.addNumber(51);
		safeShortest(sp);
		safeLongest(sp);
	}
	{
		divider("10,000 numbers — predictable (0..9999)", MAGENTA);
		const unsigned COUNT = 10000;
		Span sp(COUNT);
		std::vector<int> v;
		v.reserve(COUNT);
		for (unsigned i = 0; i < COUNT; ++i)
			v.push_back(static_cast<int>(i));
		sp.addRange(v.begin(), v.end());

		long shortest = sp.shortestSpan();   // should be 1
		long longest  = sp.longestSpan();    // should be 9999 - 0 = 9999

		std::cout << "shortestSpan = " << shortest << " (expect 1)\n";
		std::cout << "longestSpan  = " << longest  << " (expect 9999)\n";
	}
	{
		divider("Capacity edge-cases (exact fill via addRange + addNumber mix)", YELLOW);
		Span sp(5);
		int arr[] = {2,4,6};
		sp.addRange(arr, arr + 3); // 3 used
		sp.addNumber(-10);         // 4 used
		try
		{
			// add 2 more -> overflow
			int more[] = {8, 9};
			sp.addRange(more, more + 2);
		}
		catch (const std::exception& e)
		{
			std::cout << RED << e.what() << RESET << "\n";
		}
		// Fill with exactly one to cap at 5
		sp.addNumber(9); // 5 used
		safeShortest(sp);
		safeLongest(sp);
	}
}