#include "DominatingSet.h"


/// Algorithm 4 - VRegularGreedyPlus


std::set<int> DominatingSet::PerformVRegularGreedyPlus(Graph graph)
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

	graph_traits<Filtered>::vertex_iterator ui, ui_end;


	// Add all remained vertices to white-vertices set 
	for (boost::tie(ui, ui_end) = vertices(f); ui != ui_end; ++ui)
	{
		white_nodes.insert(*ui);
	}

	// Until white-vertices exist
	while (white_nodes.size() > 0)
	{
		boost::tie(ui, ui_end) = vertices(f);

		Vertex current_node = *ui;
		int max_degree = 0;

		// Find vertex with maximum degree
		for (; ui != ui_end; ++ui)
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