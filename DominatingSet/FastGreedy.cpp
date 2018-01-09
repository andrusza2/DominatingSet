#include "DominatingSet.h"


/// Algorithm 5 - FastGreedy


std::set<int> DominatingSet::PerformFastGreedy(Graph g)
{
	// Get the property map for vertex indices
	typedef property_map<Graph, vertex_index_t>::type IndexMap;
	IndexMap index = get(vertex_index, g);

	typedef std::pair<Vertex, int> VertexWithDegree;

	std::vector<VertexWithDegree> vertices_vector;

	graph_traits<Graph>::vertex_iterator ui, ui_end;

	for (boost::tie(ui, ui_end) = vertices(g); ui != ui_end; ++ui)
	{
		// Add every vertex to queue with its degree as key to vertices_vector
		vertices_vector.push_back(std::make_pair(*ui, degree(*ui, g)));
	}

	std::sort(vertices_vector.begin(),
		vertices_vector.end(),
		[](VertexWithDegree &left, VertexWithDegree &right)
	{
		return left.second > right.second;
	});


	std::set<int> dominating_set;
	std::set<int> neighbors;


	int ind = 0;

	while (neighbors.size() < g.num_vertices())
	{
		auto& i = vertices_vector[ind];

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

		if (neighbors.count(index[v]) == 0)
		{
			vertex_to_add = true;
		}

		if (vertex_to_add)
		{
			dominating_set.insert(index[v]);
			neighbors.insert(index[v]);
		}
		
		++ind;
	}

	return dominating_set;
}