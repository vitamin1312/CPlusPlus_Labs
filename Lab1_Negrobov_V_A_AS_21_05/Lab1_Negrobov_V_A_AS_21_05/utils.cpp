#include "utils.h"
#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <tuple>
#include <limits>



bool bfs(const std::vector<std::vector<double>> &r_graph, int s, int t, std::vector<int> &parent) {

	const int V = r_graph.size();
	std::vector<int> visited(V, 0);
	std::queue<int> q;
	int u;

	q.push(s);
	parent[s] = -1;

	while (!q.empty()) {
		u = q.front();
		q.pop();

		for (int v = 0; v < V; v++) {

			if (visited[v] == false && r_graph[u][v] > 0) {

				parent[v] = u;

				if (v == t) {
					
					return true;
				}

				q.push(v);
				visited[v] = true;

			}
		}
	}

	return false;
}


double ford_fulkerson(std::vector<std::vector<double>> &graph, int s, int t) {
	
	int u, v;
	int V = graph.size();
	std::vector<std::vector<double>> r_graph = graph;
	std::vector<int> parent(V, 0);
	double max_flow = 0;
	double path_flow;


	while (bfs(r_graph, s, t, parent)) {

		path_flow = std::numeric_limits<double>::max();

		for (v = t; v != s; v = parent[v]) {
			u = parent[v];
			path_flow = std::min(path_flow, r_graph[u][v]);
		}

		for (v = t; v != s; v = parent[v]) {
			u = parent[v];

			r_graph[u][v] -= path_flow;
			r_graph[v][u] += path_flow;
		}

		max_flow += path_flow;
	}

	return max_flow;
}


std::stack<int> topoligical_sort(std::unordered_map<int, std::unordered_set<int>>& graph) 
{
	std::unordered_set<int> visited;
	std::stack<int> Stack;
	std::unordered_set<int> gray;

	for (auto& [v, neighbours] : graph)	{
		if (visited.find(v) == visited.end()) {
			gray.clear();
			topological_sort_util(v, visited, Stack, graph, gray);

			if (Stack.empty())
				return Stack;
		}
			
	}

	return Stack;
	
}

void topological_sort_util(int v, std::unordered_set<int>& visited,
						 std::stack<int>& Stack, 
						 std::unordered_map<int, std::unordered_set<int>>& graph,
	                     std::unordered_set<int> gray)
{
	visited.insert(v);
	gray.insert(v);


	for (const int &adj : graph[v])
	{
		if (visited.find(adj) == visited.end())
			topological_sort_util(adj, visited, Stack, graph, gray);

		if (Stack.empty())
			return;

		if (gray.contains(adj)) {
			while (!Stack.empty())
				Stack.pop();
			return;
		}
	}

	Stack.push(v);
}


std::vector<double> dijkstra(std::vector<std::vector<double>> graph, int src) {

	std::unordered_set<int> spt_set;
	double Inf = std::numeric_limits<double>::max();
	std::vector<double> dist(graph.size(), Inf);
	dist[src] = 0;
	
	for (int count(0); count < (graph.size() - 1); ++count) {

		int u = min_dist_node(spt_set, dist);

		spt_set.insert(u);


		for (int v(0); v < graph.size(); ++v) {
			if (!spt_set.contains(v) && graph[u][v] != 0 && dist[u] != Inf)
				dist[v] = std::min(dist[v], dist[u] + graph[u][v]);
		}
	}

	return dist;
}


int min_dist_node(const std::unordered_set<int>& spt_set, const std::vector<double>& dist) {

	double least = std::numeric_limits<double>::max();
	int idx = 0;

	for (int i(0); i < dist.size(); ++i) {
		if (dist[i] < least && !spt_set.contains(i)) {
			least = dist[i];
			idx = i;
		}	
	}

	return idx;
}


bool pipe_in_rep_input() {
	std::cout << "1.Pipe is in repearing 2.Pipe is working" << std::endl;
	return get_num_value(1, 3) == 1;
}

bool check_pipe_name(const Pipe& Pp, std::string name) {
	return Pp.get_name().find(name) != std::string::npos;
}


bool check_pipe_in_rep(const Pipe& Pp, bool in_rep) {
	return Pp.get_in_rep() == in_rep;
}


bool check_compr_st_name(const Compr_station& Cs, std::string name) {
	return Cs.get_name().find(name) != std::string::npos;
}


bool check_unused_per_m(const Compr_station& Cs, double percent) {
	return Cs.unused_per() >= percent;
}


bool check_unused_per_l(const Compr_station& Cs, double percent) {
	return Cs.unused_per() <= percent;
}


bool check_unused_per_e(const Compr_station& Cs, double percent) {
	return Cs.unused_per() == percent;
}