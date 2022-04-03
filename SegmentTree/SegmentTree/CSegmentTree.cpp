#include "CSegmentTree.h"
#include "Const.h"

CSegmentTree::CSegmentTree(std::istream& input, std::ostream& output, const int n, const std::vector<int> arr)
	: m_input(input)
	, m_output(output)
	, m_count(n)
	, m_array(arr)
{
}


void CSegmentTree::BuildTree(int v, int l, int r)
{
	if (l == r) 
	{
		m_tree[v] = m_array[l];    //сумма отрезка из одного элемента равна этому элементу
	}
	else
	{
		int mid = l + (r - l) / 2;
		CSegmentTree::BuildTree(v * 2 + 1, l, mid);
		CSegmentTree::BuildTree(v * 2 + 2, mid + 1, r);
		m_tree[v] = m_tree[v * 2] + m_tree[v * 2 + 1];
	}
}

void CSegmentTree::HandleCommand()
{
	std::string commandLine;
	while (std::getline(m_input, commandLine))
	{
		std::istringstream ist(commandLine);
		std::string commandName;
		ist >> commandName;

		std::vector<int> numbers = GetNumbersFromStream(ist);

		if (commandName == ADD_COMMAND)
		{

		}
		else if (commandName == RSQ_COMMAND)
		{

		}
		else if (commandName == ADDINT_COMMAND)
		{

		}
		else if (commandName == UPDATE_COMMAND)
		{

		}
		else if (commandName == RMQ_COMMAND)
		{

		}
		else
		{
			m_output << ERROR_UNKNOWN_COMMAND << std::endl;
		}
	}
}

void CSegmentTree::PrintInfo() {}

void CSegmentTree::Add(int index, long value) {}

void CSegmentTree::Rsq(int index_begin, int index_end) {}

void CSegmentTree::AddInt(int index_begin, int index_end, long value) {}

void CSegmentTree::Update(int index_begin, int index_end, long value) {}

void CSegmentTree::Rmq(int index_begin, int index_end) {}


std::vector<int> CSegmentTree::GetNumbersFromStream(std::istringstream& iss)
{
	std::vector<int> numbers;
	numbers.assign(std::istream_iterator<int>(iss), std::istream_iterator<int>());
	return numbers;
}
