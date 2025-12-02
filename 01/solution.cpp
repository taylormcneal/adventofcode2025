#include <iostream>
#include <optional>
#include <fstream>
#include <string>

namespace {
    constexpr int RANGE = 100;
    constexpr int INITIAL_VALUE = 50;

    constexpr int wrap(int x) noexcept {
        x %= RANGE;
        return (x < 0) ? x + 100 : x;
    }

    template <typename Fn>
    std::optional<int> process_file(const std::string& filename, Fn&& fn) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "error opening file: " << filename << std::endl;
            return std::nullopt;
        }

        std::string line;
        int value = INITIAL_VALUE;
        int result = 0;

        while (std::getline(file, line)) {
            if (line.empty()) continue;
            if (line.length() < 2) { 
                std::cerr << "ignored invalid line: " << line << std::endl;
                continue;
            }

            char direction = line[0];
            int distance = stoi(line.substr(1));

            fn(direction, distance, value, result);
            value = wrap(value);
        }

        return result;
    }
}

std::optional<int> part_one(const std::string& filename) {
    return process_file(filename, 
        [](char direction, int distance, int& value, int& result) {
            if (direction == 'L')
                value -= distance;
            else
                value += distance;

            if (wrap(value) == 0)
                ++result;
        });
}

std::optional<int> part_two(const std::string& filename) {
    return process_file(filename, 
        [](char direction, int distance, int& value, int& result) {
            if (direction == 'L') {
                if (value == 0)
                    result--;

                result += (RANGE - 1 - value + distance) / RANGE;
                value -= distance;
            } else {
                result += (value + distance - 1) / RANGE;
                value += distance;
            }

            if (wrap(value) == 0) 
                result++;
        });
}

int main (int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }

    const std::string filename = argv[1];

    auto p1 = part_one(filename);
    auto p2 = part_two(filename);

    if (p1) std::cout << *p1 << std::endl;
    if (p2) std::cout << *p2 << std::endl;

    return 0;
}
