#pragma once

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

using namespace boost;

// create a typedef for the Graph type
typedef boost::undirected_graph<property<vertex_color_t, default_color_type>> Graph;

// Accessing the Vertex Set
typedef boost::graph_traits<Graph>::vertex_descriptor Vertex;


class DominatingSet
{
public:
	static std::set<int> PerformFastGreedy(Graph g);
	static std::set<int> PerformRegularGreedy(Graph g);
	static std::set<int> PerformVRegularGreedy(Graph g);

	static std::set<int> PerformRegularGreedyPlus(Graph g);
	static std::set<int> PerformVRegularGreedyPlus(Graph g);
};