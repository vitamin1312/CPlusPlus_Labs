#include "Network.h"
#include "utils.h"
#include <fstream>



int Network::input_cs_id(int forbidden_id) {
	while (true) {
		int object_id = get_num_value(1, std::numeric_limits<int>::max());
		if ((this->compr_stations.find(object_id) != this->compr_stations.end())
			and (object_id != forbidden_id)
			and (compr_stations.at(object_id).get_num_workshops() > compr_stations.at(object_id).get_pipes_number())) {

			return object_id;
		}
		else
			std::cout << "Please, input correct object id: ";
	}
}


void Network::add_new_edge() {
	
	compr_stations[current_edge.start_cs].up_pipes_number();
	compr_stations[current_edge.end_cs].up_pipes_number();

	edges.push_back(current_edge);
}


void Network::add_new_pipe() {
	std::cin >> current_pipe;
	pipes[current_pipe.get_max_id()] = current_pipe;
}


void Network::add_new_cs() {
	std::cin >> current_cs;
	compr_stations[current_cs.get_max_id()] = this->current_cs;
}


bool Network::to_file(std::string f_name) {

	std::ofstream file;
	file.open(f_name + ".txt");

	if (file.is_open()) {

		file << pipes.size() << ' ' << compr_stations.size() << ' ' << edges.size() << std::endl;

		for (const auto& Pp : pipes) {
			file << Pp.first << std::endl;
			file << Pp.second;

		}

		for (const auto& Cs : compr_stations) {
			file << Cs.first << std::endl;
			file << Cs.second;
		}

		for (const auto& Ed : edges) {
			file << Ed;
		}

		file.close();
		return true;
	}
	return false;
}


bool Network::from_file(std::string f_name) {

	std::ifstream file_handler;
	file_handler.open(f_name + ".txt");
	std::string name;

	if (file_handler.is_open()) {

		pipes.clear();
		compr_stations.clear();
		edges.clear();

		int num_Pp, num_Cs, num_Ed;
		file_handler >> num_Pp >> num_Cs >> num_Ed;

		for (int i(0); i < num_Pp; ++i) {
			Pipe Pp;
			file_handler >> Pp;
			pipes[Pp.get_id()] = Pp;
		}

		for (int i(0); i < num_Cs; ++i) {
			Compr_station Cs;
			file_handler >> Cs;
			compr_stations[Cs.get_id()] = Cs;
		}

		for (int i(0); i < num_Ed; ++i) {
			edge_ids edge;
			file_handler >> edge;
			edges.push_back(edge);
		}

		file_handler.close();
		return true;
	}
	else
		return false;
}


//std::vector<std::vector<int>> Network::to_adj_matrix() {
//
//	int length = compr_stations.size();
//
//	std::vector<std::vector<int>> matrix(length, std::vector<int>(length, 0));
//
//	for (std::vector<int> vec: matrix) {
//		for (int elem: vec) {
//
//		}
//	}
//}


bool Network::del_pipe(int id) {
	if (pipes.find(id) != pipes.end()) {
		pipes.erase(id);
		return true;
	}
	else
		return false;
}


bool Network::del_compr_station(int id) {

	if (compr_stations.find(id) != compr_stations.end()) {
		compr_stations.erase(id);
		return true;
	}
	else
		return false;
}


bool Network::not_node(int id) {
	for (edge_ids edge : edges) {
		if (id == edge.start_cs or id == edge.end_cs)
			return false;
	}
	return true;
}


std::istream& operator >> (std::istream& in, edge_ids& edge) {
	std::cout << "Input id of start cs: ";
	current_edge.start_cs = input_cs_id(-1);

	std::cout << "Input id of start cs: ";
	current_edge.end_cs = input_cs_id(current_edge.start_cs);

	std::cout << "Input diameter of Pipe for connecting: ";
	double diam = get_num_value(0.0, std::numeric_limits<double>::max());

	for (auto pipe : pipes) {
		if (pipe.second.get_diam() == diam) {
			current_edge.pipe = pipe.first;
			break;
		}
	}
	return in;
}


std::ifstream& operator >> (std::ifstream& fin, edge_ids& edge) {
	fin >> edge.start_cs
		>> edge.end_cs
		>> edge.pipe;
	return fin;
}


std::ofstream& operator << (std::ofstream& fout, const edge_ids& edge) {
	fout << edge.start_cs << ' '
		<< edge.end_cs << ' '
		<< edge.pipe << std::endl;
	return fout;
}
