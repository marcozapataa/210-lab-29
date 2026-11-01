#pragma once

#include <map>
#include <array>
#include <list>
#include <string>
using namespace std;

using PopulationMap = map<string, array<list<string>, 3>>;

// Simulation constants
constexpr int DAYS = 30;
constexpr double INFECTION_RATE = 0.30;
constexpr double RECOVERY_RATE = 0.10;

// Function prototypes
bool load_pop(PopulationMap& population);
void simulate_infections(PopulationMap& population);
void simulate_recoveries(PopulationMap& population);
void display_stats(const PopulationMap& population, int day);
void display_summary(const PopulationMap& population);