#include <iostream>
#include <fstream>
#include <unordered_map>

#include "utils.h"
#include "Pipe.h"
#include "Compr_station.h"

using namespace std;


int Pp_id = 0;
int Cs_id = 0;


int main()
{
	Pipe Pp(0);
	Compr_station Cs(0);

	unordered_map<int, Pipe> Pipes;
	unordered_map<int, Compr_station> Compr_stations;



	while (true) {
		cout << "1.Add a pipe 2.Add a CS 3.View all objects 4.Edit pipe 5.Edit CS 6.save 7.Load 0.Exit" << endl;
		int choice = get_int_value(0, 8);

		switch (choice)
		{
		case 0:
			cout << "Goodbye";
			return 0;
		case 1:
			cin >> Pp;
			Pipes[Pp_id++] = Pp;
			Pp.id = Pp_id;
			break;
		case 2:
			cin >> Cs;
			Compr_stations[Cs_id++] = Cs;
			Cs.id = Cs_id;
			break;
		case 3:
			cout << Pp << Cs;
			break;
		case 4:
			Pp.edit();
			break;
		case 5:
			Cs.edit();
			break;
		case 6:
			Pp.to_file();
			Cs.to_file();
			break;
		case 7:
			Pp.read_file();
			Cs.read_file();
			break;
		}
	}
	return 0;
}
