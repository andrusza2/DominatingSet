#include "DominatingSet.h"

#include <boost/graph/filtered_graph.hpp>
#include <boost/function.hpp>


using Filtered = filtered_graph<Graph, keep_all, boost::function<bool(Vertex)> >;


/// Algorithm 1 - RegularGreedy


std::set<int> DominatingSet::PerformRegularGreedy(Graph g)
{
	//std::cout << num_vertices(g) << std::endl;
	//std::cout << num_edges(g) << std::endl;

	std::set<int> dominating_set;

	// get the property map for vertex indices
	typedef property_map<Graph, vertex_index_t>::type IndexMap;
	IndexMap index = get(vertex_index, g);



	//Graph g1;

	//std::cout << "Before copy" << std::endl;


	//// Make copy to use in Algorithm 1
	//copy_graph(g, g1);

	//


	//typedef graph_traits<Graph>::vertex_iterator vertex_iter;
	//vertex_iter vi, vi_end, next;
	//tie(vi, vi_end) = vertices(g1);
	//for (next = vi; vi != vi_end; vi = next)
	//{
	//	++next;
	//	if (degree(*vi, g1) == 0)
	//	{
	//		clear_vertex(*vi, g1);
	//		remove_vertex(*vi, g1);
	//	}
	//}

	//std::cout << "After copy" << std::endl;

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