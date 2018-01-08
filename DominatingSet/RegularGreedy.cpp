#include "DominatingSet.h"


/// Algorithm 1 - RegularGreedy


std::set<int> DominatingSet::PerformRegularGreedy(Graph g)
{
	std::set<int> dominating_set;

	// Get the property map for vertex indices
	typedef property_map<Graph, vertex_index_t>::type IndexMap;
	IndexMap index = get(vertex_index, g);

	// Get color map (default - white)
	property_map<Graph, vertex_color_t>::type colorMap = get(vertex_color, g);

	// Set of white vertices
	std::set<Vertex> white_nodes;


	typedef graph_traits<Graph>::vertex_iterator vertex_iter;
	std::pair<vertex_iter, vertex_iter> vp;


	// Filtered graph - without black vertices
	Filtered f(g, keep_all{}, [&](Vertex v) { return colorMap[v] != black_color; });

	graph_traits<Filtered>::vertex_iterator ui, ui_end;
	for (boost::tie(ui, ui_end) = vertices(f); ui != ui_end; ++ui)
	{
		white_nodes.insert(*ui);
	}

	// Until white-vertices exist
	while (white_nodes.size() > 0)
	{
		Vertex current_node = *white_nodes.begin();
		int max_span = 0;

		// Find vertex with maximum span (size of the set of white nodes among the direct neighbors of vertex, including vertex itself)
		for (boost::tie(ui, ui_end) = vertices(f); ui != ui_end; ++ui)
		{
			int span = 1;

			typename graph_traits<Filtered>::adjacency_iterator ai;
			typename graph_traits<Filtered>::adjacency_iterator ai_end;
			for (boost::tie(ai, ai_end) = adjacent_vertices(*ui, f);
				ai != ai_end; ++ai)
			{
				if (colorMap[*ai] == white_color)
					span++;
			}

			if (span > max_span)
			{
				max_span = span;
				current_node = *ui;
			}
		}

		// Add vertex with max span to dominating set
		dominating_set.insert(index[current_node]);

		// Mark all neigbors of this vertex as gray 
		typename graph_traits<Filtered>::adjacency_iterator ai;
		typename graph_traits<Filtered>::adjacency_iterator ai_end;
		for (boost::tie(ai, ai_end) = adjacent_vertices(current_node, f);
			ai != ai_end; ++ai)
		{
			colorMap[*ai] = gray_color;
			// Remove from white-vertices set
			white_nodes.erase(*ai);
		}

		// Mark vertex as black (not consider in next iteration)
		colorMap[current_node] = black_color;
		white_nodes.erase(current_node);
	}

	return dominating_set;
}