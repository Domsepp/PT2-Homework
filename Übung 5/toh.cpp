#include <array>
#include <iostream>
#include <tuple>
#include <vector>

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
			a.second.erase(a.second.end());
			c.second.emplace_back(i);
			print();
		}else{
			simulateNextStep(n-1, a, c, b);
			simulateNextStep(1, a, b, c);
			simulateNextStep(n-1, b, a, c);
		}
		
		// move n plates from a over b to c  --> should be ready, but can't check correctness without printing
		// TODO 5.2: Implement ToH and print --> i think calling print() should do it
	}

	void print()
	{
#ifdef _WIN32
		std::system("cls");
#else
		std::system("clear");
#endif

		// TODO 5.2: Print current state

		std::cout << std::endl << std::endl;
	}

	std::array<Tower, 3> towers{ Tower('A', {}), Tower('B', {}), Tower('C', {}) };

	int item_count;
	unsigned int moves = 0;
};

int main()
{
	constexpr int ItemCount = 4;
	TowerOfHanoi toh(ItemCount);
	toh.runSimulation();

	return 0;
}
