#include <fstream>
#include <iostream>

#include <vector>

using namespace std;

auto main(void) noexcept -> int {
    static constexpr auto simulation_length = 256;

    static constexpr auto newborns = 8;
    static constexpr auto pregnant = 6;
    static constexpr auto in_labor = 0;
    static constexpr auto total_generations = 9;
    std::vector<size_t> lanternfishies(total_generations);

    {
        auto input = std::ifstream("input.txt");
        for (auto generation = 0; input >> generation; input.ignore()) {
            lanternfishies[generation]++;
        }
    }

    for (auto day = 0; day < simulation_length; day++) {
        auto birthing_fishies = lanternfishies[in_labor];
        for (auto generation = 1; generation < lanternfishies.size(); generation++) {
            lanternfishies[generation-1] = lanternfishies[generation]; 
        }

        lanternfishies[pregnant] += birthing_fishies;
        lanternfishies[newborns]  = birthing_fishies;
    }

    size_t total_fishies = 0;
    for (auto fishies : lanternfishies) total_fishies += fishies;

    std::cout << "After running a simulation of " << simulation_length << " days there should be a total of " << total_fishies << " lanternfishies." << std::endl;

    return 0;
}
