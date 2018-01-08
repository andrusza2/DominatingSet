#include <iostream>                  // for std::cout
#include <utility>                   // for std::pair
#include <algorithm>                 // for std::for_each
#include <map>					     // for std::map
#include <chrono>					 // for std::chrono::high_resolution_clock

#include "DominatingSet.h"


using namespace boost;


std::map<int, int> indices_map;
std::map<int, int> map_to_original_index;

int current_map_index = 0;

void add_edge_with_index(Graph & g, int a, int b)
{
	auto ret = indices_map.insert(std::make_pair(a, current_map_index));
	if (ret.second == true)
	{
        map_to_original_index.insert(std::make_pair(current_map_index, a));
		++current_map_index;
	}

	ret = indices_map.insert(std::make_pair(b, current_map_index));
	if (ret.second == true)
	{
        map_to_original_index.insert(std::make_pair(current_map_index, b));
		++current_map_index;
	}

	g.add_edge(vertex(indices_map[a], g), vertex(indices_map[b], g));
}


void cin_edges(Graph & g, int num_edges)
{
	for (unsigned i = 0; i < num_edges; i++)
	{
		int a, b;
		char coma;

		std::cin >> a;
		std::cin >> coma;
		std::cin >> b;

		add_edge_with_index(g, a, b);
	}
}

void print_dominating_set(std::set<int>  & dominating_set) 
{

	for(auto f : dominating_set) 
	{
		std::cout << map_to_original_index[f] << " ";
	}
	std::cout << std::endl;
}


int main(int, char*[])
{
	// Number of vertices, number of edges
	int num_ver, num_edg;

	std::cin >> num_ver >> num_edg;
	Graph g(num_ver);

	// Add edges to Graph object
	cin_edges(g, num_edg);


	/// Algorithm 1 - Regular Greedy

    auto start_time = std::chrono::high_resolution_clock::now();
	auto dominating_set_1 = DominatingSet::PerformRegularGreedy(g);
    auto end_time = std::chrono::high_resolution_clock::now();

	std::cout << "Regular Greedy ended, dominating set found (size: " << dominating_set_1.size() << "):" << std::endl;
    std::cout << "Regular Greedy duration: " << std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count() << std::endl;
	//print_dominating_set(dominating_set_1);
	std::cout << std::endl;
	std::cout << std::endl;


	/// Algorithm 2 - V Regular Greedy

    start_time = std::chrono::high_resolution_clock::now();
	auto dominating_set_2 = DominatingSet::PerformVRegularGreedy(g);
    end_time = std::chrono::high_resolution_clock::now();
	//print_dominating_set(dominating_set_2);

	std::cout << "V Regular Greedy ended, dominating set found (size: " << dominating_set_2.size() << "):" << std::endl;
    std::cout << "V Regular Greedy duration: " << std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count() << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;

	/// Algorithm 3 - Regular Greedy Plus

    start_time = std::chrono::high_resolution_clock::now();
	auto dominating_set_3 = DominatingSet::PerformRegularGreedyPlus(g);
    end_time = std::chrono::high_resolution_clock::now();
    //print_dominating_set(dominating_set_3);

	std::cout << "Regular Greedy Plus ended, dominating set found (size: " << dominating_set_3.size() << "):" << std::endl;
    std::cout << "Regular Greedy Plus duration: " << std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count() << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;


	/// Algorithm 4 - V Regular Greedy Plus

    start_time = std::chrono::high_resolution_clock::now();
	auto dominating_set_4 = DominatingSet::PerformVRegularGreedyPlus(g);
    end_time = std::chrono::high_resolution_clock::now();
	//print_dominating_set(dominating_set_4);

	std::cout << "V Regular Greedy Plus ended, dominating set found (size: " << dominating_set_4.size() << "):" << std::endl;
    std::cout << "V Regular Greedy Plus duration: " << std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count() << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;


	/// Algorithm 5 - Fast Greedy

    start_time = std::chrono::high_resolution_clock::now();
	auto dominating_set_5 = DominatingSet::PerformFastGreedy(g);
    end_time = std::chrono::high_resolution_clock::now();
	//print_dominating_set(dominating_set_5);

	std::cout << "Fast Greedy ended, dominating set found (size: " << dominating_set_5.size() << "):" << std::endl;
    std::cout << "Fast Greedy duration: " << std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count() << std::endl;
	std::cout << std::endl;

 	return 0;
}