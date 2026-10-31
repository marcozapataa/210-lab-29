#include <iostream>
#include <map>
#include <array>
#include <list>
#include <string>
using namespace std;

// Project CONTAGION
// NV-26 Outbreak Simulation

const int DAYS = 30;
const double INFECTION_RATE = 0.30;
const double RECOVERY_RATE = 0.10;

// Array indexes: 0 = healthy, 1 = infected, 2 = Recovered
using PopulationMap = map<string, array<list<string>, 3>>;

// Function prototypes
bool load_pop(PopulationMap& population);
void simulate_infections(PopulationMap& population);
void simulate_recoveries(PopulationMap& population);
void display_stats(const PopulationMap& population, int day);

int main() {
    PopulationMap population;

    cout << "Project CONTAGION - NV-26 Simulation\n";

    // Load population data from text file
    // if load fails, end program
    load_pop(population);

    // Display initial population (Day 0)
    display_stats(population, 0);

    // For each day from 1 to DAYS:
        // simulate infections
        // simulate recoveries
        // display updated population stats

    // Mockup: demo function calls
    simulate_infections(population);
    simulate_recoveries(population);

    // Display final outbreak summary

    cout << "\nSimulation mockup complete.\n";

    return 0;
}

//Read population data from external file
bool load_pop(PopulationMap& population) {

    // open population.txt
    // if file can't open, display error and return false
    // While reading records:
        // extract ID, city, and health status
        // add individual to appropriate city and status list
    // close file and return true

    // mockup: insert sample individuals
    population["San Francisco"][0].push_back("P001");
    population["San Francisco"][1].push_back("P002");
    population["Los Angeles"][0].push_back("P003");
    population["Los Angeles"][1].push_back("P004");

    return true;
}

// Simulate infections
void simulate_infections(PopulationMap& population) {

    // For each city:
        // Calculate infection probability based on infected population
        // For each healthy individual:
            // Generate random number
            // If random number < infection probability:
                // Move individual from healthy to infected

    cout << "Simulating infections...\n";
}

// Simulate recoveries
void simulate_recoveries(PopulationMap& population) {

    // For each city:
        // For each individual infected at the beginning of the day:
            // Generate random number
            // If random number < RECOVERY_RATE:
                // Move individual from infected to recovered
    
    cout << "Simulating recoveries...\n";
}

// Display population stats
void display_stats(const PopulationMap& population, int day) {

    // For each city:
        // Count healthy, infected, and recovered individuals
        // Display population stats

    cout << "\nDay " << day << endl;

    for (const auto& city : population) {
        cout << city.first
             << " | Healthy: " << city.second[0].size()
             << " | Infected: " << city.second[1].size()
             << " | Recovered: " << city.second[2].size()
             << endl;
    }
}