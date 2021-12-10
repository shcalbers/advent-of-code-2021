#ifndef ADVENT_OF_CODE__BINGO_SUBSYSTEM
#define ADVENT_OF_CODE__BINGO_SUBSYSTEM

#include <cassert>

#include <fstream>
#include <iostream>

#include <vector>
#include <string>
#include <vector>

#include <limits>

#include "bingo_board.hpp"

namespace advent_of_code {

inline namespace day4 {

class BingoSubsystem final {

public:

    ~BingoSubsystem(void) noexcept = delete;

    static auto run(std::string file_name) noexcept -> void;

private:

    static auto parse(std::string file_name, std::vector<int>& numbers_out, std::vector<BingoBoard>& boards_out) noexcept -> void;

};

inline auto BingoSubsystem::run(std::string file_name) noexcept -> void {
    std::vector<int> numbers;
    std::vector<BingoBoard> boards;

    numbers.reserve(100);
    boards.reserve(100);

    parse(file_name, numbers, boards);

    for (auto number : numbers) {
        std::cout << "Calling number... " << number << "!\n";

        for (auto board_it = boards.begin(); board_it < boards.end(); ) {
            board_it->mark(number);
            if (board_it->has_bingo()) {
                std::cout << "BINGO! The following board won:\n" << *board_it << '\n';
                std::cout << "Total Score: " << board_it->score() << '\n';
                
                board_it = boards.erase(board_it);
                if (boards.size() == 0) return;
            } else {
                board_it++;
            }
        }
    }

    std::cout << "Nobody won this round... :c" << std::endl;
    return;
}

inline auto BingoSubsystem::parse(std::string file_name, std::vector<int>& numbers_out, std::vector<BingoBoard>& boards_out) noexcept -> void {
    static constexpr auto board_size = 5;

    auto input = std::ifstream(file_name);

    // Read numbers to draw
    {
        int number = 0;
        char delimiter = '\0';
        while (input >> number >> delimiter) {
            numbers_out.push_back(number);
            if (delimiter != ',') break;
        }
    }

    // Read Bingo Boards
    while (input.peek() != EOF) {
        std::vector<std::vector<int>> numbers(board_size, std::vector<int>(board_size));
        for (auto row = 0; row < board_size; row++) {
            for (auto col = 0; col < board_size; col++) {
                input >> numbers[row][col];
            }
        }

        boards_out.emplace_back(numbers);
        
        // Skip blank lines
        input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (input.peek() == EOF) break;
    }

    return;
}

}

}

#endif
