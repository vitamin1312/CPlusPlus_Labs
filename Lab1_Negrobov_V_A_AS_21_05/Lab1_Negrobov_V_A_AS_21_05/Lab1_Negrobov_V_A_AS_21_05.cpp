#include <iostream>
#include <fstream>
#include <unordered_map>
#include <unordered_set>

#include "utils.h"
#include "Pipe.h"
#include "Compr_station.h"

using namespace std;


/*
unordered_set<int> find_in_rep_pipes(unordered_map<int, Pipe>& pipes) {
	unordered_set<int> idx;
	for (const auto& Pp : pipes) {
		if (Pp.second.in_repairing == true) {
			idx.insert(Pp.first);
		}
		return idx;
	}
}

unordered_set<int> find_name_pipes(string name, unordered_map<int, Pipe>& pipes) {
	unordered_set<int> idx;
	for (const auto& Pp : pipes) {
		if (Pp.second.name.find(name) != string::npos) {
			idx.insert(Pp.first);
		}
		return idx;
	}
}
*/


int main()
{
	unordered_map<int, Pipe> pipes;
	unordered_map<int, Compr_station> compr_stations;

	while (true) {
		print_menu();

		switch (get_num_value(0, 10))
		{
		case 0:
		{	cout << "Goodbye";
			return 0;
		}

		case 1:
		{	Pipe Pp;
			cin >> Pp;
			pipes[Pp.get_id()] = Pp;
			Pp.up_id();
			break;
		}

		case 2:
		{
			Compr_station Cs;
			cin >> Cs;
			compr_stations[Cs.get_id()] = Cs;
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
			string name;
			cout << "Input name of file for saving: ";
			cin >> name;
			save_data(name, pipes, compr_stations);
			cout << "Data was saved" << endl;
			break;
		}

		case 9:
		{
			string name;
			cout << "Input name of file for loading: ";
			cin >> name;
			read_data(name, pipes, compr_stations);
			cout << "Data was loaded" << endl;
			break;
		}

		default:
			break;
		}
	}
	return 0;
}
