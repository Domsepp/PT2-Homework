#include "bitmap_image.hpp"

#include <cstring>
#include <iostream>
#include <random>
#include <vector>

class Raster
{
public:
	Raster(int w, int h)
		: m_width(w)
		, m_height(h)
		, m_data(static_cast<unsigned int>(w * h))
	{}

	void fill(float seedProbability)
	{
		// TODO 4.1b: Fill randomly
		// Probability of value 1 is seedProbability, otherwise value is 0
	}

	void loadRasterFromFile(const std::string& filename)
	{
		bitmap_image image(filename);

		if (!image)
		{
			std::cerr << "Could not open bitmap!" << std::endl;
			return;
		}

		m_height = static_cast<int>(image.height());
		m_width = static_cast<int>(image.width());

		m_data.resize(static_cast<unsigned int>(m_width * m_height));

		// TODO 4.1b: Load image by using image.get_pixel
		// A black pixel represents 1, all other values represent 0
	}

	void save(const std::string& filename)
	{
		// TODO 4.1b: Save image by using image.set_pixel
		// Living cells should be stored as black pixels, all other pixels are white
		bitmap_image image(m_width, m_height);

		image.save_image(filename);
	}

	int width() const
	{
		return m_width;
	}

	int height() const
	{
		return m_height;
	}

	const std::vector<int>& data() const
	{
		return m_data;
	}

	int value(int x, int y)
	{
		// TODO 4.1a Implement getting value of m_data
		return 0;
	}

	void setValue(int x, int y, int value)
	{
		// TODO 4.1a Implement setting value into m_data
	}

private:
	int m_width;
	int m_height;
	std::vector<int> m_data;
};

class GameOfLife
{
public:
	explicit GameOfLife(Raster raster)
		: m_raster(std::move(raster))
		, m_gen(std::random_device()())
	{}

	int cellValue(int x, int y, bool isTorus)
	{
		// TODO 4.1c: Return whether cell is alive (1) or not (0)
		// In case isTorus is false and (x, y) is outside of raster, return 0
		// In case isTorus is true and (x, y) is outside of raster use value of matching cell of opposite side

		return 0;
	}

	void simulateInversion(float inversionFactor)
	{
		if (inversionFactor <= 0)
		{
			return;
		}

		// TODO 4.1d: Flip some cells randomly (probability to flip for each cell is inversionFactor)
	}

	void simulateNextState(bool isTorus)
	{
		// TODO 4.1c: Play one iteration of Game of Life
	}

	void save(const std::string& filename)
	{
		m_raster.save(filename);
	}

private:
	Raster m_raster;
	std::mt19937 m_gen;
};

// This struct parses all necessary command line parameters. It is already complete and doesn't have to be
// modified. However - feel free to add support for additional arguments if you like.
struct CommandLineParameter
{
	int width = 0;
	int height = 0;
	float seedProbability = 0.0F;
	std::string patternFilename;
	std::string outputDirectory;
	float inversionFactor = 0.0F;
	bool isTorus = false;
	int maxIterations = 20;
};

int main(int argc, char* argv[])
{
	if (argc % 2 == 0)
	{
		std::cerr << "Missing value for " << argv[argc - 1] << std::endl;
		argc--;
	}

	CommandLineParameter parameter;
	for (int i = 1; i < argc; i += 2)
	{
		try
		{
			if (strcmp(argv[i], "-w") == 0)
			{
				parameter.width = std::stoi(argv[i + 1]);
			}
			else if (strcmp(argv[i], "-h") == 0)
			{
				parameter.height = std::stoi(argv[i + 1]);
			}
			else if (strcmp(argv[i], "-s") == 0)
			{
				parameter.seedProbability = std::stof(argv[i + 1]);
			}
			else if (strcmp(argv[i], "-p") == 0)
			{
				parameter.patternFilename = argv[i + 1];
			}
			else if (strcmp(argv[i], "-o") == 0)
			{
				parameter.outputDirectory = argv[i + 1];
			}
			else if (strcmp(argv[i], "-iv") == 0)
			{
				parameter.inversionFactor = std::stof(argv[i + 1]);
			}
			else if (strcmp(argv[i], "-t") == 0)
			{
				parameter.isTorus = strcmp(argv[i + 1], "0") != 0;
			}
			else if (strcmp(argv[i], "-i") == 0)
			{
				parameter.maxIterations = std::stoi(argv[i + 1]);
			}
			else
			{
				std::cerr << "Unknown parameter " << argv[i] << std::endl;
				return 1;
			}
		}
		catch (...)
		{
			std::cerr << "Invalid value \"" << argv[i + 1] << "\" for parameter " << argv[i] << std::endl;
			return 1;
		}
	}

	if ((parameter.width != 0 || parameter.height != 0) && !parameter.patternFilename.empty())
	{
		std::cerr << "Width and height cannot be combined with a pattern." << std::endl;
		return 1;
	}

	if (parameter.width < 0 || parameter.height < 0)
	{
		std::cerr << "Width or height has a invalid value." << std::endl;
		return 1;
	}

	Raster raster(parameter.width, parameter.height);
	if (!parameter.patternFilename.empty())
	{
		raster.loadRasterFromFile(parameter.patternFilename);
	}
	else
	{
		raster.fill(parameter.seedProbability);
	}

	GameOfLife gol(std::move(raster));
	for (int iteration = 0; iteration <= parameter.maxIterations; iteration++)
	{
		gol.save(parameter.outputDirectory + "game_of_life_" + std::to_string(iteration) + ".bmp");
		gol.simulateInversion(parameter.inversionFactor);
		gol.simulateNextState(parameter.isTorus);
	}

	return 0;
}
