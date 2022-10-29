#include "utils.h"


bool pipe_in_rep_input() {
	std::cout << "1.Pipe is in repearing 2.Pipe is working" << std::endl;
	return get_num_value(1, 3) == 1;
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
		if (Pp.second.get_in_rep() == true) {
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


void change_in_rep(std::unordered_set<int>& idx, std::unordered_map<int, Pipe>& pipes) {
	for (int i : idx) {
		pipes[i].change_in_rep();
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


void do_command(int choice, std::unordered_map<int, Pipe>& pipes, std::unordered_map<int, Compr_station>& compr_stations) {

	if (choice == 0){
		std::cout << "Goodbye";
	}

	if (choice == 1){
		Pipe Pp;
		std::cin >> Pp;
		pipes[Pp.get_id()] = Pp;
		//pipes_idx.insert(Pp.get_id());
		Pp.up_id();
	}

	if (choice == 2){
		Compr_station Cs;
		std::cin >> Cs;
		compr_stations[Cs.get_id()] = Cs;
		//comprt_st_idx.insert(Cs.get_id());
		Cs.up_id();
	}

	if (choice == 3){
		show(pipes);
		show(compr_stations);
	}

	if (choice == 4){
		del_pipe(pipes);
	}

	if (choice == 5){
		del_compr_station(compr_stations);
	}

	if (choice == 6){
		edit_pipe(pipes);
	}

	if (choice == 7){
		edit_compr_station(compr_stations);
	}

	if (choice == 8){
		filter_pipes(pipes);
	}

	if (choice == 9){
		filter_compr_stations(compr_stations);
	}


	if (choice == 10){
		std::string name;
		std::cout << "Input name of file for saving: ";
		std::cin >> name;
		save_data(name, pipes, compr_stations);
		std::cout << "Data was saved" << std::endl;
	}

	if (choice == 11){
		std::string name;
		std::cout << "Input name of file for loading: ";
		std::cin >> name;
		read_data(name, pipes, compr_stations);
		std::cout << "Data was loaded" << std::endl;
	}

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
		std::cin >> name;

		filter_by_name(name, pipes, idx);
		show(idx, pipes);
	}

	if (choice == 2) {

		filter_by_rep(true, pipes, idx);
		show(idx, pipes);

	}

	if (choice == 3) {

		filter_by_rep(false, pipes, idx);
		show(idx, pipes);

	}

	if (idx.size() != 0) {
		choose();
		choice = get_num_value(1, 3);

		if (choice == 1) {
			del_or_edit();

			choice = get_num_value(1, 3);

			if (choice == 1) del_objects(idx, pipes);
			if (choice == 2) change_in_rep(idx, pipes);
		}

		else if (choice == 2) {
			std::unordered_set<int> new_idx = get_new_idx(idx);

			del_or_edit();
			choice = get_num_value(1, 3);

			if (choice == 1) del_objects(new_idx, pipes);
			if (choice == 2) change_in_rep(idx, pipes);
		}
	}
	else {
		std::cout << "There is no pipes" << std::endl;
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
		std::cin >> name;

		filter_by_name(name, compr_stations, idx);
		show(idx, compr_stations);
	}

	if (choice == 2) {

		int percent;
		std::cout << "Input percent: ";
		std::cin >> percent;
		filter_unused_per(percent, true, compr_stations, idx);
		show(idx, compr_stations);

	}

	if (choice == 3) {

		int percent;
		std::cout << "Input percent: ";
		std::cin >> percent;

		filter_unused_per(false, percent, compr_stations, idx);
		show(idx, compr_stations);

	}

	if (idx.size() != 0) {
		choose();
		choice = get_num_value(1, 3);

		if (choice == 1) {
			del_or_edit();

			choice = get_num_value(1, 3);

			if (choice == 1) del_objects(idx, compr_stations);
			if (choice == 2) {
				double eff;
				std::cout << "Input the efficien of CS: ";
				std::cin >> eff;
				change_eff(eff, idx, compr_stations);
			}
		}

		else if (choice == 2) {
			std::unordered_set<int> new_idx = get_new_idx(idx);

			del_or_edit();
			choice = get_num_value(1, 3);

			if (choice == 1) del_objects(new_idx, compr_stations);
			if (choice == 2) {
				double eff;
				std::cout << "Input the efficien of CS: ";
				std::cin >> eff;
				change_eff(eff, idx, compr_stations);
			}
		}
	}
	else {
		std::cout << "There is no CS" << std::endl;
	}
}
