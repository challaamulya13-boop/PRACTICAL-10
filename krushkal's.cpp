#include <iostream>
#include <algorithm>
using namespace std;

struct Edge
{
    int u, v, weight;
};

// Compare edges based on weight
bool compare(Edge a, Edge b)
{
    return a.weight < b.weight;
}

// Find parent of a vertex
int findParent(int parent[], int vertex)
{
    if (parent[vertex] == vertex)
        return vertex;

    return parent[vertex] = findParent(parent, parent[vertex]);
}

// Join two sets
void unionSet(int parent[], int rank[], int u, int v)
{
    u = findParent(parent, u);
    v = findParent(parent, v);

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
    int n, e;

    cout << "Enter number of vertices: ";
    cin >> n;

    cout << "Enter number of edges: ";
    cin >> e;

    Edge edges[100];

    cout << "Enter edges (source destination weight):\n";

    for (int i = 0; i < e; i++)
    {
        cin >> edges[i].u >> edges[i].v >> edges[i].weight;

        // Convert to 0-based indexing
        edges[i].u--;
        edges[i].v--;
    }

    // Sort edges according to weight
    sort(edges, edges + e, compare);

    int parent[100];
    int rank[100] = {0};

    // Initially every vertex is its own parent
    for (int i = 0; i < n; i++)
        parent[i] = i;

    int totalCost = 0;
    int edgeCount = 0;

    cout << "\nEdges in Minimum Spanning Tree:\n";

    for (int i = 0; i < e && edgeCount < n - 1; i++)
    {
        int u = edges[i].u;
        int v = edges[i].v;

        // Check whether adding the edge creates a cycle
        if (findParent(parent, u) != findParent(parent, v))
        {
            cout << u + 1 << " - " << v + 1
                 << " : " << edges[i].weight << endl;

            totalCost += edges[i].weight;

            unionSet(parent, rank, u, v);

            edgeCount++;
        }
    }

    cout << "\nMinimum Cost = " << totalCost << endl;

    return 0;
}
