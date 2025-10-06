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
		divider("easyfind() function test", GREEN);
		std::vector<int> v;
		v.push_back(1);
		v.push_back(42);
		v.push_back(27);
		std::cout << *easyfind(v, 42) << std::endl;

		divider("easyfind() exception test", BLUE);
		try
		{
			easyfind(v, -1);
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << '\n';
		}
	}
}