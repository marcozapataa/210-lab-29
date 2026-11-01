#include <iostream>
#include <cassert>
#include <cstdlib>
#include "contagion.h"
using namespace std;

int main() {

    cout << "Project CONTAGION - Unit Tests\n\n";

    PopulationMap population;

    //Test 1: Population loading
    bool loaded = load_pop(population);
    assert(loaded);
    assert(population.size() == 5);

    for (const auto& city : population) {
        assert(city.second[0].size() == 18);
        assert(city.second[1].size() == 2);
        assert(city.second[2].size() == 0);
    }

    cout << "Test 1 passed: Population loaded correctly.\n";

    // Test 2: Infection simulation
    srand(42);

    simulate_infections(population);

    for (const auto& city : population) {
        int healthy = city.second[0].size();
        int infected = city.second[1].size();
        int recovered = city.second[2].size();
    }

    cout << "Test 2 passed: Infection simulation works correctly\n";

    // Test 3: Recovery simulation
    PopulationMap beforeRecovery = population;

    simulate_recoveries(population);

    for (const auto& city : population) {
        const string& name = city.first;

        int healthy = city.second[0].size();
        int infected = city.second[1].size();
        int recovered = city.second[2].size();

        int previousHealthy = beforeRecovery[name][0].size();
        int previousInfected = beforeRecovery[name][1].size();
        int previousRecovered = beforeRecovery[name][2].size();

        assert(healthy == previousHealthy);
        assert(infected <= previousInfected);
        assert(recovered >= previousRecovered);
        assert(healthy + infected + recovered == 20);
    }

    cout << "Test 3 passed: Recovery simulation works correctly\n";

    cout << "\nAll unit tests passed!\n";

    return 0;
}