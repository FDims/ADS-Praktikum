#include "KruskalMST.h"

/**
 * Erstellt einen MST zum Graph G mit dem Kruskal Algorithmus
 *
 * \param[in]  G		Kantengewichteter-Graph
 */
KruskalMST::KruskalMST(EdgeWeightedGraph G)
{
	treeID.resize(G.getV());
	std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> pq;
	std::vector<Edge> e = G.edges();			//kanten von G.
	for (int i = 0; i < e.size(); i++)
		pq.push(e[i]);							//jede Knote bildet ein eigener baum.
	for (int i = 0; i < G.getV(); i++)
		treeID[i] = i;

	while (!pq.empty()) {
		Edge e = pq.top();
		pq.pop();
		int v = e.either();
		int w = e.other(v);

		if (treeID[v] != treeID[w]) {				//v und w zu unterschiedlichen Baeumen gehoert, keine Zykel.
			mst.push_back(e);
			int treeID_w = treeID[w];
			for (int i = 0; i < G.getV(); i++) {	//Baum von v und w angleichen
				if (treeID[i] == treeID_w)
					treeID[i] = treeID[v];
			}
		}

	}
}

/**
 * Gibt alle Kanten vom MST zurueck
 *
 * \return Vektor mit Kanten des MST
 */
std::vector<Edge> KruskalMST::edges() const
{
	
	return this->mst;
}

/**
 * Gibt die Summe aller Gewichte im MST zurueck
 *
 * \return Summe der Gewichte im MST
 */
double KruskalMST::weight() const
{
	std::vector<Edge> mst1 = edges();
	double res = 0.0;
	for (int i = 0; i < mst1.size(); i++) {
		res += mst1[i].weight();
	}
	return res;
}

void KruskalMST::print() const {
	bool a = true;
	for (int i = 0; i < mst.size(); i++) {
		a = true;
		std::cout << std::endl;
		for (int k = 0; k < mst.size(); k++) {
			if (mst[k].either() == i) {
				if (a) {
					std::cout << i << " -> " << mst[k].other(i) << " [" << mst[k].weight() << "]";
					a = false;
				}
				else
					std::cout << " -> " << mst[k].other(i) << " [" << mst[k].weight() << "]";

			}
		}
	}
}
