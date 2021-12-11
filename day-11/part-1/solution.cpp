#include "dumbo_sim.hpp"

using namespace advent_of_code::day_11;

auto main(void) -> int {
    DumboSim simulation = DumboSim::load("input.txt");
    simulation.run();
    return 0;
}
