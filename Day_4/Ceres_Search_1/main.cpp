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

bool inBounds(int x, int y, int rows, int cols)
{
    return (x >= 0 && x < rows && y >= 0 && y < cols);
}

int check_XMAS(std::vector<std::vector<char>>& grid, int x1, int y1)
{
    const std::string search = "XMAS";
    int r = grid.size();
    int c = grid[0].size();
    int cnt = 0;


    for (int drow = -1; drow <= 1; drow++)
    {
        for (int dcol = -1; dcol <= 1; dcol++)
        {
            if (drow == 0 && dcol == 0) continue;
            bool found = true;

            for (int i = 0; i < 4; ++i)
            {
                int x2 = x1 + drow * i;
                int y2 = y1 + dcol * i;

                if (!(inBounds(x2, y2, r, c) && grid[x2][y2] == search[i]))
                {
                    found = false;
                    break;
                }
            }

            cnt += found;
        }
    }

    return cnt;
}

// Naive approach
int check(std::vector<std::vector<char>>& grid, int i, int j)
{
    int row = grid.size();
    int col = grid[0].size();
    int cnt = 0;

    bool right = (j < col - 3);
    bool left = (j >= 3);
    bool up = (i >= 3 );
    bool down = (i < row - 3);

    // check to the right
    if(right && grid[i][j + 1] == 'M' && grid[i][j + 2] == 'A' && grid[i][j + 3] == 'S')
    {
        std::cout << "To the right of (" <<  i << "-" << j << ")" << std::endl;
        ++cnt;
    }
    
    // check to the left
    if(left && grid[i][j - 1] == 'M' && grid[i][j - 2] == 'A' && grid[i][j - 3] == 'S')
    {
        std::cout << "To the left of (" <<  i << "-" << j << ")" << std::endl;
        ++cnt;
    }

    // check upwards
    if(up && grid[i - 1][j] == 'M' && grid[i - 2][j] == 'A' && grid[i - 3][j] == 'S')
    {
        std::cout << "Above (" <<  i << "-" << j << ")" << std::endl;
        ++cnt;
    }

    // check downwards
    if(down && grid[i + 1][j] == 'M' && grid[i + 2][j] == 'A' && grid[i + 3][j] == 'S')
    {
        std::cout << "Below (" <<  i << "-" << j << ")" << std::endl;
        ++cnt;
    }

    // check right upwards
    if(right && up && grid[i - 1][j + 1] == 'M' && grid[i - 2][j + 2] == 'A' && grid[i - 3][j + 3] == 'S')
    {
        std::cout << "Rigth and upwards (" <<  i << "-" << j << ")" << std::endl;
        ++cnt;
    }

    // check left upwards
    if(left && up && grid[i - 1][j - 1] == 'M' && grid[i - 2][j - 2] == 'A' && grid[i - 3][j - 3] == 'S')
    {
        std::cout << "Left and upwards (" <<  i << "-" << j << ")" << std::endl;
        ++cnt;
    }

    // check right downwards
    if(right && down && grid[i + 1][j + 1] == 'M' && grid[i + 2][j + 2] == 'A' && grid[i + 3][j + 3] == 'S')
    {
        std::cout << "Right and downwards (" <<  i << "-" << j << ")" << std::endl;
        ++cnt;
    }


    // check left downwards
    if(left && down && grid[i + 1][j - 1] == 'M' && grid[i + 2][j - 2] == 'A' && grid[i + 3][j - 3] == 'S')
    {
        std::cout << "Rigth and upwards (" <<  i << "-" << j << ")" << std::endl;
        ++cnt;
    }

    return cnt;
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

    // Parse the input
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

    // Check in all directions for the word "XMAS" starting with 'X'

    for(int i = 0; i < grid.size(); ++i)
    {
        for(int j = 0; j < grid[0].size(); ++j)
        {
            if(grid[i][j] == 'X')
            {
                ans += check_XMAS(grid, i, j);
            }
        }
    }

    std::cout << ans << " ";
    inputFile.close();

    return 0;
}
