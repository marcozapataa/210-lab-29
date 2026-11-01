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

    cout << "Total Healthy: " << totalHealthy << endl;
    cout << "Total Infected: " << totalInfected << endl;
    cout << "Total Recovered: " << totalRecovered << endl;
    cout << "Total Population: "
         << totalHealthy + totalInfected + totalRecovered
         << endl;
}