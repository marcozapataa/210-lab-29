#include <iostream>
#include "contagion.h"
#include <cstdlib>
#include <ctime>
using namespace std;

// Project CONTAGION
// NV-26 Outbreak Simulation

int main() {

    srand(static_cast<unsigned int>(time(nullptr)));

    PopulationMap population;

    cout << "Project CONTAGION - NV-26 Simulation\n";

    // Load population data from text file
    if (!load_pop(population)) {
        cout << "Couldn't load population data" << endl;
        return 1;
    }

    // Display initial population (Day 0)
    display_stats(population, 0);

    for (int day = 1; day <= DAYS; day++) {

        // Process recoveries before infections
        simulate_recoveries(population);

        // Process new infections
        simulate_infections(population);

        // Display daily stats
        display_stats(population, day);

    }

    display_summary(population);

    cout << "\nSimulation complete!\n";

    return 0;
}