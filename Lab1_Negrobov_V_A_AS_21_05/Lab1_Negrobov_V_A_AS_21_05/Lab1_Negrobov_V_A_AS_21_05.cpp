#include <iostream>
#include <fstream>

#include "utils.h"
#include "Pipe.h"
#include "Compr_station.h"

using namespace std;


unsigned long long int Pp_id = 0;
unsigned long long int Cs_id = 0;


int main()
{
	Pipe Pp;
	Compr_station Cs;


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
			break;
		case 2:
			cin >> Cs;
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
