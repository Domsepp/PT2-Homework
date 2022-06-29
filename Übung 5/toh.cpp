#include <array>
#include <iostream>
#include <tuple>
#include <vector>
#include <fstream>


class TowerOfHanoi
{
public:
	using Tower = std::pair<char, std::vector<int>>;

	explicit TowerOfHanoi(int item_count)
		: item_count(item_count)
	{
		for (int i = item_count; i > 0; --i)
		{
			towers[0].second.emplace_back(i);
		}
	}

	void runSimulation()
	{
		print();
		std::ignore = getchar();
		simulateNextStep(item_count, towers[0], towers[1], towers[2]);
		std::cout << "Minimal number of moves: " << moves << std::endl;

		std::ignore = getchar();
	}

private:
	void simulateNextStep(const int n, Tower& a, Tower& b, Tower& c)
	{	
		if (n == 1)
		{	
			int i = a.second[a.second.size()-1];
			a.second.erase(a.second.end()-1);
			c.second.emplace_back(i);
			moves ++;
			print();
			std::ignore = getchar();
		}else{
			simulateNextStep(n-1, a, c, b);
			simulateNextStep(1, a, b, c);
			simulateNextStep(n-1, b, a, c);
		}
	}

	void print()
	{

#ifdef _WIN32
		std::system("cls");
#else
		std::system("clear");
#endif
		for (int i = item_count - 1; i >= 0; i--)
		{
			for (auto &tower: towers)
			{
				std::cout << "\t";
				for (size_t j = 0; j < item_count + 1; j++)
				{
					std::cout << " ";
				}
				std::cout << char(219);
				for (size_t j = 0; j < item_count + 1; j++)
				{
					std::cout << " ";
				}
			}
			std::cout << "\n";
			for (auto &tower: towers)
			{
				std::cout << "\t";
				if (tower.second.size() < i + 1)
				{
					for (size_t j = 0; j < item_count + 1; j++)
					{
						std::cout << " ";
					}
					std::cout << char(219);
					for (size_t j = 0; j < item_count + 1; j++)
					{
						std::cout << " ";
					}
				} else {
					for (size_t j = 0; j < item_count-tower.second[i] + 1; j++)
					{
						std::cout << " ";
					}
					for (size_t j = 0; j < 2*(tower.second[i]) + 1; j++)
					{
						std::cout << char(219);
					}
					for (size_t j = 0; j < item_count-tower.second[i] + 1; j++)
					{
						std::cout << " ";
					}
				}
			}
			std::cout << "\n";
		}
		for (size_t i = 0; i < 3; i++)
		{
			std::cout << "\t";
			for (size_t j = 0; j < 2*item_count + 3; j++)
			{
				std::cout << "-";
			}
		}
		std::cout << std::endl;
		for (size_t i = 0; i < 3; i++)
		{
			std::cout << "\t";
			for (size_t j = 0; j < item_count + 1; j++)
			{
				std::cout << "-";
			}
			std::cout << char('A' + i);
			for (size_t j = 0; j < item_count + 1; j++)
			{
				std::cout << "-";
			}
		}
		std::cout << std::endl;
	}
	
	std::array<Tower, 3> towers{ Tower('A', {}), Tower('B', {}), Tower('C', {}) };

	int item_count;
	unsigned int moves = 0;
};


int main()
{
	constexpr int ItemCount = 5;
	TowerOfHanoi toh(ItemCount);
	toh.runSimulation();

	return 0;
}
