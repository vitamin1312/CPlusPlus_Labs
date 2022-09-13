#include <iostream>

using namespace std;


int menu_choice() {
	int choice = 0;
	while (true) {
		cin >> choice;
		if ((choice >= 0) && (choice <= 7)) return choice;
		cout << "Please, enter the correct number" << endl;
	};
}


float pipe_len_input() {
	float len = 0;
	while (true) {
		cout << "Input the length of Pipe: ";
		cin >> len;
		if (len > 0) return len;
		cout << "Please, input correct length of pipe: ";
	};
}


float pipe_diam_input() {
	float diam = 0;
	while (true) {
		cout << "Input the diameter of Pipe: ";
		cin >> diam;
		if (diam > 0) return diam;;
		cout << "Please, input correct diameter of pipe: ";
	};
}


bool pipe_in_rep_input() {
	int in_repearing = false;
	while (true) {
		cout << "1.Pipe is in repearing 2.Pipe is working" << endl;
		cin >> in_repearing;

		if (in_repearing == 1) return true;

		else if (in_repearing == 2) return false;

		else cout << "Input the correct number";
	};
}


string cs_name_input() {
	string name = "";
	cout << "Input the Name of CS: ";
	cin >> name;
	return name;
};


int cs_num_worksh_input() {
	int num_workshops = 0;
	while (true) {
		cout << "Input number of workshops: ";
		cin >> num_workshops;
		if (num_workshops > 0) return num_workshops;
		cout << "Please, input correct num of workshops: ";
	};
}


int cs_num_run_worksh_input(int num_workshops) {
	int num_run_workshops = 0;
	while (true) {
		cout << "Input number of running workshops: ";
		cin >> num_run_workshops;
		if ((num_run_workshops > 0) && (num_run_workshops <= num_workshops)) return num_run_workshops;
		cout << "Please, input correct num of running workshops: ";
	};
}


float cs_efficiency_input() {
	float efficiency = 0;
	cout << "Input the efficiency of CS";
	cin >> efficiency;
	return efficiency;
};


struct Pipe {
	float len;
	float diameter;
	bool in_repairing;
};


struct Compr_station {
	string name;
	int num_workshops;
	int num_run_workshops;
	float efficiency;
};


int main()
{
	Pipe Pp = {0, 0, 0};
	Compr_station Cs = {"0", 0, 0, 0};

	while (true) {
		cout << "1.Add a pipe 2.Add a CS 3.View all objects 4.Edit pipe 5.Edit CS 6.save 7.Load 0.Exit" << endl;
		int choice = menu_choice();

		if (choice == 0) break;

		if (choice == 1) {
			Pp.len = pipe_len_input();
			Pp.diameter = pipe_diam_input();
			Pp.in_repairing = pipe_in_rep_input();
		};

		if (choice == 2) {
			Cs.name = cs_name_input();
			Cs.num_workshops = cs_num_worksh_input();
			Cs.num_run_workshops = cs_num_run_worksh_input(Cs.num_workshops);
			Cs.efficiency = cs_efficiency_input();
		};

	};

	cout << Pp.len << Pp.diameter << Pp.in_repairing << endl;
	cout << Cs.name << Cs.num_workshops << Cs.num_run_workshops;
	return 0;
}
