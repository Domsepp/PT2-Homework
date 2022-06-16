#include <algorithm>
#include <array>
#include <cassert>
#include <fstream>
#include <iostream>
#include <limits>
#include <random>
#include <string>

// tour set and tour definitions
constexpr int N = 20;  // length of sequence, i.e., number of cities
constexpr int M = 20;  // population size per generation, i.e., no of tours
int minDist = std::numeric_limits<int>::max();  // global minimum of tour
                                                // length, over all generations
int maxDist = std::numeric_limits<int>::min();  // global maximum of tour
                                                // length, over all generations

// real data for N=20 (German city distances)
constexpr std::array<std::string_view, N> cityNames{
    "Berlin",    "Hamburg",     "Muenchen",  "Koeln",     "Frankfurt am Main",
    "Stuttgart", "Duesseldorf", "Dortmund",  "Essen",     "Bremen",
    "Dresden",   "Leipzig",     "Hannover",  "Nuernberg", "Duisburg",
    "Bochum",    "Wuppertal",   "Bielefeld", "Bonn",      "Muenster"};

constexpr std::array<std::array<int, N>, N> distanceTable = {
    // clang-format off
	{{  0, 255, 504, 477, 424, 512, 477, 422, 453, 315, 165, 149, 249, 378, 471, 439, 452, 336, 479, 398},
	 {255,   0, 612, 356, 393, 534, 338, 284, 308,  95, 377, 294, 132, 462, 321, 297, 320, 196, 370, 237},
	 {504, 612,   0, 456, 304, 190, 486, 477, 493, 582, 359, 360, 488, 150, 503, 486, 470, 483, 433, 510},
	 {477, 356, 456,   0, 152, 288,  34,  72,  57, 269, 474, 380, 249, 336,  56,  62,  37, 162,  25, 123},
	 {424, 393, 304, 152,   0, 152, 182, 177, 190, 329, 371, 293, 261, 187, 200, 184, 167, 212, 131, 218},
	 {512, 534, 190, 288, 152,   0, 322, 328, 335, 478, 412, 364, 401, 157, 342, 332, 311, 364, 264, 371},
	 {477, 338, 486,  34, 182, 322,   0,  57,  30, 248, 485, 389, 240, 363,  23,  41,  26, 150,  59, 101},
	 {422, 284, 477,  72, 177, 328,  57,   0,  32, 196, 439, 340, 182, 343,  49,  17,  36,  93,  90,  51},
	 {453, 308, 493,  57, 190, 335,  30,  32,   0, 217, 470, 371, 212, 364,  18,  14,  24, 122,  81,  70},
	 {315,  95, 582, 269, 329, 478, 248, 196, 217,   0, 405, 310, 100, 433, 229, 207, 231, 118, 285, 150},
	 {165, 377, 359, 474, 371, 412, 485, 439, 470, 405,   0, 100, 312, 259, 487, 456, 460, 375, 467, 434},
	 {149, 294, 360, 380, 293, 364, 389, 340, 371, 310, 100,   0, 214, 229, 389, 358, 363, 275, 375, 334},
	 {249, 132, 488, 249, 261, 401, 240, 182, 212, 100, 312, 214,   0, 338, 229, 199, 217,  90, 258, 151},
	 {378, 462, 150, 336, 187, 157, 363, 343, 364, 433, 259, 229, 338,   0, 377, 355, 343, 337, 318, 370},
	 {471, 321, 503,  56, 200, 342,  23,  49,  18, 229, 487, 389, 229, 377,   0,  32,  33, 138,  81,  84},
	 {439, 297, 486,  62, 184, 332,  41,  17,  14, 207, 456, 358, 199, 355,  32,   0,  26, 109,  84,  61},
	 {452, 320, 470,  37, 167, 311,  26,  36,  24, 231, 460, 363, 217, 343,  33,  26,   0, 128,  58,  85},
	 {336, 196, 483, 162, 212, 364, 150,  93, 122, 118, 375, 275,  90, 337, 138, 109, 128,   0, 175,  62},
	 {479, 370, 433,  25, 131, 264,  59,  90,  81, 285, 467, 375, 258, 318,  81,  84,  58, 175,   0, 142},
	 {398, 237, 510, 123, 218, 371, 101,  51,  70, 150, 434, 334, 151, 370,  84,  61,  85,  62, 142,   0}}
    // clang-format on
};

using Tour = std::array<int, N>;

// array printing
std::ostream& operator<<(std::ostream& os, const Tour& tour) {
    os << tour[0];
    for (size_t i = 1; i < tour.size(); ++i) {
        os << ", " << tour[i];
    }
    return os;
}

std::mt19937& randomNumberEngine() {
    static std::random_device rd;
    static std::mt19937 gen(rd());

    return gen;
}

static auto gen = randomNumberEngine();

// check if a tour is completely defined
bool tourDefined(const Tour& tour) {
    // all tours have N distinct cities
    // if a tour has undefined slots, they are marked by -1
    return std::none_of(tour.begin(), tour.end(),
                        [](int city) { return city == -1; });
}

// check if city is in tour
bool findCity(const Tour& tour, int city) {
    assert(city >= 0 && city < N);

    // a valid tour always returns true as the tour must include all cities
    // during evolution, tours temporarily have undefined slots, so this is why
    // we need this function
    return std::any_of(tour.begin(), tour.end(),
                       [city](int tourCity) { return tourCity == city; });
}

// check that all cities are included in a complete tour
bool validTour(const Tour& tour) {
    for (int i = 0; i < N; ++i) {
        if (!findCity(tour, i)) {
            return false;
        }
    }
    return true;
}

// returns distance between two cities based on the distance table
int cityDistance(int city1, int city2) {
    int distance = 0;
    assert(city1 >= 0 && city1 < 20 && city2 >= 0 && city2 < 20 && city1 != city2);
    distance = distanceTable[city1][city2];
    return distance;
}

// calculate the length for a given tour, assuming a round trip
int tourLength(const Tour& tour) {
    assert(validTour(tour));
    int length = 0;
    for (int i = 0; i<N-1;i++)
    {
        length += cityDistance(tour[i],tour[i+1]);
    }
    length += cityDistance(tour[N-1],tour[0]);
    if (length < minDist)
    {
        minDist = length;
    }
    if (length > maxDist)
    {
        maxDist = length;
    }
    return length;
}

//  print city names of a tour
void printTourCityNames(const Tour& tour) {
    assert(validTour(tour));
    std::cout << "Tour:\n";
    for (int i = 0; i < N; ++i) {
        std::cout << "  " << cityNames[tour[i]] << '\n';
    }
    std::cout << std::endl;
}

// debug, print tour indices
void printTours(const std::vector<Tour>& tourList) {
    for (size_t i = 0; i < tourList.size(); i++) {
        const auto& tour = tourList[i];
        assert(validTour(tour));
        std::cout << i << ": " << tour << " = " << tourLength(tour)
                  << std::endl;
    }
}

// inserts a city in an incomplete tour, using the next free slot
void insertCity(Tour& tour, int city) {
    assert(0<= city && city < N);
    assert(!(validTour(tour)));
    int i = 0;
    while (tour[i] != -1)
    {
        i++;
    }
    tour[i]=city;
}

// Generate the tours as initial population and store them in the tour set.
std::vector<Tour> generateTours() {
    static std::random_device rd;
    static std::mt19937 g(rd());

    std::vector<Tour> tours(M);
    for (auto& tour : tours) {
        for (int i = 0; i < N; ++i) {
            tour[i] = i;  // set to default tour
        }
        std::shuffle(tour.begin(), tour.end(), g);  // randomize cities
        assert(tourDefined(tour));
        assert(validTour(tour));
    }
    return tours;
}

// Take two (good) parent tours, and build a new one by the gens of both.
Tour crossover(const Tour& parent1, const Tour& parent2) {
    Tour child;
    // ...
 
    std::uniform_int_distribution<int> distrib(0,19);

    for(int i = 0; i< N; i++){
        child[i] = -1;
    }
    int rand = distrib(gen);
    for(int i = rand; i < rand+5; i++){
        child[i%20] = parent1[i%20];
    }

    for(int i = 0; i<20; i++){
        if(!(findCity(child,parent2[i]))){
            insertCity(child,parent2[i]);
        }
    }

    assert(tourDefined(child));  // check for undefined city indices
    assert(validTour(child));    // check that each city is defined only once

    return child;
}

// Mutate a given tour, swapping cities randomly based on probability.
void mutate(Tour& tour) {
    constexpr float mutationProbability = 0.02F;  // x% probability per city in a tour to get mutated
    std::uniform_int_distribution<int> distrib(0,1000);                                                     // Zahlen zur Zufallsberechnung
    int random = distrib(gen);
    std::uniform_int_distribution<int> distrib2(0,19);

    int rand1 = 0;
    int between = 0;                                                                                        // temporäre Swap-Variable
    for(int i = 0; i<N;i++){

        random = distrib(gen);

        if(random <= 1000*mutationProbability){
            
            do{                                                                                             // Überprüfung, ob beide Zufallszahlen gleich sind
                rand1=distrib2(gen);
            }while(rand1 == i);

            between = tour[i];
            tour[i] = tour[rand1];
            tour[rand1] = between;
        }
    }
}

// fitness function based on tour length: the shorter, the better
std::vector<std::pair<int, int>> calculateFitness(std::vector<Tour>& tours) {
    // fitness will become a sorted sequence of (tour length, tour index) pairs
    std::vector<std::pair<int, int>> fitness(M);

    // calculate tour length for each tour in the tour set
    for (int i = 0; i < M; ++i) {
        fitness[i] = std::make_pair(tourLength(tours[i]), i);
    }

    // sort (ascending tour length; tour length is first value in a pair
    std::sort(fitness.begin(), fitness.end(),
              [](std::pair<int, int> p1, std::pair<int, int> p2) {
                  return p1.first < p2.first;
              });
    return fitness;
}

// evolution step: transform the tour set into the next generation tour set
std::pair<int, int> evolution(std::vector<Tour>& tours) {
    assert(tours.size() == M);
    std::pair<int, int>
        statistics;  // used as return values (min/max tour lengths)

    // compute fitness of tours, store shortest and largest tour length in
    // statistics
    auto fitness = calculateFitness(tours);
    statistics.first = fitness[0].first;       // tour with shortest tour length
    statistics.second = fitness[M - 1].first;  // tour with largest tour length

    // compute and store crossover tour
    const auto& tour1 = tours[fitness[0].second];  // take first best tour
    const auto& tour2 = tours[fitness[1].second];  // take second best tour
    tours[fitness.back().second] = crossover(
        tour1, tour2);  // overwrite worst tour by newly generated crossover

    // TODO 3.3e: Mutate all other tours (ignore two best trips and the former
    // worst trip (replaced)). Use the mutate method.

    for(int i = 0; i<M;i++){
        if(!(i ==fitness[0].second) && !(i == fitness[1].second) && !(i  == fitness.back().second)){
            mutate(tours[i]);
        }
    }

    return statistics;
}

int main() {
    // report shortest/longest tour length for each evolution iteration in a csv
    // file
    std::ofstream stats("output.csv");
    stats << "min tour length; max tour length\n";

    // generate randomly a tour set with M tours, each one between N cities
    auto tours = generateTours();

    // log on the first tour set generated
    const auto initialFitness = calculateFitness(tours);
    std::cout << "Initial shortest trip: " << initialFitness[0].first << "km"
              << std::endl;

    // do a fixed number of evolution steps
    for (int e = 0; e < 5000; e++) {
        auto lengths = evolution(tours);

        // report statistics
        stats << lengths.first << "; " << lengths.second << '\n';
    }

    // after evolution iterations, log on last tour
    const auto finalFitness = calculateFitness(tours);
    std::cout << "Final shortest trip:  " << finalFitness[0].first << "km"
              << std::endl;
    printTourCityNames(tours[finalFitness[0].second]);
    std::cout << "Over all generations, min dist = " << minDist
              << ", max dist = " << maxDist << std::endl;

    // close the log file (use excel to visualize data)
    stats.close();

    return 0;
}
