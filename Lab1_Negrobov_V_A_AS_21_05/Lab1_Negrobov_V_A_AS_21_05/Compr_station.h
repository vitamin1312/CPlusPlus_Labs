#pragma once
#include <iostream>
#include <string>
#include <fstream>


class Compr_station
{
private:
	std::string name;
	int num_workshops;
	int num_run_workshops;
	double efficiency;

public:
	static int id;
	Compr_station();
	void edit();
	int unused_per();
	int get_id();
	void up_id();
	std::string get_name();
	void set_eff(double);

	friend std::istream& operator >> (std::istream& in, Compr_station& Cs);
	friend std::ostream& operator << (std::ostream& out, const Compr_station& Cs);
	friend std::ifstream& operator >> (std::ifstream& fin, Compr_station& Cs);
	friend std::ofstream& operator << (std::ofstream& fout, const Compr_station& Cs);

};

