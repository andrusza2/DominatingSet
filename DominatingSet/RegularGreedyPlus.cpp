#include "DominatingSet.h"


/// Algorithm 3 - RegularGreedyPlus


std::set<int> DominatingSet::PerformRegularGreedyPlus(Graph g)
{
	std::set<int> dominating_set;

	// Get the property map for vertex indices
	typedef property_map<Graph, vertex_index_t>::type IndexMap;
	IndexMap index = get(vertex_index, g);

	// Get color map (default - white)
	property_map<Graph, vertex_color_t>::type colorMap = get(vertex_color, g);

	std::set<Vertex> white_nodes;

	typedef graph_traits<Graph>::vertex_iterator vertex_iter;
	std::pair<vertex_iter, vertex_iter> vp;


	// Filtered graph - without black vertices
	Filtered f(g, keep_all{}, [&](Vertex v) { return colorMap[v] != black_color; });

	// Add all remained vertices to white-vertices set 
	graph_traits<Filtered>::vertex_iterator ui, ui_end;
	for (boost::tie(ui, ui_end) = vertices(f); ui != ui_end; ++ui)
		white_nodes.insert(*ui);
	
	// Until white-vertices exist
	while (white_nodes.size() > 0)
	{
		Vertex current_node = *white_nodes.begin();
		int max_degree = 0;

		// Find vertex with maximum degree
		for (boost::tie(ui, ui_end) = vertices(f); ui != ui_end; ++ui)
		{
			if (degree(*ui, f) > max_degree)
			{
				max_degree = degree(*ui, f);
				current_node = *ui;
			}
		}

		// Add vertex with max degree to dominating set
		dominating_set.insert(index[current_node]);

		// Mark all neigbors of this vertex as black (not consider in next iteration)
		std::set<Vertex> neighbors_of_current_node;

		typename graph_traits<Filtered>::adjacency_iterator ai;
		typename graph_traits<Filtered>::adjacency_iterator ai_end;
		for (boost::tie(ai, ai_end) = adjacent_vertices(current_node, f);
			ai != ai_end; ++ai)
		{
			neighbors_of_current_node.insert(*ai);
		}

		for (auto&& node : neighbors_of_current_node)
		{
			colorMap[node] = black_color;
			white_nodes.erase(node);
		}

		// Mark vertex as black (not consider in next iteration)
		colorMap[current_node] = black_color;
		white_nodes.erase(current_node);
	}

	return dominating_set;
}