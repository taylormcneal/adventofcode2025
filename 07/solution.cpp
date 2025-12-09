#include <iostream>
#include <fstream>
#include <set>
#include <optional>
#include <map>
#include <string>

namespace {
    std::set<size_t> split_beams(const std::string_view input, std::set<size_t> input_beam_indices, int& split_count) {
        std::set<size_t> output_beam_indices;

        for (auto beam_index : input_beam_indices) {
            if (input[beam_index] == '^') {
                ++split_count;

                output_beam_indices.insert(beam_index - 1);
                output_beam_indices.insert(beam_index + 1);
            } else {
                output_beam_indices.insert(beam_index);
            }
        }

        return output_beam_indices;
    }

    std::map<size_t, long> quantum_beam_split(const std::string_view input, std::map<size_t, long> input_quantum_space) {
        std::map<size_t, long> output_quantum_space;

        for (auto quantum_beam : input_quantum_space) {
            if (input[quantum_beam.first] == '^') {
                if (output_quantum_space.find(quantum_beam.first - 1) == output_quantum_space.end())
                    output_quantum_space.emplace(quantum_beam.first - 1, quantum_beam.second);
                else
                    output_quantum_space[quantum_beam.first - 1] += quantum_beam.second;

                if (output_quantum_space.find(quantum_beam.first + 1) == output_quantum_space.end())
                    output_quantum_space.emplace(quantum_beam.first + 1, quantum_beam.second);
                else
                    output_quantum_space[quantum_beam.first + 1] += quantum_beam.second;
            } else {
                output_quantum_space.insert(quantum_beam);
            }
        }

        return output_quantum_space;
    }
}

std::optional<int> part_one(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "error opening file: " << filename << std::endl;
        return std::nullopt;
    }


    std::set<size_t> beam_indices;
    std::string line;

    std::getline(file, line);
    beam_indices.insert(line.find('S'));

    int split_count = 0;
    do {
        beam_indices = split_beams(line, beam_indices, split_count);
    } while (std::getline(file, line));

    return split_count;
}

std::optional<long> part_two(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "error opening file: " << filename << std::endl;
        return std::nullopt;
    }

    std::map<size_t, long> quantum_beam_space;
    std::string line;

    std::getline(file, line);
    quantum_beam_space.emplace(line.find('S'), 1);

    do {
        quantum_beam_space = quantum_beam_split(line, quantum_beam_space);
        for (auto quantum_beam : quantum_beam_space) {
            std::cout << "[" << quantum_beam.first << "," << quantum_beam.second << "]";
        }
        std::cout << std::endl;
        
    } while (std::getline(file, line));

    int quantum_path_count = 0;
    for (auto quantum_beam : quantum_beam_space)
        quantum_path_count += quantum_beam.second;

    return quantum_path_count;
}

int main (int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "expected format: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }

    auto p2 = part_two(argv[1]);
    if (p2) std::cout << *p2 << std::endl;

    return 0;
}
