#include <bits/stdc++.h>
using namespace std;
#define ll long long

struct edge {
    int node; ll weight; //node on the end of edge, weight of edge
};
// to customize the priority queue, we can use a custom comparator
bool operator < (edge a, edge b){
    return a.weight > b.weight; // O(1)
}
const int N = 1e5;
ll distance_to_node[N];
int parent[N];
vector<edge> graph[N];

void dijkstra(int start, int destination)
{
    memset(distance_to_node,63,sizeof distance_to_node); // O(N)
    priority_queue<edge>pq; // O(1)
    pq.push({start,0}); // O(log 1) = O(1)
    distance_to_node[start] = 0; parent[start] = -1; // O(1)
    
    while(!pq.empty()){ // loop runs up to O((V + E) log V) overall
        auto current = pq.top(); pq.pop(); // O(log V)
        
        if (current.node == destination) break; // O(1)
        
        for (auto e : graph[current.node]){ // iterates over neighbors → O(E) total across all loops
            ll new_weight = current.weight + e.weight; // O(1)
            if (distance_to_node[e.node] > new_weight) { // O(1)
                distance_to_node[e.node] = new_weight; // O(1)
                pq.push({e.node, new_weight}); // O(log V)
                parent[e.node] = current.node; // O(1)
            }
        }
    }
	//no path
    if (parent[destination] == 0)
    	return; // O(1)

    vector<int> path; // O(1)
    int cur = destination; // O(1)
    while(cur != -1){ // O(V) in worst case
        path.push_back(cur); // O(1) amortized
        cur = parent[cur]; // O(1)
    }
    reverse(path.begin(), path.end()); // O(V)
}
