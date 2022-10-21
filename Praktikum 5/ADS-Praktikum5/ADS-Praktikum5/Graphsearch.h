#pragma once
#include "EdgeWeightedDigraph.h"
#include "EdgeWeightedGraph.h"
#include <iostream>

namespace Graphsearch {

	/**
		* Fuehrt eine rekursive Tiefensuche im Graphen G,
		* ab dem Knoten v aus und markiert alle besuchten
		* Knoten in marked.
		* Alle besuchten Knoten werden ausgegeben.
		*
		* \param[in]	 G			Graph
		* \param[in]	 v			Startknoten
		* \param[in/out] marked		Bereits besuchte Knoten
		* \param[in/out] edgeTo		Vektor mit dem Nachfolgeknoten zu jedem Knoten
		*/
	void DFS_recursive(const EdgeWeightedGraph& G, int v, std::vector<bool>& marked, std::vector<int>& edgeTo) {


		marked[v] = true;
		std::vector<Edge> ad_list = G.getAdj(v);

		for (int i = 0; i < ad_list.size();i++) {
			int w = ad_list[i].other(v);
			if (!marked[w]) {
				std::cout << "-> ";
				std::cout << w;
				edgeTo[w] = v;
				DFS_recursive(G, w, marked, edgeTo);
			}
		}
		 
		 
	}

	/**
		* Fuehrt eine rekursive Tiefensuche im Graphen g, ab dem Knoten v aus.
		* Alle besuchten Knoten werden ausgegeben.
		* Starterfunktion zu DFS_recursive(EdgeWeigtedGraph, int, std::vector<bool>, std::vector<int>)
		*
		* \param[in]  G			Graph
		* \param[out] marked	Bereits besuchte Knoten
		* \param[out] edgeTo	Vektor mit dem Nachfolgeknoten zu jedem Knoten
		* \param[in]  v			Startknoten
		* \return	  true		Graph ist zusammenhaengend
		*			  false		Graph ist nicht zusammenhaengend
		*/

	bool DFS(const EdgeWeightedGraph& G, int v, std::vector<bool>& marked, std::vector<int>& edgeTo) {
		

		marked.assign(G.getV(), false);
		edgeTo.assign(G.getV(), -1);
	

	
		std::cout << v;
		DFS_recursive(G, v, marked, edgeTo);
		std::cout << std::endl;
		for (int i = 0; i < marked.size(); i++) {
			if (marked[i] == false)
				return false;
		}
		return true;
		
	}

	/**
		* Fuehrt eine iterative Breitensuche im Graphen g, ab dem Knoten v aus.
		* Alle besuchten Knoten werden ausgegeben.
		*
		* \param[in]  G			Graph
		* \param[in]  v			Startknoten
		* \param[out] marked	Gibt an welche Knoten besucht wurden bei der Suche
		* \param[out] edgeTo	Gibt den Nachfolgerknoten eines Knoten an
		* \return	  true		Graph ist zusammenhaengend
		*			  false		Graph ist nicht zusammenhaengend
		*/
	bool BFS(const EdgeWeightedGraph& G, int v, std::vector<bool>& marked, std::vector<int>& edgeTo) {
		marked.assign(G.getV(), false);
		edgeTo.assign(G.getV(), -1);
		


		std::queue<int> q;
		q.push(v);
		int tmp = v;
		std::cout<< v;
		while (!q.empty())
		{
			tmp = q.front(); 
			q.pop();
			if (marked[tmp])
				continue;
			if (tmp != v)
				std::cout << " -> " << tmp;
			marked[tmp] = true;
			std::vector<Edge> ad_list = G.getAdj(tmp);

			for (int i = 0; i < ad_list.size(); i++)
			{
				int w;
				ad_list[i].either() == tmp ? w = ad_list[i].other(tmp) : w = ad_list[i].either();
				if (!marked[w]) {
					if (edgeTo[w] == -1)
						edgeTo[w] = tmp;
					q.push(w);
				}
			}
		}
		std::cout << std::endl;
		for (int i = 0; i < marked.size(); i++) {
			if (!marked[i])
				return false;
		}
		return true;
	}

		
}
