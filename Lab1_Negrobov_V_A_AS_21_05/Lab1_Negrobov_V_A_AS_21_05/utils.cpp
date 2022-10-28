#include "utils.h"


bool pipe_in_rep_input() {
	std::cout << "1.Pipe is in repearing 2.Pipe is working" << std::endl;
	return get_num_value(1, 3) == 1;
}

void print_menu() {
	std::cout << "1.Add a pipe" << std::endl
		<< "2.Add a CS" << std::endl
		<< "3.View all objects" << std::endl
		<< "4.Delete pipe" << std::endl
		<< "5.Delete CS" << std::endl
		<< "6.Edit pipe" << std::endl
		<< "7.Edit CS" << std::endl
		<< "8.save" << std::endl
		<< "9.Load" << std::endl
		<< "0.Exit" << std::endl;
}


void del_pipe(std::unordered_map<int, Pipe>& pipes) {
	int id;
	std::cout << "Select the pipe id: ";
	std::cin >> id;

	if (pipes.find(id) != pipes.end()) {
		pipes.erase(id);
		std::cout << "Pipe was deleted" << std::endl;
	}
	else {
		std::cout << "There is no pipe with this id" << std::endl;
	}
}


void del_compr_station(std::unordered_map<int, Compr_station>& compr_stations) {
	int id;
	std::cout << "Select the pipe id: ";
	std::cin >> id;

	if (compr_stations.find(id) != compr_stations.end()) {
		compr_stations.erase(id);
		std::cout << "CS was deleted" << std::endl;
	}
	else {
		std::cout << "There is no CS with this id" << std::endl;
	}
}


void edit_pipe(std::unordered_map<int, Pipe>& pipes) {
	int id;
	std::cout << "Select the pipe id: " << std::endl;
	std::cin >> id;

	if (pipes.find(id) != pipes.end()) {
		pipes[id].edit();
		std::cout << "Pipe was edited" << std::endl;
	}
	else {
		std::cout << "There is no pipe with this id" << std::endl;
	}
}

void edit_compr_station(std::unordered_map<int, Compr_station>& compr_stations) {
	int id;
	std::cout << "Select the CS id: " << std::endl;
	std::cin >> id;

	if (compr_stations.find(id) != compr_stations.end()) {
		compr_stations[id].edit();
		std::cout << "CS was edited" << std::endl;
	}
	else {
		std::cout << "There is no CS with this id" << std::endl;
	}

}


void save_data(std::string f_name, const std::unordered_map<int, Pipe>& pipes, const std::unordered_map<int, Compr_station>& compr_stations) {
	std::ofstream file(f_name + ".txt");

	file << pipes.size() << ' ' << compr_stations.size() << std::endl;

	for (const auto& Pp : pipes) {
		file << Pp.first << std::endl;
		file << Pp.second;

	}

	for (const auto& Cs : compr_stations) {
		file << Cs.first << std::endl;
		file << Cs.second;
	}
}


void read_data(std::string f_name, std::unordered_map<int, Pipe>& pipes, std::unordered_map<int, Compr_station>& compr_stations) {

	pipes.clear();
	compr_stations.clear();

	std::ifstream file_handler(f_name + ".txt");
	std::string name;

	if (file_handler.is_open()) {

		int num_Pp;
		int num_Cs;
		file_handler >> num_Pp >> num_Cs;


		for (int i(0); i < num_Pp; ++i) {
			Pipe Pp;
			file_handler >> Pp;
			pipes[Pp.get_id()] = Pp;
			Pp.up_id();
		}

		for (int i(0); i < num_Cs; ++i) {
			Compr_station Cs;
			file_handler >> Cs;
			compr_stations[Cs.get_id()] = Cs;
			Cs.up_id();
		}

	}

	else
	{
		std::cout << "There is no file with that name" << std::endl;
	}
}


void show_pipes(std::unordered_map<int, Pipe>& pipes) {
	if (pipes.size() != 0) {
		for (const auto& Pp : pipes) {
			std::cout << "Pipe id: " << Pp.first << std::endl;
			std::cout << Pp.second;
		}
	}
	else {
		std::cout << "There is no pipes" << std::endl;
	}
}


void show_pipes(std::unordered_set<int>& idx, std::unordered_map<int, Pipe>& pipes) {
	if (idx.size() != 0) {
		for (int i : idx) {
			std::cout << "Pipe id: " << i << std::endl;
			std::cout << pipes[i];
		}
	}
	else {
		std::cout << "There is no pipes" << std::endl;
	}
}


void show_compr_stations(const std::unordered_map<int, Compr_station>& compr_stations) {
	if (compr_stations.size() != 0) {
		for (const auto& Cs : compr_stations) {
			std::cout << "CS id: " << Cs.first << std::endl;
			std::cout << Cs.second;
		}
	}
	else {
		std::cout << "There is no CS" << std::endl;
	}
}


void show_compr_stations(std::unordered_set<int>& idx, std::unordered_map<int, Compr_station>& compr_stations) {
	if (idx.size() != 0) {
		for (int i : idx) {
			std::cout << "Cs id: " << i;
			std::cout << compr_stations[i];
		}
	}
	else {
		std::cout << "There is no CS" << std::endl;
	}
}
