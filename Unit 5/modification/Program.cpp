#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Edge
{
    int u, v, weight;
};

int findParent(vector<int>& parent, int x)
{
    if (parent[x] == x)
        return x;

    return parent[x] = findParent(parent, parent[x]);
}

void unionSet(vector<int>& parent, vector<int>& rank,
              int u, int v)
{
    u = findParent(parent, u);
    v = findParent(parent, v);

    if (u == v)
        return;

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

int main()
{
    int V, E;

    cout << "Enter number of stations: ";
    cin >> V;

    cout << "Enter number of railway links: ";
    cin >> E;

    vector<Edge> edges(E);

    cout << "\nEnter source, destination and cost:\n";

    for (int i = 0; i < E; i++)
    {
        cin >> edges[i].u
            >> edges[i].v
            >> edges[i].weight;
    }

    // Update edge weight
    int src, dest, newWeight;

    cout << "\nEnter edge to update (source destination): ";
    cin >> src >> dest;

    cout << "Enter new weight: ";
    cin >> newWeight;

    bool found = false;

    for (auto& edge : edges)
    {
        if ((edge.u == src && edge.v == dest) ||
            (edge.u == dest && edge.v == src))
        {
            edge.weight = newWeight;
            found = true;
            break;
        }
    }

    if (!found)
    {
        cout << "Edge not found.\n";
        return 0;
    }

    // Sort edges according to weight
    sort(edges.begin(), edges.end(),
         [](Edge a, Edge b)
         {
             return a.weight < b.weight;
         });

    vector<int> parent(V + 1);
    vector<int> rank(V + 1, 0);

    for (int i = 1; i <= V; i++)
        parent[i] = i;

    int totalCost = 0;
    int selectedEdges = 0;

    cout << "\n----- KRUSKAL'S MST -----\n";

    for (Edge edge : edges)
    {
        int pu = findParent(parent, edge.u);
        int pv = findParent(parent, edge.v);

        if (pu != pv)
        {
            unionSet(parent, rank, edge.u, edge.v);

            selectedEdges++;
            totalCost += edge.weight;

            cout << "Selected Edge: "
                 << edge.u << " - " << edge.v
                 << " | Weight = " << edge.weight
                 << " | Running Total = "
                 << totalCost << endl;

            if (selectedEdges == V - 1)
                break;
        }
    }

    // Check whether MST can be formed
    if (selectedEdges == V - 1)
    {
        cout << "\nMinimum Spanning Tree can be formed.";
        cout << "\nTotal Construction Cost = "
             << totalCost << endl;
    }
    else
    {
        cout << "\nGraph is disconnected.";
        cout << "\nMinimum Spanning Tree cannot be formed."
             << endl;
    }

    return 0;
}
