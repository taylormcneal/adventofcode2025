#include <iostream>
#include <fstream>
#include <optional>
#include <vector>

namespace {
    bool is_inbounds(int row, int col, int row_count, int col_count) {
        if (row >= 0 && row < row_count && col >= 0 && col < col_count)
            return true;

        return false;
    }

    bool is_occupied(char c) {
        return c == '@' || c == 'X';
    }

    void clean_grid(std::vector<std::string>& grid) {
        for (size_t i = 0; i < grid.size(); ++i) {
            for (size_t j = 0; j < grid[i].size(); ++j) {
                if (grid[i][j] == 'X')
                    grid[i][j] = '.';
            }
        }
    }

    std::optional<std::vector<std::string>> process_file(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "error opening file: " << filename << std::endl;
            return std::nullopt;
        }

        std::vector<std::string> grid;
        std::string line;
        while (std::getline(file, line)) {
            grid.push_back(line);
        }

        return grid;
    }

    int find_reachable_rolls(std::vector<std::string>& grid) {
        int result = 0;

        std::pair<int, int> offsets[] = {
            { -1, -1 }, { -1, 0 }, { -1, 1 },
            { 0, -1 }, { 0, 1 },
            { 1, -1 }, { 1, 0 }, { 1, 1 }
        };

        int row_count = grid.size();
        int col_count = grid[0].size();

        for (int row = 0; row < row_count; ++row) {
            for (int col = 0; col < col_count; ++col) {
                if (grid[row][col] != '@')
                    continue;

                int adjacent_roll_count = 0;
                for (auto offset : offsets) {
                    int offset_row = row + offset.first;
                    int offset_col = col + offset.second;

                    if (is_inbounds(offset_row, offset_col, row_count, col_count) && is_occupied(grid[offset_row][offset_col])) {
                        ++adjacent_roll_count;
                    }
                }

                if (adjacent_roll_count < 4) {
                    grid[row][col] = 'X';
                    ++result;
                }
            }
        }

        return result;
    }
}

std::optional<int> part_one(const std::string& filename) {
    std::optional<std::vector<std::string>> grid;
    grid = process_file(filename);

    int result = find_reachable_rolls(*grid);

    return result;
}

std::optional<int> part_two(const std::string& filename) {
    std::optional<std::vector<std::string>> grid;
    grid = process_file(filename);

    int total_result = 0;
    int result = 0;
    while ((result = find_reachable_rolls(*grid)) != 0) {
        clean_grid(*grid);
        total_result += result;
    }

    return total_result;
}

int main (int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "expected format: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }

    auto p1 = part_one(argv[1]);
    if (p1) std::cout << *p1 << std::endl;
    
    auto p2 = part_two(argv[1]);
    if (p2) std::cout << *p2 << std::endl;
    
    return 0;
}
