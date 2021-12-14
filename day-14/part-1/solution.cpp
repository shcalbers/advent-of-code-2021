#include <fstream>
#include <iostream>

#include <map>
#include <string>
#include <string_view>

#include <algorithm>
#include <limits>
#include <utility>

auto main(void) noexcept -> int {
    static constexpr auto insertion_steps = 10;

    std::string polymer;
    std::map<std::string, char> insertion_rules;

    {
        auto input = std::ifstream("input.txt");
        std::getline(input, polymer);

        for (std::string insertion_rule; std::getline(input, insertion_rule); ) {
            const auto polymer_pair = insertion_rule.substr(0, 2);
            const auto element = insertion_rule.back();

            insertion_rules[polymer_pair] = element;
        }
    }

    std::cout << "Template: " << polymer << '\n';

    for (auto step = 0; step < insertion_steps; step++) {
        std::string new_polymer;
        new_polymer.reserve(polymer.size() + polymer.size()/2);

        for (auto i = 0; i < polymer.size()-1; i++) {
            new_polymer += polymer[i];
            
            const auto polymer_pair = polymer.substr(i, 2);
            if (auto insertion_rule_it = insertion_rules.find(polymer_pair); insertion_rule_it != insertion_rules.end()) {
                new_polymer += insertion_rule_it->second;
            }
        }
        
        new_polymer += polymer.back();
        
        polymer = std::move(new_polymer);

        std::cout << "After step " << (step+1) << ": " << std::string_view(polymer.data(), std::min(polymer.size(), size_t(50)))
                  << (polymer.size() > 50 ? "...\n" : "\n");
    }

    std::map<char, size_t> element_count;
    auto most_common_it = element_count.end();
    auto least_common_it = element_count.end();
    for (auto i = 0; i < polymer.size(); i++) {
        auto [element_it, first_occurrence] = element_count.insert({polymer[i], 0});
        if (first_occurrence == false) element_it->second++;
        
             if (most_common_it  == element_count.end() || element_it->second > most_common_it->second)  most_common_it  = element_it;
        else if (least_common_it == element_count.end() || element_it->second < least_common_it->second) least_common_it = element_it;
    }

    std::cout << "The most common element is "  << most_common_it->first  << " with " << most_common_it->second  << " occurrences, "
              << "The least common element is " << least_common_it->first << " with " << least_common_it->second << " occurrences.\n";

    std::cout << "Difference: " << (most_common_it->second - least_common_it->second) << std::endl;

    return 0;
}
