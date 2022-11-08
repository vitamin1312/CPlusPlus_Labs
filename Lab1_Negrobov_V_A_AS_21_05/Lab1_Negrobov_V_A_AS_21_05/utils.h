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
		if (std::cin >> val && (std::cin.peek() == EOF || std::cin.peek() == '\n') && (val >= least) && (val < great)) return val;
		else {
			std::cin.clear();
			std::cin.ignore(10000, '\n');
			std::cout << "Please, input correct value: ";
		}
	}
}


template <typename T>
bool show(std::unordered_map<int, T>& object) {
	if (object.size() != 0) {
		for (const auto& obj : object) {
			std::cout << "Object id: " << obj.first << std::endl;
			std::cout << obj.second;

		}
		return true;
	}
	else {
		std::cout << "There are no objects" << std::endl;
		return false;
	}
}


template <typename T>
bool show(std::unordered_set<int>& ids, std::unordered_map<int, T>& objects) {
	if (ids.size() != 0) {
		for (int i : ids) {
			std::cout << "Object id: " << i << std::endl;
			std::cout << objects[i];
		}
		return true;
	}
	else {
		std::cout << "There are no such objets" << std::endl;
		return false;
	}
}


template <typename T>
using pipe_filter = bool (*)(const Pipe& Cs, T params);


template <typename T>
std::unordered_set<int> find_pipes_ids(std::unordered_map<int, Pipe>& pipes, pipe_filter<T> filter, T params) {
	std::unordered_set<int> ids;

	for (const auto& Pp : pipes) {
		if (filter(Pp.second, params)) {
			ids.insert(Pp.first);
		}
	}
	return ids;
}


template <typename T>
using compr_st_filter = bool (*)(const Compr_station& Cs, T params);


template <typename T>
std::unordered_set<int> find_compr_st_ids(std::unordered_map<int, Compr_station>& comp_stations, compr_st_filter<T> filter, T params) {
	std::unordered_set<int> ids;

	for (const auto& Cs : comp_stations) {
		if (filter(Cs.second, params)) {
			ids.insert(Cs.first);
		}
	}
	return ids;
}


template <typename T>
void del_objects(std::unordered_set<int>& ids, std::unordered_map<int, T>& objects) {
	for (int i : ids) {
		objects.erase(i);
	}
}


bool pipe_in_rep_input();

bool save_data(std::string f_name, const std::unordered_map<int, Pipe>& pipes, const std::unordered_map<int, Compr_station>& compr_stations);

bool read_data(std::string f_name, std::unordered_map<int, Pipe>& pipes, std::unordered_map<int, Compr_station>& compr_stations);

bool del_pipe(int id, std::unordered_map<int, Pipe>& pipes);

bool del_compr_station(int id, std::unordered_map<int, Compr_station>& compr_stations);

bool edit_pipe(int id, std::unordered_map<int, Pipe>& pipes);

bool edit_compr_station(int id, std::unordered_map<int, Compr_station>& compr_stations);

std::unordered_set<int> get_new_ids(std::unordered_set<int> ids);

int choose();

int del_or_edit();

void change_run_ws(int num, std::unordered_set<int>& ids, std::unordered_map<int, Compr_station>& compr_stataions);

void filter_pipes(std::unordered_map<int, Pipe>& pipes);

void filter_compr_stations(std::unordered_map<int, Compr_station>& compr_stations);

bool check_pipe_name(const Pipe& Pp, std::string name);

bool check_pipe_in_rep(const Pipe& Pp, bool in_rep);

bool check_compr_st_name(const Compr_station& Cs, std::string name);

bool check_unused_per_m(const Compr_station& Cs, double percent);

bool check_unused_per_l(const Compr_station& Cs, double percent);

bool check_unused_per_e(const Compr_station& Cs, double percent);
