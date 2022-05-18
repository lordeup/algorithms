#include "CMaximumPath.h"

CMaximumPath::CMaximumPath(std::istream& input, std::ostream& output)
	: m_input(input)
	, m_output(output)
{
}

void CMaximumPath::ProcessingCommand()
{
	FillingData();
	BreadthFirstSearch(m_graph, m_data.start);
	PrintInfo();
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

void CMaximumPath::BreadthFirstSearch(Graph& graph, int start)
{
	m_weightsDistances.assign(graph.size(), EMPTY_VALUE);
	m_parents.assign(graph.size(), EMPTY_VALUE);

	std::deque<int> dequeEdge;

	dequeEdge.push_back(start);
	m_weightsDistances[start] = 0;

	while (!dequeEdge.empty())
	{
		int vertex = dequeEdge.front();
		dequeEdge.pop_front();

		for (auto& item : graph[vertex])
		{
			int endEdge = item.first;
			int weight = item.second;
			int newDistance = std::max(m_weightsDistances[endEdge], m_weightsDistances[vertex] + weight);

			if (m_weightsDistances[endEdge] < newDistance)
			{
				m_parents[endEdge] = vertex;
				m_weightsDistances[endEdge] = newDistance;

				auto it = std::find(dequeEdge.begin(), dequeEdge.end(), endEdge);

				if (it == dequeEdge.end())
				{
					dequeEdge.push_back(endEdge);
				}
			}
		}
	}
}

void CMaximumPath::PrintInfo()
{
	int finish = m_data.finish;
	int maxWeight = m_weightsDistances[finish];

	if (maxWeight != EMPTY_VALUE)
	{
		m_output << maxWeight << std::endl;
		std::vector<int> paths = GetPaths(m_parents, finish);

		std::copy(paths.begin(), paths.end() - 1, std::ostream_iterator<int>(m_output, " "));
		m_output << paths.back();
	}
	else
	{
		m_output << "No";
	}
}

std::vector<int> CMaximumPath::GetPaths(const std::vector<int>& data, int value)
{
	std::vector<int> result;
	int currentVertex = value;

	while (currentVertex != EMPTY_VALUE)
	{
		result.push_back(currentVertex);
		currentVertex = data[currentVertex];
	}

	std::reverse(result.begin(), result.end());

	return result;
}
