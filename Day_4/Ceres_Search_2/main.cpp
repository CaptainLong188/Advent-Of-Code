#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

void printVector2D(std::vector<std::vector<char>> v)
{
    for(const auto& row : v)
    {
        for(const auto e : row)
        {
            std::cout << e << " ";
        }
        
        std::cout << std::endl; 
    }

}

bool check_X_MAS(std::vector<std::vector<char>>& grid, int i, int j)
{
    std::vector<std::pair<int, int>> dirs = {{-1, -1}, {-1, 1}, {1, 1}, {1, -1}};
    std::string s;

    for (const auto& dir : dirs)
    {
        s += grid[i + dir.first][j + dir.second];
    }

    if(s == "MMSS" || s == "MSSM" || s == "SMMS" || s == "SSMM")
    {
        std::cout << "Patter found at (" << i << " " << j << ")" << std::endl;
        return true;
    }

    return false;
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

    std::vector<std::vector<char>> grid;

    if (inputFile.is_open())
    {
       std::string line;

       while (std::getline(inputFile, line))
       {
            std::vector<char> row;
            char c;
            std::istringstream inputStream(line);

            while (inputStream >> c)
            {
                row.push_back(c);
            }

            grid.push_back(row);
            row.clear();
       }
    }

    //printVector2D(grid);

    // Check for every element equal to A for the pattern
    // Don't need to check in first or last row or first or last column

    for(int i = 1; i < grid.size() - 1; ++i)
    {
        for(int j = 1; j < grid[0].size() - 1; ++j)
        {
            if(grid[i][j] == 'A')
            {
                ans += check_X_MAS(grid, i, j);
            }
        }
    }

    std::cout << ans << " ";
    inputFile.close();

    return 0;
}
