#pragma once
#include <iostream>
#include <fstream>
#include <string>


class Pipe
{
private:
	std::string name;
	double len;
	double diameter;
	bool in_repairing;
	static int id;

public:
	Pipe();
	void to_file();
	void read_file();
	void edit();
	int get_id();
	void up_id();


	friend std::istream& operator >> (std::istream& in, Pipe& Pp);
	friend std::ostream& operator << (std::ostream& out, const Pipe& Pp);
	friend std::ifstream& operator >> (std::ifstream& fin, Pipe& Pp);
	friend std::ofstream& operator << (std::ofstream& fout, const Pipe& Pp);

};
