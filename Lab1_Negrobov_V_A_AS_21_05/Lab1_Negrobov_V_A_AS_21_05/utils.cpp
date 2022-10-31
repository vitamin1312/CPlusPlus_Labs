#include "utils.h"


bool pipe_in_rep_input() {
	std::cout << "1.Pipe is in repearing 2.Pipe is working" << std::endl;
	return get_num_value(1, 3) == 1;
}


bool del_pipe(int id, std::unordered_map<int, Pipe>& pipes) {
	if (pipes.find(id) != pipes.end()) {
		pipes.erase(id);
		return true;
	}

	else {
		return false;
	}
}


bool del_compr_station(int id, std::unordered_map<int, Compr_station>& compr_stations) {

	if (compr_stations.find(id) != compr_stations.end()) {
		compr_stations.erase(id);
		return true;
	}
	else {
		return false;
	}
}


bool  edit_pipe(int id, std::unordered_map<int, Pipe>& pipes) {

	if (pipes.find(id) != pipes.end()) {
		pipes[id].edit();
		return true;
	}
	else {
		return false;
	}
}


bool edit_compr_station(int id, std::unordered_map<int, Compr_station>& compr_stations) {

	if (compr_stations.find(id) != compr_stations.end()) {
		compr_stations[id].edit();
		return true;
	}
	else {
		return false;
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


bool read_data(std::string f_name, std::unordered_map<int, Pipe>& pipes, std::unordered_map<int, Compr_station>& compr_stations) {

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

		return true;

	}

	else
	{
		return false;
	}
}


std::unordered_set<int> get_new_idx(std::unordered_set<int> idx) {
	std::unordered_set<int> new_idx;
	int id;
	while (true) {
		std::cout << "Input -1 to close." << std::endl << "Input selected id: ";
		id = get_num_value(-1, std::numeric_limits<int>::max());

		if (id == -1) {
			break;
		}

		else if (idx.find(id) != idx.end()) {
			new_idx.insert(id);
		}
		else {
			std::cout << "There is no object with that id" << std::endl;
		}
	}
	return new_idx;
}


void filter_by_rep(const bool in_rep, std::unordered_map<int, Pipe>& pipes, std::unordered_set<int>& idx) {
	for (auto& Pp : pipes) {
		if (Pp.second.get_in_rep() == in_rep) {
			idx.insert(Pp.first);
		}
	}
}


void filter_unused_per(int percent, const bool more, std::unordered_map<int, Compr_station>& compr_stataions, std::unordered_set<int>& idx) {
	for (auto& Cs : compr_stataions) {
		if (more) {
			if (Cs.second.unused_per() > percent) {
				idx.insert(Cs.first);
			}
		}
		else {
			if (Cs.second.unused_per() > percent) {
				idx.insert(Cs.first);
			}
		}
	}
}


void change_in_rep(bool in_rep, std::unordered_set<int>& idx, std::unordered_map<int, Pipe>& pipes) {
	for (int i : idx) {
		pipes[i].set_in_rep(in_rep);
    }
}


void change_eff(double eff, std::unordered_set<int>& idx, std::unordered_map<int, Compr_station>& compr_stataions) {
	for (int i : idx) {
		compr_stataions[i].set_eff(eff);
	}
}


void choose() {
	std::cout << "1.Choose all objects" << std::endl;
	std::cout << "2.Choose some objects" << std::endl;
}


void del_or_edit() {
	std::cout << "1.Delete objects" << std::endl;
	std::cout << "2.Edit objects" << std::endl;
}


void filter_pipes(std::unordered_map<int, Pipe>& pipes) {
	std::cout << "1.Filter by name" << std::endl
		<< "2.Filter by \"In repearing\"" << std::endl
		<< "3.Filter by \"Working\"" << std::endl;
	int choice = get_num_value(1, 4);
	std::unordered_set<int> idx;

	if (choice == 1) {

		std::string name;
		std::cout << "Input name of pipe: ";
		std::cin.ignore(10000, '\n');
		std::getline(std::cin, name);

		filter_by_name(name, pipes, idx);
	}

	if (choice == 2) {

		filter_by_rep(true, pipes, idx);
	}

	if (choice == 3) {

		filter_by_rep(false, pipes, idx);
	}

	if (show(idx, pipes)) {

		std::cout << "1.close" << std::endl << "2.filter pipes" << std::endl;
		choice = get_num_value(1, 3);

		if (choice == 1) {
			return;
		}

		if (choice == 2) {
			choose();
			choice = get_num_value(1, 3);

			if (choice == 1);
			if (choice == 2) idx = get_new_idx(idx);

			del_or_edit();

			choice = get_num_value(1, 3);

			if (choice == 1) del_objects(idx, pipes);
			if (choice == 2) {
				bool in_rep;
				std::cout << "Choose status: 1.In repairing, 2.Working" << std::endl;
				in_rep = pipe_in_rep_input();
				change_in_rep(in_rep, idx, pipes);
			}
		}
	}
}


void filter_compr_stations(std::unordered_map<int, Compr_station>& compr_stations) {
	std::cout << "1.Filter by name" << std::endl
		<< "2.Filter by \"percent of unused worcstataoins > \"" << std::endl
		<< "3.Filter by \"percent of unused worcstataoins < \"" << std::endl;
	int choice = get_num_value(1, 4);
	std::unordered_set<int> idx;

	if (choice == 1) {

		std::string name;
		std::cout << "Input name of CS: ";
		std::cin.ignore(10000, '\n');
		std::getline(std::cin, name);

		filter_by_name(name, compr_stations, idx);
	}

	if (choice == 2) {

		int percent;
		std::cout << "Input percent: ";
		std::cin >> percent;
		filter_unused_per(percent, true, compr_stations, idx);
	}

	if (choice == 3) {

		int percent;
		std::cout << "Input percent: ";
		std::cin >> percent;

		filter_unused_per(false, percent, compr_stations, idx);
	}

	if (show(idx, compr_stations)) {

		std::cout << "1.close" << std::endl << "2.filter CS" << std::endl;
		choice = get_num_value(1, 3);

		if (choice == 1) {
			return;
		}

		if (choice == 2) {
			choose();
			choice = get_num_value(1, 3);

			if (choice == 1);
			if (choice == 2) idx = get_new_idx(idx);


			choice = get_num_value(1, 3);

			if (choice == 1) del_objects(idx, compr_stations);
			if (choice == 2) {
				double eff;
				std::cout << "Input the efficien of CS: ";
				std::cin >> eff;
				change_eff(eff, idx, compr_stations);
			}
		}
	}
}
