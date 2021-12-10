#include <fstream>
#include <iostream>

#include <map>
#include <set>
#include <stack>
#include <string>

constexpr auto is_opening(const char parenthesis) noexcept -> bool {
    switch (parenthesis) {
    case '(': case '[': case '{': case '<': return true;
    default: return false;
    }
}

constexpr auto is_closing(const char parenthesis) noexcept -> bool {
    switch (parenthesis) {
    case ')': case ']': case '}': case '>': return true;
    default: return false;
    }
}

constexpr auto is_matching(const char opening_parenthesis, const char closing_parenthesis) noexcept -> bool {
    switch (opening_parenthesis) {
    case '(': return (closing_parenthesis == ')');
    case '[': return (closing_parenthesis == ']');
    case '{': return (closing_parenthesis == '}');
    case '<': return (closing_parenthesis == '>');
    default:  return false;
    }
}

constexpr auto matching_parenthesis(const char parenthesis) noexcept -> char {
    switch (parenthesis) {
    // Opening parenthesis matches
    case '(': return ')';
    case '[': return ']';
    case '{': return '}';
    case '<': return '>';
    
    // Closing Parenthesis matches
    case ')': return '(';
    case ']': return ']';
    case '}': return '}';
    case '>': return '<';

    // Character was not a parenthesis :/
    default:  return '\0';
    }
}

auto main(void) noexcept -> int {
    static auto score_table = []() noexcept {
        std::map<char, int> score_table;
        score_table[')'] = 1;
        score_table[']'] = 2;
        score_table['}'] = 3;
        score_table['>'] = 4;
        return score_table;
    }();

    std::multiset<uint64_t> completion_scores;
    {
        auto input = std::ifstream("input.txt");
        for (std::string line; std::getline(input, line); ) {
            // Find incomplete lines
            std::stack<char> opening_parentheses; 
            bool is_corrupted = false;

            for (const auto parenthesis : line) {
                if (is_opening(parenthesis)) {
                    opening_parentheses.push(parenthesis);
                } else {
                    const auto opening_parenthesis = opening_parentheses.top();
                    opening_parentheses.pop();

                    if (is_matching(opening_parenthesis, parenthesis) == false) {
                        is_corrupted = true;
                        break;
                    }
                }
            }

            // Line is corrupted so skip it
            if (is_corrupted) continue;

            // Score incomplete line
            auto completion_score = uint64_t{0};
            while (opening_parentheses.empty() == false) {
                const auto opening_parenthesis = opening_parentheses.top();
                opening_parentheses.pop();
                
                completion_score = completion_score * 5 + score_table[matching_parenthesis(opening_parenthesis)];
            }

            completion_scores.insert(completion_score);
        }
    }

    auto median_it = completion_scores.cbegin();
    std::advance(median_it, completion_scores.size() / 2);

    std::cout << "The median of the completion scores equals " << *median_it << "!" << std::endl;
    
    return 0;
}
