#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

typedef long long  ll;

template <typename T>
void printVector(std::vector<T>& v)
{
    for (const auto & e : v) std::cout << e << " ";
    std::cout << std::endl;
}

ll countDigits (ll num)
{
    ll cnt = 0;

    while (num > 0)
    {
        num /= 10, cnt++;
    }
    
    return cnt;
}

// Need it to split the number of even number of digits
ll pow10 (ll num)
{
    ll prod = 1;

    for (int i = 0; i < num; ++i) prod *= 10;

    return prod;
}

// Split number in its 2 halves
std::pair<ll, ll> splitNumber(ll num)
{
    ll dig = countDigits(num);
    ll div = pow10(dig / 2);

    return {num / div, num % div}; 
}

std::vector<ll> blink(std::vector<ll>& stones)
{   
    std::vector<ll> n;
    n.reserve(stones.size());

    for (const auto& stone : stones)
    {
        if (stone == 0) n.push_back(1);
        else if (countDigits(stone) % 2 == 0)
        {
            std::pair<ll, ll> split = splitNumber(stone);
            n.push_back(split.first);
            n.push_back(split.second);
        }
        else
        {
            n.push_back(2024 * stone);
        }
    }

    return n;
}

int main(int argc, char const *argv[])
{

    if (argc < 2) return 0;
    
    ll ans = 0;
    std::ifstream inputFile;
    inputFile.open(argv[1]);

    const int numberOfBlinks = 25;

    if (inputFile.is_open())
    {
        // Parse the input
        std::string line;
        std::getline(inputFile, line);
        std::vector<ll> stones;
        std::istringstream inputStream(line);

        ll stone; 
        while (inputStream >> stone)
        {
            stones.push_back(stone);
        }

        // Simulating the blinks 
        for (int i = 0; i < numberOfBlinks; ++i)
        {
           stones = blink(stones);
        }

        ans =(ll) stones.size();
    }

    std::cout << ans << "\n";    

    return 0;
}
