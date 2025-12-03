#include <iostream>
#include <fstream>
#include <optional>
#include <string>

namespace {
    template <typename Fn>
    std::optional<long> process_file(const std::string& filename, Fn&& fn) {
        std::ifstream file(filename);

        if (!file.is_open()) {
            std::cerr << "error opening file: " << filename << std::endl;
            return std::nullopt;
        }

        std::string id_range;
        long result = 0;

        while (std::getline(file, id_range, ',')) {
            int split = id_range.find('-');

            long lower_bound = stol(id_range.substr(0, split));
            long upper_bound = stol(id_range.substr(split + 1));

            for (long i = lower_bound; i <= upper_bound; ++i) {
                std::string str = std::to_string(i);
                int len = str.length();

                fn(str, i, result);
            }
        }

        return result;
    }
}

std::optional<long> part_one(const std::string& filename) {
    return process_file(filename,
        [](const std::string_view str, long value, long& result) {
            size_t len = str.size();

            if (str.substr(0, len / 2) == str.substr(len / 2))
                result += value;
        });
}

std::optional<long> part_two(const std::string& filename) {
    return process_file(filename,
        [](const std::string_view str, long value, long& result) {
            size_t len = str.size();

            for (size_t x = 1; x <= len / 2; ++x) {
                if (len % x != 0)
                    continue;

                const std::string_view first_substr = str.substr(0, x);
                for (size_t y = x; y < len; y += x) {
                    if (first_substr != str.substr(y, x))
                        break; 

                    if (y == len / x - 1) {
                        result += value;
                        return;
                    }
                }
            }
        });
}

int main (int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "expected format :" << argv[0] << " <filename>" << std::endl;
        return 1;
    }

    auto p1 = part_one(argv[1]);
    auto p2 = part_two(argv[1]);

    if (p1) std::cout << *p1 << std::endl;
    if (p2) std::cout << *p2 << std::endl;
    
    return 0;
}
