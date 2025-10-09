#include "MutantStack.hpp"
#include <list>

static void divider(std::string const & title, std::string const &colour)
{
	std::cout << colour << "\n// ===================================================================\n" << RESET;
	std::cout << colour << "// " << title << "\n" << RESET;
	std::cout << colour << "// ===================================================================\n" << RESET;
	return;
}

template <typename Container>
void print_bottom_to_top(const Container &c)
{
	std::cout << "\n--- (BOTTOM -> TOP) ---\n";
	typename Container::const_iterator it  = c.begin();
	typename Container::const_iterator ite = c.end();
	for (; it != ite; ++it)
		std::cout << "[" << *it << "]\n";
}

template <typename Container>
void print_top_to_bottom(const Container &c)
{
	std::cout << "\n--- (TOP -> BOTTOM) ---\n";
	typename Container::const_reverse_iterator rit  = c.rbegin();
	typename Container::const_reverse_iterator rite = c.rend();
	for (; rit != rite; ++rit)
		std::cout << "[" << *rit << "]\n";
}


int	main()
{
	{
		divider("From Subject PDF (Modified)", GREEN);
		MutantStack<int> mstack;
		if (mstack.empty())
			std::cout << "mstack is empty after default construction!\n";
		mstack.push(5);
		mstack.push(17);
		std::cout << "Top: " << mstack.top() << std::endl;
		std::cout << "Stack Size Before Pop: " << mstack.size() << std::endl;
		mstack.pop();
		std::cout << "Stack Size After Pop: " << mstack.size() << std::endl;
		mstack.push(3);
		mstack.push(5);
		mstack.push(737);
		mstack.push(0);
		MutantStack<int>::iterator it = mstack.begin();
		MutantStack<int>::iterator ite = mstack.end();
		++it;
		--it;
		std::cout << "\n----Printing a Stack [BOTTOM -> TOP]----\n";
		while (it != ite)
		{
			std::cout << "[" << *it << "]" << std::endl;
			++it;
		}
		std::cout << "\nCalling std::stack Copy Constructor\n";
		std::stack<int> s(mstack);
		{

			std::cout << "\n--- Normal Stack [s] (TOP -> BOTTOM) ---\n";
			std::stack<int> tmp = s;
			while (!tmp.empty())
			{
				std::cout << "[" << tmp.top() << "]\n";
				tmp.pop();
			}
		}
		{
			std::cout << "\n--- Normal Stack [s] (BOTTOM -> TOP) ---\n";
			std::stack<int> tmp = s;     // copy
			std::stack<int> aux;         // helper to reverse
			while (!tmp.empty())
			{
				// reverse once
				aux.push(tmp.top());
				tmp.pop();
			}
			while (!aux.empty())
			{
				// now bottom->top
				std::cout << "[" << aux.top() << "]\n";
				aux.pop();
			}
		}
	}
	{
		divider("Testing Iterators Printing With MutantStack", BLUE);
		MutantStack<int> mstack;
		mstack.push(5);
		mstack.push(17);
		mstack.pop();
		mstack.push(3);
		mstack.push(5);
		mstack.push(737);
		mstack.push(0);

		print_bottom_to_top(mstack);
		print_top_to_bottom(mstack);
	}

	{
		divider("Replace MutantStack with std::list — outputs should match", YELLOW);

		// Reproduce the SAME logical sequence using std::list:
		// push 5, push 17, pop (remove 17), then push 3, 5, 737, 0.
		std::list<int> lst;
		if (lst.empty())
			std::cout << "lst is empty after default construction\n";
		lst.push_back(5);
		lst.push_back(17);
		std::cout << "Top: " << lst.back() << std::endl;
		std::cout << "List Size Before Pop: " << lst.size() << std::endl;
		lst.pop_back();         // removes 17 (like stack::pop)
		std::cout << "List Size After Pop: " << lst.size() << std::endl;
		lst.push_back(3);
		lst.push_back(5);
		lst.push_back(737);
		lst.push_back(0);

		// Now print via iterators. Should match the MutantStack output.
		print_bottom_to_top(lst);   // list.begin()..end() is bottom->top (oldest to newest)
		print_top_to_bottom(lst);   // list.rbegin()..rend() is top->bottom (newest to oldest)
	}
}