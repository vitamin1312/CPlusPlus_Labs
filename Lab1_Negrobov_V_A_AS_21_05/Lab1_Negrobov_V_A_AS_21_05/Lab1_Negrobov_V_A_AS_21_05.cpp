#include <iostream>
#include <string>
#include <limits>
#include <fstream>

using namespace std;


struct Pipe {
	float len = 0;
	float diameter = 0;
	bool in_repairing = 0;
	bool exist = false;
};


struct Compr_station {
	string name = " ";
	int num_workshops = 0;
	int num_run_workshops = 0;
	float efficiency = 0;
	bool exist = false;
};


float get_float_value(float least=0) {
	float val = 0;
	while (true) {
		cin >> val;
		if ((val > least) && (cin.good())) return val;
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cout << "Please, input correct value: ";
	}
}

int get_int_value(float least=0, float great=std::numeric_limits<float>::max()) {
	int val = 0;
	while (true) {
		cin >> val;
		if ((val > least) && cin.good() && (val < great)) return val;
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cout << "Please, input correct value: ";
	}
}


bool pipe_in_rep_input() {
	int in_repearing = false;
	while (true) {
		cin >> in_repearing;

		if ((in_repearing == 1) && cin.good()) return true;

		else if ((in_repearing == 2) && (cin.good())) return false;

		else cout << "Input the correct number: ";

		cin.clear();
		cin.ignore(INT_MAX, '\n');
	}
}


void view_obj(Pipe Pp, Compr_station Cs) {
	if (Cs.exist == true) {
		cout << "Ccompressor station" << endl;
		cout << "The name of compressor station: " << Cs.name << endl;
		cout << "Number of workshops on conpressor station: " << Cs.num_workshops << endl;
		cout << "Number of running workshops on conpressor station: " << Cs.num_run_workshops << endl;
		cout << "Efficiency conpressor station: " << Cs.efficiency << endl << endl;
	}
	else {
		cout << "There is no compressor station" << endl;
	}

	if (Pp.exist == true) {
		cout << "Pipe" << endl;
		cout << "Length of pipe: " << Pp.len << endl;
		cout << "Diameter of pipe: " << Pp.diameter << endl;
		string in_rep = Pp.in_repairing ? "Pipe is working" : "Pipe in repearing";
		cout << in_rep << endl << endl;
	}
	else {
		cout << "There is no pipe" << endl;
	}
};


int main()
{
	Pipe Pp;
	Compr_station Cs;

	while (true) {
		system("cls");
		cout << "1.Add a pipe 2.Add a CS 3.View all objects 4.Edit pipe 5.Edit CS 6.save 7.Load 0.Exit" << endl;
		int choice = get_int_value(-1, 8);

		if (choice == 0) {
			system("cls");
			cout << "Goodbye";
			break;
		}

		if (choice == 1) {
			if (Pp.exist == true) {
				cout << "Pipe exist" << endl;
				system("pause");
			}
			else {
				system("cls");
				cout << "Input the length of Pipe: ";
				Pp.len = get_float_value();
				cout << "Input the diameter of Pipe: ";
				Pp.diameter = get_float_value();
				cout << "1.Pipe is in repearing 2.Pipe is working" << endl;
				Pp.in_repairing = pipe_in_rep_input();
				Pp.exist = true;
			}
		}

		if (choice == 2) {
			if (Cs.exist == true) {
				cout << "CS exist" << endl;
				system("pause");
			}
			else {
				system("cls");
				cout << "Input the Name of CS: ";
				cin.ignore();
				getline(cin, Cs.name);
				cout << "Input number of workshops: ";
				Cs.num_workshops = get_int_value();
				cout << "Input number of running workshops: ";
				Cs.num_run_workshops = get_int_value(0, Cs.num_workshops + 1);
				cout << "Input the efficiency of CS: ";
				Cs.efficiency = get_float_value(-std::numeric_limits<float>::max());
				Cs.exist = true;
			}
		}

		if (choice == 3) {
			view_obj(Pp, Cs);
			system("pause");
		}

		if (choice == 4) {
			if (Pp.exist == false) {
				cout << "There is no pipe to edit" << endl;
				system("pause");
			}
			else {
				system("cls");
				cout << "Input the length of Pipe: ";
				Pp.len = get_float_value();
				cout << "Input the diameter of Pipe: ";
				Pp.diameter = get_float_value();
				cout << "1.Pipe is in repearing 2.Pipe is working" << endl;
				Pp.in_repairing = pipe_in_rep_input();
				Pp.exist = true;
			}
		}

		if (choice == 5) {
			if (Cs.exist == false) {
				cout << "There is no CS now" << endl;
				system("pause");
			}
			else {
				system("cls");
				cout << "Input the Name of CS: ";
				cin.ignore();
				getline(cin, Cs.name);
				cout << "Input number of workshops: ";
				Cs.num_workshops = get_int_value();
				cout << "Input number of running workshops: ";
				Cs.num_run_workshops = get_int_value(0, Cs.num_workshops + 1);
				cout << "Input the efficiency of CS: ";
				Cs.efficiency = get_float_value(-std::numeric_limits<float>::max());
				Cs.exist = true;
			}
		}

		if (choice == 6) {
			ofstream file("data.txt");
			file << Pp.len << endl << Pp.diameter << endl << Pp.in_repairing << endl << Pp.exist << endl
			 << Cs.name << endl << Cs.num_workshops << endl << Cs.num_run_workshops << endl << Cs.efficiency << endl << Cs.exist;
			file.close();
			cout << "Data was saved" << endl;
			system("pause");
		}

		if (choice == 7) {
			ifstream file_handler("data.txt");
			string name;

			if (file_handler.is_open()) {

				file_handler >> Pp.len;
				file_handler >> Pp.diameter;
				file_handler >> Pp.in_repairing;
				file_handler >> Pp.exist;

				if (getline(file_handler, name)) Cs.name = name;
				if (getline(file_handler, name)) Cs.name = name;
				file_handler >> Cs.num_workshops;
				file_handler >> Cs.num_run_workshops;
				file_handler >> Cs.efficiency;
				file_handler >> Cs.exist;

				cout << "Data was load" << endl;
			}
			else cout << "There is no data file" << endl;
			system("pause");


		}
	}
	return 0;
}
