#include <fstream>
#include <iostream>
#include <sstream>

#include <string>
#include <vector>

#include <limits>

using namespace std;

auto main(void) noexcept -> int {
    auto unique_digits = 0;

    {
        auto input = ifstream("input.txt");
        for (std::string line; std::getline(input, line); ) {
            auto input = istringstream(line);
            input.ignore(numeric_limits<streamsize>::max(), '|');
            input.ignore(1);

            for (std::string digit; std::getline(input, digit, ' '); ) {
                switch (digit.size()) {
                case 2: case 4: case 3: case 7: unique_digits++;
                }
            }
        }
    }

    std::cout << "The numbers 1, 4, 7, 8 appear " << unique_digits << " in the output values" << std::endl;

    return 0;
}
