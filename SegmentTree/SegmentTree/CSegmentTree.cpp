#include "CSegmentTree.h"
#include "Const.h"
#include <iostream>

CSegmentTree::CSegmentTree(std::istream& input, std::ostream& output, SegmentTreeData& treeData, const std::vector<int>& arr)
	: m_input(input)
	, m_output(output)
	, m_treeData(treeData)
	, m_array(arr)
{
	m_tree.resize(4 * m_array.size());
	m_marked.resize(m_tree.size());
}

void CSegmentTree::BuildTree()
{
	Build(m_treeData.root, m_treeData.left, m_treeData.right);
}

void CSegmentTree::HandleCommand()
{
	std::string commandLine;
	long root = m_treeData.root;
	long tLeft = m_treeData.left;
	long tRight = m_treeData.right;

	while (std::getline(m_input, commandLine))
	{
		std::istringstream ist(commandLine);
		std::string commandName;
		ist >> commandName;

		std::vector<long> numbers = GetNumbersFromStream(ist);
		size_t size = numbers.size();

		std::string log = commandLine;

		if (commandName == ADD_COMMAND)
		{
			if (size < 2)
			{
				throw InvalidArgumentError(ADD_COMMAND, "<index> <value>");
			}

			Add(root, tLeft, tRight, numbers[0], numbers[1]);
		}
		else if (commandName == RSQ_COMMAND)
		{
			if (size < 2)
			{
				throw InvalidArgumentError(RSQ_COMMAND, "<index_begin> <index_end>");
			}

			long result = Rsq(root, tLeft, tRight, numbers[0], numbers[1]);
			log.append(" " + std::to_string(result));
		}
		else if (commandName == ADDINT_COMMAND)
		{
			if (size < 3)
			{
				throw InvalidArgumentError(ADDINT_COMMAND, "<index_begin> <index_end> <value>");
			}

			AddInt(root, tLeft, tRight, numbers[0], numbers[1], numbers[2]);
		}
		else if (commandName == UPDATE_COMMAND)
		{
			if (size < 3)
			{
				throw InvalidArgumentError(UPDATE_COMMAND, "<index_begin> <index_end> <value>");
			}

			Update(root, tLeft, tRight, numbers[0], numbers[1], numbers[2]);
		}
		else if (commandName == RMQ_COMMAND)
		{
			if (size < 2)
			{
				throw InvalidArgumentError(RMQ_COMMAND, "<index_begin> <index_end>");
			}

			long result = Rmq(root, tLeft, tRight, numbers[0], numbers[1]);
			log.append(" " + std::to_string(result));
		}
		else
		{
			m_output << ERROR_UNKNOWN_COMMAND << std::endl;
		}
		m_logger.push_back(log);
	}
}

void CSegmentTree::PrintInfo()
{
	for (std::string log : m_logger) 
	{
		m_output << log << std::endl;
	}
}

void CSegmentTree::Build(long root, long left, long right)
{
	if (left == right)
	{
		m_tree[root] = m_array[left];
	}
	else
	{
		SegmentTreeData segmentTree = GetSegmentTreeData(root, left, right);

		Build(segmentTree.left, left, segmentTree.middle);
		Build(segmentTree.right, segmentTree.middle + 1, right);
		m_tree[root] = m_tree[segmentTree.left] + m_tree[segmentTree.right];
	}
}

void CSegmentTree::Add(long root, long tLeft, long tRight, long index, long value)
{
	if (tLeft == tRight)
	{
		m_tree[root] += value;
	}
	else
	{
		SegmentTreeData segmentTree = GetSegmentTreeData(root, tLeft, tRight);
		long middle = segmentTree.middle;

		if (index <= middle)
		{
			Add(segmentTree.left, tLeft, middle, index, value);
		}
		else
		{
			Add(segmentTree.right, middle + 1, tRight, index, value);
		}

		m_tree[root] = m_tree[segmentTree.left] + m_tree[segmentTree.right];
	}
}


void CSegmentTree::AddInt(long root, long tLeft, long tRight, long left, long right, long value)
{
	if (left == tLeft && tRight == right)
	{
	}
	else
	{
		SegmentTreeData segmentTree = GetSegmentTreeData(root, tLeft, tRight);
		long middle = segmentTree.middle;

		if (right <= middle)
		{
			AddInt(segmentTree.left, tLeft, middle, left, right, value);
		}
		else if (left > middle)
		{
			AddInt(segmentTree.right, middle + 1, tRight, left, right, value);
		}
		else
		{
			AddInt(segmentTree.left, tLeft, middle, left, middle, value);
			AddInt(segmentTree.right, middle + 1, tRight, middle + 1, right, value);
		}
	}
	
	m_tree[root] += value * (right - left + 1);
}

void CSegmentTree::Update(long root, long tLeft, long tRight, long left, long right, long value)
{
	if (left > right)
	{
		return;
	}

	if (left == tLeft && tRight == right)
	{
		m_tree[root] = value;
		m_marked[root] = true;
	}
	else
	{
		SegmentTreeData segmentTree = GetSegmentTreeData(root, tLeft, tRight);
		long middle = segmentTree.middle;

		PushValue(root);

		Update(segmentTree.left, tLeft, middle, left, std::min(right, middle), value);
		Update(segmentTree.right, middle + 1, tRight, std::max(left, middle + 1), right, value);
	}
}

void CSegmentTree::PushValue(long root)
{
	long leftIndex = GetLeftIndex(root);
	long rightIndex = GetRightIndex(root);

	if (m_marked[root])
	{
		m_tree[leftIndex] = m_tree[rightIndex] = m_tree[root];
		m_marked[leftIndex] = m_marked[rightIndex] = true;
		m_marked[root] = false;
	}
}

long CSegmentTree::Rsq(long root, long tLeft, long tRight, long left, long right)
{
	if (left > right)
	{
		return 0;
	}

	if (left == tLeft && right == tRight)
	{
		return m_tree[root];
	}

	SegmentTreeData segmentTree = GetSegmentTreeData(root, tLeft, tRight);
	long middle = segmentTree.middle;

	long elmentOne = Rsq(segmentTree.left, tLeft, middle, left, std::min(right, middle));
	long elmentTwo = Rsq(segmentTree.right, middle + 1, tRight, std::max(left, middle + 1), right);

	return elmentOne + elmentTwo;
}

long CSegmentTree::Rmq(long root, long tLeft, long tRight, long left, long right)
{
	if (left > tRight || tLeft > right)
	{
		return INT_MAX;
	}

	if (tLeft >= left && tRight <= right)
	{
		return m_tree[root];
	}

	SegmentTreeData segmentTree = GetSegmentTreeData(root, tLeft, tRight);
	long middle = segmentTree.middle;

	long elmentOne = Rmq(segmentTree.left, tLeft, middle, left, right);
	long elmentTwo = Rmq(segmentTree.right, middle + 1, tRight, left, right);

	return std::min(elmentOne, elmentTwo);
}

std::vector<long> CSegmentTree::GetNumbersFromStream(std::istringstream& iss)
{
	std::vector<long> numbers;
	numbers.assign(std::istream_iterator<long>(iss), std::istream_iterator<long>());
	return numbers;
}

SegmentTreeData CSegmentTree::GetSegmentTreeData(long root, long left, long right)
{
	SegmentTreeData treeData;

	treeData.root = root;
	treeData.middle = (left + right) / 2;
	treeData.left = GetLeftIndex(root);
	treeData.right = GetRightIndex(root);

	return treeData;
}

long CSegmentTree::GetLeftIndex(long root)
{
	return 2 * root;
}

long CSegmentTree::GetRightIndex(long root)
{
	return 2 * root + 1;
}
