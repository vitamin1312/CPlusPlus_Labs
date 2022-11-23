#include <iostream>
#include <unordered_map>
#include <limits>

#include "utils.h"
#include "Pipe.h"
#include "Compr_station.h"
#include "Network.h"

void do_command(int choice, Network& network);


int main()
{
	Network network;
	int choice;

	while (true) {
		std::cout << "1.Add a pipe" << std::endl
				  << "2.Add a CS" << std::endl
			      << "3.Add a edge" << std::endl
				  << "4.View all objects" << std::endl
				  << "5.Delete single pipe" << std::endl
				  << "6.Delete single CS" << std::endl
				  << "7.Edit single pipe" << std::endl
				  << "8.Edit single CS" << std::endl
				  << "9.Filter pipes" << std::endl
				  << "10.Filter CS" << std::endl
				  << "11.Save" << std::endl
				  << "12.Load" << std::endl
				  << "0.Exit" << std::endl;

		choice = get_num_value(0, 12);
		do_command(choice, network);
		if (choice == 0) break;
	}
	return 0;
}


void do_command(int choice, Network& network) {

	if (choice == 0) {
		std::cout << "Goodbye";
	}

	else if (choice == 1) {
		network.add_new_pipe();
	}

	else if (choice == 2) {
		network.add_new_cs();
	}

	else if (choice == 3) {
		network.add_new_edge();
	}

	else if (choice == 4) {
		std::cout << "Pipes:" << std::endl;
		show(network.pipes);
		std::cout << "Compresor stations:" << std::endl;
		show(network.compr_stations);
	}

	else if (choice == 5) {
		if (show(network.pipes)) {
			int id;
			std::cout << "Select pipe id: ";
			id = get_num_value(0, std::numeric_limits<int>::max());
			if (network.del_pipe(id)) std::cout << "Pipe was deleted" << std::endl;
			else std::cout << "There is no pipe with that id" << std::endl;
		}
	}

	else if (choice == 6) {
		if (show(network.compr_stations)) {
			int id;
			std::cout << "Input CS id: ";
			id = get_num_value(0, std::numeric_limits<int>::max());
			if (network.del_compr_station(id)) std::cout << "CS was deleted" << std::endl;
			else std::cout << "There is no CS with that id" << std::endl;
		}
	}

	else if (choice == 7) {

		if (show(network.pipes)) {
			int id;
			std::cout << "Input pipe id: " << std::endl;
			id = get_num_value(0, std::numeric_limits<int>::max());;

			if (edit_pipe(id, network.pipes)) std::cout << "Pipe was edited" << std::endl;
			else std::cout << "There is no pipe with that id" << std::endl;
		}
	}

	else if (choice == 8) {
		if (show(network.compr_stations)) {
			int id;
			std::cout << "Input CS id: " << std::endl;
			id = get_num_value(0, std::numeric_limits<int>::max());

			edit_compr_station(id, network.compr_stations);
		}
	}

	else if (choice == 9) {
		if (network.pipes.size() != 0) filter_pipes(network.pipes);
		else std::cout << "There are no Pipes" << std::endl;
	}

	else if (choice == 10) {
		if (network.compr_stations.size() != 0)	filter_compr_stations(network.compr_stations);
		else std::cout << "There are no CS" << std::endl;
	}


	else if (choice == 11) {
		std::string name;
		std::cout << "Input name of file for saving: ";
		std::cin >> name;
		if (network.to_file(name)) std::cout << "Data was saved" << std::endl;
		else std::cout << "Data was not saved" << std::endl;
	}

	else if (choice == 12) {
		std::string name;
		std::cout << "Input name of file for loading: ";
		std::cin >> name;
		if (network.from_file(name)) std::cout << "Data was loaded" << std::endl;
		else std::cout << "There is no file with that name" << std::endl;
	}
}
