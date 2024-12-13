#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <set>

typedef long long ll;

template <typename T>
void printVector(std::vector<T> v)
{
    for (const auto &e : v)
    {
        std::cout << e << " ";
    }

    std::cout << std::endl;
}

ll concatenate(ll a, ll b)
{
    ll prod = 1;
    while (prod <= b) prod *= 10;
    return (a*prod + b);
}

void check(int i, ll current, ll target, const std::vector<ll>& v, bool &ok)
{
    if (current > target) return;
    if (i == (int) v.size()) // Base case
    {
        if (target == current) {ok = true;}
        return;
    }

    check(i + 1, current + v[i], target, v, ok);
    check(i + 1, current * v[i], target, v, ok);
    check(i + 1, concatenate(current, v[i]), target, v, ok);
}   

int main(int argc, char const *argv[])
{
    if (argc < 2)
        return 0;

    ll ans = 0;
    std::string eq;
    std::ifstream inputFile;
    inputFile.open(argv[1]);

    if (inputFile.is_open())
    {
        while (std::getline(inputFile, eq))
        {
            // Parse the input
            ll target;
            std::vector<ll> nums;
            int idx = (int)eq.find(':');
            target = std::stoll(eq.substr(0, idx));

            std::istringstream stream(eq.substr(idx + 1));
            ll num;
            while (stream >> num)
            {
                nums.push_back(num);
            }

            // Check if the target can be obtained with the values in nums
            bool possible = false;
            check(1, nums[0], target, nums, possible);

            if (possible) { ans += target; }
        }
    }

    std::cout << ans << std::endl;
    inputFile.close();

    return 0;
}
