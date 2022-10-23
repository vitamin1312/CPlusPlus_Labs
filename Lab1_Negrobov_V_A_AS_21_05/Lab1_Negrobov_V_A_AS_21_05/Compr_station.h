#pragma once
#include <iostream>
#include <string>
#include <fstream>


class Compr_station
{
private:
	std::string name = "";
	int num_workshops = 0;
	int num_run_workshops = 0;
	float efficiency = 0;

public:
	int id = 0;

	void edit();
	void to_file();
	void read_file();

	friend std::istream& operator >> (std::istream& in, Compr_station& Cs);
	friend std::ostream& operator << (std::ostream& out, const Compr_station& Cs);

};


std::istream& operator >> (std::istream& in, Compr_station& Cs);
std::ostream& operator << (std::ostream& out, const Compr_station& Cs);
