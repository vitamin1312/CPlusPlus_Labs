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


/////////////////////////////////////////working with files/////////////////////////////////////////
bool save_data(std::string f_name, const std::unordered_map<int, Pipe>& pipes, const std::unordered_map<int, Compr_station>& compr_stations) {
	std::ofstream file; 
	file.open(f_name + ".txt");
	if (file.is_open()) {
		file << pipes.size() << ' ' << compr_stations.size() << std::endl;

		for (const auto& Pp : pipes) {
			file << Pp.first << std::endl;
			file << Pp.second;

		}

		for (const auto& Cs : compr_stations) {
			file << Cs.first << std::endl;
			file << Cs.second;
		}
		file.close();
		return true;
	}
	return false;
}


bool read_data(std::string f_name, std::unordered_map<int, Pipe>& pipes, std::unordered_map<int, Compr_station>& compr_stations) {

	pipes.clear();
	compr_stations.clear();

	std::ifstream file_handler;
	file_handler.open(f_name + ".txt");
	std::string name;

	if (file_handler.is_open()) {

		int num_Pp;
		int num_Cs;
		file_handler >> num_Pp >> num_Cs;


		for (int i(0); i < num_Pp; ++i) {
			Pipe Pp;
			file_handler >> Pp;
			pipes[Pp.get_max_id()] = Pp;
			Pp.up_max_id();
		}

		for (int i(0); i < num_Cs; ++i) {
			Compr_station Cs;
			file_handler >> Cs;
			compr_stations[Cs.get_max_id()] = Cs;
			Cs.up_max_id();
		}

		file_handler.close();
		return true;

	}

	else
	{
		return false;
	}
}

/////////////////////////////////////////working with some objects/////////////////////////////////////////
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


void change_run_ws(int num, std::unordered_set<int>& ids, std::unordered_map<int, Compr_station>& compr_stataions) {
	for (int i : ids) {
		compr_stataions[i].up_num_run_ws(num);
	}
}


/////////////////////////////////////////choice/////////////////////////////////////////
int choose() {
	std::cout << "1.Choose all objects" << std::endl;
	std::cout << "2.Choose some objects" << std::endl;
	return get_num_value(1, 3);
}


int del_or_edit() {
	std::cout << "1.Delete objects" << std::endl;
	std::cout << "2.Edit objects" << std::endl;
	return get_num_value(1, 3);
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
			
			choice = choose();

			if (choice == 2) 
				ids = get_new_ids(ids);


			choice = del_or_edit();

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
		<< "2.Filter by \"percent of unused worcstataoins >= \"" << std::endl
		<< "3.Filter by \"percent of unused worcstataoins <= \"" << std::endl
		<< "4.Filter by \"percent of unused worcstataoins = \"" << std::endl;
	int choice = get_num_value(1, 5);
	std::unordered_set<int> ids;

	if (choice == 1) {

		std::string name;
		std::cout << "Input name of CS: ";
		std::cin.ignore(10000, '\n');
		std::getline(std::cin, name);

		ids = find_compr_st_ids(compr_stations, check_compr_st_name, name);
	}

	if (choice == 2) {

		std::cout << "Input percent: ";
		double percent = get_num_value(0.0, 100.0);
		ids = find_compr_st_ids(compr_stations, check_unused_per_m, percent);
	}

	if (choice == 3) {

		std::cout << "Input percent: ";
		double percent = get_num_value(0.0, 100.0);
		ids = find_compr_st_ids(compr_stations, check_unused_per_l, percent);
	}

	if (choice == 4) {

		std::cout << "Input percent: ";
		double percent = get_num_value(0.0, 100.0);
		ids = find_compr_st_ids(compr_stations, check_unused_per_e, percent);
	}


	if (show(ids, compr_stations)) {

		std::cout << "1.close" << std::endl << "2.filter CS" << std::endl;
		choice = get_num_value(1, 3);

		if (choice == 1) {
			return;
		}

		if (choice == 2) {
			
			choice = choose();

			if (choice == 2)
				ids = get_new_ids(ids);

			choice = del_or_edit();

			if (choice == 1) del_objects(ids, compr_stations);
			if (choice == 2) {
				std::cout << "Input number of workshops to add: ";
				int num = get_num_value(-std::numeric_limits<int>::max(), std::numeric_limits<int>::max());
				change_run_ws(num, ids, compr_stations);
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


bool check_unused_per_m(const Compr_station& Cs, double percent) {
	return Cs.unused_per() >= percent;
}


bool check_unused_per_l(const Compr_station& Cs, double percent) {
	return Cs.unused_per() <= percent;
}


bool check_unused_per_e(const Compr_station& Cs, double percent) {
	return Cs.unused_per() == percent;
}
