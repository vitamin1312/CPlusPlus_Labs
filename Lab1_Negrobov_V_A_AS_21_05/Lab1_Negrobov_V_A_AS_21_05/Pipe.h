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
	static int max_id;

public:
	void edit();
	void set_in_rep(bool in_rep);
	int get_max_id() const;
	bool get_in_rep() const;
	std::string get_name() const;


	friend std::istream& operator >> (std::istream& in, Pipe& Pp);
	friend std::ostream& operator << (std::ostream& out, const Pipe& Pp);
	friend std::ifstream& operator >> (std::ifstream& fin, Pipe& Pp);
	friend std::ofstream& operator << (std::ofstream& fout, const Pipe& Pp);

};
