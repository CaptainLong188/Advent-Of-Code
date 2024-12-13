#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <algorithm>

typedef long long ll;

// to check if the value can be obtained with the numbers and operations + and *
bool check(ll value, std::vector<ll>& values)
{
    int n = (int)values.size();
    bool ok = false;

    for(ll i = 0; i < (1 << n); ++i)
    {
        std::vector<int> bits;
        ll curr = values[0];

        // for example if n = 3
        for(int j = n - 2; j >= 0; --j)
        {
            bits.push_back((i >> j) & 1);
        }

        for (int i = 0; i < (int)bits.size(); i++)
        {
            if(curr > value) break;

            if(bits[i] == 0)
            {
                curr += values[i + 1];
            }
            else
            {
                curr *= values[i + 1];
            }
        }

        if  (curr == value)
        {
            ok = true;
        }
        
    }

    return ok;
}

int main(int argc, char const *argv[])
{

    if (argc < 2)
        return 0;
        
    ll ans = 0;
    std::ifstream inputFile;
    inputFile.open(argv[1]);

    if (inputFile.is_open())
    {
        std::string line;
        std::vector<ll> values;
        std::vector<std::vector<ll>> nums;

        while (std::getline(inputFile, line))
        {
            std::vector<ll> aux;
            int len = (int)line.size();
            int n = line.find(':');
            ll testValue = std::stoll(line.substr(0, n));
            values.push_back(testValue);

            int i = n + 2;
            ll num = 0;

            while (i < len)
            {
                if(line[i] == ' ')
                {
                    aux.push_back(num);
                    num = 0;    
                    ++i;
                }
                else
                {
                    num = num * 10 + (line[i] - '0');
                    ++i;
                }
            }

            if(num > 0) aux.push_back(num);

            nums.push_back(aux);
        }


        for(int i = 0; i < values.size(); ++i)
        {
            if(check(values[i], nums[i]))
            {
                ans += values[i];
            }
        }
    }

    std::cout << ans << "\n";    

    return 0;
}
