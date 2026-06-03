#ifndef GRAPH_HIGH_H
#define GRAPH_HIGH_H

#include "../graph/graph.h"

// Запуск об'єднаних лабораторних 27-30 (Дейкстра, Беллман-Форд, Флойд-Воршалл, A*)
void RunHighLabs();

void RunHighDijkstra(const AdjMatrix& graph);
void RunHighBellmanFord(const AdjMatrix& graph);
void RunHighFloydWarshall(const AdjMatrix& graph);
void RunHighAStar(const AdjMatrix& graph);

#endif // GRAPH_HIGH_H
