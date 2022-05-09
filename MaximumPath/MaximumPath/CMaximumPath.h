#pragma once
#include <algorithm>
#include <sstream>
#include <vector>
#include "Const.h"

struct ArcItem
{
	int start{};	// начало дуги
	int finish{};	// конец дуги
	int weight{};	// длина (вес)
};

struct Data
{
	int sizVertex{};	// количество вершин графа (3 ≤ N ≤ 2000)
	int sizeArc{};		// количество дуг (3 ≤ M ≤ 200000)
	int start{};		// номер начальной вершины
	int finish{};		// номер конечной вершины
	std::vector<ArcItem> items;
};

class CMaximumPath
{
public:
	CMaximumPath(std::istream& input, std::ostream& output);

	void ProcessingCommand();

private:
	void FillingData();

private:
	std::istream& m_input;
	std::ostream& m_output;

	Data m_data;
};