#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <numeric>

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
        num /= 10;
        cnt++;
    }

    return cnt;
}

ll pow_10(int exp)
{
    ll prod = 1;
    for (int i = 0; i < exp; ++i) prod *= 10;

    return prod;
}

std::pair<ll, ll> splitNumber(ll num)
{
    ll dig = countDigits(num);
    ll div = pow_10(dig / 2);

    return {num / div, num % div}; // split the number in its 2 halves
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
            std::pair<ll, ll> num = splitNumber(stone);
            n.push_back(num.first);
            n.push_back(num.second);
        }
        else
        {
            n.push_back(2024 * stone);
        }
    }

    return n;
}

void countStones(std::unordered_map<ll, ll>& mapStones)
{
    std::unordered_map<ll, ll> n_mapStones;

    // Count of stones will increment according to the rules
    for (const auto& e : mapStones)
    {
        if (e.first == 0)
        {
            n_mapStones[1] += e.second; 
        }
        else if (countDigits(e.first) % 2 == 0)
        {
            std::pair<ll, ll> num = splitNumber(e.first);
            n_mapStones[num.first] += e.second;
            n_mapStones[num.second] += e.second;
        }
        else
        {
            n_mapStones[e.first * 2024] += e.second;
        }
    }
    
    mapStones = n_mapStones;
    n_mapStones.clear();
}

int main(int argc, char const *argv[])
{

    if (argc < 2) return 0;
    
    ll ans = 0;
    std::ifstream inputFile;
    inputFile.open(argv[1]);
    const int numberOfBlinks = 75;

    if (inputFile.is_open())
    {
        // Parsing the input
        std::string line;
        std::getline(inputFile, line);
        std::vector<ll> stones;
        std::istringstream inputStream(line);

        ll stone; 
        while (inputStream >> stone)
        {
            stones.push_back(stone);
        }

        // Filling the hashMap with the current number of stones
        std::unordered_map<ll, ll> mapStones;
        for (const auto& stone : stones) ++mapStones[stone];

        // Updating after every blink the number of stones
        for (int i = 0; i < numberOfBlinks; ++i)
        {
           countStones(mapStones);
        }

        ans = std::accumulate(  mapStones.begin(), mapStones.end(), (ll)0, 
                                [](ll value, const auto& p)
                                {
                                    return value + p.second;
                                }
                                );
    }

    std::cout << ans << "\n";    

    return 0;
}
