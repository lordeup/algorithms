#include "CMaximumPath.h"

CMaximumPath::CMaximumPath(std::istream& input, std::ostream& output)
	: m_input(input)
	, m_output(output)
{
}

void CMaximumPath::ProcessingCommand()
{
	FillingData();
	BreadthFirstSearch(m_graph, m_data.start, m_data.finish);
}

void CMaximumPath::FillingData()
{
	m_input >> m_data.sizeVertex >> m_data.sizeEdge >> m_data.start >> m_data.finish;

	m_graph.resize((size_t)m_data.sizeEdge + 1);

	for (size_t i = 0; i < m_graph.size(); ++i)
	{
		int beginEdge, endEdge, weight;
		m_input >> beginEdge >> endEdge >> weight;
		m_graph[beginEdge].emplace_back(endEdge, weight);
	}
}

void CMaximumPath::BreadthFirstSearch(Graph& graph, int start, int finish)
{
	const int initialValue = -1;
	std::vector<int> distances(graph.size(), initialValue);
	std::vector<int> paths(graph.size(), initialValue);
	std::queue<int> queueEdge;

	queueEdge.push(start);
	distances[start] = 0;

	while (!queueEdge.empty())
	{
		int vertex = queueEdge.front();
		queueEdge.pop();

		for (auto& item: graph[vertex])
		{
			int endEdge = item.first;
			int weight = item.second;

			if (distances[endEdge] == initialValue)
			{
				distances[endEdge] = distances[vertex] + 1;
				paths[endEdge] = vertex;
				queueEdge.push(endEdge);
			}
		}
	}

	std::vector<int> ans;
	int curr = finish;
	while (curr != -1)
	{
		ans.push_back(curr);
		curr = paths[curr];
	}

	reverse(ans.begin(), ans.end());


	int g = 0;
}
