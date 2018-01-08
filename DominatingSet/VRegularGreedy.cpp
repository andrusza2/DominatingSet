#include "DominatingSet.h"


/// Algorithm 2 - VRegularGeeedy


std::set<int> DominatingSet::PerformVRegularGreedy(Graph graph)
{
	std::set<int> dominating_set;


	std::set<Vertex> white_nodes;


	// Get color map (default - white)
	property_map<Graph, vertex_color_t>::type colorMap = get(vertex_color, graph);

	// Get the property map for vertex indices
	typedef property_map<Graph, vertex_index_t>::type IndexMap;
	IndexMap index = get(vertex_index, graph);


	typedef graph_traits<Graph>::vertex_iterator vertex_iter;
	std::pair<vertex_iter, vertex_iter> vp;
	for (vp = vertices(graph); vp.first != vp.second; ++vp.first) {
		Vertex v = *vp.first;
		if (degree(v, graph) == 0)
		{
			colorMap[v] = black_color;
			dominating_set.insert(index[v]);
		}
	}


	std::set<Vertex> D1; // degree_of_1_vertices
	std::set<Vertex> neighbors_of_D1;


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

	for (auto&& v : D1)
	{
		colorMap[v] = black_color;
	}

	for (auto&& v : neighbors_of_D1)
	{
		dominating_set.insert(index[v]);

		colorMap[v] = black_color;

		typename graph_traits<Graph>::adjacency_iterator ai;
		typename graph_traits<Graph>::adjacency_iterator ai_end;
		for (boost::tie(ai, ai_end) = adjacent_vertices(v, graph);
			ai != ai_end; ++ai)
			colorMap[*ai] = black_color;
	}

	//PreformRegularGreedy(g);
	////auto g_prim_ds = PreformRegularGreedy(g);

	////dominating_set.insert(g_prim_ds.begin(), g_prim_ds.end());


	Filtered f(graph, keep_all{}, [&](Vertex v) { return colorMap[v] != black_color; });


	graph_traits<Filtered>::vertex_iterator ui, ui_end;
	for (boost::tie(ui, ui_end) = vertices(f); ui != ui_end; ++ui)
		white_nodes.insert(*ui);


	while (white_nodes.size() > 0)
	{
		Vertex current_node = *white_nodes.begin();
		int max_span = 0;

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

		dominating_set.insert(index[current_node]);

		typename graph_traits<Filtered>::adjacency_iterator ai;
		typename graph_traits<Filtered>::adjacency_iterator ai_end;
		for (boost::tie(ai, ai_end) = adjacent_vertices(current_node, f);
			ai != ai_end; ++ai)
		{
			colorMap[*ai] = gray_color;
			white_nodes.erase(*ai);
		}

		colorMap[current_node] = black_color;
		white_nodes.erase(current_node);
	}

	return dominating_set;
}