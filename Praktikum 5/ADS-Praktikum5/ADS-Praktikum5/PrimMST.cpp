#include "PrimMST.h"

/**
 * Erstellt einen MST zum Graph G mit dem Prim Algorithmus
 *
 * \param[in]  G		Kantengewichteter-Graph
 * \param[in]  s		Startknoten
 */
PrimMST::PrimMST(EdgeWeightedGraph G, int s)
{
	marked.resize(G.getV(), false);
	visit(G, s);
	while (!pq.empty()) {
		Edge e = pq.top();		//Hole Kante mit geringstem Gewicht aus PQ
		pq.pop();				//delete geholte Kante
		int v = e.either();		//Knote 1 der Kante
		int w = e.other(v);		//Knote 2 der Kante

		//Ueberspringen falss beide Knote markiert, weil es ein Zykel bilden wird 
		if (marked[v] && marked[w])
			continue;

		mst.push_back(e);		//Fuege Kante e zum MST hinzu
								//Knote v und w zum MST hinzufuegen
		if (!marked[v]) visit(G, v);
		if (!marked[w]) visit(G, w);
	}
}

/**
 * Markiert Knoten v im Graph G als markiert und fuegt alle Nachbarn zur pq hinzu
 *
 * \param[in]  G		Kantengewichteter-Graph
 * \param[in]  v		Knoten im Graph G
 */
void PrimMST::visit(EdgeWeightedGraph G, int v)
{
	/*
	 * TODO
	 */
	//Knote als besucht markiert
	marked[v] = true;
	std::vector<Edge> edges = G[v]; //alle Kanten von v

	//unmarkierten Knoten in die PQ hinzufuegen
	for (int i = 0; i < edges.size(); i++) {
		if (!marked[edges[i].other(v)])
			pq.push(edges[i]);
	}
}

/**
 * Gibt alle Kanten vom MST zurueck
 *
 * \return Vektor mit Kanten des MST
 */
std::vector<Edge> PrimMST::edges() const
{
	
	return this->mst;
}

/**
 * Gibt die Summe aller Gewichte im MST zurueck
 *
 * \return Summe der Gewichte im MST
 */
double PrimMST::weight() const
{
	std::vector<Edge> mst1 = edges();
	double res = 0.0;
	for (int i = 0; i < mst1.size(); i++) {
		res += mst1[i].weight();
	}
	return res;
}

void PrimMST::print() const {
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