#include "Network.h"
#include "utils.h"


int Network::get_pipes_size() { return pipes.size(); }

int Network::get_compr_stations_size() { return compr_stations.size(); }

bool Network::show_pipes() { return show(pipes); }

bool Network::show_compr_stations() { return show(compr_stations); }



void Network::del_edge(int id) {

	if (edges.find(id) != edges.end()) {
		current_edge = edges[id];
		compr_stations[current_edge.start_cs].down_pipes_number();
		compr_stations[current_edge.end_cs].down_pipes_number();
		edges.erase(id);
	}		
}


void Network::del_pipes(const std::unordered_set<int>& ids) {
	for (int i : ids) {
		pipes.erase(i);
		del_edge(i);
	}
}


void Network::del_compr_stations(const std::unordered_set<int>& ids) {
	for (int i : ids) {
		if (not_node(i))
			compr_stations.erase(i);
	}
}


bool Network::not_node(int id) {
	for (auto edge : edges) {
		if (id == edge.second.start_cs or id == edge.second.end_cs)
			return false;
	}
	return true;
}


bool Network::not_edge(int id) {
	for (auto edge : edges) {
		if (id == edge.second.pipe)
			return false;
	}
	return true;
}


bool Network::is_free_nodes() {
	
	int free_number = 0;

	for (auto& Cs : compr_stations) {
		if (Cs.second.get_num_workshops() > Cs.second.get_pipes_number())
			free_number++;
	}

	if (free_number >= 2)
		return true;

	else
		return false;
}


bool Network::edit_pipe(int id) {

	if (pipes.find(id) != pipes.end()) {
		pipes[id].edit();
		return true;
	}
	else {
		return false;
	}
}


bool Network::edit_compr_station(int id) {

	if (compr_stations.find(id) != compr_stations.end()) {
		compr_stations[id].edit();
		return true;
	}
	return false;
}


int Network::input_cs_id(int forbidden_id) {
	while (true) {
		int object_id = get_num_value(1, std::numeric_limits<int>::max());
		if ((this->compr_stations.find(object_id) != this->compr_stations.end())
			and (object_id != forbidden_id)
			and (compr_stations.at(object_id).get_num_workshops() > compr_stations.at(object_id).get_pipes_number())) {

			return object_id;
		}
		else
			std::cout << "Please, input correct object id: ";
	}
}


void Network::add_new_pipe() {
	std::cin >> current_pipe;
	pipes[current_pipe.get_max_id()] = current_pipe;
}


void Network::add_new_cs() {
	std::cin >> current_cs;
	compr_stations[current_cs.get_max_id()] = this->current_cs;
}


void Network::add_new_edge() {

	if (is_free_nodes()) {
		std::cout << "Input id of start cs: ";
		current_edge.start_cs = input_cs_id(-1);

		std::cout << "Input id of end cs: ";
		current_edge.end_cs = input_cs_id(current_edge.start_cs);

		std::cout << "Input diameter of Pipe for connecting: ";
		double diam = get_num_value(0.0, std::numeric_limits<double>::max());

		bool exist = false;

		for (auto pipe : pipes) {
			if (pipe.second.get_diam() == diam and not_edge(pipe.first)) {
				current_edge.pipe = pipe.first;
				exist = true;
				break;
			}
		}

		if (!exist) {
			std::cout << "There is no pipe with that diameter, please create new" << std::endl;
			add_new_pipe();
			current_edge.pipe = current_pipe.get_id();
		}

		compr_stations[current_edge.start_cs].up_pipes_number();
		compr_stations[current_edge.end_cs].up_pipes_number();

		edges[current_edge.pipe] = current_edge;
	}
	else
		std::cout << "You have not free Cs" << std::endl;
}


bool Network::to_file(std::string f_name) {

	std::ofstream file;
	file.open(f_name + ".txt");

	if (file.is_open()) {

		file << pipes.size() << ' ' << compr_stations.size() << ' ' << edges.size() << std::endl;

		for (const auto& Pp : pipes) {
			file << Pp.first << std::endl;
			file << Pp.second;

		}

		for (const auto& Cs : compr_stations) {
			file << Cs.first << std::endl;
			file << Cs.second;
		}

		for (const auto& Ed : edges) {
			file << Ed.second;
		}

		file.close();
		return true;
	}
	return false;
}


bool Network::from_file(std::string f_name) {

	std::ifstream file_handler;
	file_handler.open(f_name + ".txt");
	std::string name;

	if (file_handler.is_open()) {

		pipes.clear();
		compr_stations.clear();
		edges.clear();

		int num_Pp, num_Cs, num_Ed;
		file_handler >> num_Pp >> num_Cs >> num_Ed;

		for (int i(0); i < num_Pp; ++i) {
			file_handler >> current_pipe;
			pipes[current_pipe.get_id()] = current_pipe;
		}

		for (int i(0); i < num_Cs; ++i) {
			file_handler >> current_cs;
			compr_stations[current_cs.get_id()] = current_cs;
		}

		for (int i(0); i < num_Ed; ++i) {
			edge_ids edge;
			file_handler >> edge;
			edges[edge.pipe] = edge;
		}

		file_handler.close();
		return true;
	}
	else
		return false;
}


void Network::get_max_flow() {
	std::unordered_map<int, int> id_idx;
	std::unordered_map<int, int> idx_id;
	std::unordered_set<int> spt_compr_stations;

	std::vector<std::vector<double>> graph(compr_stations.size(), std::vector<double>(compr_stations.size(), 0.0));

	int idx = 0;

	for (auto& [Pp_id, edge] : edges) {
		if (!spt_compr_stations.contains(edge.start_cs)) {
			id_idx[edge.start_cs] = idx;
			idx_id[idx] = edge.start_cs;
			spt_compr_stations.insert(edge.start_cs);

			idx++;
		}

		if (!spt_compr_stations.contains(edge.end_cs)) {
			id_idx[edge.end_cs] = idx;
			idx_id[idx] = edge.end_cs;
			spt_compr_stations.insert(edge.end_cs);

			idx++;
		}
	}

	for (auto& [Pp_id, edge] : edges) {
		if (pipes[Pp_id].get_in_rep() != true)
			graph[id_idx[edge.start_cs]][id_idx[edge.end_cs]] = pipes[Pp_id].get_diam();
	}

	int start, finish;

	while (true) {
		std::cout << "Input start node: ";
		start = get_num_value(1, std::numeric_limits<int>::max());
		if (id_idx.contains(start)) {
			start = id_idx[start];
			break;
		}
		std::cout << "There is no this node in graph" << std::endl;
	}

	while (true) {
		std::cout << "Input start node: ";
		finish = get_num_value(1, std::numeric_limits<int>::max());
		if (id_idx.contains(finish)) {
			finish = id_idx[finish];
			break;
		}
		std::cout << "There is no this node in graph" << std::endl;
	}

	std::cout << "Max flow form " << idx_id[start] << " to " << idx_id[finish] << " is "
		<< ford_fulkerson(graph, start, finish) << std::endl;

}


void Network::top_sort() {
	if (edges.empty()) {
		std::cout << "There is no graph";
	}
	else {
		std::unordered_map<int, std::unordered_set<int>> graph;
		std::stack<int> topo;

		for (auto& [pipe, edges] : edges) {
			graph[edges.start_cs].insert(edges.end_cs);
		}

		topo = topoligical_sort(graph);

		int i = 1;

		if (topo.empty())
			std::cout << "There is a cycle in graph" << std::endl;

		else {
			while (!topo.empty())
			{
				std::cout << "Number " << i << ": "
					<< topo.top()
					<< std::endl;

				topo.pop();
				i++;
			}
		}
	}
}


void Network::shortest_path() {

	std::unordered_map<int, int> id_idx;
	std::unordered_map<int, int> idx_id;
	std::unordered_set<int> spt_compr_stations;

	std::vector<std::vector<double>> graph(compr_stations.size(), std::vector<double>(compr_stations.size(), 0.0));

	int idx = 0;

	for (auto& [Pp_id, edge] : edges) {
		if (!spt_compr_stations.contains(edge.start_cs)) {
			id_idx[edge.start_cs] = idx;
			idx_id[idx] = edge.start_cs;
			spt_compr_stations.insert(edge.start_cs);

			idx++;
		}

		if (!spt_compr_stations.contains(edge.end_cs)) {
			id_idx[edge.end_cs] = idx;
			idx_id[idx] = edge.end_cs;
			spt_compr_stations.insert(edge.end_cs);

			idx++;
		}
	}

	for (auto& [Pp_id, edge] : edges) {
		if (pipes[Pp_id].get_in_rep() != true)
			graph[id_idx[edge.start_cs]][id_idx[edge.end_cs]] = pipes[Pp_id].get_len();
	}

	int src;

	while (true) {
		std::cout << "Input start node: ";
		src = get_num_value(1, std::numeric_limits<int>::max());
		if (id_idx.contains(src)) {
			src = id_idx[src];
			break;
		}
		std::cout << "There is no this node in graph" << std::endl;
	}

	std::vector<double> dist = dijkstra(graph, src);

	for (int i(0); i < dist.size(); ++i) {
		std::cout << "Distance to node " << idx_id[i];
		if (dist[i] == std::numeric_limits<double>::max())
			 std::cout << " is Inf" << std::endl;
		else
			std::cout << " is " << dist[i] << std::endl;
	}
}


bool Network::del_pipe(int id) {
	if (pipes.find(id) != pipes.end()) {
		pipes.erase(id);
		del_edge(id);
		return true;
	}
	else
		return false;
}


bool Network::del_compr_station(int id) {

	if (compr_stations.find(id) != compr_stations.end()) {
		if (not_node(id)) {
			compr_stations.erase(id);
			return true;
		}
		else {
			std::cout << "This CS is node" << std::endl;
			return false;
		}
			
	}
	else {
		std::cout << "There is no CS with that id" << std::endl;
		return false;
	}
}


std::ostream& operator << (std::ostream & out, edge_ids edge) {
	std::cout << "CS (id: " << edge.start_cs << ") ----Pipe (id: " << edge.pipe << ")---> CS (id: " << edge.end_cs << ")" << std::endl;
	return out;
}


std::ifstream& operator >> (std::ifstream& fin, edge_ids& edge) {
	fin >> edge.start_cs
		>> edge.end_cs
		>> edge.pipe;
	return fin;
}


std::ofstream& operator << (std::ofstream& fout, const edge_ids& edge) {
	fout << edge.start_cs << ' '
		<< edge.end_cs << ' '
		<< edge.pipe << std::endl;
	return fout;
}


void Network::change_in_rep(bool in_rep, std::unordered_set<int>& ids) {
	for (int i : ids) {
		pipes[i].set_in_rep(in_rep);
	}
}


void Network::filter_pipes() {
	std::cout << "1.Filter by name" << std::endl
		<< "2.Filter by \"In repearing\"" << std::endl
		<< "3.Filter by \"Working\"" << std::endl;
	int choice = get_num_value(1, 4);
	std::unordered_set<int> ids;

	if (choice == 1) {

		std::string name;
		std::cout << "Input name of pipe: ";
		std::cin.ignore(10000, '\n');
		std::getline(std::cin, name);

		ids = find_pipes_ids(pipes, check_pipe_name, name);
	}

	if (choice == 2) {

		ids = find_pipes_ids(pipes, check_pipe_in_rep, IN_REPEARING);
	}

	if (choice == 3) {

		ids = find_pipes_ids(pipes, check_pipe_in_rep, WORKING);
	}

	if (show(ids, pipes)) {

		std::cout << "1.close" << std::endl << "2.edit pipes" << std::endl;
		choice = get_num_value(1, 3);

		if (choice == 1) {
			return;
		}

		if (choice == 2) {

			choice = choose();

			if (choice == 2)
				ids = get_new_ids(ids);


			choice = del_or_edit();

			if (choice == 1) del_pipes(ids);
			if (choice == 2) {
				bool in_rep;
				in_rep = pipe_in_rep_input();
				change_in_rep(in_rep, ids);
			}
		}
	}
}


void Network::filter_compr_stations() {
	std::cout << "1.Filter by name" << std::endl
		<< "2.Filter by \"percent of unused worcstataoins >= \"" << std::endl
		<< "3.Filter by \"percent of unused worcstataoins <= \"" << std::endl
		<< "4.Filter by \"percent of unused worcstataoins = \"" << std::endl;
	int choice = get_num_value(1, 5);
	std::unordered_set<int> ids;

	if (choice == 1) {

		std::string name;
		std::cout << "Input name of CS: ";
		std::cin.ignore(10000, '\n');
		std::getline(std::cin, name);

		ids = find_compr_st_ids(compr_stations, check_compr_st_name, name);
	}

	if (choice == 2) {

		std::cout << "Input percent: ";
		double percent = get_num_value(0.0, 100.0);
		ids = find_compr_st_ids(compr_stations, check_unused_per_m, percent);
	}

	if (choice == 3) {

		std::cout << "Input percent: ";
		double percent = get_num_value(0.0, 100.0);
		ids = find_compr_st_ids(compr_stations, check_unused_per_l, percent);
	}

	if (choice == 4) {

		std::cout << "Input percent: ";
		double percent = get_num_value(0.0, 100.0);
		ids = find_compr_st_ids(compr_stations, check_unused_per_e, percent);
	}


	if (show(ids, compr_stations)) {

		std::cout << "1.close" << std::endl << "2.edit CS" << std::endl;
		choice = get_num_value(1, 3);

		if (choice == 1) {
			return;
		}

		if (choice == 2) {

			choice = choose();

			if (choice == 2)
				ids = get_new_ids(ids);

			choice = del_or_edit();

			if (choice == 1) del_compr_stations(ids);
			if (choice == 2) {
				std::cout << "Input number of workshops to add: ";
				int num = get_num_value(-std::numeric_limits<int>::max(), std::numeric_limits<int>::max());
				change_run_ws(num, ids);
			}
		}
	}
}


int Network::choose() {
	std::cout << "1.Choose all objects" << std::endl;
	std::cout << "2.Choose some objects" << std::endl;
	return get_num_value(1, 3);
}


int Network::del_or_edit() {
	std::cout << "1.Delete objects" << std::endl;
	std::cout << "2.Edit objects" << std::endl;
	return get_num_value(1, 3);
}


void Network::change_run_ws(int num, std::unordered_set<int>& ids) {
	for (int i : ids) {
		compr_stations[i].change_num_run_workstation(num);
	}
}


std::unordered_set<int> Network::get_new_ids(std::unordered_set<int> ids) {
	std::unordered_set<int> new_ids;
	int id;
	while (true) {
		std::cout << "Input -1 to close." << std::endl << "Input selected id: ";
		id = get_num_value(-1, std::numeric_limits<int>::max());

		if (id == -1) {
			break;
		}

		else if (ids.find(id) != ids.end()) {
			new_ids.insert(id);
		}
		else {
			std::cout << "There is no object with that id" << std::endl;
		}
	}
	return new_ids;
}

bool Network::show_edges() {
	if (edges.size() != 0) {
		for (auto& edge : edges)
			std::cout << edge.second;
		return true;
	}
	return false;
}


