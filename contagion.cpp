#include "contagion.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <iterator>
using namespace std;

// Load population data from population.txt
bool load_pop(PopulationMap& population) {

    ifstream file("population.txt");

    if (!file.is_open()) {
        cout << "Couldn't open population.txt" << endl;
        return false;
    }

    string line;

    while (getline(file, line)) {

        stringstream ss(line);

        string id, city, status;

        getline(ss, id, ',');
        getline(ss, city, ',');
        getline(ss, status);

        if (status == "Healthy") {
            population[city][0].push_back(id);
        }
        else if (status == "Infected") {
            population[city][1].push_back(id);
        }
        else if (status == "Recovered") {
            population[city][2].push_back(id);
        }
    }

    file.close();
    return true;
}

void display_stats(const PopulationMap& population, int day) {

    cout << "Day " << day << endl;

    int totalHealthy = 0;
    int totalInfected = 0;
    int totalRecovered = 0;

    for (const auto& city : population) {

        int healthy = city.second[0].size();
        int infected = city.second[1].size();
        int recovered = city.second[2].size();

        cout << city.first << ": "
             << "Healthy: " << healthy
             << " | Infected: " << infected
             << " | Recovered: " << recovered << endl;

        totalHealthy += healthy;
        totalInfected += infected;
        totalRecovered += recovered;
    }

    cout << "---------------------------------" << endl;

    cout << "Total Healthy: " << totalHealthy << " "
         << "Total Infected: " << totalInfected << " "
         << "Total Recovered: " << totalRecovered << endl;
    cout << "Total Population: "
         << totalHealthy + totalInfected + totalRecovered
         << endl;
    cout << endl;
}

void simulate_infections(PopulationMap& population) {

    for (auto& city : population) {

        int total = city.second[0].size()
                  + city.second[1].size()
                  + city.second[2].size();
        
        if (total == 0) {
            continue;
        }

        int infected = city.second[1].size();

        double infectionProbability =
            INFECTION_RATE * static_cast<double>(infected) / total;

        auto it = city.second[0].begin();

        while (it != city.second[0].end()) {

            double randomNum = static_cast<double>(rand()) / RAND_MAX;

            auto nextIt = next(it);

            if (randomNum < infectionProbability) {

                city.second[1].splice(
                    city.second[1].end(),
                    city.second[0], it
                );
            }

            it = nextIt;
        }
    }
}

void simulate_recoveries(PopulationMap& population) {

    for (auto& city : population) {

        auto it = city.second[1].begin();

        while (it != city.second[1].end()) {

            double randomNum = static_cast<double>(rand()) / RAND_MAX;

            auto nextIt = next(it);

            if (randomNum < RECOVERY_RATE) {

                city.second[2].splice(
                    city.second[2].end(),
                    city.second[1], it
                );
            }

            it = nextIt;
        }
    }


}