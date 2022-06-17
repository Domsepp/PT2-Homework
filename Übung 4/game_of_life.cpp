#include <cstring>
#include <iostream>
#include <random>
#include <vector>

#include "bitmap_image.hpp"

class Raster {
   public:
    Raster(int w, int h)
        : m_width(w), m_height(h), m_data(static_cast<unsigned int>(w * h)) {}

    void fill(float seedProbability) {
        // TODO 4.1b: Fill randomly
        // Probability of value 1 is seedProbability, otherwise value is 0
        std::mt19937 generator;
        std::uniform_int_distribution<int> distribution(1, 10000);
        for (size_t i = 0; i < m_height; i++) {
            for (size_t j = 0; j < m_width; j++) {
                int randomNumber = distribution(generator);
                if (randomNumber <= 10000 * seedProbability) {
                    setValue(i,j,1);
                } else {
                    setValue(i,j,0);
                }
            }
        }
    }

    void loadRasterFromFile(const std::string& filename) {
        bitmap_image image(filename);

        if (!image) {
            std::cerr << "Could NOT open bitmap!" << std::endl;
            return;
        }

        m_height = static_cast<int>(image.height());
        m_width = static_cast<int>(image.width());

        m_data.resize(static_cast<unsigned int>(m_width * m_height));

        // TODO 4.1b: Load image by using image.get_pixel
        // A black pixel represents 1, all other values represent 0
        unsigned char red = 0, green = 0, blue = 0;
        for (int i = 0; i < m_height; i++) {
            for (int j = 0; j < m_width; j++) {
                image.get_pixel(i, j, red, green, blue);
                if (red=='0' && green=='0' && blue=='0') {
                    setValue(i, j, 1);
                } else {
                    setValue(i, j, 0);
                }
            }
        }
    }

    void save(const std::string& filename) {
        // TODO 4.1b: Save image by using image.set_pixel
        // Living cells should be stored as black pixels, all other pixels are
        // white
        std::cout << m_width << ", " << m_height<<std::endl;
        bitmap_image image(m_width, m_height);
        
        for (int height = 0; height < m_height; height++){
            for (int width = 0; width < m_width; width++){
                std::cout << value(height, width) << std::endl;
                if (value(height, width)){
                    image.set_pixel(width, height, 255, 255, 255);
                }else{
                    image.set_pixel(width, height, 0, 0, 0);
                }
            }
        }
        image.save_image(filename);
    }

    int width() const { return m_width; }

    int height() const { return m_height; }

    const std::vector<int>& data() const { return m_data; }

    int value(int x, int y) { return m_data[x * m_width + y]; }

    void setValue(int x, int y, int value) { m_data[x * m_width + y] = value; }

   private:
    int m_width;
    int m_height;
    std::vector<int> m_data;
};

class GameOfLife {
   public:
    explicit GameOfLife(Raster raster)
        : m_raster(std::move(raster)), m_gen(std::random_device()()) {}

    int cellValue(int x, int y, bool isTorus) {
        // TODO 4.1c: Return whether cell is alive (1) or not (0)
        // In case isTorus is false and (x, y) is outside of raster, return 0
        // In case isTorus is true and (x, y) is outside of raster use value of
        // matching cell of opposite side
        if (isTorus){
            return m_raster.value(x%m_raster.width(),y%m_raster.height());
        }else{
            if (x>=0 && x<m_raster.width()&&y>=0&&y<m_raster.height()){
                return m_raster.value(x,y);
            }
        }
        return 0;
    }

    void simulateInversion(float inversionFactor) {
        if (inversionFactor <= 0) {
            return;
        }

        // TODO 4.1d: Flip some cells randomly (probability to flip for each
        // cell is inversionFactor)
        std::mt19937 generator;
        std::uniform_int_distribution<int> distribution(1, 10000);

        int rando = 0;

        for(int y = 0; y<m_raster.width();y++){
            for(int x = 0; x<m_raster.height();y++){
                if(distribution(generator)<10000*inversionFactor){
                    m_raster.setValue(x,y,!(m_raster.value(x,y)));
                }   
            }
        }
    }

    void simulateNextState(bool isTorus) {
        // TODO 4.1c: Play one iteration of Game of Life
        Raster newRaster(m_raster.width(), m_raster.height());
        int sum = 0;
        for (int width = 0; width < m_raster.width(); width++){
            for (int height = 0; height < m_raster.height(); height++){
                sum = 0;
                for (int i = -1; i < 2; i++){
                    for (int j = -1; j < 2; j++){
                        if (!(i==0 && j== 0)){
                            sum += cellValue(width+i,height+j, isTorus);
                        }
                    }
                }
                if ((m_raster.value(width, height) == 0 && sum == 3)||(m_raster.value(width, height)==1 && (sum >= 2 && sum <= 3))){
                    newRaster.setValue(width, height, 1);

                }else{
                    newRaster.setValue(width, height, 0);
                }
            }
        }
        m_raster = newRaster;
        
    }

    void save(const std::string& filename) { m_raster.save(filename); }

   private:
        Raster m_raster;
        std::mt19937 m_gen;
};

// This struct parses all necessary command line parameters. It is already
// complete and doesn't have to be modified. However - feel free to add support
// for additional arguments if you like.
struct CommandLineParameter {
    int width = 0;
    int height = 0;
    float seedProbability = 0.0F;
    std::string patternFilename;
    std::string outputDirectory;
    float inversionFactor = 0.0F;
    bool isTorus = false;
    int maxIterations = 20;
};

int main(int argc, char* argv[]) {
    if (argc % 2 == 0) {
        std::cerr << "Missing value for " << argv[argc - 1] << std::endl;
        argc--;
    }

    CommandLineParameter parameter;
    for (int i = 1; i < argc; i += 2) {
        try {
            if (strcmp(argv[i], "-w") == 0) {
                parameter.width = std::stoi(argv[i + 1]);
            } else if (strcmp(argv[i], "-h") == 0) {
                parameter.height = std::stoi(argv[i + 1]);
            } else if (strcmp(argv[i], "-s") == 0) {
                parameter.seedProbability = std::stof(argv[i + 1]);
            } else if (strcmp(argv[i], "-p") == 0) {
                parameter.patternFilename = argv[i + 1];
                std::cout << parameter.patternFilename << std::endl;
            } else if (strcmp(argv[i], "-o") == 0) {
                parameter.outputDirectory = argv[i + 1];
            } else if (strcmp(argv[i], "-iv") == 0) {
                parameter.inversionFactor = std::stof(argv[i + 1]);
            } else if (strcmp(argv[i], "-t") == 0) {
                parameter.isTorus = strcmp(argv[i + 1], "0") != 0;
            } else if (strcmp(argv[i], "-i") == 0) {
                parameter.maxIterations = std::stoi(argv[i + 1]);
            } else {
                std::cerr << "Unknown parameter " << argv[i] << std::endl;
                return 1;
            }
        } catch (...) {
            std::cerr << "Invalid value \"" << argv[i + 1]
                      << "\" for parameter " << argv[i] << std::endl;
            return 1;
        }
    }

    if ((parameter.width != 0 || parameter.height != 0) &&
        !parameter.patternFilename.empty()) {
        std::cerr << "Width and height cannot be combined with a pattern."
                  << std::endl;
        return 1;
    }

    if (parameter.width < 0 || parameter.height < 0) {
        std::cerr << "Width or height has a invalid value." << std::endl;
        return 1;
    }

    Raster raster(parameter.width, parameter.height);
    if (!parameter.patternFilename.empty()) {
        raster.loadRasterFromFile(parameter.patternFilename);
    } else {
        raster.fill(parameter.seedProbability);
    }

    GameOfLife gol(std::move(raster));
    for (int iteration = 0; iteration <= parameter.maxIterations; iteration++){
        gol.save(parameter.outputDirectory + "game_of_life_" +
                 std::to_string(iteration) + ".bmp");
        gol.simulateInversion(parameter.inversionFactor);
        gol.simulateNextState(parameter.isTorus);
    }

    return 0;
}
