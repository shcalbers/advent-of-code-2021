#include <fstream>
#include <iostream>

#include <map>
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

auto main(void) noexcept -> int {
    static auto score_table = []() noexcept {
        std::map<char, int> score_table;
        score_table[')'] = 3;
        score_table[']'] = 57;
        score_table['}'] = 1197;
        score_table['>'] = 25137;
        return score_table;
    }();

    auto syntax_error_score = 0;
    {
        auto input = std::ifstream("input.txt");
        for (std::string line; std::getline(input, line); ) {
            std::stack<char> opening_parentheses;
            for (const auto parenthesis : line) {
                if (is_opening(parenthesis)) {
                    opening_parentheses.push(parenthesis);
                } else {
                    const auto opening_parenthesis = opening_parentheses.top();
                    opening_parentheses.pop();

                    if (is_matching(opening_parenthesis, parenthesis) == false) {
                        syntax_error_score += score_table[parenthesis];
                        break;
                    }
                }
            }
        }
    }

    std::cout << "The total syntax error score is " << syntax_error_score << "!" << std::endl;

    return 0;
}
