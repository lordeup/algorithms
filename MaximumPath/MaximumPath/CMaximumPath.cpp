#include "CMaximumPath.h"

CMaximumPath::CMaximumPath(std::istream& input, std::ostream& output)
	: m_input(input)
	, m_output(output)
{
}

void CMaximumPath::ProcessingCommand()
{
	FillingData();
}

void CMaximumPath::FillingData()
{
	m_input >> m_data.sizVertex >> m_data.sizeArc >> m_data.start >> m_data.finish;

	for (size_t i = 0; i < m_data.sizeArc; ++i)
	{
		ArcItem item;
		m_input >> item.start >> item.finish >> item.weight;
		m_data.items.push_back(item);
	}
}
