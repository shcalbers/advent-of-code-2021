#include <cmath>

#include <fstream>
#include <iostream>

#include <set>

auto main(void) noexcept -> int {
    std::multiset<int> crabby_positions;

    { // Read all crabby positions from the input file.
        auto input = std::ifstream("input.txt");
        for (int position = 0; input >> position; input.ignore()) {
           crabby_positions.insert(position); 
        }
    } // Done reading all crabby positions.

    // Find median crabby position, this will be the most efficient position to move towards.
    const auto median_position = [&]() noexcept -> int {
        auto median_it = crabby_positions.cbegin();
        std::advance(median_it, crabby_positions.size() / 2);
        return *median_it;
    }();

    // Determine total fuel cost for moving towards the median.
    auto fuel_cost = 0;
    for (auto crabby_position : crabby_positions) {
        fuel_cost += std::abs(crabby_position - median_position);
    }

    std::cout << "The total fuel cost for horizontally alligning all crabbies, based on the median, is " << fuel_cost << " units of fuel." << std::endl; 

    return 0;
}
