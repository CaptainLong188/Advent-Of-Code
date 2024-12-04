#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>

int main(int argc, char const *argv[])
{

    if (argc < 2)
    {
        std::cout << "Please provide the name of the text file" << std::endl;
        return 0;
    }
    
    long long  ans = 0;
    std::ifstream inputFile;
    inputFile.open(argv[1]);

    if (inputFile.is_open())
    {
        std::string line;

        while (std::getline(inputFile, line))
        {
            int n = line.size();
            int i = 0, j = 0;    

            while (j < n)
            {
                i = line.find("mul(", j); // find "mul(" ocurrences in the string

                if(i == std::string::npos || i > n - 8) break; // no more possible mul operations in the line
                else
                {
                    i += 4; // move to start of the first number
                    int start = i;
                    int k1 = 0, k2 = 0; // k1 is the number of digits of the first number

                    while(i < n && std::isdigit(line[i]))
                    {
                        ++k1, ++i;
                    }

                    if(k1 >= 1 && k1 <= 3)
                    {
                        if(i < n && line[i] == ',' )
                        {
                            i += 1;
                            while(i < n && std::isdigit(line[i]))
                            {
                                ++k2, ++i;
                            }

                            if(k2 >= 1 && k2 <= 3)
                            {                                
                                if(i < n && line[i] == ')')
                                {
                                    std::cout << line.substr(start, k1) << " " << line.substr(start + k1 + 1, k2) << "\n"; // print both numbers in a valid mul operation
                                    ans += stoi(line.substr(start, k1)) * stoi(line.substr(start + k1 + 1, k2));
                                }                    
                            }
                        }
                    }
                    
                    j = i;

                }         
            }
        }        
    }

    std::cout << ans << "\n";

    return 0;
}
