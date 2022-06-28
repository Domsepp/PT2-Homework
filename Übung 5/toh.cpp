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
			a.second.erase(a.second.end());
			c.second.emplace_back(i);
			print();
			std::ignore = getchar();
		}else{
			simulateNextStep(n-1, a, c, b);
			simulateNextStep(1, a, b, c);
			simulateNextStep(n-1, b, a, c);
		}
		
		// move n plates from a over b to c  --> should be ready, but can't check correctness without proper printing
		// TODO 5.2: Implement ToH and print --> i think calling print() should do it
	}

	void print()
	{
#ifdef _WIN32
		std::system("cls");
#else
		std::system("clear");
#endif

		// TODO 5.2: Print current state	--> this produces the correct result once, but then produces bs
		std::system("cls");
		for (size_t i = item_count - 1; i >= 0; --i)
		{
			for (auto &tower: towers)
			{
				std::cout << "\t";
				for (size_t j = 0; j < item_count + 1; j++)
				{
					std::cout << " ";
				}
				std::cout << "#";
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
					std::cout << "#";
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
						std::cout << "&";
					}
					for (size_t j = 0; j < item_count-tower.second[i] + 1; j++)
					{
						std::cout << " ";
					}
				}
			}
			std::cout << "\n";
		}
		//somehow the following does not get printed
		for (size_t i = 0; i < 3; i++)
		{
			std::cout << "\t";
			for (size_t j = 0; j < 2*item_count+3; j++)
			{
				std::cout << "#";
			}
			
		}
		

		std::cout << std::endl << std::endl;
	}

	std::array<Tower, 3> towers{ Tower('A', {}), Tower('B', {}), Tower('C', {}) };

	int item_count;
	unsigned int moves = 0;
};

std::string generate_line(int width){
	std::string line = "  ";
	std::cout << width << std::endl;
	for(int i = 1; i<=21;i++){
		if(i<=((21-width)/2) || i>=(21-((21-width)/2))){
			line.push_back(' ');
		}
		else{
			line.push_back('+');
		}
	}
	line.push_back(' ');
	return line;
}

void pretty_print(int first_pole, int second_pole, int third_pole){
	std::vector<std::string> ouput_graphics;
	for(int i = 0; i<first_pole;i++){
		ouput_graphics.push_back(generate_line(((i*2)+3)));	
	}
	ouput_graphics.push_back(" #####################  #####################  ##################### ");
	for(std::string &line: ouput_graphics){
		std::cout << line << std::endl;
	}
}

int main()
{
	/*constexpr int ItemCount = 4;
	TowerOfHanoi toh(ItemCount);
	toh.runSimulation();*/
	std::cout << "Press any key to continue...";
	char ch = getchar();
	std::cout << ch;
	if(ch){
		std::cout << "Congrats"<< std::endl;
		pretty_print(5,4,5);
	}

	return 0;
}
