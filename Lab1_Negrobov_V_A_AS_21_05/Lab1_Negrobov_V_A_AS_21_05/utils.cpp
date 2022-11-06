#include "utils.h"

/////////////////////////////////////////single objects/////////////////////////////////////////
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
	return false;
}


/////////////////////////////////////////working with data/////////////////////////////////////////
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


std::unordered_set<int> get_new_ids(std::unordered_set<int> ids) {
	std::unordered_set<int> new_ids;
	int id;
	while (true) {
		std::cout << "Input -1 to close." << std::endl << "Input selected id: ";
		id = get_num_value(-1, std::numeric_limits<int>::max());

		if (id == -1) {
			break;
		}

		else if (ids.find(id) != ids.end()) {
			new_ids.insert(id);
		}
		else {
			std::cout << "There is no object with that id" << std::endl;
		}
	}
	return new_ids;
}


void change_in_rep(bool in_rep, std::unordered_set<int>& ids, std::unordered_map<int, Pipe>& pipes) {
	for (int i : ids) {
		pipes[i].set_in_rep(in_rep);
    }
}


void change_eff(double eff, std::unordered_set<int>& ids, std::unordered_map<int, Compr_station>& compr_stataions) {
	for (int i : ids) {
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


/////////////////////////////////////////batch edditing/////////////////////////////////////////
void filter_pipes(std::unordered_map<int, Pipe>& pipes) {
	std::cout << "1.Filter by name" << std::endl
		<< "2.Filter by \"In repearing\"" << std::endl
		<< "3.Filter by \"Working\"" << std::endl;
	int choice = get_num_value(1, 4);
	std::unordered_set<int> ids;

	if (choice == 1) {

		std::string name;
		std::cout << "Input name of pipe: ";
		std::cin.ignore(10000, '\n');
		std::getline(std::cin, name);

		ids = find_pipes_ids(pipes, check_pipe_name, name);
	}

	if (choice == 2) {

		ids = find_pipes_ids(pipes, check_pipe_in_rep, true);
	}

	if (choice == 3) {

		ids = find_pipes_ids(pipes, check_pipe_in_rep, false);
	}

	if (show(ids, pipes)) {

		std::cout << "1.close" << std::endl << "2.filter pipes" << std::endl;
		choice = get_num_value(1, 3);

		if (choice == 1) {
			return;
		}

		if (choice == 2) {
			choose();
			choice = get_num_value(1, 3);

			if (choice == 2) 
				ids = get_new_ids(ids);

			del_or_edit();

			choice = get_num_value(1, 3);

			if (choice == 1) del_objects(ids, pipes);
			if (choice == 2) {
				bool in_rep;
				std::cout << "Choose status: 1.In repairing, 2.Working" << std::endl;
				in_rep = pipe_in_rep_input();
				change_in_rep(in_rep, ids, pipes);
			}
		}
	}
}


void filter_compr_stations(std::unordered_map<int, Compr_station>& compr_stations) {
	std::cout << "1.Filter by name" << std::endl
		<< "2.Filter by \"percent of unused worcstataoins > \"" << std::endl;
	int choice = get_num_value(1, 4);
	std::unordered_set<int> ids;

	if (choice == 1) {

		std::string name;
		std::cout << "Input name of CS: ";
		std::cin.ignore(10000, '\n');
		std::getline(std::cin, name);

		ids = find_compr_st_ids(compr_stations, check_compr_st_name, name);
	}

	if (choice == 2) {

		double percent = get_num_value(0.0, 100.0);
		std::cout << "Input percent: ";
		ids = find_compr_st_ids(compr_stations, check_unused_per, percent);
	}


	if (show(ids, compr_stations)) {

		std::cout << "1.close" << std::endl << "2.filter CS" << std::endl;
		choice = get_num_value(1, 3);

		if (choice == 1) {
			return;
		}

		if (choice == 2) {
			choose();
			choice = get_num_value(1, 3);

			if (choice == 2)
				ids = get_new_ids(ids);

			del_or_edit();
			choice = get_num_value(1, 3);

			if (choice == 1) del_objects(ids, compr_stations);
			if (choice == 2) {
				double eff;
				std::cout << "Input the efficien of CS: ";
				std::cin >> eff;
				change_eff(eff, ids, compr_stations);
			}
		}
	}
}


/////////////////////////////////////////filters/////////////////////////////////////////
bool check_pipe_name(const Pipe& Pp, std::string name) {
	return Pp.get_name().find(name) != std::string::npos;
}


bool check_pipe_in_rep(const Pipe& Pp, bool in_rep) {
	return Pp.get_in_rep() == in_rep;
}

//////////////////////////////////////////////////////////////////////////////////
bool check_compr_st_name(const Compr_station& Cs, std::string name) {
	return Cs.get_name().find(name) != std::string::npos;
}


bool check_unused_per(const Compr_station& Cs, double percent) {
	return Cs.unused_per() <= percent;
}
