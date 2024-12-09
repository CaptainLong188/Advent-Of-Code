#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_set>
#include <unordered_map>

bool isOrdered(std::vector<int>& vertices, std::unordered_map<int, std::vector<int>>& adj)
{   
    std::unordered_set<int> seen;

    for(const auto& v : vertices)
    {
        for (const auto& e : adj[v])
        {
            if (seen.count(e) > 0)
            {
                return false;
            }
        }

        seen.insert(v);
    }

    return true;
}

// Kahn's algorithm for topological sort
void topologicalSort(std::vector<int>& vertices, std::unordered_map<int, std::vector<int>>& adj, std::vector<int>& ordered)
{
    // Calculate in-degrees for each vertex
    std::unordered_map<int, int> inDegrees;
    std::unordered_set<int> present;

    for (const auto& v : vertices)
    {
        present.insert(v);
        inDegrees[v] = 0;
    }

    for (const auto& v : vertices)
    {
        for (const auto& neighbor : adj[v])
        {
            if (present.count(neighbor)) // add just for v present in vertices
            {
                ++inDegrees[neighbor];
            }
        }
    }
    
    // Printing all vertices with their respective indegree
    std::cout << "======================" << std::endl;
    for (const auto& v : vertices)
    {
        std::cout << "Vertex " << v << " with indegree : " << inDegrees[v] << std::endl;
    }
    std::cout << "======================" << std::endl;

    std::queue<int> q;

    // Add elements with indegree 0
    for (const auto& v : vertices)
    {
        if (inDegrees[v] == 0) q.push(v);
    }

    while (!q.empty())
    {
        int v = q.front();
        q.pop();    
        ordered.push_back(v);

        // Reduce the indegree of the neighbors of current vertex
        for (const auto& neighbor : adj[v])
        {
            --inDegrees[neighbor];

            if (inDegrees[neighbor] == 0) q.push(neighbor);
        }
    }

    if (ordered.size() != vertices.size()) 
    {
        std::cout << "The graph contains a cycle" << std::endl;
    }

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
        std::unordered_map<int, std::vector<int>> rules;

        while (std::getline(inputFile, line))
        {
            if (line.empty()) continue;

            std::vector<int> pageNumbers;
            bool isRule = false;

            // Parse the input
            for (int i = 0; i < (int) line.size(); i++)
            {
                if (isdigit(line[i]))
                {
                    int num = 0;

                    while (isdigit(line[i]))
                    {
                        num = num * 10 + (line[i] - '0'); 
                        ++i;
                    }
                    
                    pageNumbers.push_back(num);

                    if (line[i] == '|') isRule = true;
                }
            }

            if (isRule) // the row is {}|{}
            {
                rules[pageNumbers[0]].push_back(pageNumbers[1]); // building adjacency list
            }
            else // the row is {}, {}, ..., {} 
            {
                std::vector<int> ordered;

                // check if the row is ordered correctly
                if (!isOrdered(pageNumbers, rules))
                {
                    topologicalSort(pageNumbers, rules, ordered);
                    ans += ordered[ordered.size()/2];   
                }

            }
        }
    }

    std::cout << ans << "\n";    

    return 0;
}