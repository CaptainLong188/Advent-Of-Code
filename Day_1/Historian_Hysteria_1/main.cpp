#include <iostream>
#include <vector>
#include <algorithm>

int main(int argc, char const *argv[])
{
    std::vector<int> v1, v2;    
    int num1 = 0, num2 = 0;
    long long ans = 0;

    while (std::cin >> num1 >> num2)
    {
        v1.push_back(num1);
        v2.push_back(num2);
    }

    std::sort(v1.begin(), v1.end());
    std::sort(v2.begin(), v2.end());
    
    for (int i = 0; i < v1.size(); i++)
    {
        ans += std::abs(v1[i] - v2[i]);
    }
    
    std::cout << ans << "\n";

    return 0;
}
