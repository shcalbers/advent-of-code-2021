#include <fstream>
#include <iostream>

#include <map>
#include <string>

auto main(void) noexcept -> int {
    // Amount of insertions to perform.
    static constexpr auto insertion_steps = 40;

    // A map storing all the unique pairs and the amount of times they appear within the polymer.
    std::map<std::string, size_t> polymer;
    // Almost the same as above, but instead stores the amount of times a unique element appears.
    std::map<char, size_t> element_count;
    
    // A map storing the insertion rules to apply.
    std::map<std::string, char> insertion_rules;

    { // Load the polymer template and all insertion rules from the input.
        auto input = std::ifstream("input.txt");
        
        // Load the polymer template from the input.
        std::string polymer_template;
        std::getline(input, polymer_template);

        // Split the polymer template up into its pairs. For example 'NNCB' becomes 'NN', 'NC' and 'CB'.
        // And store it into the polymer map, which counts the amount of unique pairs occurring within the polymer.
        for (auto i = 0; i < polymer_template.size()-1; i++) {
            const auto polymer_pair = polymer_template.substr(i, 2);
            polymer[polymer_pair]++;
            element_count[polymer_template[i]]++; // Also count the amount of unique elements while we're at it. ¯\_(``/)_/¯
        }
        element_count[polymer_template.back()]++; // Count the last element because we skipped it in the loop.

        // Then load all the insertion rules, which specifies what element to add based on a pair in the polymer.
        // For example 'NC -> B' means: if the polymer contains the pair 'NC', insert 'B' between the elements 'N' and 'C',
        // thus resulting into two new pairs: 'NB' and 'BC'.
        for (std::string insertion_rule; std::getline(input, insertion_rule); ) {
            const auto polymer_pair = insertion_rule.substr(0, 2);
            const auto element = insertion_rule.back();

            insertion_rules[polymer_pair] = element;
        }
    } // Done loading data from input.

    // Now that we've loaded the polymer, split it up in its pairs and loaded the insertion rules
    // we can start applying these insertion rules N times (where N = insertion_steps).
    for (auto step = 0; step < insertion_steps; step++) {
        // Create a temporary for storing the new polymer, because the old polymer needs to retain its structure.
        std::map<std::string, size_t> new_polymer;

        // Iterate over all pairs and apply the appropriate insertion rule.
        for (auto& [polymer_pair, count] : polymer) {
            // The new element to be inserted.
            const auto new_element = insertion_rules[polymer_pair];
            
            // The new pair formed to the left of the inserted element;
            auto new_pair_left  = polymer_pair;
            new_pair_left[1] = new_element;
            // The new pair formed to the right of the inserted element;
            auto new_pair_right = polymer_pair;
            new_pair_right[0] = new_element;

            // Insert the newly formed pairs "'count' times", because each pair 'polymer_pair' forms these new pairs separately.
            new_polymer[new_pair_left]  += count;
            new_polymer[new_pair_right] += count;
            
            // Also continue counting the new elements we've added.
            // The left and right pair both share the 'new_element' and we thus only have to add it 'count' times, as opposed to '2*count'.
            element_count[new_element] += count;
        }

        // Finally move the newly created polymer into the variable polymer.
        polymer = std::move(new_polymer);
    }

    // Then we only have to find the most and least common element within the polymer.
    auto* most_common  = &(*element_count.begin());
    auto* least_common = &(*element_count.begin());
    for (auto& element : element_count) {
        if (element.second > most_common->second) most_common = &element;
        else if (element.second < least_common->second) least_common = &element;
    }

    // And lastly print the output of our solution.
    std::cout << "The most common element is "  << most_common->first  << " with " << most_common->second  << " occurrences, "
              << "The least common element is " << least_common->first << " with " << least_common->second << " occurrences.\n";

    std::cout << "Difference: " << (most_common->second - least_common->second) << " O_O" << std::endl;

    return 0;
}
