#include <cstdio>
#include "graphviewer.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>


void exercicio1();
void exercicio2();
void exercicio3();


void exercicio1()
{
	GraphViewer *gv = new GraphViewer(600, 600, true);
	gv->rearrange();
	gv->setBackground("background.jpg");
	gv->createWindow(600, 600);
	gv->defineVertexColor("blue");
	gv->defineEdgeColor("black");

	gv->addNode(0);
	gv->addNode(1);

	gv->addEdge(0,0,1,EdgeType::DIRECTED);

	gv->setVertexLabel(1, "No de Chegada");

	gv->setEdgeLabel(0, "Primeira Aresta");

	gv->setVertexColor(1, "red");

	gv->setEdgeColor(0, "yellow");

	getchar();
	gv->closeWindow();
}

void exercicio2()
{
	GraphViewer *gv = new GraphViewer(600, 600, false);
	gv->createWindow(600, 600);
	gv->rearrange();
	gv->defineVertexColor("blue");
	gv->defineEdgeColor("black");

	gv->addNode( 0,  300, 50);
	gv->addNode( 1,  318, 58);
	gv->addNode( 2,  325,  75);
	gv->addNode( 3,  318,  93);
	gv->addNode( 4,  300,  100);
	gv->addNode( 5,  282,  93);
	gv->addNode( 6,  275,  75);
	gv->addNode( 7,  282,  58);
	gv->addNode( 8,  150,  200);
	gv->addNode( 9,  300,  200);
	gv->addNode( 14,  340,  375);
	gv->addNode( 11,  300,  400);
	gv->addNode( 12,  200,  550);
	gv->addNode( 13,  400,  550);

	gv->addEdge( 0, 0, 1, EdgeType::UNDIRECTED);
	gv->addEdge( 1, 1, 2, EdgeType::UNDIRECTED);
	gv->addEdge( 2, 2, 3, EdgeType::UNDIRECTED);
	gv->addEdge( 3, 3, 4, EdgeType::UNDIRECTED);
	gv->addEdge( 4, 4, 5, EdgeType::UNDIRECTED);
	gv->addEdge( 5, 5, 6, EdgeType::UNDIRECTED);
	gv->addEdge( 6, 6, 7, EdgeType::UNDIRECTED);
	gv->addEdge( 7, 7, 0, EdgeType::UNDIRECTED);
	gv->addEdge( 8, 4, 9, EdgeType::UNDIRECTED);
	gv->addEdge( 9, 9, 8, EdgeType::UNDIRECTED);
	gv->addEdge( 10, 9, 14, EdgeType::UNDIRECTED);
	gv->addEdge( 11, 9, 11, EdgeType::UNDIRECTED);
	gv->addEdge( 12, 11, 12, EdgeType::UNDIRECTED);
	gv->addEdge( 13, 11, 13, EdgeType::UNDIRECTED);

	int lastNode = 14;
	while(true){
		for (int i = 1; i < 40; i++) {
			Sleep(10);
			gv->removeNode(lastNode);
			gv->rearrange();
			gv->addNode(++lastNode, 340 - i, 375 + i);
			gv->addEdge(10, 9, lastNode, EdgeType::UNDIRECTED);
		}

		for (int i = 0; i < 40; i++) {
			Sleep(10);
			gv->removeNode(lastNode);
			gv->rearrange();
			gv->addNode(++lastNode, 301 + i, 414 - i);
			gv->addEdge(10, 9, lastNode, EdgeType::UNDIRECTED);
		}
}



	getchar();
	gv->closeWindow();
}

void exercicio3()
{
	GraphViewer *gv = new GraphViewer(600, 600, false);
	gv->createWindow(600, 600);
	gv->rearrange();
	gv->defineVertexColor("blue");
	gv->defineEdgeColor("black");

	ifstream nodes("nos.txt");
	string node;
	while (getline(nodes, node)) {
		istringstream nodeSS(node);
		int id, x, y;
		char a, b;

		nodeSS >> id >> a >> x >> b >> y;

		gv->addNode(id, x, y);

	}

	ifstream edges("arestas.txt");
	string edge;
	while (getline(edges, edge)) {
		istringstream edgeSS(edge);
		int id, source, dest;
		char a, b;

		edgeSS >> id >> a >> source >> b >> dest;
		gv->addEdge(id, source, dest, EdgeType::UNDIRECTED);
	}

	getchar();
	gv->closeWindow();
}


int main() {
	//exercicio1();
	//exercicio2();
	exercicio3();
	return 0;
}
