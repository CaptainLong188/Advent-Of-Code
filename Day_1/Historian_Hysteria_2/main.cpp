#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

int main(int argc, char const *argv[])
{
    std::vector<int> v1, v2;    
    int num1 = 0, num2 = 0;
    long long ans = 0;
    std::unordered_map<int, int> hashMap;

    while (std::cin >> num1 >> num2)
    {
        v1.push_back(num1);
        v2.push_back(num2);
    }
    
    for (int i = 0; i < v2.size(); i++)
    {
        hashMap[v2[i]]++;
    }
    
    for (int i = 0; i < v1.size(); i++)
    {
        if (hashMap.count(v1[i]) > 0)
        {
            ans += v1[i] * hashMap[v1[i]];
        }
    }
    
    std::cout << ans << "\n";

    return 0;
}
