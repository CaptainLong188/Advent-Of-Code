#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>


bool isSafe(std::vector<int>& nums)
{
    int n = nums.size();
    bool increasing = true, decreasing = true;

    for(int i = 0; i < n - 1; ++i)
    {
        int diff = nums[i] - nums[i + 1];

        if(diff > 0)
        {
            if(!decreasing) return false; // already know that is not decreasing nor increasing
            increasing = false;
        }

        if(diff < 0)
        {
            if(!increasing) return false; // already know that is not decreasing nor increasing
            decreasing = false;
        }

        if(std::abs(diff) < 1 || std::abs(diff) > 3)
        {
            return false;
        }
    }

    return increasing || decreasing;
}

// check if the report is safe after erasing the level k 
bool check(std::vector<int> &nums, int k)
{
    std::vector<int> aux {nums};
    aux.erase(aux.begin() + k);
    return isSafe(aux);
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

        while (std::getline(inputFile, line))
        {
            int num;
            std::istringstream inputStream(line);
            std::vector<int> nums;

            while (inputStream >> num)
            {
                nums.push_back(num);
            }
            
            bool ok = true;
            int n = nums.size();

            for (int  i = 0; i < n - 1; i++)
            {
                int diff = nums[i] - nums[i + 1];
                std::cout << diff << " "; 

                if (std::abs(diff) < 1 || std::abs(diff) > 3)
                {
                    ok = check(nums, i) || check(nums, i + 1);
                    break;
                }
                
                if(i + 2 < n)
                {
                    int next_diff = nums[i + 1] - nums[i + 2];

                    if( (diff > 0) != (next_diff > 0)) // this means either that we have a triplet (a, b, c ) such that (a > b && c > b) || (a < b && c < b)
                    {
                        ok = check(nums, i) || check(nums, i + 1) || check(nums, i + 2);
                        break;
                    }  
                }
                
            }
            
            std::cout << std::boolalpha << ok << "\n";

            if(ok) ++ans;
        }
    }

    std::cout << ans << "\n";    

    return 0;
}
