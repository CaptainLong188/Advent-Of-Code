#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <utility>

void printGrid(std::vector<std::vector<char>>& grid)
{
    for (const auto& row : grid)
    {
        for (const auto& rowCell : row)
        {
            std::cout << rowCell << " ";
        }
        std::cout << "\n";
    }
}

void printLocations(std::unordered_map<char, std::vector<std::pair<int, int>>>& mp)
{
    for (const auto& e : mp) 
    {
        std::cout << e.first << ":\n";

        for (const auto& location : e.second) 
        {
            std::cout << "(" << location.first << ", " << location.second << ") ";
        }

        std::cout << "\n";
    }
}

int countAntennas(std::vector<std::vector<bool>>& antennas)
{
    int cnt = 0;

    for(const auto& row : antennas)
    {
        for(const auto& rowCell : row)
        {
            if(rowCell == 1) ++cnt;
        }
    }

    return cnt;
}

void findCollinear(std::vector<std::vector<char>>& grid, std::pair<int, int> point1, std::pair<int, int> point2, std::vector<std::vector<bool>>& antennas)
{
    for (int i = 0; i < grid.size(); ++i)
    {
        for (int j = 0; j < grid[0].size(); ++j)
        {
            if (antennas[i][j] == 1) continue;

            if ((point2.second - point1.second) * (i - point1.first) == (point2.first - point1.first) * (j - point1.second))
            {
                antennas[i][j] = 1;
            }
        }
    }
}

int main(int argc, char const *argv[])
{

    if (argc < 2)
    {
        std::cout << "Please provide the name of the text file" << std::endl;
        return 0;
    }

    int ans = 0;
    std::ifstream inputFile;
    inputFile.open(argv[1]);

    if (inputFile.is_open())
    {
        std::string line;
        std::vector<std::vector<char>> grid;

        // Parse the input
        while (std::getline(inputFile, line))
        {
            std::istringstream inputStream(line);
            char ch;
            std::vector<char> row;

            while (inputStream >> ch)
            {
                row.push_back(ch);
            }

            grid.push_back(row);
        }

        // Store characters and their locations in the grid
        const int rows = grid.size();
        const int cols = grid[0].size();
        std::unordered_map<char, std::vector<std::pair<int, int>>> locations;

        for(int i = 0; i < rows; i++)
        {
            for(int j = 0; j < cols; j++)
            {
                if(grid[i][j] != '.')
                {
                    locations[grid[i][j]].push_back(std::make_pair(i, j));
                }
            }
        }

        // Find all possible positions for antennas
        std::vector<std::vector<bool>> antennas(rows, std::vector<bool>(cols, 0));
        for(const auto& e : locations)
        {
            std::vector<std::pair<int, int>> coordinates = e.second;

            // Check for every pair of coordinates
            for(int i = 0; i < coordinates.size(); ++i)
            {
                for(int j = i + 1; j < coordinates.size();++j)
                {
                    std::pair<int, int> point1 = coordinates[i];
                    std::pair<int, int> point2 = coordinates[j];

                    // Find all points in the grid that are collineal 
                    findCollinear(grid, point1, point2, antennas);
                }
            }
        }

        ans = countAntennas(antennas);
    }

    std::cout << ans << "\n";
    inputFile.close();
    return 0;
}
