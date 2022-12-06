#pragma once
#include <limits>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <fstream>
#include "Pipe.h"
#include "Compr_station.h"
#include "Network.h"


template <typename T>
T get_num_value(T least, T great) {
	T val = 0;
	while (true) {
		if (std::cin >> val && (std::cin.peek() == EOF || std::cin.peek() == '\n') && (val >= least) && (val < great)) return val;
		else {
			std::cin.clear();
			std::cin.ignore(10000, '\n');
			std::cout << "Please, input correct value: ";
		}
	}
}


//template <typename T>
//using pipe_filter = bool (*)(const Pipe& Cs, T params);
//
//
//template <typename T>
//std::unordered_set<int> find_pipes_ids(std::unordered_map<int, Pipe>& pipes,pipe_filter<T> filter, T params) {
//	std::unordered_set<int> ids;
//
//	for (const auto& Pp : pipes) {
//		if (filter(Pp.second, params)) {
//			ids.insert(Pp.first);
//		}
//	}
//	return ids;
//}
//
//
//template <typename T>
//using compr_st_filter = bool (*)(const Compr_station& Cs, T params);
//
//
//template <typename T>
//std::unordered_set<int> find_compr_st_ids(std::unordered_map<int, Compr_station>& compr_stations, compr_st_filter<T> filter, T params) {
//	std::unordered_set<int> ids;
//
//	for (const auto& Cs : compr_stations) {
//		if (filter(Cs.second, params)) {
//			ids.insert(Cs.first);
//		}
//	}
//	return ids;
//}


bool pipe_in_rep_input();

bool check_pipe_name(const Pipe& Pp, std::string name);

bool check_pipe_in_rep(const Pipe& Pp, bool in_rep);

bool check_compr_st_name(const Compr_station& Cs, std::string name);

bool check_unused_per_m(const Compr_station& Cs, double percent);

bool check_unused_per_l(const Compr_station& Cs, double percent);

bool check_unused_per_e(const Compr_station& Cs, double percent);

void topological_sort_util(int v, std::unordered_set<int>& visited,
	std::stack<int>& Stack,
	std::unordered_map<int, std::unordered_set<int>>& graph,
	std::unordered_set<int> gray);

std::stack<int> topoligical_sort(std::unordered_map<int, std::unordered_set<int>>& graph);