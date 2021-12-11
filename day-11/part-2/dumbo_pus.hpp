#ifndef ADVENT_OF_CODE__DUMBO_PUS
#define ADVENT_OF_CODE__DUMBO_PUS

#include <vector>

namespace advent_of_code {

inline namespace day_11 {

class DumboPus {

public:

    DumboPus(int initial_energy_level) noexcept;

    auto is_overcharged(void) const noexcept -> bool;

    auto charge(void) noexcept -> void;
    auto release_charge(void) noexcept -> void;
    
    auto add_neighbour(DumboPus& neighbour) noexcept -> void;

private:

    static constexpr auto flash_threshold = 9;
    
    int energy_level; 
    std::vector<DumboPus*> neighbours;

    auto flash(void) noexcept -> void;

};

DumboPus::DumboPus(const int initial_energy_level) noexcept {
    this->energy_level = initial_energy_level;
    this->neighbours.reserve(8);
}

auto DumboPus::is_overcharged(void) const noexcept -> bool {
    return (energy_level > flash_threshold);
}

auto DumboPus::charge(void) noexcept -> void {
    if (this->energy_level++ == flash_threshold) this->flash();
}

auto DumboPus::release_charge(void) noexcept -> void {
    this->energy_level = 0;
}

auto DumboPus::flash(void) noexcept -> void {
    for (auto neighbour : neighbours) neighbour->charge(); 
}

auto DumboPus::add_neighbour(DumboPus& neighbour) noexcept -> void {
    this->neighbours.push_back(&neighbour);
}

}

}

#endif
