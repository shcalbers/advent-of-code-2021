#include <fstream>
#include <iostream>
#include <string>

using namespace std;

auto main(void) noexcept -> int {
    auto aim = 0;
    auto position = 0;
    auto depth = 0;

    {
        auto commands = ifstream("input.txt");
        for (string command; getline(commands, command); ) {
            const auto split = command.find(' ');
            
            const auto direction = command.substr(0, split);
            const auto units = stoi(command.substr(split+1, command.size()));
            if (direction == "forward") {
                position += units;
                depth -= aim*units;
            } else if (direction == "up") {
                aim += units;
            } else if (direction == "down") {
                aim -= units;
            } else {
                cout << "Invalid format! Command given: '" << command << "'" << endl;
                return 1;
            }
        }
    }

    cout << "Depth and position after applying commands: "
         << depth << " units deep and " << position << " units forward."
         << endl;

    cout << "Solution depth * position: " << (depth*position) << endl;

    return 0;
}
