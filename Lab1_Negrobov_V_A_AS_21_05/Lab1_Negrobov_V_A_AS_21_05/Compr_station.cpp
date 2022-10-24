#include "Compr_station.h"
#include "utils.h"


Compr_station::Compr_station(int id) {
	this->id = id;
	std::cout << "Compr_station was created" << std::endl;
}


void Compr_station::edit(){
	if (this->num_workshops == 0) {
		std::cout << "There is no CS now" << std::endl;
	}
	else {
		std::cout << "Input number of running workshops: ";
		this->num_run_workshops = get_int_value(0, this->num_workshops + 1);

	}
}


void Compr_station::to_file() {
	std::ofstream file("data.txt");
	file << this->id << ' ' << this->name << ' ' << this->num_workshops << ' ' << this->num_run_workshops << ' ' << this->efficiency << std::endl;
	file.close();
	std::cout << "CS was saved" << std::endl;
}

void Compr_station::read_file() {
	std::ifstream file_handler("data.txt");
	std::string name;

	if (file_handler.is_open()) {
		file_handler.ignore();
		if (getline(file_handler, name, '\n')) this->name = name;
		file_handler >> this->id >> this->num_workshops >> this->num_run_workshops >> this->efficiency;
		std::cout << "Data was load" << std::endl;
	}
	else std::cout << "There is no data file" << std::endl;
}


std::istream& operator >> (std::istream& in, Compr_station& Cs) {
	std::cout << "Input the Name of CS: ";
	std::cin.ignore(10000, '\n');
	std::getline(std::cin, Cs.name);
	std::cout << "Input number of workshops: ";
	Cs.num_workshops = get_int_value(1);
	std::cout << "Input number of running workshops: ";
	Cs.num_run_workshops = get_int_value(1, Cs.num_workshops + 1);
	std::cout << "Input the efficiency of CS: ";
	Cs.efficiency = get_float_value(-std::numeric_limits<float>::max());
	return in;
}


std::ostream& operator << (std::ostream& out, const Compr_station& Cs) {
	if (!(Cs.num_workshops == 0)) {
		std::cout << "Compressor station" << std::endl;
		std::cout << "The name of compressor station: " << Cs.name << std::endl;
		std::cout << "Number of workshops on conpressor station: " << Cs.num_workshops << std::endl;
		std::cout << "Number of running workshops on conpressor station: " << Cs.num_run_workshops << std::endl;
		std::cout << "Efficiency compressor station: " << Cs.efficiency << std::endl << std::endl;
	}
	else {
		std::cout << "There is no compressor station" << std::endl;
	}
	return out;
}

