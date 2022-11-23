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
	static int max_id;
	int pipes_number=0;

public:
	void edit();
	double unused_per() const;
	int get_num_workshops();
	void change_num_run_workstation(int num);
	int get_max_id() const;
	int get_id() const;
	std::string get_name() const;
	int get_pipes_number();
	void up_pipes_number();


	friend std::istream& operator >> (std::istream& in, Compr_station& Cs);
	friend std::ostream& operator << (std::ostream& out, const Compr_station& Cs);
	friend std::ifstream& operator >> (std::ifstream& fin, Compr_station& Cs);
	friend std::ofstream& operator << (std::ofstream& fout, const Compr_station& Cs);

};

