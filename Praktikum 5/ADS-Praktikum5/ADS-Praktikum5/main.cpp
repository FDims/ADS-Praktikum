#define CATCH_CONFIG_RUNNER
#include "catch.h"
#include <iostream>
#include "EdgeWeightedGraph.h"
#include "PrimMST.h"
#include "Graphsearch.h"
#include "KruskalMST.h"
#include "DijkstraSP.h"
using namespace std;

int main() {
	// Starte Unit-Tests
	Catch::Session().run();
	

	//------------------------------------------------------------------------
	// 1. Ausgabe eines Graphen als Adjazenzliste implementieren
	//------------------------------------------------------------------------
	


	//------------------------------------------------------------------------
	// 2. Suche in Graphen
	//------------------------------------------------------------------------
	// Verwenden Sie hierfür die Vorlagen in Graphsearch.h
	//
	// Beispielaufruf der Tiefensuche: 
	// std::vector<bool> marked;
	// std::vector<int>  edgeTo;
	// bool connected = Graphsearch::DFS(G1, start, marked, edgeTo);



	//------------------------------------------------------------------------
	// 3. Minimaler Spannbaum mit Prim und Kruskal
	//------------------------------------------------------------------------
	// Vorlage für Prim ist die Klasse PrimMST (PrimMST.h + PrimMST.cpp)
	// Vorlage für Kruskal ist die Klasse KruskalMST (KruskalMST.h + KruskalMST.cpp)
	//
	// Beispielaufruf von Prim:
	// PrimMST prim(G, 0);



	//------------------------------------------------------------------------
	// 4. Kuerzeste Wege mit Dijkstra
	//------------------------------------------------------------------------
	// Beispielaufruf von Dijkstra
	//
	// EdgeWeightedDigraph G1_directed("graph1.txt");
	// Dijkstra dijkstra(G1_directed, start);
	// path = dijkstra.pathTo(target);



	//------------------------------------------------------------------------
	// 5. Menü für Benutzereingaben
	//------------------------------------------------------------------------
	// Alle Funktionalitäten aus der Aufgabenstellung muessen umgesetzt werden
	cout << "Praktikum 5: Graphenalgorihtmen: " << endl << endl;
	int eingabe, g, s, z;
	EdgeWeightedGraph G(0);
	EdgeWeightedDigraph dG(0);
	while (true) {
		cout << "Menu :" << endl
			<< "1) Graph einlesen" << endl
			<< "2) Tiefensuche" << endl
			<< "3) Breitensuche" << endl
			<< "4) MST nach Prim (eingabe: Startknoten)" << endl
			<< "5) MST nach Kruskal" << endl
			<< "6) Kuerzeste Wege nach Dijkstra (Eingabe: Startknoten)" << endl
			<< "7) Ausgabe der Adjazenzliste" << endl
			<< "8) Program beenden" << endl
			<< "weiter mit beliebiger Eingabe..." << endl
			<< "?> ";
		cin >> eingabe;
		if (eingabe == 1) {
			cout << "Welche Graph-Datei möchten Sie einlesen ?" << endl
				<< "1) graph1.txt" << endl
				<< "2) graph2.txt" << endl
				<< "3) graph3.txt" << endl
				<< "?>";
			cin.ignore();
			cin >> g;
			if (g == 1) {
				G = EdgeWeightedGraph("graph1.txt");
				dG = EdgeWeightedDigraph("graph1.txt");
			}
			if (g == 2) {
				G = EdgeWeightedGraph("graph2.txt");
				dG = EdgeWeightedDigraph("graph2.txt");
			}
			if (g == 3) {
				G = EdgeWeightedGraph("graph3.txt");
				dG = EdgeWeightedDigraph("graph3.txt");
			}
			cout << "Graph eingelesen.";
			cout << endl << endl;

		}
		else if (eingabe == 2) {
			int v = 0;
			std::vector<bool>marked;
			std::vector<int>edgeTo;
			bool result;
			cout << "Tiefensuche (Depth-First-Search (DFS)) - Startknoten: " << v << endl
				<< "Besuchreihenfolge: " << endl;
			result = Graphsearch::DFS(G, v, marked, edgeTo);
			cout << endl << endl << "EdgeTo_Array: " << endl;
			for (int i = 0; i < edgeTo.size(); i++) {
				cout << i << " -> " << edgeTo[i];
				if (i == v)
					cout << " (Startknoten)";
				cout << endl;
			}
			cout << endl;
			cout << endl << endl << "Marked_Array: " << endl;
			for (int i = 0; i < marked.size(); i++) {
				cout << i << " -> " << marked[i];
				if (i == v)
					cout << " (Startknoten)";
				cout << endl;
			}
			if (result)
				cout << "Graph ist zusammenhaengend.";
			else
				cout << "Graph ist nicht zusammenhaengend.";
			cout << endl << endl;
		}
		else if (eingabe == 3) {
			int v = 5;
			std::vector<bool>marked;
			std::vector<int>edgeTo;
			bool result;
			cout << "Tiefensuche (Depth-First-Search (DFS)) - Startknoten: " << v << endl
				<< "Besuchreihenfolge: " << endl;
			result = Graphsearch::BFS(G, v, marked, edgeTo);
			cout << endl << endl << "EdgeTo_Array: " << endl;
			for (int i = 0; i < edgeTo.size(); i++) {
				cout << i << " -> " << edgeTo[i];
				if (i == v)
					cout << " (Startknoten)";
				cout << endl;
			}
			cout << endl;
			cout << endl << endl << "Marked_Array: " << endl;
			for (int i = 0; i < marked.size(); i++) {
				cout << i << " -> " << marked[i];
				if (i == v)
					cout << " (Startknoten)";
				cout << endl;
			}
			if (result)
				cout << "Graph ist zusammenhaengend.";
			else
				cout << "Graph ist nicht zusammenhaengend.";
			cout << endl << endl;
		}
		else if (eingabe == 4) {
			cin.ignore();
			cout << "Bitte Startknoten eingeben: " << endl
				<< "?> ";
			cin >> s;
			PrimMST prim(G, s);
			cout << endl << "Minimaler Spannbaum (MST) nach Prim: " << endl
				<< "Gewicht: " << prim.weight() << endl
				<< "Adjazentliste: " << endl;
			prim.print();
			cout << endl << endl;
		}
		else if (eingabe == 5) {
			KruskalMST kruskal(G);
			cout << endl << "Minimaler Spannbaum (MST) nach Kruskal: " << endl
				<< "Gewicht: " << kruskal.weight() << endl
				<< "Adjazentliste: " << endl;
			kruskal.print();
			cout << endl << endl;
		}
		else if (eingabe == 6) {
			cin.ignore();
			cout << "Bitte Startknoten eingeben: " << endl
				<< "?> ";
			cin >> s;
			cout << "Bitte Zielknoten eingeben: " << endl
				<< "?> ";
			cin >> z;
			dG.print();
			DijkstraSP dijkstra(dG, s);
			cout << endl << "Kuerzester Weg (Dijkstra) :" << endl
				<< "Start  : " << s << endl
				<< "Ziel   : " << z << endl
				<< "Pfad :";
			if (dijkstra.hasPathTo(z)) {
				vector<DirectedEdge> pfad = dijkstra.pathTo(z);
				cout << pfad[0].from();
				for (int i = 0; i < pfad.size(); i++) {
					cout << "[" << pfad[i].weight() << "] -> " << pfad[i].to();
				}
				cout << endl << "Kosten: " << dijkstra.distTo(z);
			}
			else
				cout << "Es gibt keinen Pfad von Start nach Ziel.";
			cout << endl << endl;
		}
		else if (eingabe == 7) {
			G.print();
			cout << endl << endl;
		}
		else if (eingabe == 8) {
			break;
			cout << endl << endl;
		}
	}

	system("PAUSE");
	return 0;
}