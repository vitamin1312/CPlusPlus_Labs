#include "Compr_station.h"
#include "utils.h"


int Compr_station::id = 0;


Compr_station::Compr_station() {
	std::cout << "Compr_station was created" << std::endl;
}


void Compr_station::edit(){
	if (this->num_workshops == 0) {
		std::cout << "There is no CS now" << std::endl;
	}
	else {
		std::cout << "Input number of running workshops: ";
		this->num_run_workshops = get_num_value(0, this->num_workshops + 1);

	}
}

int Compr_station::unused_per() {
    int result = 1 - this->num_workshops / this->num_run_workshops * 100;
	return result;
}


int Compr_station::get_id() {
	return this->id;
}

void Compr_station::up_id() {
	this->id++;
}

std::istream& operator >> (std::istream& in, Compr_station& Cs) {
	std::cout << "Input the Name of CS: ";
	std::cin.ignore(10000, '\n');
	std::getline(std::cin, Cs.name);
	std::cout << "Input number of workshops: ";
	Cs.num_workshops = get_num_value(0, std::numeric_limits<int>::max());
	std::cout << "Input number of running workshops: ";
	Cs.num_run_workshops = get_num_value(0, Cs.num_workshops + 1);
	std::cout << "Input the efficiency of CS: ";
	Cs.efficiency = get_num_value(-std::numeric_limits<double>::max(), std::numeric_limits<double>::max());
	return in;
}


std::ostream& operator << (std::ostream& out, const Compr_station& Cs) {
	std::cout << "The name of compressor station: " << Cs.name << std::endl;
	std::cout << "Number of workshops on conpressor station: " << Cs.num_workshops << std::endl;
	std::cout << "Number of running workshops on conpressor station: " << Cs.num_run_workshops << std::endl;
	std::cout << "Efficiency compressor station: " << Cs.efficiency << std::endl << std::endl;

	return out;
}


std::ifstream& operator >> (std::ifstream& fin, Compr_station& Cs) {
	std::string name;
	fin >> Cs.id;
	fin.ignore();
	if (std::getline(fin, name, '\n')) Cs.name = name;
	fin >> Cs.num_workshops >> Cs.num_run_workshops >> Cs.efficiency;
	return fin;
}

std::ofstream& operator << (std::ofstream& fout, const Compr_station& Cs) {
	fout << Cs.name << std::endl
		<< Cs.num_workshops << ' '
		<< Cs.num_run_workshops << ' '
		<< Cs.efficiency << std::endl;
	return fout;
}
