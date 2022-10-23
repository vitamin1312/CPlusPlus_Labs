#include <iostream>

using namespace std;

float get_float_value(float least = 0, float great = std::numeric_limits<float>::max()) {
	float val = 0;
	while (true) {
		cin >> val;
		if (cin.good() && (val > least) && (val < great)) return val;
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "Please, input correct value: ";
	}
}


int get_int_value(int least = 0, int great = std::numeric_limits<int>::max()) {
	int val = 0;
	while (true) {
		if (cin.good() && (cin >> val) && (val >= least) && (val < great)) return val;
		else {
			cin.clear();
			cin.ignore(10000, '\n');
			cout << "Please, input correct value: ";
		}
	}
}


bool pipe_in_rep_input() {
	cout << "1.Pipe is in repearing 2.Pipe is working" << endl;
	return get_int_value(1, 3) == 1;
}