#include "DominatingSet.h"


/// Algorithm 5 - FastGreedy

std::set<int> DominatingSet::PerformFastGreedy(Graph g)
{
	// get the property map for vertex indices
	typedef property_map<Graph, vertex_index_t>::type IndexMap;
	IndexMap index = get(vertex_index, g);

	std::vector<std::pair<Vertex, int>> vertices_vector;

	graph_traits<Graph>::vertex_iterator ui, ui_end;

	for (boost::tie(ui, ui_end) = vertices(g); ui != ui_end; ++ui)
	{
		vertices_vector.push_back(std::make_pair(*ui, degree(*ui, g)));
		// add every vertex to queue with its degree as key
	}

	std::sort(vertices_vector.begin(),
		vertices_vector.end(),
		[](auto &left, auto &right)
	{
		return left.second > right.second;
	});

	//std::cout << "Sorting vertices" << std::endl;

	std::set<int> dominating_set;

	std::set<int> neighbors;


	int ind = 0;
	while (neighbors.size() < g.num_vertices())
		//for (auto&& i : vertices_vector)
	{
		auto& i = vertices_vector[ind];

		//std::cout << "Vertex " << index[i.first] << " of degree " << i.second << std::endl;

		Vertex& v = i.first;

		bool vertex_to_add = false;

		typename graph_traits<Graph>::adjacency_iterator ai;
		typename graph_traits<Graph>::adjacency_iterator ai_end;
		for (boost::tie(ai, ai_end) = adjacent_vertices(v, g);
			ai != ai_end; ++ai)
		{
			if (neighbors.count(index[*ai]) == 0)
			{
				vertex_to_add = true;
				neighbors.insert(index[*ai]);
			}
		}

		if (vertex_to_add)
		{
			//std::cout << "Inserting vertex " << index[v] << std::endl;
			dominating_set.insert(index[v]);
		}
		++ind;
	}

	return dominating_set;
}