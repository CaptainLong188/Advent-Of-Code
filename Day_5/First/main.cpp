#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>

bool check(std::string str1, std::string str2, std::unordered_map<std::string, std::vector<std::string>>& rules)
{
    // check if str2 exists in rules[str1] 

    bool ok = false;

    for (const auto& e : rules[str1])
    {
        if (e == str2)
        {
            ok = true;
            break;
        }
        
    }

    return ok;
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
        std::unordered_map<std::string, std::vector<std::string>> rules;

        while (std::getline(inputFile, line))
        {
            // Get all the rules
            if(line.size() == 5)
            {
                rules[line.substr(0, 2)].push_back(line.substr(3, 2));
            }

            if(line.size() > 5)
            {
                // 75,47,61,53,29 (all pages are 2 digits separated by a comma)
                std::vector<std::string> pages;

                for (int i = 0; i < line.size(); i += 3)
                {
                    pages.push_back(line.substr(i, 2));
                }
                
                // check if updates are already in the right order

                int n = pages.size();
                bool ok = true;

                for(int i = 0 ; i < n - 1; ++i)
                {
                    if(!check(pages[i], pages[i + 1], rules))
                    {
                        ok = false;
                        break;
                    }
                }

                if (ok)
                {
                    // sum the middle page number
                    ans += stoi(pages[(n - 1) / 2]);
                }
                
            }
        }
    }

    std::cout << ans << "\n";    

    return 0;
}
