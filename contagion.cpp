#include "contagion.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <iterator>
#include <iomanip>
#include <set>
using namespace std;

// Load population data from population.txt
bool load_pop(PopulationMap& population) {

    ifstream file("population.txt");

    if (!file.is_open()) {
        cout << "Couldn't open population.txt" << endl;
        return false;
    }

    string line;

    set<string> seenIDs;

    while (getline(file, line)) {

        stringstream ss(line);

        string id, city, status;

        getline(ss, id, ',');
        getline(ss, city, ',');
        getline(ss, status);

        if (id.find_first_not_of(" \t\r\n") == string::npos) {
            cout << "Error: Missing or invalid individual ID." << endl;
            return false;
        }

        if (city.find_first_not_of(" \t\r\n") == string::npos) {
            cout << "Error: Missing or invalid city for ID " << id << endl;
            return false;
        }

        if (seenIDs.find(id) != seenIDs.end()) {
            cout << "\nError: Duplicate individual ID " << id << endl;
            return false;
        }

        if (status == "Healthy") {
            population[city][0].push_back(id);
        }
        else if (status == "Infected") {
            population[city][1].push_back(id);
        }
        else if (status == "Recovered") {
            population[city][2].push_back(id);
        }
        else {
            cout << "\nInvalid health status for ID " << id << endl;
            cout << endl;
            return false;
        }

        seenIDs.insert(id);
    }

    if (population.empty()) {
        cout << "\nPopulation file is empty.\n" << endl;
        return false;
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

void display_summary(const PopulationMap& population) {
    cout << "\n=========== FINAL OUTBREAK SUMMARY ==============\n";

    cout << left << setw(20) << "City"
         << right << setw(10) << "Healthy"
         << setw(12) << "Infected"
         << setw(12) << "Recovered" << endl;

    cout << string(54, '-') << endl;


    // Track cities with the most infections and recoveries
    string mostInfectedCity;
    string mostRecoveredCity;

    int maxInfected = -1;
    int maxRecovered = -1;

    // Calculate and display each city
    for (const auto& city : population) {
        int healthy = city.second[0].size();
        int infected = city.second[1].size();
        int recovered = city.second[2].size();

        // find city with most infections
        if (infected > maxInfected) {
            maxInfected = infected;
            mostInfectedCity = city.first;
        }

        // find city with the most recoveries
        if (recovered > maxRecovered) {
            maxRecovered = recovered;
            mostRecoveredCity = city.first;
        }

        cout << left << setw(20) << city.first
             << right << setw(10) << healthy
             << setw(12) << infected
             << setw(12) << recovered << endl;
    }

    cout << string(54, '-') << endl;

    if (!population.empty()) {
        cout << "Most active infections: " << mostInfectedCity
             << " (" << maxInfected << ")" << endl;

        cout << "Most recoveries: " << mostRecoveredCity
             << " (" << maxRecovered << ")" << endl;
    }
}