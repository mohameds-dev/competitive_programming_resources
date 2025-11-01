#include <bits/stdc++.h>
using namespace std;
#define ll long long


struct edge {
    int node; ll weight; //node on the end of edge, weight of edge
};
// to customize the priority queue, we can use a custom comparator
bool operator < (edge a, edge b){
    return a.weight > b.weight;
}
const int N = 1e5;
ll distance_to_node[N];
int parent[N];
vector<edge> graph[N];

void dijkstra(int start, int destination)
{
    memset(distance_to_node,63,sizeof distance_to_node);
    priority_queue<edge>pq;
    pq.push({start,0});
    distance_to_node[start] = 0; parent[start] = -1;
    
    while(!pq.empty()){
        auto current = pq.top(); pq.pop();

        if (current.node == destination) break;
        
        for (auto e : graph[current.node]){
            ll new_weight = current.weight + e.weight;
            if (distance_to_node[e.node] > new_weight) {
                distance_to_node[e.node] = new_weight;
                pq.push({e.node, new_weight});
                parent[e.node] = current.node;
            }
        }
    }
	//no path
    if (parent[destination] == 0)
    	return;

    vector<int> path;
    int cur = destination;
    while(cur != -1){
        path.push_back(cur);
        cur = parent[cur];
    }
    reverse(path.begin(), path.end());
}
