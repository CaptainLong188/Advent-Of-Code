#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

bool check(std::string str1, std::string str2, std::unordered_map<std::string, std::vector<std::string>>& rules)
{
    std::vector<std::string> opt = rules[str1];
    return std::find(opt.begin(), opt.end(), str2) != opt.end();
}

bool checkOrder(std::vector<std::string>& pages, std::unordered_map<std::string, std::vector<std::string>>& rules)
{
    bool ok = true;

    for(int i = 0; i < pages.size() - 1; ++i)
    {
        if (!check(pages[i], pages[i + 1], rules))
        {
            ok = false;
            break;
        }
        
    }

    return ok;
}

std::vector<std::string> searchCorrect(std::vector<std::string>& pages, std::unordered_map<std::string, std::vector<std::string>>& rules)
{
    bool c = false;

    for(int i = 0; i < 100 && !c; ++i) // Brute force
    {
        for(int j = 0; j < pages.size() - 1; ++j)
        {
            if(!check(pages[j], pages[j + 1], rules)) // swapping every pair that is not in correct order
            {
                std::swap(pages[j], pages[j + 1]);
            }
        }

        c = checkOrder(pages, rules);
    }    

    return pages;
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
                // e.g. 75,47,61,53,29 (all pages are 2 digits separated by a comma)
                std::vector<std::string> pages;

                for (int i = 0; i < line.size(); i += 3)
                {
                    pages.push_back(line.substr(i, 2));
                }
                
                // check if updates are already in the right order
                int n = pages.size();
                bool inOrder = checkOrder(pages, rules);

                if (!inOrder) // now we take only the incorrectly-ordered
                {
                    std::vector<std::string> correct = searchCorrect(pages, rules);

                    for(const auto& p : correct) std::cout << p << " ";
                    std::cout << std::endl;
                    //sum the middle page number after ordering them correctly
                    ans += stoi(correct[(n - 1) / 2]);
                }
                
                //pages.clear();
            }
        }
    }

    std::cout << ans << "\n";    

    return 0;
}
