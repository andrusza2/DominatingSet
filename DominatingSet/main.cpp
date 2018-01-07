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

using namespace boost;


// create a typedef for the Graph type
typedef boost::undirected_graph<property<vertex_color_t, default_color_type>> Graph;



void cin_edges(Graph & g, int num_edges)
{
	for (unsigned i = 0; i < num_edges; i++)
	{
		int a, b;
		char coma;
		std::cin >> a;
		std::cin >> coma;
		std::cin >> b;

		Vertex u, v;

		g.add_edge(vertex(a-1, g), vertex(b-1, g));
	}
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

	cin_edges(g, num_edg);


	// Accessing the Vertex Set

	typedef typename graph_traits<Graph>::vertex_descriptor Vertex;

	// get the property map for vertex indices
	typedef property_map<Graph, vertex_index_t>::type IndexMap;
	IndexMap index = get(vertex_index, g);



	

	//std::cout << "vertices(g) = ";
	//typedef graph_traits<Graph>::vertex_iterator vertex_iter;
	//std::pair<vertex_iter, vertex_iter> vp;
	//for (vp = vertices(g); vp.first != vp.second; ++vp.first) {
	//	Vertex v = *vp.first;
	//	std::cout << index[v] << " (degree: " << degree(v, g) << ") ";
	//}
	//std::cout << std::endl;

	//std::cout << "edges(g) = ";
	//graph_traits<Graph>::edge_iterator ei, ei_end;
	//for (boost::tie(ei, ei_end) = edges(g); ei != ei_end; ++ei)
	//	std::cout << "(" << index[source(*ei, g)]
	//	<< "," << index[target(*ei, g)] << ") ";
	//std::cout << std::endl;
	//std::cout << std::endl;


	// Accessing the Edge Set

	std::set<Vertex> D1; // degree_of_1_vertices
	std::set<Vertex> neighbors_of_D1;

	std::set<int> dominating_set;

	/// Algorithm 1 - Regular Greedy

	auto dominating_set_1 = DominatingSet::PerformRegularGreedy(g);

	std::cout << "Regular Greedy ended, dominating set found (size: " << dominating_set_1.size() << "):" << std::endl;
	//for (auto&& node_index : dominating_set_1)
	//{
	//	std::cout << node_index << " ";
	//}
	std::cout << std::endl;
	std::cout << std::endl;


	/// Algorithm 2 - V Regular Greedy

	auto dominating_set_2 = DominatingSet::PerformVRegularGreedy(g);

	std::cout << "V Regular Greedy ended, dominating set found (size: " << dominating_set_2.size() << "):" << std::endl;
	//for (auto&& node_index : dominating_set_2)
	//{
	//	std::cout << node_index << " ";
	//}
	std::cout << std::endl;
	std::cout << std::endl;

	/// Algorithm 3 - Regular Greedy Plus

	auto dominating_set_3 = DominatingSet::PerformRegularGreedyPlus(g);

	std::cout << "Regular Greedy Plus ended, dominating set found (size: " << dominating_set_3.size() << "):" << std::endl;
	//for (auto&& node_index : dominating_set_3)
	//{
	//	std::cout << node_index << " ";
	//}
	std::cout << std::endl;
	std::cout << std::endl;


	/// Algorithm 4 - V Regular Greedy Plus

	auto dominating_set_4 = DominatingSet::PerformVRegularGreedyPlus(g);

	std::cout << "V Regular Greedy Plus ended, dominating set found (size: " << dominating_set_4.size() << "):" << std::endl;
	//for (auto&& node_index : dominating_set_4)
	//{
	//	std::cout << node_index << " ";
	//}
	std::cout << std::endl;
	std::cout << std::endl;



	/// Algorithm 5 - Fast Greedy

	auto dominating_set_5 = DominatingSet::PerformFastGreedy(g);

	std::cout << "Fast Greedy ended, dominating set found (size: " << dominating_set_5.size() << "):" << std::endl;
	//for (auto&& vertex : dominating_set_5)
	//{
	//	std::cout << vertex << " ";
	//}
	std::cout << std::endl;


 	return 0;
}