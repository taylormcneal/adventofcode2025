#include <iostream>
#include <fstream>
#include <optional>
#include <sstream>
#include <utility>
#include <vector>

std::optional<long> part_one (const std::string& filename) {
    std::fstream file(filename);
    if (!file.is_open()) {
        std::cerr << "error opening file: " << filename << std::endl;
        return std::nullopt;
    }

    std::vector<std::vector<std::string>> values;

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::vector<std::string> input_line;

        std::string x;
        while (iss >> x)
            input_line.push_back(x);

        values.push_back(input_line);
    }

    size_t operator_index = values.size() - 1;
    long total = 0;
    for (size_t i = 0; i < values[0].size(); ++i) {
        long operation_result;
        if (values[operator_index][i] == "+") {
            operation_result = 0;
            for (size_t j = 0; j < operator_index; ++j) {
                operation_result += stol(values[j][i]);
            }
        }
        else {
            operation_result = 1;
            for (size_t j = 0; j < operator_index; ++j) {
                operation_result *= stol(values[j][i]);
            }
        }

        total += operation_result;
    }

    return total;
}

std::optional<long> part_two (const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "error opening file: " << filename << std::endl;
        return std::nullopt;
    }

    std::vector<std::string> input;

    std::string line;
    while (std::getline(file, line))
        input.push_back(line);

    std::vector<std::pair<char, size_t>> operation_info;

    size_t index = 0;
    size_t operator_input_index = input.size() - 1;
    size_t operator_input_size = input[operator_input_index].size();
    while (index < operator_input_size) {
        char c;
        c = input[operator_input_index][index++];

        size_t operation_size = 0;
        while (index < operator_input_size && input[operator_input_index][index] == ' ') {
            ++operation_size;
            ++index;
        }

        if (index == operator_input_size) ++operation_size;

        operation_info.emplace_back(c, operation_size);
    }

    index = 0;
    long total = 0;
    for (auto operation : operation_info) {
        std::vector<std::string> numbers(operator_input_index);
        for (size_t i = 0; i < operation.second; ++i) {
            for (size_t j = 0; j < operator_input_index; ++j) {
                if (input[j][i + index] != ' ')
                    numbers[i].push_back(input[j][i + index]);
            }
        }
        
        long operation_total = operation.first == '+' ? 0 : 1;
        for (auto number : numbers) {
            if (number.empty())
                continue;

            if (operation.first == '+')
                operation_total += stol(number);
            else
                operation_total *= stol(number);
        }

        total += operation_total;
        index += operation.second + 1;
    }
    
    return total;
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
