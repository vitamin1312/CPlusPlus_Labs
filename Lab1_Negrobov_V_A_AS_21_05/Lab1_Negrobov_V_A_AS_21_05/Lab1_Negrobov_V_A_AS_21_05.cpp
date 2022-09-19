#include <iostream>
#include <string>
#include <windows.h>
//#include <winuser.h>

using namespace std;


struct Pipe {
	float len;
	float diameter;
	bool in_repairing;
	bool exist = false;
};


struct Compr_station {
	string name;
	int num_workshops;
	int num_run_workshops;
	float efficiency;
	bool exist = false;
};


int menu_choice() {
	int choice = 0;
	while (true) {
		cin >> choice;
		if ((choice >= 0) && (choice <= 7) && (cin.good())) return choice;
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cout << "Please, enter the correct number" << endl;
	};
}


float pipe_len_input() {
	float len = 0;
	cout << "Input the length of Pipe: ";
	while (true) {
		cin >> len;
		if ((len > 0) && (cin.good())) return len;
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cout << "Please, input correct length of pipe: ";
	};
}


float pipe_diam_input() {
	float diam = 0;
	cout << "Input the diameter of Pipe: ";
	while (true) {
		cin >> diam;
		if ((diam > 0) && cin.good()) return diam;
		cout << "Please, input correct diameter of pipe: ";
		cin.clear();
		cin.ignore(INT_MAX, '\n');
	};
}


bool pipe_in_rep_input() {
	int in_repearing = false;
	cout << "1.Pipe is in repearing 2.Pipe is working" << endl;
	while (true) {
		cin >> in_repearing;

		if ((in_repearing == 1) && cin.good()) return true;

		else if ((in_repearing == 2) && (cin.good())) return false;

		else cout << "Input the correct number";

		cin.clear();
		cin.ignore(INT_MAX, '\n');
	};
}


string cs_name_input() {
	string name = "";
	cout << "Input the Name of CS: ";
	cin.ignore();
	getline(cin, name);
	return name;
};


int cs_num_worksh_input() {
	int num_workshops = 0;
	cout << "Input number of workshops: ";
	while (true) {
		cin >> num_workshops;
		if ((num_workshops > 0) && cin.good()) return num_workshops;
		cout << "Please, input correct num of workshops: ";
		cin.clear();
		cin.ignore(INT_MAX, '\n');
	};
}


int cs_num_run_worksh_input(int num_workshops) {
	int num_run_workshops = 0;
	cout << "Input number of running workshops: ";
	while (true) {
		cin >> num_run_workshops;
		if ((num_run_workshops > 0) && (num_run_workshops <= num_workshops) && cin.good()) return num_run_workshops;
		cout << "Please, input correct num of running workshops: ";
		cin.clear();
		cin.ignore(INT_MAX, '\n');
	};
}


float cs_efficiency_input() {
	float efficiency = 0;
	cout << "Input the efficiency of CS: ";
	while (true) {
		cin >> efficiency;
		if (cin.good()) return efficiency;
		else {
			cout << "Please, input the correct efficiency: ";
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}
	}
};


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
	};

	if (Pp.exist == true) {
		cout << "Pipe" << endl;
		cout << "Length of pipe: " << Pp.len << endl;
		cout << "Diameter of pipe: " << Pp.diameter << endl;
		string in_rep = Pp.in_repairing ? "Pipe is working" : "Pipe in repearing";
		cout << in_rep << endl << endl;
	}
	else {
		cout << "There is no pipe" << endl;
	};
};


int main()
{
	Pipe Pp;
	Compr_station Cs;

	while (true) {
		system("cls");
		cout << "1.Add a pipe 2.Add a CS 3.View all objects 4.Edit pipe 5.Edit CS 6.save 7.Load 0.Exit" << endl;
		int choice = menu_choice();

		if (choice == 0) {
			system("cls");
			cout << "Goodbye";
			break;
		}

		if (choice == 1) {
			system("cls");
			Pp.len = pipe_len_input();
			Pp.diameter = pipe_diam_input();
			Pp.in_repairing = pipe_in_rep_input();
			Pp.exist = true;
		}

		if (choice == 2) {
			system("cls");
			Cs.name = cs_name_input();
			Cs.num_workshops = cs_num_worksh_input();
			Cs.num_run_workshops = cs_num_run_worksh_input(Cs.num_workshops);
			Cs.efficiency = cs_efficiency_input();
			Cs.exist = true;
		}

		if (choice == 3) {
			view_obj(Pp, Cs);
			system("pause");
		}

		if (choice == 4) {
			if (Pp.exist == false) {
				cout << "There is no pipe to edit";
				system("pause");
			}
			else {
				system("cls");
				Pp.len = pipe_len_input();
				Pp.diameter = pipe_diam_input();
				Pp.in_repairing = pipe_in_rep_input();
			}
		}

		if (choice == 5) {
			if (Cs.exist == false) {
				cout << "There is no CS now";
				system("pause");
			}
			else {
				system("cls");
				Cs.name = cs_name_input();
				Cs.num_workshops = cs_num_worksh_input();
				Cs.num_run_workshops = cs_num_run_worksh_input(Cs.num_workshops);
				Cs.efficiency = cs_efficiency_input();
			}
		}


	}

	return 0;
}
