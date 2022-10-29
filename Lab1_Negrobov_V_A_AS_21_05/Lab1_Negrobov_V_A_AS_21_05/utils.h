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


template <typename T>
void show(std::unordered_map<int, T>& object) {
	if (object.size() != 0) {
		for (const auto& obj : object) {
			std::cout << "Object id: " << obj.first << std::endl;
			std::cout << obj.second;
		}
	}
}


template <typename T>
void show(std::unordered_set<int>& idx, std::unordered_map<int, T>& objects) {
	if (idx.size() != 0) {
		for (int i : idx) {
			std::cout << "Object id: " << i << std::endl;
			std::cout << objects[i];
		}
	}
}


template <typename T>
void filter_by_name(const std::string& name, std::unordered_map<int, T>& objects, std::unordered_set<int>& idx) {
	for (auto& obj : objects) {
		if (obj.second.get_name().find(name) != std::string::npos) {
			idx.insert(obj.first);
		}
	}
}


template <typename T>
void del_objects(std::unordered_set<int>& idx, std::unordered_map<int, T>& objects) {
	for (int i : idx) {
		objects.erase(i);
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

std::unordered_set<int> get_new_idx(std::unordered_set<int> idx);

void filter_by_rep(const bool in_rep, std::unordered_map<int, Pipe>& pipes, std::unordered_set<int>& idx);

void change_in_rep(std::unordered_set<int>& idx, std::unordered_map<int, Pipe>& pipes);

void choose();

void del_or_edit();

void filter_unused_per(int percent, const bool more, std::unordered_map<int, Compr_station>& compr_stataions, std::unordered_set<int>& idx);

void change_eff(double eff, std::unordered_set<int>& idx, std::unordered_map<int, Compr_station>& compr_stataions);

void filter_compr_stations(std::unordered_map<int, Compr_station>& compr_stations);

void filter_pipes(std::unordered_map<int, Pipe>& pipes);

void do_command(int choice, std::unordered_map<int, Pipe>& pipes, std::unordered_map<int, Compr_station>& compr_stations);