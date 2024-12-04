#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int getDigits(std::string s, int& i)
{
    int num = 0;

    while (num < 1000 && s[i] >= '0' && s[i] <= '9')
    {
        num = num * 10 + (s[i] - '0');
        ++i;
    }
    
    if (num > 0 && num < 1000) // final number must be between 1 and 3 digits
    {
        return num;
    }
    
    return -1; // return -1 in case there's no number || number has more then 3 digits
}

int main(int argc, char const *argv[])
{

    if (argc < 2)
    {
        std::cout << "Please provide the name of the text file" << std::endl;
        return 0;
    }
    
    long long  ans = 0;
    std::ifstream inputFile;
    inputFile.open(argv[1]);

    if (inputFile.is_open())
    {
        std::string input, line;

        while (std::getline(inputFile, line))
        {
            input += line; // all in one line
        }

        input += "******************"; // to avoid out of bounds
        int n = (int) input.length();

        bool en = true; // mul instruction are enable

        for(int i = 0; i < n; ++i)
        {
            if(input.substr(i, 4) == "do()")
                en = true;

            if(input.substr(i, 7) == "don\'t()")
                en = false;

            if(en && input.substr(i, 4) == "mul(") // only mul operations when enabled
            {
                i += 4; // move to the start of the first number
                int first =  getDigits(input, i);

                if(first != - 1 && input[i] == ',')
                {
                    i += 1; // move to the start of the second number
                    int second = getDigits(input, i);

                    if(second != -1 && input[i] == ')')
                    {
                        std::cout << first << " " << second << "\n";
                        ans += first * second;
                    }
                }
            }
        }
        
    }

    std::cout << ans << "\n";
    inputFile.close();

    return 0;
}
