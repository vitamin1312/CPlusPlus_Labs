#include <iostream>
#include <unordered_map>
#include <limits>

#include "utils.h"
#include "Pipe.h"
#include "Compr_station.h"

void do_command(int choice, std::unordered_map<int, Pipe>& pipes, std::unordered_map<int, Compr_station>& compr_stations);


int main()
{
	std::unordered_map<int, Pipe> pipes;
	std::unordered_map<int, Compr_station> compr_stations;
	int choice;

	while (true) {
		std::cout << "1.Add a pipe" << std::endl
			<< "2.Add a CS" << std::endl
			<< "3.View all objects" << std::endl
			<< "4.Delete single pipe" << std::endl
			<< "5.Delete single CS" << std::endl
			<< "6.Edit single pipe" << std::endl
			<< "7.Edit single CS" << std::endl
			<< "8.Filter pipes" << std::endl
			<< "9.Filter CS" << std::endl
			<< "10.Save" << std::endl
			<< "11.Load" << std::endl
			<< "0.Exit" << std::endl;

		choice = get_num_value(0, 12);
		do_command(choice, pipes, compr_stations);
		if (choice == 0) break;
	}
	return 0;
}


void do_command(int choice, std::unordered_map<int, Pipe>& pipes, std::unordered_map<int, Compr_station>& compr_stations) {

	if (choice == 0) {
		std::cout << "Goodbye";
	}

	else if (choice == 1) {
		Pipe Pp;
		std::cin >> Pp;
		pipes[Pp.get_max_id()] = Pp;
	}

	else if (choice == 2) {
		Compr_station Cs;
		std::cin >> Cs;
		compr_stations[Cs.get_max_id()] = Cs;
	}

	else if (choice == 3) {
		std::cout << "Pipes:" << std::endl;
		show(pipes);
		std::cout << "Compresor stations:" << std::endl;
		show(compr_stations);
	}

	else if (choice == 4) {
		if (show(pipes)) {
			int id;
			std::cout << "Select the pipe id: ";
			id = get_num_value(0, std::numeric_limits<int>::max());
			if (del_pipe(id, pipes)) std::cout << "Pipe was deleted" << std::endl;
			else std::cout << "There is no pipe with that id" << std::endl;
		}
	}

	else if (choice == 5) {
		if (show(compr_stations)) {
			int id;
			std::cout << "Input the CS id: ";
			id = get_num_value(0, std::numeric_limits<int>::max());
			if (del_compr_station(id, compr_stations)) std::cout << "CS was deleted" << std::endl;
			else std::cout << "There is no CS with that id" << std::endl;
		}
	}

	else if (choice == 6) {

		if (show(pipes)) {
			int id;
			std::cout << "Input pipe id: " << std::endl;
			id = get_num_value(0, std::numeric_limits<int>::max());;

			if (edit_pipe(id, pipes)) std::cout << "Pipe was edited" << std::endl;
			else std::cout << "There is no pipe with that id" << std::endl;
		}
	}

	else if (choice == 7) {
		if (show(compr_stations)) {
			int id;
			std::cout << "Input CS id: " << std::endl;
			id = get_num_value(0, std::numeric_limits<int>::max());

			edit_compr_station(id, compr_stations);
		}
	}

	else if (choice == 8) {
		if (pipes.size() != 0) filter_pipes(pipes);
		else std::cout << "There are no Pipes" << std::endl;
	}

	else if (choice == 9) {
		if (compr_stations.size() != 0)	filter_compr_stations(compr_stations);
		else std::cout << "There are no CS" << std::endl;
	}

	else if (choice == 10) {
		std::string name;
		std::cout << "Input name of file for saving: ";
		std::cin >> name;
		if (save_data(name, pipes, compr_stations))	std::cout << "Data was saved" << std::endl;
		else std::cout << "Data was not saved" << std::endl;
	}

	else if (choice == 11) {
		std::string name;
		std::cout << "Input name of file for loading: ";
		std::cin >> name;
		if (read_data(name, pipes, compr_stations)) std::cout << "Data was loaded" << std::endl;
		else std::cout << "There is no file with that name" << std::endl;
	}
}
