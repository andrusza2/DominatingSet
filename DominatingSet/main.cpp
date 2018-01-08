#define _CRT_SECURE_NO_WARNINGS

#include <iostream>                  // for std::cout
#include <utility>                   // for std::pair
#include <algorithm>                 // for std::for_each
#include <map>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/undirected_graph.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/properties.hpp>
#include <boost/graph/copy.hpp>

#include <boost/graph/detail/d_ary_heap.hpp>
#include "DominatingSet.h"
#include <chrono>


#include <cstdio>

using namespace boost;


// create a typedef for the Graph type
typedef boost::undirected_graph<property<vertex_color_t, default_color_type>> Graph;

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

void print_dominating_set(std::set<int>  & dominating_set_1) {

	for(auto f : dominating_set_1) {
		std::cout << map_to_original_index[f] << " ";
	}
	std::cout << std::endl;
}


int main(int, char*[])
{
	//// Make convenient labels for the vertices
	//enum { A, B, C, D, E, F, G, H, I, N };
	//const int num_vertices1 = N;
	//const char* name = "ABCDE";

	//// writing out the edges in the graph
	//typedef std::pair<int, int> Edge;
	////Edge edge_array[] =
	////{ Edge(A,B), Edge(A,C), Edge(A,D), Edge(A,E),
	////	Edge(B,F), Edge(C, G), Edge(D,H), Edge(E, I) };
	//Edge edge_array[] =
	//{ Edge(A,B), Edge(A,C), Edge(A,D), Edge(A,E),
	//	Edge(A,F), Edge(A, G), Edge(A,H), Edge(A, I) };
	//const int num_edges = sizeof(edge_array) / sizeof(edge_array[0]);

	////// declare a graph object
	////Graph g(num_vertices);

	////// add the edges to the graph object
	////for (int i = 0; i < num_edges; ++i)
	////	add_edge(edge_array[i].first, edge_array[i].second, g);

	//Graph g(edge_array, edge_array + sizeof(edge_array) / sizeof(Edge), num_vertices1);




	int num_ver, num_edg;

	std::cin >> num_ver >> num_edg;



	Graph g(num_ver);

	std::cout << "Empty Graph Created" << std::endl;

	cin_edges(g, num_edg);


	std::cout << "Edges added to Graph" << std::endl;


	// Accessing the Vertex Set

	typedef typename graph_traits<Graph>::vertex_descriptor Vertex;

	// get the property map for vertex indices
	typedef property_map<Graph, vertex_index_t>::type IndexMap;
	IndexMap index = get(vertex_index, g);


	// Accessing the Edge Set

	std::set<Vertex> D1; // degree_of_1_vertices
	std::set<Vertex> neighbors_of_D1;

	std::set<int> dominating_set;

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