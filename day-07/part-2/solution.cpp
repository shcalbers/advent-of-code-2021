#include <cmath>

#include <fstream>
#include <iostream>

#include <vector>

auto main(void) noexcept -> int {
    // Reserve some space for storing the positions of all crabbies.
    std::vector<int> crabby_positions;
    crabby_positions.reserve(1000);
    
    // The sum of all positions, used later to calculate the average.
    int positions_sum = 0;

    { // Read all crabby positions from the input file.
        auto input = std::ifstream("input.txt");
        for (int position = 0; input >> position; input.ignore()) {
           crabby_positions.push_back(position);
           positions_sum += position;
        }
    } // Done reading all crabby positions.

    // Find average crabby position, this will be the most efficient position to move towards.
    const auto average_position = float(positions_sum) / float(crabby_positions.size());
    
    // Then determine the floor and ceil, because we want to work with integers only.
    // Rounding doesn't work because the result might be slightly farther from one point and closer to another causing the fuel cost to be higher.
    const auto average_floored = int(floor(average_position));
    const auto average_ceiled  = int(ceil(average_position));

    // Determine total fuel cost for moving towards the average.
    // First determine the cost for going to the floored average and ceiled average separately.
    auto fuel_cost_A = 0;
    auto fuel_cost_B = 0;
    for (auto crabby_position : crabby_positions) {
        const auto distance_A = std::abs(crabby_position - average_floored);
        const auto distance_B = std::abs(crabby_position - average_ceiled);
        
        fuel_cost_A += (distance_A*(distance_A+1)/2);
        fuel_cost_B += (distance_B*(distance_B+1)/2);
    }

    // Then determine the lowest value of the two.
    auto fuel_cost = std::min(fuel_cost_A, fuel_cost_B);

    // Print the final result :D
    std::cout << "The total fuel cost for horizontally alligning all crabbies, based on the average, is " << fuel_cost << " units of fuel." << std::endl; 

    return 0;
}
