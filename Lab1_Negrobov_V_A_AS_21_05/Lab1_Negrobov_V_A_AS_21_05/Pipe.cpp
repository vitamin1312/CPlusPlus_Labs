#include "Pipe.h"
#include "utils.h"


int Pipe::id = 0;


Pipe::Pipe() {
	std::cout << "Pipe was created" << std::endl;
}

int Pipe::get_id() {
	return this->id;
}


void Pipe::up_id() {
	this->id++;
}


std::string Pipe::get_name() {
	return this->name;
}


bool Pipe::get_in_rep() {
	return this->in_repairing;
}


void Pipe::change_in_rep() {
	if (this->in_repairing == true) this->in_repairing = false;
	else this->in_repairing = true;
}


void Pipe::edit() {
	if (this->len == 0) std::cout << "There is no pipe to edit" << std::endl;
	else this->in_repairing = pipe_in_rep_input();
}


void Pipe::to_file() {
	std::ofstream file("data.txt");
	file << this->id << ' ' << this->len << ' ' << this->diameter << ' ' << this->in_repairing << std::endl;
	file.close();
	std::cout << "Pipe was saved" << std::endl;
}

void Pipe::read_file() {
	std::ifstream file_handler("data.txt");

	if (file_handler.is_open()) {

		file_handler >> this->id >> this->len >> this->diameter >> this->in_repairing;

		std::cout << "Data was load" << std::endl;
	}
	else std::cout << "There is no data file" << std::endl;
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

	std::cout << "The name of Pipe" << Pp.name << std::endl;
	std::cout << "Length of pipe: " << Pp.len << std::endl;
	std::cout << "Diameter of pipe: " << Pp.diameter << std::endl;
	std::string in_rep = Pp.in_repairing ? "Pipe in repearing" : "Pipe is working";
	std::cout << in_rep << std::endl << std::endl;
	return out;
}



std::ifstream& operator >> (std::ifstream& fin, Pipe& Pp) {
	std::string name;
	fin >> Pp.id;
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

