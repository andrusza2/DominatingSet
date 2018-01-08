#include "DominatingSet.h"

#include <boost/graph/filtered_graph.hpp>
#include <boost/function.hpp>


using Filtered = filtered_graph<Graph, keep_all, boost::function<bool(Vertex)> >;


/// Algorithm 3 - RegularGreedyPlus


std::set<int> DominatingSet::PerformRegularGreedyPlus(Graph g)
{
	//std::cout << num_vertices(g) << std::endl;
	//std::cout << num_edges(g) << std::endl;

	std::set<int> dominating_set;

	// get the property map for vertex indices
	typedef property_map<Graph, vertex_index_t>::type IndexMap;
	IndexMap index = get(vertex_index, g);


	typedef boost::graph_traits<Filtered>::vertex_descriptor Vertex;
	std::set<Vertex> white_nodes;

	// Get color map (default - white)
	property_map<Graph, vertex_color_t>::type colorMap = get(vertex_color, g);


	typedef graph_traits<Graph>::vertex_iterator vertex_iter;
	std::pair<vertex_iter, vertex_iter> vp;
	for (vp = vertices(g); vp.first != vp.second; ++vp.first) {
		Vertex v = *vp.first;
		if (degree(v, g) == 0)
		{
			colorMap[v] = black_color;
			dominating_set.insert(index[v]);
		}
	}

	Filtered f(g, keep_all{}, [&](Vertex v) { return colorMap[v] != black_color; });

	graph_traits<Filtered>::vertex_iterator ui, ui_end;
	for (boost::tie(ui, ui_end) = vertices(f); ui != ui_end; ++ui)
		white_nodes.insert(*ui);
	

	while (white_nodes.size() > 0)
	{
		
		//Vertex current_node = *ui;
		Vertex current_node = *white_nodes.begin();
		int max_degree = 0;


		for (boost::tie(ui, ui_end) = vertices(f); ui != ui_end; ++ui)
		{
			if (degree(*ui, f) > max_degree)
			{
				max_degree = degree(*ui, f);
				current_node = *ui;
			}
		}

		dominating_set.insert(index[current_node]);

		std::set<Vertex> neighbors_of_current_node;

		typename graph_traits<Filtered>::adjacency_iterator ai;
		typename graph_traits<Filtered>::adjacency_iterator ai_end;
		for (boost::tie(ai, ai_end) = adjacent_vertices(current_node, f);
			ai != ai_end; ++ai)
		{
			neighbors_of_current_node.insert(*ai);
			//colorMap[*ai] = black_color;
			//white_nodes.erase(*ai);
		}

		colorMap[current_node] = black_color;
		white_nodes.erase(current_node);

		for (auto&& node : neighbors_of_current_node)
		{
			colorMap[node] = black_color;
			white_nodes.erase(node);
		}
	}

	return dominating_set;
}