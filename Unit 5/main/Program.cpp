#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Structure to represent a railway link
struct Edge
{
    int source;
    int destination;
    int cost;
};

// Find the parent of a vertex
int findParent(vector<int>& parent, int vertex)
{
    if (parent[vertex] == vertex)
        return vertex;

    return parent[vertex] = findParent(parent, parent[vertex]);
}

// Union two sets
void unionSets(vector<int>& parent, vector<int>& rank,
               int u, int v)
{
    u = findParent(parent, u);
    v = findParent(parent, v);

    if (u != v)
    {
        if (rank[u] < rank[v])
            parent[u] = v;
        else if (rank[u] > rank[v])
            parent[v] = u;
        else
        {
            parent[v] = u;
            rank[u]++;
        }
    }
}

int main()
{
    int V, E;

    cout << "Enter number of railway stations: ";
    cin >> V;

    cout << "Enter number of proposed railway links: ";
    cin >> E;

    vector<Edge> edges(E);

    cout << "\nEnter each link as:\n";
    cout << "Source Destination Construction_Cost\n";

    for (int i = 0; i < E; i++)
    {
        cin >> edges[i].source
            >> edges[i].destination
            >> edges[i].cost;
    }

    // Sort edges according to cost
    sort(edges.begin(), edges.end(),
         [](Edge a, Edge b)
         {
             return a.cost < b.cost;
         });

    // Initially every station belongs to a separate set
    vector<int> parent(V + 1);
    vector<int> rank(V + 1, 0);

    for (int i = 1; i <= V; i++)
        parent[i] = i;

    vector<Edge> selected;
    vector<Edge> rejected;

    int totalCost = 0;

    // Kruskal's Algorithm
    for (Edge edge : edges)
    {
        int u = findParent(parent, edge.source);
        int v = findParent(parent, edge.destination);

        if (u != v)
        {
            // Edge does not form a cycle
            selected.push_back(edge);
            totalCost += edge.cost;

            unionSets(parent, rank,
                      edge.source, edge.destination);

            // MST contains V-1 edges
            if (selected.size() == V - 1)
                break;
        }
        else
        {
            // Edge forms a cycle
            rejected.push_back(edge);
        }
    }

    // Display selected links
    cout << "\n----- SELECTED RAILWAY LINKS -----\n";

    for (Edge edge : selected)
    {
        cout << "Station " << edge.source
             << " - Station " << edge.destination
             << " : Cost = " << edge.cost << endl;
    }

    // Display rejected links
    cout << "\n----- REJECTED CYCLE-FORMING LINKS -----\n";

    if (rejected.empty())
    {
        cout << "No cycle-forming links were rejected.\n";
    }
    else
    {
        for (Edge edge : rejected)
        {
            cout << "Station " << edge.source
                 << " - Station " << edge.destination
                 << " : Cost = " << edge.cost << endl;
        }
    }

    // Display total cost
    cout << "\nTotal Minimum Construction Cost = "
         << totalCost << endl;

    return 0;
}
