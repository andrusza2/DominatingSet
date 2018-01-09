#pragma once

#include <boost/graph/graph_traits.hpp>
#include <boost/graph/undirected_graph.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/properties.hpp>
#include <boost/graph/copy.hpp>
#include <boost/graph/filtered_graph.hpp>
#include <boost/function.hpp>


using namespace boost;

// Create a typedef for the undirected graph type
typedef boost::undirected_graph<property<vertex_color_t, default_color_type>> Graph;

// Accessing the Vertex Set
typedef boost::graph_traits<Graph>::vertex_descriptor Vertex;

// Type for "filtered" graph
using Filtered = filtered_graph<Graph, keep_all, boost::function<bool(Vertex)> >;

// Class that contains methods for calculating an approximation to the minimum dominating set problem
class DominatingSet
{
public:
	// Eubank et al. 2004
	static std::set<int> PerformFastGreedy(Graph g);
	static std::set<int> PerformRegularGreedy(Graph g);
	static std::set<int> PerformVRegularGreedy(Graph g);

	// Campan et al. 
	static std::set<int> PerformRegularGreedyPlus(Graph g);
	static std::set<int> PerformVRegularGreedyPlus(Graph g);

	enum Algorithm
	{
		REGULAR_GREEDY = 1,
		V_REGULAR_GREEDY,
		REGULAR_GREEDY_PLUS,
		V_REGULAR_GREEDY_PLUS,
		FAST_GREEDY,
		LAST = FAST_GREEDY
	};

};