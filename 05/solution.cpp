#include <iostream>
#include <fstream>
#include <vector>
#include <optional>
#include <algorithm>

std::optional<int> part_one(const std::string& filename) {
    std::fstream file(filename);
    if (!file.is_open()) {
        std::cerr << "error opening file: " << filename << std::endl;
        return std::nullopt;
    }

    std::vector<std::pair<long, long>> ranges;
    std::string line;
    while (std::getline(file, line)) {
        if (line.size() == 0) {
            break;
        }

        int split = line.find('-');
        long lower_bound = stol(line.substr(0, split));
        long upper_bound = stol(line.substr(split + 1));

        ranges.emplace_back(lower_bound, upper_bound);
    }

    int fresh_count = 0;
    while (std::getline(file, line)) {
        long ingredient_id = stol(line);

        for (auto range : ranges) {
            if (ingredient_id >= range.first && ingredient_id <= range.second) {
                ++fresh_count;
                break;
            }
        }
    }

    return fresh_count;
}

std::optional<long> part_two(const std::string& filename) {
    std::fstream file(filename);
    if (!file.is_open()) {
        std::cerr << "error opening file: " << filename << std::endl;
        return std::nullopt;
    }

    std::vector<std::pair<long, long>> ranges;
    std::string line;
    while (std::getline(file, line)) {
        if (line.size() == 0) {
            break;
        }

        size_t split = line.find('-');
        long lower_bound = stol(line.substr(0, split));
        long upper_bound = stol(line.substr(split + 1));

        ranges.emplace_back(lower_bound, upper_bound);
    }

    std::sort(ranges.begin(), ranges.end());

    for (size_t i = 0; i + 1 < ranges.size(); ++i) {
        if (ranges[i + 1].first <= ranges[i].second) {
            if (ranges[i + 1].second > ranges[i].second)
                ranges[i].second = ranges[i + 1].second;

            ranges.erase(ranges.begin() + i + 1);

            --i;
        }
    }

    long fresh_count = 0;
    for (size_t i = 0; i < ranges.size(); ++i)
        fresh_count += (ranges[i].second - ranges[i].first + 1);

    return fresh_count;
}

int main (int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "expected format: " << argv[1] << " <filename>" << std::endl;
        return 1;
    }

    auto p1 = part_one(argv[1]);
    if (p1) std::cout << *p1 << std::endl;

    auto p2 = part_two(argv[1]);
    if (p2) std::cout << *p2 << std::endl;
    
    return 0;
}
