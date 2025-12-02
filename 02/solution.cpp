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
        long result;

        while (std::getline(file, id_range, ',')) {
            int split = id_range.find('-');

            long lower_bound = stol(id_range.substr(0, split));
            long upper_bound = stol(id_range.substr(split + 1));

            for (long i = lower_bound; i <= upper_bound; ++i) {
                std::string str = std::to_string(i);
                int len = str.length();

                fn(str, len, i, result);
            }
        }

        return result;
    }
}

std::optional<long> part_one(const std::string& filename) {
    return process_file(filename,
        [](const std::string& str, int len, long& i, long& result) {
            if (str.substr(0, len / 2) == str.substr(len / 2))
                result += i;
        });
}

std::optional<long> part_two(const std::string& filename) {
    return process_file(filename,
        [](const std::string& str, int len, long& i, long& result) {
            for (int x = 1; x <= len / 2; ++x) {
                if (len % x != 0)
                    continue;

                const std::string first_substr = str.substr(0, x);
                for (int y = 1; y < len / x; ++y) {
                    if (first_substr != str.substr(y * x, x))
                        break; 

                    if (y == len / x - 1) {
                        result += i;
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
