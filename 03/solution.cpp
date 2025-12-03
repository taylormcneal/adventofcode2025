#include <iostream>
#include <fstream>
#include <optional>
#include <string>

std::optional<long> find_max_joltage(const std::string& filename, size_t battery_count) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "error opening file: " << filename << std::endl;
        return std::nullopt;
    }

    long total_joltage = 0;
    std::string bank;
    while (std::getline(file, bank)) {
        std::string joltage(battery_count, '0');
        
        joltage[0] = bank[0];
        int last_used_index = 0;
        for (size_t i = 0; i < battery_count; ++i) {
            for (size_t j = last_used_index + 1; j < bank.size() - battery_count + 1 + i; ++j) {
                if (bank[j] > joltage[i]) {
                    joltage[i] = bank[j];
                    last_used_index = j;
                }
            }
        }

        total_joltage += stol(joltage);
    }

    return total_joltage;
}

int main (int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "expected format: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }

    auto p1 = find_max_joltage(argv[1], 2);
    if (p1) std::cout << *p1 << std::endl;

    auto p2 = find_max_joltage(argv[1], 12);
    if (p2) std::cout << *p2 << std::endl;
    
    return 0;
}
