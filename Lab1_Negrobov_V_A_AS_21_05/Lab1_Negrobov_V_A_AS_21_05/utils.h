#pragma once
#include <limits>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <fstream>
#include "Pipe.h"
#include "Compr_station.h"
#include <iostream>

template <typename T>
T get_num_value(T least, T great) {
	T val = 0;
	while (true) {
		if (std::cin.good() && (std::cin >> val) && (val >= least) && (val < great)) return val;
		else {
			std::cin.clear();
			std::cin.ignore(10000, '\n');
			std::cout << "Please, input correct value: ";
		}
	}
}

bool pipe_in_rep_input();

void print_menu();

void save_data(std::string f_name, const std::unordered_map<int, Pipe>& pipes, const std::unordered_map<int, Compr_station>& compr_stations);

void read_data(std::string f_name, std::unordered_map<int, Pipe>& pipes, std::unordered_map<int, Compr_station>& compr_stations);

void del_pipe(std::unordered_map<int, Pipe>& pipes);

void del_compr_station(std::unordered_map<int, Compr_station>& compr_stations);

void edit_pipe(std::unordered_map<int, Pipe>& pipes);

void edit_compr_station(std::unordered_map<int, Compr_station>& compr_stations);

void show_pipes(std::unordered_map<int, Pipe>& pipes);


void show_pipes(std::unordered_set<int>& idx, std::unordered_map<int, Pipe>& pipes);

void show_compr_stations(const std::unordered_map<int, Compr_station>& compr_stations);

void show_compr_stations(std::unordered_set<int>& idx, std::unordered_map<int, Compr_station>& compr_stations);
