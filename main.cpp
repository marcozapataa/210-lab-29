#include <iostream>
#include "contagion.h"
using namespace std;

// Project CONTAGION
// NV-26 Outbreak Simulation

int main() {
    PopulationMap population;

    cout << "Project CONTAGION - NV-26 Simulation\n";

    // Load population data from text file
    if (!load_pop(population)) {
        cout << "Couldn't load population data" << endl;
        return 1;
    }

    // Display initial population (Day 0)
    display_stats(population, 0);

    cout << "\nPopulation loading complete.\n";

    return 0;
}