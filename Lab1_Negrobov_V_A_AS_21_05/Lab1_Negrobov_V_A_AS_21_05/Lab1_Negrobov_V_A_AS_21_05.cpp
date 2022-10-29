#include <iostream>
#include <unordered_map>

#include "utils.h"
#include "Pipe.h"
#include "Compr_station.h"


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
			<< "10.save" << std::endl
			<< "11.Load" << std::endl
			<< "0.Exit" << std::endl;
		choice = get_num_value(0, 12);
		do_command(choice, pipes, compr_stations);
		if (choice == 0) break;
	}
	return 0;
}
