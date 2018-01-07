//#include <iostream>                  // for std::cout
//#include <utility>                   // for std::pair
//#include <algorithm>                 // for std::for_each
//#include <map>
//#include <boost/graph/graph_traits.hpp>
//#include <boost/graph/undirected_graph.hpp>
//#include <boost/graph/dijkstra_shortest_paths.hpp>
//#include <boost/graph/properties.hpp>
//
//#include <boost/graph/detail/d_ary_heap.hpp>
//
//using namespace boost;
//
//
//template <typename TQueue>
//static void OutputQueue(TQueue queue);
//
//// create a typedef for the Graph type
//typedef boost::undirected_graph<boost::no_property> Graph;
//
//template <class Graph> struct exercise_vertex {
//	exercise_vertex(Graph& g_) : g(g_) {}
//	//...
//
//	typedef typename graph_traits<Graph>
//		::vertex_descriptor Vertex;
//
//	void operator()(const Vertex& v) const
//	{
//		typedef graph_traits<Graph> GraphTraits;
//		typename property_map<Graph, vertex_index_t>::type
//			index = get(vertex_index, g);
//
//		std::cout << "out-edges: ";
//		typename GraphTraits::out_edge_iterator out_i, out_end;
//		typename GraphTraits::edge_descriptor e;
//		for (boost::tie(out_i, out_end) = out_edges(v, g);
//			out_i != out_end; ++out_i) {
//			e = *out_i;
//			Vertex src = source(e, g), targ = target(e, g);
//			std::cout << "(" << index[src] << ","
//				<< index[targ] << ") ";
//		}
//		std::cout << std::endl;
//		//...
//
//		std::cout << "in-edges: ";
//		typedef typename graph_traits<Graph> GraphTraits;
//		typename GraphTraits::in_edge_iterator in_i, in_end;
//		for (boost::tie(in_i, in_end) = in_edges(v, g);
//			in_i != in_end; ++in_i) {
//			e = *in_i;
//			Vertex src = source(e, g), targ = target(e, g);
//			std::cout << "(" << index[src] << "," << index[targ] << ") ";
//		}
//		std::cout << std::endl;
//
//
//
//		std::cout << "adjacent vertices: ";
//		typename graph_traits<Graph>::adjacency_iterator ai;
//		typename graph_traits<Graph>::adjacency_iterator ai_end;
//		for (boost::tie(ai, ai_end) = adjacent_vertices(v, g);
//			ai != ai_end; ++ai)
//			std::cout << index[*ai] << " ";
//		std::cout << std::endl;
//
//
//	}
//
//	Graph& g;
//};
//
//int main(int, char*[])
//{
//	// Make convenient labels for the vertices
//	enum { A, B, C, D, E, N };
//	const int num_vertices1 = N;
//	const char* name = "ABCDE";
//
//	// writing out the edges in the graph
//	typedef std::pair<int, int> Edge;
//	Edge edge_array[] =
//	{ Edge(A,B), Edge(A,D), Edge(C,A), Edge(D,C),
//		Edge(C,E), Edge(A,D), Edge(D,E) };
//	const int num_edges = sizeof(edge_array) / sizeof(edge_array[0]);
//
//	//// declare a graph object
//	//Graph g(num_vertices);
//
//	//// add the edges to the graph object
//	//for (int i = 0; i < num_edges; ++i)
//	//	add_edge(edge_array[i].first, edge_array[i].second, g);
//
//	Graph g(edge_array, edge_array + sizeof(edge_array) / sizeof(Edge), num_vertices1);
//
//
//	// Accessing the Vertex Set
//
//	typedef graph_traits<Graph>::vertex_descriptor Vertex;
//
//	// get the property map for vertex indices
//	typedef property_map<Graph, vertex_index_t>::type IndexMap;
//	IndexMap index = get(vertex_index, g);
//
//	std::cout << "vertices(g) = ";
//	typedef graph_traits<Graph>::vertex_iterator vertex_iter;
//	std::pair<vertex_iter, vertex_iter> vp;
//	for (vp = vertices(g); vp.first != vp.second; ++vp.first) {
//		Vertex v = *vp.first;
//		std::cout << index[v] << " (degree: " << degree(v, g) << ") ";
//	}
//	std::cout << std::endl;
//
//	std::cout << "edges(g) = ";
//	graph_traits<Graph>::edge_iterator ei, ei_end;
//	for (boost::tie(ei, ei_end) = edges(g); ei != ei_end; ++ei)
//		std::cout << "(" << index[source(*ei, g)]
//		<< "," << index[target(*ei, g)] << ") ";
//	std::cout << std::endl;
//	// ...
//
//	//// Priority Queue for vertices degrees, using std::multimap
//	//typedef std::multimap<unsigned int, graph_traits<Graph>::vertex_iterator> priority_queue;
//
//	//priority_queue mQueue;
//
//
//	////property_map<Graph, vertex_degree_t>::type deg = get(vertex_degree, g);
//	////for (boost::tie(ui, ui_end) = vertices(g); ui != ui_end; ++ui)
//	////	deg[*ui] = degree(*ui, g);
//
//	////property_map<Graph, priority_queue::iterator>::type degr;
//	//std::map<Vertex, priority_queue::iterator> degr;
//	//for (boost::tie(ui, ui_end) = vertices(g); ui != ui_end; ++ui)
//	//{
//	//	// add every vertex to queue with its degree as key
//	//	priority_queue::iterator qIter = mQueue.insert(std::make_pair(degree(*ui, g), ui));
//	//	degr[*ui] = qIter;
//	//}
//
//
//
//
//
//
//	/// Algorithm 5 - FastGreedy
//
//	std::vector<std::pair<Vertex, int>> vertices_vector;
//
//	graph_traits<Graph>::vertex_iterator ui, ui_end;
//
//	for (boost::tie(ui, ui_end) = vertices(g); ui != ui_end; ++ui)
//	{
//		vertices_vector.push_back(std::make_pair(*ui, degree(*ui, g)));
//		// add every vertex to queue with its degree as key
//	}
//
//	std::sort(vertices_vector.begin(),
//		vertices_vector.end(),
//		[](auto &left, auto &right)
//	{
//		return left.second > right.second;
//	});
//
//	std::cout << "Sorting vertices" << std::endl;
//
//	std::set<int> dominating_set_5;
//
//	std::set<int> neighbors;
//
//
//	int ind = 0;
//	while (neighbors.size() < g.num_vertices())
//		//for (auto&& i : vertices_vector)
//	{
//		auto& i = vertices_vector[ind];
//
//		std::cout << "Vertex " << index[i.first] << " of degree " << i.second << std::endl;
//
//		Vertex& v = i.first;
//
//		bool vertex_to_add = false;
//
//		typename graph_traits<Graph>::adjacency_iterator ai;
//		typename graph_traits<Graph>::adjacency_iterator ai_end;
//		for (boost::tie(ai, ai_end) = adjacent_vertices(v, g);
//			ai != ai_end; ++ai)
//		{
//			if (neighbors.count(index[*ai]) == 0)
//			{
//				vertex_to_add = true;
//				neighbors.insert(index[*ai]);
//			}
//		}
//
//		if (vertex_to_add)
//		{
//			std::cout << "Inserting vertex " << index[v] << std::endl;
//			dominating_set_5.insert(index[v]);
//		}
//		++ind;
//	}
//
//	std::cout << "Founded dominating set has " << dominating_set_5.size() << "elements: " << std::endl;
//	for (auto&& vertex : dominating_set_5)
//	{
//		std::cout << vertex << std::endl;
//	}
//
//
//
//
//
//	//void Item::remove()
//	//{
//	//	mQueue.erase(mIterator);
//	//	mQueue = 0;
//	//	mIterator = priority_queue::iterator();
//	//}
//
//
//
//	// Accessing the Edge Set
//
//	std::set<Vertex> D1; // degree_of_1_vertices
//	std::set<Vertex> neighbors_of_D1;
//
//	std::set<int> dominating_set;
//
//	//std::set<graph_traits<Graph>::vertex_iterator> D1; // degree_of_1_vertices
//	//std::set<graph_traits<Graph>::vertex_iterator> neighbors_of_D1;
//
//	//priority_queue::reverse_iterator rit;
//	//for (rit = mQueue.rbegin(); rit != mQueue.rend() ; ++rit)
//
//	//for (auto it = mQueue.begin(); it->first < 2 && it != mQueue.end(); ++ it)
//	//{
//	//	std::cout << it->first << std::endl;
//	//	if (it->first == 1) //degree ==1
//	//	{
//	//		Vertex v = *(it->second);
//	//		D1.insert(v);
//
//	//		typename graph_traits<Graph>::adjacency_iterator ai;
//	//		typename graph_traits<Graph>::adjacency_iterator ai_end;
//	//		for (boost::tie(ai, ai_end) = adjacent_vertices(v, g);
//	//			ai != ai_end; ++ai)
//	//			neighbors_of_D1.insert(*ai);
//	//	}
//	//}
//
//	for (vp = vertices(g); vp.first != vp.second; ++vp.first) {
//		Vertex v = *vp.first;
//		if (degree(v, g) == 1)
//		{
//			D1.insert(v);
//
//			typename graph_traits<Graph>::adjacency_iterator ai;
//			typename graph_traits<Graph>::adjacency_iterator ai_end;
//			for (boost::tie(ai, ai_end) = adjacent_vertices(v, g);
//				ai != ai_end; ++ai)
//				neighbors_of_D1.insert(*ai);
//		}
//	}
//
//	//std::cout << "D1 size: " << D1.size() << std::endl;
//	//std::cout << "Queue size: " << mQueue.size() << std::endl;
//
//	//for (auto&& v : D1)
//	//{
//	//	std::cout << "D1: " << std::endl;
//	//	std::cout << index[v] << std::endl;
//	//	clear_vertex(v, g);
//	//	//remove_vertex(v, g);
//	//	auto queue_it = degr[v];
//	//	mQueue.erase(queue_it);
//
//	//	std::cout << "Deleted vertex, current queue size: " << mQueue.size() << std::endl;
//	//}
//
//	//for (auto&& v : neighbors_of_D1)
//	//{
//	//	std::cout << "Neighbors_of_D1: " << std::endl;
//	//	std::cout << index[v] << std::endl;
//	//	clear_vertex(v, g);
//	//	//remove_vertex(v, g);
//	//	auto queue_it = degr[v];
//	//	mQueue.erase(queue_it);
//
//	//	std::cout << "Deleted vertex, current queue size: " << mQueue.size() << std::endl;
//	//}
//
//	//std::cout << "D1 size: " << D1.size() << std::endl;
//	//std::cout << "Queue size: " << mQueue.size() << std::endl;
//
//	for (auto&& v : D1)
//	{
//		std::cout << "D1: " << std::endl;
//		std::cout << index[v] << std::endl;
//		clear_vertex(v, g);
//		remove_vertex(v, g);
//	}
//
//	for (auto&& v : neighbors_of_D1)
//	{
//		std::cout << "Neighbors_of_D1: " << std::endl;
//		std::cout << index[v] << std::endl;
//
//		dominating_set.insert(index[v]);
//
//		clear_vertex(v, g);
//		remove_vertex(v, g);
//	}
//
//	while (num_vertices(g) > 0)
//	{
//		//find max degree vertex
//		vp = vertices(g);
//		Vertex max_v = *vp.first;
//		for (; vp.first != vp.second; ++vp.first) {
//			Vertex v = *vp.first;
//			if (degree(v, g) > degree(max_v, g))
//			{
//				max_v = v;
//			}
//		}
//
//		//find adj
//
//		std::set<Vertex> neighbors_of_max_v;
//
//		typename graph_traits<Graph>::adjacency_iterator ai;
//		typename graph_traits<Graph>::adjacency_iterator ai_end;
//		for (boost::tie(ai, ai_end) = adjacent_vertices(max_v, g); ai != ai_end; ++ai)
//			neighbors_of_max_v.insert(*ai);
//
//		// add max_v to dominanting set
//		dominating_set.insert(index[max_v]);
//
//		clear_vertex(max_v, g);
//		remove_vertex(max_v, g);
//
//		for (auto&& v : neighbors_of_max_v)
//		{
//			std::cout << "neighbors_of_max_v: " << std::endl;
//			std::cout << index[v] << std::endl;
//
//			clear_vertex(v, g);
//			remove_vertex(v, g);
//		}
//	}
//
//	std::cout << "Algorithm ended!!!" << std::endl;
//	std::cout << "Dominating set founded ( " << dominating_set.size() << " vertieces): " << std::endl;
//	for (auto&& vertex : dominating_set)
//	{
//		std::cout << vertex << " ";
//	}
//	std::cout << std::endl;
//
//
//
//
//
//
//	std::cout << "vertices(g) = ";
//
//	for (vp = vertices(g); vp.first != vp.second; ++vp.first) {
//		Vertex v = *vp.first;
//		std::cout << index[v] << " (degree: " << degree(v, g) << ") ";
//	}
//	std::cout << std::endl;
//
//	std::cout << "edges(g) = ";
//	for (boost::tie(ei, ei_end) = edges(g); ei != ei_end; ++ei)
//		std::cout << "(" << index[source(*ei, g)]
//		<< "," << index[target(*ei, g)] << ") ";
//	std::cout << std::endl;
//	// ...
//
//
//	//typedef graph_traits<Graph>::vertices_size_type vertices_size_type;
//	//typedef property_map<Graph, vertex_index_t>::const_type vertex_index_map;
//
//	//std::vector<vertices_size_type> degree_vec(num_vertices(g));
//
//	//iterator_property_map<vertices_size_type*, vertex_index_map>
//	//	color(degree_vec.front(), get(degree, g));
//
//
//
//
//
//	//// The Adjacency Structure
//
//	//std::for_each(vertices(g).first, vertices(g).second,
//	//	exercise_vertex<Graph>(g));
//
//
//	// ...
//	return 0;
//}