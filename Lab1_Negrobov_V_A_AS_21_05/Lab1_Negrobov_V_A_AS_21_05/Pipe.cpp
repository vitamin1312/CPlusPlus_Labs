#include "Pipe.h"
#include "utils.h"


int Pipe::max_id = 0;

int Pipe::get_id() const { return max_id; }

std::string Pipe::get_name() const { return name; }

bool Pipe::get_in_rep() const { return in_repairing; }

double Pipe::get_diam() const { return diameter; }



void Pipe::set_in_rep(bool in_rep) {
	this->in_repairing = in_rep;
}


void Pipe::edit(){
	this->in_repairing = pipe_in_rep_input();
}


int Pipe::get_max_id() const {
	max_id++;
	return max_id;
}


std::istream& operator >> (std::istream& in, Pipe& Pp) {
	std::cout << "Input the Name of Pipe: ";
	std::cin.ignore(10000, '\n');
	std::getline(std::cin, Pp.name);
	std::cout << "Input the length of Pipe: ";
	Pp.len = get_num_value(0.0, std::numeric_limits<double>::max());
	std::cout << "Input the diameter of Pipe: ";
	Pp.diameter = get_num_value(0.0, std::numeric_limits<double>::max());
	Pp.in_repairing = pipe_in_rep_input();
	return in;
}



std::ostream& operator << (std::ostream& out, const Pipe& Pp) {

	std::cout << "----------------------------------------------------------------" << std::endl;
	std::cout << "Pipe" << std::endl;
	std::cout << "The name of Pipe: " << Pp.name << std::endl;
	std::cout << "Length of pipe: " << Pp.len << std::endl;
	std::cout << "Diameter of pipe: " << Pp.diameter << std::endl;
	std::string in_rep = Pp.in_repairing ? "Pipe in repearing" : "Pipe is working";
	std::cout << in_rep << std::endl;
	std::cout << "----------------------------------------------------------------" << std::endl << std::endl;
	return out;
}



std::ifstream& operator >> (std::ifstream& fin, Pipe& Pp) {
	std::string name;
	fin >> Pp.max_id;
	fin.ignore();
	if (std::getline(fin, name, '\n')) Pp.name = name;
	fin >> Pp.len >> Pp.diameter >> Pp.in_repairing;
	return fin;
}


std::ofstream& operator << (std::ofstream& fout, const Pipe& Pp) {
	fout << Pp.name << std::endl
		<< Pp.len << ' '
		<< Pp.diameter << ' '
		<< Pp.in_repairing << std::endl;
	return fout;
}

