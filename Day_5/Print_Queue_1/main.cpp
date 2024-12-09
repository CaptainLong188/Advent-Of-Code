#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>

bool isOrdered(std::vector<int>& vertices, std::unordered_map<int, std::vector<int>>& adj)
{   
    std::unordered_set<int> seen;

    for(const auto& v : vertices)
    {
        for (const auto& neighbor : adj[v])
        {
            if (seen.count(neighbor) > 0) // a neighbor of the current element has been visited
            {
                return false; 
            }
        }

        seen.insert(v);
    }

    return true;
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
        std::unordered_map<int, std::vector<int>> rules; // adjacency list

        while (std::getline(inputFile, line))
        {
            if (line.empty()) continue;

            std::vector<int> pageNumbers;
            bool isRule = false;

            // Parse the input
            for (int i = 0; i < (int) line.size(); i++)
            {
                if (isdigit(line[i]))
                {
                    int num = 0;

                    while (isdigit(line[i]))
                    {
                        num = num * 10 + (line[i] - '0'); 
                        ++i;
                    }
                    
                    pageNumbers.push_back(num);

                    if (line[i] == '|') isRule = true;
                }
            }

            if (isRule) // the row is {}|{}
            {
                rules[pageNumbers[0]].push_back(pageNumbers[1]); // directed graph
            }
            else // the row is {}, {}, ..., {} 
            {
                // check if the row is ordered correctly
                if (isOrdered(pageNumbers, rules))
                {
                    ans += pageNumbers[pageNumbers.size() / 2];
                }
            }
        }
    }

    std::cout << ans << "\n";    

    return 0;
}