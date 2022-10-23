#pragma once
#include <iostream>
#include <fstream>


class Pipe
{
private:
	float len = 0;
	float diameter = 0;
	bool in_repairing = false;

public:
	int id = 0;

	void to_file();
	void read_file();
	void edit();


	friend std::istream& operator >> (std::istream& in, Pipe& Pp);
	friend std::ostream& operator << (std::ostream& out, const Pipe& Pp);
};

