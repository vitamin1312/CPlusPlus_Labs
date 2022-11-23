#pragma once
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "Pipe.h"
#include "Compr_station.h"


struct edge_ids {
	int start_cs;
	int end_cs;
	int pipe;
};


std::ifstream& operator >> (std::ifstream& fin, edge_ids& edge);
std::ofstream& operator << (std::ofstream& fout, const edge_ids& edge);


class Network
{
public:
	Pipe current_pipe;
	Compr_station current_cs;
	edge_ids current_edge;

	std::unordered_map<int, Pipe> pipes;
	std::unordered_map<int, Compr_station> compr_stations;
	std::vector<edge_ids> edges;


	bool not_node(int id);

	int input_cs_id();

	int input_cs_id(int forbidden_id);

	void add_new_edge();

	void add_new_pipe();
	
	void add_new_cs();
	
	bool to_file(std::string f_name);
	
	bool from_file(std::string f_name);
	
	bool del_pipe(int id);

	bool del_compr_station(int id);
	
	//std::vector<std::vector<int>> to_adj_matrix();

	friend std::istream& operator >> (std::istream& in, edge_ids& edge);
};
