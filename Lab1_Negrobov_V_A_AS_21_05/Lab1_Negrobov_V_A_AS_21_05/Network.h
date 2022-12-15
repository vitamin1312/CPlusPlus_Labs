#pragma once
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <fstream>
#include <stack>

#include "Pipe.h"
#include "Compr_station.h"

#define IN_REPEARING true
#define WORKING false


struct edge_ids {
	int start_cs;
	int end_cs;
	int pipe;
};

std::ifstream& operator >> (std::ifstream& fin, edge_ids& edge);
std::ofstream& operator << (std::ofstream& fout, const edge_ids& edge);


class Network
{
private:
	Pipe current_pipe;
	Compr_station current_cs;
	edge_ids current_edge;

	std::unordered_map<int, Pipe> pipes;
	std::unordered_map<int, Compr_station> compr_stations;
	std::unordered_map<int, edge_ids> edges;

	bool not_node(int id);

	bool not_edge(int id);

	bool is_free_nodes();

	void del_edge(int id);

	int input_cs_id(int forbidden_id);

	void change_in_rep(bool in_rep, std::unordered_set<int>& ids);

	int choose();

	int del_or_edit();

	void change_run_ws(int num, std::unordered_set<int>& ids);

	void del_pipes(const std::unordered_set<int>& ids);

	void del_compr_stations(const std::unordered_set<int>& ids);

	std::unordered_set<int> get_new_ids(std::unordered_set<int> ids);

	template <typename T>
	bool show(std::unordered_map<int, T>& object) {
		if (object.size() != 0) {
			for (const auto& obj : object) {
				std::cout << "Object id: " << obj.first << std::endl;
				std::cout << obj.second;

			}
			return true;
		}
		else {
			std::cout << "There are no objects" << std::endl;
			return false;
		}
	}


	template <typename T>
	bool show(std::unordered_set<int>& ids, std::unordered_map<int, T>& objects) {
		if (ids.size() != 0) {
			for (int i : ids) {
				std::cout << "Object id: " << i << std::endl;
				std::cout << objects[i];
			}
			return true;
		}
		else {
			std::cout << "There are no such objets" << std::endl;
			return false;
		}
	}

	template <typename T>
	using pipe_filter = bool (*)(const Pipe& Cs, T params);


	template <typename T>
	std::unordered_set<int> find_pipes_ids(std::unordered_map<int, Pipe>& pipes, pipe_filter<T> filter, T params) {
		std::unordered_set<int> ids;

		for (const auto& Pp : pipes) {
			if (filter(Pp.second, params)) {
				ids.insert(Pp.first);
			}
		}
		return ids;
	}


	template <typename T>
	using compr_st_filter = bool (*)(const Compr_station& Cs, T params);


	template <typename T>
	std::unordered_set<int> find_compr_st_ids(std::unordered_map<int, Compr_station>& compr_stations, compr_st_filter<T> filter, T params) {
		std::unordered_set<int> ids;

		for (const auto& Cs : compr_stations) {
			if (filter(Cs.second, params)) {
				ids.insert(Cs.first);
			}
		}
		return ids;
	}


public:

	int get_pipes_size();

	int get_compr_stations_size();

	void add_new_pipe();

	void add_new_cs();

	void add_new_edge();

	bool show_pipes();

	bool show_compr_stations();

	bool show_edges();

	bool del_pipe(int id);

	bool del_compr_station(int id);

	bool edit_pipe(int id);

	bool edit_compr_station(int id);

	void filter_pipes();

	void filter_compr_stations();
	
	bool to_file(std::string f_name);
	
	bool from_file(std::string f_name);
	
	void top_sort();

	void shortest_path();

	void get_max_flow();
};
