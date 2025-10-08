#include "easyfind.hpp"

static void divider(std::string const & title, std::string const &colour)
{
	std::cout << colour << "\n// ===================================================================\n" << RESET;
	std::cout << colour << "// " << title << "\n" << RESET;
	std::cout << colour << "// ===================================================================\n" << RESET;
	return;
}

int main()
{
	{
		divider("easyfind() - [Vector Success Test]", GREEN);
		std::vector<int> v;
		v.push_back(1);
		v.push_back(42);
		v.push_back(27);
		std::vector<int>::iterator it = easyfind(v, 42);
		std::cout << "[Vector]: " << *it << std::endl;
		// std::cout << *easyfind(v, 42) << std::endl; // same output as above

		divider("easyfind() - [Vector Exception Test]", GREEN);
		try
		{
			easyfind(v, -1);
		}
		catch(const std::exception &e)
		{
			std::cerr << e.what() << '\n';
		}

		divider("easyfind() - [Vector Empty Container Test]", GREEN);
		std::vector<int> emptyv;
		try
		{
			easyfind(emptyv, 1);
		}
		catch(const std::exception &e)
		{
			std::cerr << e.what() << '\n';
		}

		divider("easyfind() - [Vector Const Success Test]", GREEN);
		const std::vector<int> cv = v; // reuse filled vector
		std::vector<int>::const_iterator cit = easyfind(cv, 42);
		std::cout << "[Vector const]: " << *cit << std::endl;

		divider("easyfind() - [Vector Const Exception Test]", GREEN);
		try
		{
			easyfind(cv, 999);
		}
		catch (const std::exception &e)
		{
			std::cerr << e.what() << '\n';
		}
	}
	{
		divider("easyfind() - [Deque Success Test]", YELLOW);
		std::deque<int> dq;
		dq.push_back(10);
		dq.push_back(27);
		dq.push_back(42);
		dq.push_back(27); // duplicate to check "first match" behavior
		std::deque<int>::iterator it = easyfind(dq, 27);
		std::cout << "[Deque]: " << *it << std::endl;

		divider("easyfind() - [Deque Exception Test]", YELLOW);
		try
		{
			easyfind(dq, 12345);
		}
		catch (const std::exception &e)
		{
			std::cerr << e.what() << std::endl;
		}

		divider("easyfind() - [Deque Empty Container Test]", YELLOW);
		std::deque<int> emptydq;
		try
		{
			easyfind(emptydq, 1);
		}
		catch(const std::exception &e)
		{
			std::cerr << e.what() << '\n';
		}

		divider("easyfind() - [Deque Const Success Test]", YELLOW);
		const std::deque<int> cdq = dq; // reuse filled deque
		std::deque<int>::const_iterator dcit = easyfind(cdq, 27); // first 27
		std::cout << "[Deque const]: " << *dcit << std::endl;

		divider("easyfind() - [Deque Const Exception Test]", YELLOW);
		try
		{
			easyfind(cdq, -777);
		}
		catch (const std::exception &e)
		{
			std::cerr << e.what() << '\n';
		}
	}
	{
		divider("easyfind() - [List Success Test]", BLUE);
		std::list<int> lst;
		lst.push_back(0);
		lst.push_back(-5);
		lst.push_back(42);
		lst.push_back(0); // duplicate to check "first match" behavior
		std::list<int>::iterator it = easyfind(lst, 0);
		std::cout << "[List]: " << *it << std::endl;

		divider("easyfind() - [List Exception Test]", BLUE);
		try
		{
			easyfind(lst, 12345);
		}
		catch (const std::exception &e)
		{
			std::cerr << e.what() << std::endl;
		}

		divider("easyfind() - [List Empty Container Test]", BLUE);
		std::list<int> emptylst;
		try
		{
			easyfind(emptylst, 1);
		}
		catch(const std::exception &e)
		{
			std::cerr << e.what() << '\n';
		}

		divider("easyfind() - [List Const Success Test]", BLUE);
		const std::list<int> clst = lst; // reuse filled list
		std::list<int>::const_iterator lcit = easyfind(clst, 0); // first 0
		std::cout << "[List const]: " << *lcit << std::endl;

		divider("easyfind() - [List Const Exception Test]", BLUE);
		try
		{
			easyfind(clst, 31415);
		}
		catch (const std::exception &e)
		{
			std::cerr << e.what() << '\n';
		}
	}
}