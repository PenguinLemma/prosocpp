#include <algorithm>
#include <iostream>
#include <unordered_set>
#include <vector>
#include <numeric>

using Junction = std::size_t;
using AdjacencyList = std::unordered_set<Junction>;

using Graph = std::vector<AdjacencyList>;

Graph ConstructUserInputGraph()
{
    std::size_t num_junctions;
    std::cin >> num_junctions;
    Graph g(num_junctions);
    for (std::size_t i = 0; i < num_junctions - 1; ++i) {
        Junction a, b;
        std::cin >> a >> b;
        g[a].insert(b);
        g[b].insert(a);
    }
    return g;
}

int CountPartRecursive(Graph const& g, std::unordered_set<Junction> const& added)
{
        
}

int CountPartitions(Graph const& g)
{
    if (g.size() <= 3)
        return 1;
    std::unordered_set<Junction> added;

}

int main()
{
    Graph g = ConstructUserInputGraph();
    std::cout << CountPartitions(g) << std::endl;
}
