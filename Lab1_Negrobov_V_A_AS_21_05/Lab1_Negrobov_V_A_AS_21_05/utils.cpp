#include "utils.h"
#include <vector>
#include <list>
#include <stack>

void topologicalSortUtil(int v, std::unordered_set<int>& visited,
						 std::stack<int>& Stack, 
						 std::unordered_map<int, std::unordered_set<int>>& graph)
{
	visited.insert(v);
	for (auto& adj : graph[v])
	{
		if (visited.find(adj) == visited.end())
			topologicalSortUtil(adj, visited, Stack, graph);
	}

	Stack.push(v);
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