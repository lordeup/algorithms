#pragma once
#include <algorithm>
#include <deque>
#include <sstream>
#include <vector>
#include "Const.h"

using Edge = std::pair<int, int>;
using Graph = std::vector<std::vector<Edge>>;

const int EMPTY_VALUE = -1;

struct Data
{
	int sizeVertex{};	// количество вершин графа (3 ≤ N ≤ 2000)
	int sizeEdge{};		// количество дуг (3 ≤ M ≤ 200000)
	int start{};		// номер начальной вершины
	int finish{};		// номер конечной вершины
};

class CMaximumPath
{
public:
	CMaximumPath(std::istream& input, std::ostream& output);

	void ProcessingCommand();

private:
	void FillingData();
	void BreadthFirstSearch(Graph& graph, int start);
	void PrintInfo();
	std::vector<int> GetPaths(const std::vector<int>& data, int value);

private:
	std::istream& m_input;
	std::ostream& m_output;

	Data m_data;
	Graph m_graph;

	std::vector<int> m_weightsDistances;
	std::vector<int> m_parents;
};