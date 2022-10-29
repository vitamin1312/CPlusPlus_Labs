#include <iostream>
#include <fstream>
#include <unordered_map>
#include <unordered_set>

#include "utils.h"
#include "Pipe.h"
#include "Compr_station.h"




void filter_pipes(std::unordered_map<int, Pipe>& pipes) {
	std::cout << "1.Filter by name" << std::endl
		<< "2.Filter by \"In repearing\"" << std::endl
		<< "3.Filter by \"Working\"" << std::endl;
	int choice = get_num_value(1, 4);
	std::unordered_set<int> idx;

	if (choice == 1) {

		std::string name;
		std::cout << "Input name" << std::endl;
		std::cin >> name;

		for (auto& Pp : pipes) {
			if (Pp.second.get_name().find(name) != std::string::npos) {
				idx.insert(Pp.first);
			}
		}

		show_pipes(idx, pipes);

	}

	if (choice == 2) {


		for (auto& Pp : pipes) {
			if (Pp.second.get_in_rep() == true) {
				idx.insert(Pp.first);
			}
		}

		show_pipes(idx, pipes);

	}

	if (choice == 3) {

		for (auto& Pp : pipes) {
			if (Pp.second.get_in_rep() == false) {
				idx.insert(Pp.first);
			}
		}
		show_pipes(idx, pipes);

	}

	if (idx.size() != 0){

		std::cout << "1.Choose all pipes" << std::endl;
		std::cout << "2.Choose some pipes" << std::endl;

		choice = get_num_value(1, 3);

		if (choice == 1) {
			std::cout << "1.Delete pipes" << std::endl;
			std::cout << "2.Edit pipes" << std::endl;

			choice = get_num_value(1, 3);

			if (choice == 1) {
				for (int i : idx) {
					pipes.erase(i);
				}
			}

			if (choice == 2) {
				for (int i : idx) {
					pipes[i].change_in_rep();
				}
			}
		}

		else if (choice == 2) {
			std::unordered_set<int> new_idx;
			int id;
			while (true) {
				std::cout << "Input index of pipe: ";
				id = get_num_value(-1, pipes[0].get_id() + 1);

				if (id == -1) {
					break;
				}

				if (idx.find(id) != idx.end()) {
					new_idx.insert(id);
				}

			}

			choice = get_num_value(1, 3);


			if (choice == 1) {
				std::cout << "1.Delete pipes" << std::endl;
				std::cout << "2.Edit pipes" << std::endl;
				choice = get_num_value(1, 3);

				if (choice == 1) {
					for (int i : new_idx) {
						pipes.erase(i);
					}
				}

				if (choice == 2) {
					for (int i : new_idx) {
						pipes[i].change_in_rep();
					}
				}
			}
		}
	}


		


}


void filter_compr_stations(std::unordered_map<int, Compr_station>& compr_stations) {
	std::cout << "1.Filter by name" << std::endl
		<< "2.Filter by \"Unused more than\"" << std::endl
		<< "3.Filter by \"Unused less than\"" << std::endl;
	int choice = get_num_value(1, 4);

	if (choice == 1) {

		std::string name;
		std::cout << "Input name" << std::endl;
		std::cin >> name;
		std::unordered_set<int> idx;

		for (auto& Pp : compr_stations) {
			if (Pp.second.get_name().find(name) != std::string::npos) {
				idx.insert(Pp.first);
			}
		}

		show_compr_stations(idx, compr_stations);

	}

	if (choice == 2) {

		int per = get_num_value(0, 100);
		std::unordered_set<int> idx;

		for (auto& Cs : compr_stations) {
			if (Cs.second.unused_per() >= per) {
				idx.insert(Cs.first);
			}
		}

		show_compr_stations(idx, compr_stations);
	}

	if (choice == 3) {
		if (choice == 2) {

			int per = get_num_value(0, 100);
			std::unordered_set<int> idx;

			for (auto& Cs : compr_stations) {
				if (Cs.second.unused_per() <= per) {
					idx.insert(Cs.first);
				}
			}

			show_compr_stations(idx, compr_stations);
		}
	}

}



int main()
{
	//std::unordered_set<int> pipes_idx;
	//std::unordered_set<int> comprt_st_idx;
	std::unordered_map<int, Pipe> pipes;
	std::unordered_map<int, Compr_station> compr_stations;

	while (true) {
		print_menu();

		switch (get_num_value(0, 12))
		{
		case 0:
		{	std::cout << "Goodbye";
		return 0;
		}

		case 1:
		{	Pipe Pp;
		std::cin >> Pp;
		pipes[Pp.get_id()] = Pp;
		//pipes_idx.insert(Pp.get_id());
		Pp.up_id();
		break;
		}

		case 2:
		{
			Compr_station Cs;
			std::cin >> Cs;
			compr_stations[Cs.get_id()] = Cs;
			//comprt_st_idx.insert(Cs.get_id());
			Cs.up_id();
			break;
		}

		case 3:
		{
			show_pipes(pipes);
			show_compr_stations(compr_stations);
			break;
		}

		case 4:
		{

			del_pipe(pipes);
			break;
		}

		case 5:
		{
			del_compr_station(compr_stations);
			break;
		}

		case 6:
		{
			edit_pipe(pipes);
			break;
		}

		case 7:
		{
			edit_compr_station(compr_stations);
			break;
		}

		case 8:
		{
			filter_pipes(pipes);
			break;
		}

		case 9:
		{
			filter_compr_stations(compr_stations);
			break;
		}


		case 10:
		{
			std::string name;
			std::cout << "Input name of file for saving: ";
			std::cin >> name;
			save_data(name, pipes, compr_stations);
			std::cout << "Data was saved" << std::endl;
			break;
		}

		case 11:
		{
			std::string name;
			std::cout << "Input name of file for loading: ";
			std::cin >> name;
			read_data(name, pipes, compr_stations);
			std::cout << "Data was loaded" << std::endl;
			break;
		}

		default:
			break;
		}
	}
}
