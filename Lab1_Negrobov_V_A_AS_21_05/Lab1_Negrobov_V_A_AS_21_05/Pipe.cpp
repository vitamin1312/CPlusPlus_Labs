#include "Pipe.h"
#include "utils.h"


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
	std::cout << "Input the length of Pipe: ";
	Pp.len = get_float_value();
	std::cout << "Input the diameter of Pipe: ";
	Pp.diameter = get_float_value();
	Pp.in_repairing = pipe_in_rep_input();
	return in;
}



std::ostream& operator << (std::ostream& out, const Pipe& Pp) {
	if (!(Pp.len == 0)) {
		std::cout << "Pipe" << std::endl;
		std::cout << "Length of pipe: " << Pp.len << std::endl;
		std::cout << "Diameter of pipe: " << Pp.diameter << std::endl;
		std::string in_rep = Pp.in_repairing ? "Pipe in repearing" : "Pipe is working";
		std::cout << in_rep << std::endl << std::endl;
	}
	else {
		std::cout << "There is no pipe" << std::endl;
	}
	return out;
}
