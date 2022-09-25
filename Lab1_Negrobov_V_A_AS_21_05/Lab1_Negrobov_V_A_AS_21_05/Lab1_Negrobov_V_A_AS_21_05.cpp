#include <iostream>
#include <string>
#include <limits>
#include <fstream>

using namespace std;


struct Pipe {
	float len = 0;
	float diameter = 0;
	bool in_repairing = 0;
};


struct Compr_station {
	string name = " ";
	int num_workshops = 0;
	int num_run_workshops = 0;
	float efficiency = 0;
};


float get_float_value(float least=0, float great= std::numeric_limits<float>::max()) {
	float val = 0;
	while (true) {
		cin >> val;
		if (cin.good() && (val > least) &&  (val < great)) 
			return val;
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "Please, input correct value: ";
	}
}

int get_int_value(float least = 0, float great = std::numeric_limits<int>::max()) {
	int val = 0;
	while (true) {
		if (cin.good() && (cin >> val) && (val >= least) && (val < great)) {
			return val;
		}
		else {
			cin.clear();
			cin.ignore(10000, '\n');
			cout << "Please, input correct value: ";
		}
	}
}


bool pipe_in_rep_input() {
	int in_repearing = 1;
	cout << "1.Pipe is in repearing 2.Pipe is working" << endl;

	while (true) {
		cin >> in_repearing;

		if ((in_repearing == 1) && cin.good()) return true;

		else if ((in_repearing == 2) && (cin.good())) return false;

		else cout << "Input the correct number: ";

		cin.clear();
		cin.ignore(10000, '\n');
	}
}


void file_write(const Pipe& Pp, const Compr_station& Cs) {
	ofstream file("data.txt");
	file << Pp.len << endl << Pp.diameter << endl << Pp.in_repairing << endl 
		 << Cs.name << endl << Cs.num_workshops << endl << Cs.num_run_workshops << endl << Cs.efficiency << endl;
	file.close();
	cout << "Data was saved" << endl;
}


void file_read(Pipe& Pp, Compr_station& Cs) {
	{
			ifstream file_handler("data.txt");
			string name;

			if (file_handler.is_open()) {

				file_handler >> Pp.len >> Pp.diameter >> Pp.in_repairing;

				file_handler.ignore();
				if (getline(file_handler, name, '\n')) Cs.name = name;
				file_handler >> Cs.num_workshops >> Cs.num_run_workshops >> Cs.efficiency;
				cout << "Data was load" << endl;
			}
			else cout << "There is no data file" << endl;
		}
}

istream& operator >> (istream& in, Pipe& Pp) {
	cout << "Input the length of Pipe: ";
	Pp.len = get_float_value();
	cout << "Input the diameter of Pipe: ";
	Pp.diameter = get_float_value();
	Pp.in_repairing = pipe_in_rep_input();
	return in;
}


istream& operator >> (istream& in, Compr_station& Cs) {
	cout << "Input the Name of CS: ";
	cin.ignore(10000, '\n');
	getline(cin, Cs.name);
	cout << "Input number of workshops: ";
	Cs.num_workshops = get_int_value(1);
	cout << "Input number of running workshops: ";
	Cs.num_run_workshops = get_int_value(1, Cs.num_workshops + 1);
	cout << "Input the efficiency of CS: ";
	Cs.efficiency = get_float_value(-std::numeric_limits<float>::max());
	return in;
}

ostream& operator << (ostream& out, Compr_station& Cs) {
	if (!(Cs.num_workshops == 0)) {
		cout << "Compressor station" << endl;
		cout << "The name of compressor station: " << Cs.name << endl;
		cout << "Number of workshops on conpressor station: " << Cs.num_workshops << endl;
		cout << "Number of running workshops on conpressor station: " << Cs.num_run_workshops << endl;
		cout << "Efficiency compressor station: " << Cs.efficiency << endl << endl;
	}
	else {
		cout << "There is no compressor station" << endl;
	}
	return out;
}


ostream& operator << (ostream& out, Pipe& Pp) {
	if (!(Pp.len == 0)) {
		cout << "Pipe" << endl;
		cout << "Length of pipe: " << Pp.len << endl;
		cout << "Diameter of pipe: " << Pp.diameter << endl;
		string in_rep = Pp.in_repairing ? "Pipe in repearing" : "Pipe is working";
		cout << in_rep << endl << endl;
	}
	else {
		cout << "There is no pipe" << endl;
	}
	return out;
}


int main()
{
	Pipe Pp;
	Compr_station Cs;

	while (true) {
		cout << "1.Add a pipe 2.Add a CS 3.View all objects 4.Edit pipe 5.Edit CS 6.save 7.Load 0.Exit" << endl;
		int choice = get_int_value(0, 8);

		if (choice == 0) {
			cout << "Goodbye";
			break;
		}

		if (choice == 1) cin >> Pp;

		if (choice == 2) cin >> Cs;

		if (choice == 3) cout << Pp << Cs;

		if (choice == 4) {
			if (Pp.len == 0) cout << "There is no pipe to edit" << endl;
			else Pp.in_repairing = pipe_in_rep_input();
			}

		if (choice == 5) {
			if (Cs.num_workshops == 0) {
				cout << "There is no CS now" << endl;
			}
			else {
				cout << "Input the Name of CS: ";
				cin.ignore(10000, '\n');
				getline(cin, Cs.name);
				cout << "Input number of running workshops: ";
				Cs.num_run_workshops = get_int_value(0, Cs.num_workshops + 1);
				cout << "Input the efficiency of CS: ";
				Cs.efficiency = get_float_value(-std::numeric_limits<float>::max());
			}
		}

		if (choice == 6) file_write(Pp, Cs);
		if (choice == 7) file_read(Pp, Cs);
	}
	return 0;
}
