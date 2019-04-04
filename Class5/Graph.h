/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <queue>
#include <list>
#include <limits>
#include <cmath>
#include "MutablePriorityQueue.h"

using namespace std;

template <class T> class Edge;
template <class T> class Graph;
template <class T> class Vertex;

#define INF std::numeric_limits<double>::max()

/************************* Vertex  **************************/

template <class T>
class Vertex {
	T info;                // contents
	vector<Edge<T> > adj;  // outgoing edges
	bool visited;          // auxiliary field
	double dist = 0;
	Vertex<T> *path = NULL;
	int queueIndex = 0; 		// required by MutablePriorityQueue

	bool processing = false;
	void addEdge(Vertex<T> *dest, double w);

public:
	Vertex(T in);
	bool operator<(Vertex<T> & vertex) const; // // required by MutablePriorityQueue
	T getInfo() const;
	double getDist() const;
	Vertex *getPath() const;
	friend class Graph<T>;
	friend class MutablePriorityQueue<Vertex<T>>;
};


template <class T>
Vertex<T>::Vertex(T in): info(in) {}

/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */
template <class T>
void Vertex<T>::addEdge(Vertex<T> *d, double w) {
	adj.push_back(Edge<T>(d, w));
}

template <class T>
bool Vertex<T>::operator<(Vertex<T> & vertex) const {
	return this->dist < vertex.dist;
}

template <class T>
T Vertex<T>::getInfo() const {
	return this->info;
}

template <class T>
double Vertex<T>::getDist() const {
	return this->dist;
}

template <class T>
Vertex<T> *Vertex<T>::getPath() const {
	return this->path;
}

/********************** Edge  ****************************/

template <class T>
class Edge {
	Vertex<T> * dest;      // destination vertex
	double weight;         // edge weight
public:
	Edge(Vertex<T> *d, double w);
	friend class Graph<T>;
	friend class Vertex<T>;
};

template <class T>
Edge<T>::Edge(Vertex<T> *d, double w): dest(d), weight(w) {}


/*************************** Graph  **************************/

template <class T>
class Graph {
	vector<Vertex<T> *> vertexSet;    // vertex set

public:
	Vertex<T> *findVertex(const T &in) const;
	bool addVertex(const T &in);
	bool addEdge(const T &sourc, const T &dest, double w);
	int getNumVertex() const;
	vector<Vertex<T> *> getVertexSet() const;

	// Fp05 - single source
	void dijkstraShortestPath(const T &s);
	void dijkstraShortestPathOld(const T &s);
	void unweightedShortestPath(const T &s);
	void bellmanFordShortestPath(const T &s);
	vector<T> getPath(const T &origin, const T &dest) const;

	// Fp05 - all pairs
	void floydWarshallShortestPath();
	vector<T> getfloydWarshallPath(const T &origin, const T &dest) const;

};

template <class T>
int Graph<T>::getNumVertex() const {
	return vertexSet.size();
}

template <class T>
vector<Vertex<T> *> Graph<T>::getVertexSet() const {
	return vertexSet;
}

/*
 * Auxiliary function to find a vertex with a given content.
 */
template <class T>
Vertex<T> * Graph<T>::findVertex(const T &in) const {
	for (auto v : vertexSet)
		if (v->info == in)
			return v;
	return NULL;
}

/*
 *  Adds a vertex with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
template <class T>
bool Graph<T>::addVertex(const T &in) {
	if ( findVertex(in) != NULL)
		return false;
	vertexSet.push_back(new Vertex<T>(in));
	return true;
}

/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
template <class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, double w) {
	auto v1 = findVertex(sourc);
	auto v2 = findVertex(dest);
	if (v1 == NULL || v2 == NULL)
		return false;
	v1->addEdge(v2,w);
	return true;
}


/**************** Single Source Shortest Path algorithms ************/

template<class T>
void Graph<T>::dijkstraShortestPath(const T &origin) {
	for(auto & v : vertexSet) {
		v->dist = INF;
		v->path = NULL;
	}

	MutablePriorityQueue<Vertex<T>> queue;
	auto first = findVertex(origin);
	first->dist = 0;
	queue.insert(first);

	while(!queue.empty()) {
		auto v = queue.extractMin();

		for (auto & w : v->adj) {
			auto oldDist = w.dest->dist;
			if (w.dest->dist > v->dist + w.weight) {
				w.dest->dist = v->dist + w.weight;
				w.dest->path = v;

				if (oldDist == INF)
					queue.insert(w.dest);
				else
					queue.decreaseKey(w.dest);
			}
		}
	}

}

template<class T>
vector<T> Graph<T>::getPath(const T &origin, const T &dest) const{
	vector<T> res;

	auto vertex = findVertex(dest);
	auto finalVertex = findVertex(origin);

	while (vertex != finalVertex) {
		res.push_back(vertex->info);
		vertex = vertex->path;
	}

	res.push_back(vertex->info);
	reverse(res.begin(), res.end());

	return res;
}

template<class T>
void Graph<T>::unweightedShortestPath(const T &orig) {
	for(auto & v : vertexSet) {
		v->dist = INF;
		v->path = NULL;
	}

	auto first = findVertex(orig);
	first->dist = 0;
	queue<Vertex<T> *> aux;
	aux.push(first);

	while(!aux.empty()) {
		auto v = aux.front();
		aux.pop();

		for (auto & e : v->adj) {
			if (e.dest->dist == INF) {
				aux.push(e.dest);
				e.dest->dist = v->dist + 1;
				e.dest->path = v;
			}
		}
	}


}

template<class T>
void Graph<T>::bellmanFordShortestPath(const T &orig) {
	for(auto & v : vertexSet) {
		v->dist = INF;
		v->path = NULL;
	}

	auto first = findVertex(orig);
	first->dist = 0;

	for (size_t i = 1; i < vertexSet.size(); i++) {
		for (auto & v : vertexSet) {
			for (auto & e : v->adj) {
				if (e.dest->dist > v->dist + e.weight) {
					e.dest->dist = v->dist + e.weight;
					e.dest->path = v;
				}
			}
		}
	}

	for (auto & v : vertexSet) {
		for (auto & e : v->adj) {
			if (e.dest->dist > v->dist + e.weight) {
				std::cout << "There are cycles of negative weight"<< std::endl;
			}
		}
	}
}


/**************** All Pairs Shortest Path  ***************/

template<class T>
void Graph<T>::floydWarshallShortestPath() {
	// TODO
}

template<class T>
vector<T> Graph<T>::getfloydWarshallPath(const T &orig, const T &dest) const{
	vector<T> res;
	// TODO
	return res;
}


#endif /* GRAPH_H_ */
