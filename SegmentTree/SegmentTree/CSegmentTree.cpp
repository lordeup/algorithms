#include "CSegmentTree.h"
#include "Const.h"

CSegmentTree::CSegmentTree(std::istream& input, std::ostream& output, const size_t size, const std::vector<int>& arr)
	: m_input(input)
	, m_output(output)
	, m_count(size)
	, m_array(arr)
{
	m_tree.resize(4 * m_count);
}


void CSegmentTree::BuildTree(int root, int left, int right)
{
	if (left == right)
	{
		m_tree[root] = m_array[left];    //сумма отрезка из одного элемента равна этому элементу
	}
	else
	{
		int middle = (left + right) / 2;
		int leftItemIndex = 2 * root;
		int rightItemIndex = 2 * root + 1;

		BuildTree(leftItemIndex, left, middle);
		BuildTree(rightItemIndex, middle + 1, right);
		m_tree[root] = m_tree[leftItemIndex] + m_tree[rightItemIndex];
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

void CSegmentTree::Rsq(int indexBegin, int indexEnd) {}

void CSegmentTree::AddInt(int indexBegin, int indexEnd, long value) {}

void CSegmentTree::Update(int indexBegin, int indexEnd, long value) {}

void CSegmentTree::Rmq(int indexBegin, int indexEnd) {}


std::vector<int> CSegmentTree::GetNumbersFromStream(std::istringstream& iss)
{
	std::vector<int> numbers;
	numbers.assign(std::istream_iterator<int>(iss), std::istream_iterator<int>());
	return numbers;
}
