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

int check(std::vector<std::vector<char>>& grid, int i, int j)
{
    int row = grid.size();
    int col = grid[0].size();

    bool right = (j <= col - 2);
    bool left = (j >= 1);
    bool up = (i >= 1);
    bool down = (i <= row - 2);

    // check for the pattern
    if(right && left && up && down)
    {
        char ul = grid[i - 1][j - 1];
        char ur = grid[i - 1][j + 1];
        char dl = grid[i + 1][j - 1]; 
        char dr = grid[i + 1][j + 1];

        if((ul == 'M' && dr == 'S') || (ul == 'S' && dr == 'M'))
        {
            if((ur == 'M' && dl == 'S') || (ur == 'S' && dl == 'M'))
            {
                std::cout << "Patter found at (" << i << " " << j << ")" << std::endl;
                return 1;
            }
        }
    }

    return 0;
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
       }
    }

    //printVector2D(grid);

    // check for every element equal to A for the pattern

    for(int i = 0; i < grid.size(); ++i)
    {
        for(int j = 0; j < grid[0].size(); ++j)
        {
            if(grid[i][j] == 'A')
            {
                ans += check(grid, i, j);
            }
        }
    }

    std::cout << ans << " ";

    return 0;
}
