#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

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

        while (std::getline(inputFile, line))
        {
            std::istringstream inputStream(line);

            int i, j;
            inputStream >> i >> j;
            bool safe = true;
            
            // If the level is increasing
            if(j > i && j <= i + 3)
            {
                i = j;

                while (inputStream >> j)
                {

                    if(j <= i || j > i + 3)
                    {
                        safe = false;
                        break;
                    }

                    i = j;
                }
            }
            else if(j < i && i <= j + 3) // If the level is decreasing
            {
                i = j;

                while (inputStream >> j)
                {

                    if(j >= i || i > j + 3)
                    {
                        safe = false;
                        break;
                    }

                    i = j;
                }
            }
            else
            {
                safe = false;
            }

            ans += (safe == true);
    
        }
    }

    std::cout << ans << "\n";    

    return 0;
}
