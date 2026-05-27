#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <string>

using AdjMatrix = std::vector<std::vector<int>>;

AdjMatrix ReadAdjMatrixKeyboard(int n);
bool ReadAdjMatrixFromFile(const std::string& path, AdjMatrix& out);
bool WriteAdjMatrixToFile(const std::string& path, const AdjMatrix& a);

bool BuildAdjMatrixFromEdgeList(int n, int edgeCount, bool directed, AdjMatrix& out);

bool IsNonNegative(const AdjMatrix& a);
bool IsSymmetric(const AdjMatrix& a);
bool IsUnweightedLike(const AdjMatrix& a);
bool HasLoops(const AdjMatrix& a);
int CountEdges(const AdjMatrix& a, bool directed);

AdjMatrix BuildAdjList(const AdjMatrix& a);
bool IsConnectedUndirected(const AdjMatrix& adjList);

void PrintAdjMatrix(const AdjMatrix& a);
void PrintDegrees(const AdjMatrix& a, bool directed);
void PrintAdjListInfo(const AdjMatrix& g);
void PrintReport(const AdjMatrix& a);

void Dfs(int start, const AdjMatrix& graph, std::vector<bool>& visited, bool visualize);
void Bfs(int start, const AdjMatrix& graph, std::vector<bool>& visited, bool visualize);

#endif
