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
	std::cout << dominating_set.size() << std::endl;

	for(auto f : dominating_set) 
	{
		std::cout << map_to_original_index[f] << ",";
	}
	std::cout << std::endl;
}


static void show_usage(std::string name)
{
	std::cerr << "Usage: " << name << " <option(s)>"
		<< "Options:\n"
		<< "\t-h,--help\t\tShow this help message\n"
		<< "\t-r,--run-algorithm ALGORITHM\tSpecify the algorithm to use (ALGORITHM can be {1,2,3,4,5}\n"
		<< "\t-b,--benchmark \tRun benchmark mode - test all algorithms, show dominating set sizes and run times of algorithms"
		<< std::endl;
}


int main(int argc, char* argv[])
{
	//// Parse arguments

	bool benchmark_mode = false;
	int algorithm = DominatingSet::Algorithm::LAST;

	if (argc < 2 || argc > 3) {
		show_usage(argv[0]);
		return 1;
	}

	for (int i = 1; i < argc; ++i) 
	{
		std::string arg = argv[i];
		if ((arg == "-h") || (arg == "--help")) 
		{
			show_usage(argv[0]);
			return 0;
		}
		else if ((arg == "-r") || (arg == "--run-algorithm")) 
		{
			if (i + 1 < argc) 
			{ // Make sure we aren't at the end of argv
				try 
				{
					algorithm = std::stoi(argv[++i]);
				}
				catch (std::invalid_argument& ia)
				{
					std::cerr << "Invalid argument: " << ia.what() << '\n';
					return 1;
				}

				if (algorithm > DominatingSet::Algorithm::LAST)
				{
					std::cerr << "Wrong algorithm specified. Choose one of {1,2,3,4,5} \n";
					return 1;
				}

			}
			else { // There was no argument to the run-algorith option
				std::cerr << "--run-algorith option requires one argument." << std::endl;
				return 1;
			}
		}
		else if ((arg == "-b") || (arg == "--benchmark"))
		{
			benchmark_mode = true;
		}
		else
		{
			show_usage(argv[0]);
			return 1;
		}
	}

	//// Load graph from stdin

	// Number of vertices, number of edges
	int num_ver, num_edg;

	std::cin >> num_ver >> num_edg;
	Graph g(num_ver);

	// Add edges to Graph object
	cin_edges(g, num_edg);

	//// Run algorithms

	if (benchmark_mode)
	{
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
	}
	else // run-algorithm
	{
		std::set<int> dominating_set;

		switch (algorithm)
		{
		case DominatingSet::Algorithm::REGULAR_GREEDY:
			dominating_set = DominatingSet::PerformRegularGreedy(g);
			break;
		case DominatingSet::Algorithm::V_REGULAR_GREEDY:
			dominating_set = DominatingSet::PerformVRegularGreedy(g);
			break;
		case DominatingSet::Algorithm::REGULAR_GREEDY_PLUS:
			dominating_set = DominatingSet::PerformRegularGreedyPlus(g);
			break;
		case DominatingSet::Algorithm::V_REGULAR_GREEDY_PLUS:
			dominating_set = DominatingSet::PerformVRegularGreedyPlus(g);
			break;
		case DominatingSet::Algorithm::FAST_GREEDY:
		default:
			dominating_set = DominatingSet::PerformFastGreedy(g);
			break;
		}

		print_dominating_set(dominating_set);
	}

 	return 0;
}