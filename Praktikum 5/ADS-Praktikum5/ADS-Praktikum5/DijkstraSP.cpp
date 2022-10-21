#include <assert.h>
#include "DijkstraSP.h"

/**
 * Füge eine Kante mit minimalen Kosten hinzu, die von einem
 * Baumknoten zu einem Nicht-Baumknoten verläuft und deren
 * Ziel w dem Startknoten s am nächsten ist.
 *
 * \param[in]  G		Kantengewichteter-Digraph
 * \param[in]  v		Zielknoten
 */
void DijkstraSP::relax(EdgeWeightedDigraph G, int v)
{
	std::vector<DirectedEdge> edges = G[v];//adjazente Knoten zum Knoten v
	for (DirectedEdge e : edges) {
		int w = e.to(); //end Knoten von e
		if (distToVect[w] > distToVect[v] + e.weight()) {
			distToVect[w] = distToVect[v] + e.weight();
			edgeTo[w] = e;
			if (pq.contains(w))
				pq.change(w, distToVect[w]);
			else
				pq.push(w, distToVect[w]);
		}
	}
}

/**
 * Fuert den Dijkstra Algorithmus von s, im Graph G aus.
 *
 * \param[in]  G		Kantengewichteter-Digraph
 * \param[in]  s		Startknoten
 */
DijkstraSP::DijkstraSP(EdgeWeightedDigraph G, int s)
{
	distToVect.resize(G.getV());
	for (int v = 0; v < G.getV(); v++) {
		distToVect[v] = DBL_MAX;
	}
	distToVect[s] = 0.0;
	pq.push(s, 0.0);
	while (!pq.empty()) {
		int min_node = pq.top().value;
		pq.pop();
		relax(G, min_node);
	}
}

/**
 * Gibt die Distanz von s zum Knoten v zurueck
 *
 * \param[in]  v		Zielknoten
 * \return Summe der Gewichte auf dem Pfad zu v
 */
double DijkstraSP::distTo(int v) const
{
	
	return this->distToVect[v];
}

/**
 * Gibt zurueck ob es einen Pfad zu v von s aus gibt
 *
 * \param[in]  v		Zielknoten
 * \return true, wenn es einen Pfad von s nach v gibt, sonst false
 */
bool DijkstraSP::hasPathTo(int v) const
{
	
	if (distTo(v) < DBL_MAX)// nicht unendlich
		return true;
	else
		return false;
}

/**
 * Gibt den Pfad von s nach v als Vektor zurueck
 *
 * \param[in]  v		Zielknoten
 * \return Vektor mit allen Kanten des Pfades von s nach v
 */
std::vector<DirectedEdge> DijkstraSP::pathTo(int v) 
{
	std::vector<DirectedEdge> path;
	int from = 0;
	bool a = true;
	if (hasPathTo(v)) {
		for (std::map<int, DirectedEdge>::iterator it = edgeTo.begin(); it != edgeTo.end();) {
			if (edgeTo[it->first].to() == v) {
				v = edgeTo[it->first].from();
				path.push_back(edgeTo[it->first]);
				it = edgeTo.begin();
			}
			else
				it++;
		}
	}
	
	std::reverse(path.begin(), path.end());
	return path;
}
