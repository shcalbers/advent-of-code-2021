#include <fstream>
#include <iostream>
#include <sstream>

#include <array>
#include <string>

#include "signal.cpp"

using namespace advent_of_code::day_8;

auto parse_line(std::string line, std::array<Signal, 10>& signal_patterns_out, std::array<Signal, 4>& output_digits_out) {
    auto input = std::istringstream(line);
    auto left_from_delimiter = true;
    auto index = 0;

    for (std::string sequence; std::getline(input, sequence, ' '); ) {
        if (sequence != "|") {
            if (left_from_delimiter) {
                signal_patterns_out[index] = Signal(sequence.data());
                index++;
            } else {
                output_digits_out[index] = Signal(sequence.data());
                index++;
            }
        } else {
            left_from_delimiter = false;
            index = 0;
        }
    }
}

auto main(void) noexcept -> int {
    auto output_sum = 0;

    {
        auto input = std::ifstream("input.txt");
        for (std::string line; std::getline(input, line); ) {
            std::array<Signal, 10> signal_patterns;
            std::array<Signal, 4> output_signals;

            parse_line(std::move(line), signal_patterns, output_signals);
            auto signal_map = map_signals(signal_patterns);
            
            std::cout << "-------------------\n";
            std::cout << "XGFEDCBA | XGFEDCBA\n";
            for (auto entry : signal_map) {
                std::cout << entry.first << " : " << entry.second << '\n';
            }

            auto output = 0;
            for (auto output_signal : output_signals) {
                output = output*10 + decode_signal(output_signal, signal_map).to_digit();
            }
            std::cout << "Displayed value: " << output << std::endl;
        
            output_sum += output;
        }
    }

    std::cout << "Total sum of output values = " << output_sum << " <3" << std::endl;
    return 0;
}
