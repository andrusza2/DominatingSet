#include "DominatingSet.h"


/// Algorithm 2 - VRegularGeeedy


std::set<int> DominatingSet::PerformVRegularGreedy(Graph graph)
{
	std::set<int> dominating_set;

	// Get the property map for vertex indices
	typedef property_map<Graph, vertex_index_t>::type IndexMap;
	IndexMap index = get(vertex_index, graph);

	// Get color map (default - white)
	property_map<Graph, vertex_color_t>::type colorMap = get(vertex_color, graph);

	std::set<Vertex> white_nodes;


	typedef graph_traits<Graph>::vertex_iterator vertex_iter;
	std::pair<vertex_iter, vertex_iter> vp;


	std::set<Vertex> D1; // degree_of_1_vertices
	std::set<Vertex> neighbors_of_D1;


	// Find all vertices with degree=1 and their neighbors
	for (vp = vertices(graph); vp.first != vp.second; ++vp.first) {
		Vertex v = *vp.first;
		if (degree(v, graph) == 1)
		{
			D1.insert(v);

			typename graph_traits<Graph>::adjacency_iterator ai;
			typename graph_traits<Graph>::adjacency_iterator ai_end;
			for (boost::tie(ai, ai_end) = adjacent_vertices(v, graph);
				ai != ai_end; ++ai)
				neighbors_of_D1.insert(*ai);
		}
	}

	// Mark all vertices with degree=1 as black (not consider in next step)
	for (auto&& v : D1)
	{
		colorMap[v] = black_color;
	}

	// Any dominating set must contain Neigbors(D1)
	for (auto&& v : neighbors_of_D1)
	{
		dominating_set.insert(index[v]);

		colorMap[v] = black_color;

		typename graph_traits<Graph>::adjacency_iterator ai;
		typename graph_traits<Graph>::adjacency_iterator ai_end;
		for (boost::tie(ai, ai_end) = adjacent_vertices(v, graph); ai != ai_end; ++ai)
		{
			// Mark all Neighbors(Nieghbors(D1)) as black (not consider in next step)
			colorMap[*ai] = black_color;
		}
	}


	// Filtered graph - without black vertices
	Filtered f(graph, keep_all{}, [&](Vertex v) { return colorMap[v] != black_color; });

	// Add all remained vertices to white-vertices set 
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
		for (boost::tie(ai, ai_end) = adjacent_vertices(current_node, f); ai != ai_end; ++ai)
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