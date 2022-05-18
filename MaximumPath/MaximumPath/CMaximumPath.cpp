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

	m_output << m_weightsDistances[m_data.finish] << std::endl;

	PrintInfo(m_data.finish);
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

	m_weightsDistances.assign(graph.size(), initialValue);
	m_parents.assign(graph.size(), initialValue);

	std::vector<bool> inque(graph.size(), false);

	std::queue<int> queueEdge;
	//std::vector<std::queue<int>> queues(graph.size());

	queueEdge.push(start);
	//queues[0].push(start);
	m_weightsDistances[start] = 0;
	m_parents[start] = start;
	inque[start] = true;

	while (!queueEdge.empty())
	{
		int vertex = queueEdge.front();
		queueEdge.pop();
		inque[vertex] = false;

		for (auto& item : graph[vertex])
		{
			int endEdge = item.first;
			int weight = item.second;
			int newDistance = std::max(m_weightsDistances[endEdge], m_weightsDistances[vertex] + weight);
			//int newDistance = weightsDistances[vertex] + weight;

			if (m_weightsDistances[endEdge] < newDistance)
			{
				m_parents[endEdge] = vertex;
				m_weightsDistances[endEdge] = newDistance;

				if (!inque[endEdge])
				{
					queueEdge.push(endEdge);
					inque[endEdge] = true;
				}
			}
		}
	}

	//std::vector<int> ans;
	//int curr = finish;
	//while (curr != -1)
	//{
	//	ans.push_back(curr);
	//	curr = parents[curr];
	//}

	//reverse(ans.begin(), ans.end());

	//for (size_t i = 0; i < graph.size(); ++i)
	//{
	//	while (!queues[i].empty())
	//	{
	//		int vertex = queues[i].front();
	//		queues[i].pop();

	//		if (weightsDistances[vertex] > i)
	//		{
	//			continue;
	//		}
	//			
	//		for (auto& item : graph[vertex])
	//		{
	//			int endEdge = item.first;
	//			int newDistance = std::max(weightsDistances[endEdge], weightsDistances[vertex] + item.second);

	//			if (weightsDistances[endEdge] < newDistance)
	//			{
	//				weightsDistances[endEdge] = newDistance;
	//				// TODO
	//				int h = weightsDistances[endEdge];
	//				queues[endEdge].push(endEdge);
	//			}
	//		}
	//	}
	//}


	int g = 0;
}

void CMaximumPath::PrintInfo(int value)
{
	if (m_parents[value] != value) 
	{
		PrintInfo(m_parents[value]);
	}
	m_output << value << ' ';
	//m_output << "No" << std::endl;
}
