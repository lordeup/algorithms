#include "CSegmentTree.h"
#include "Const.h"

CSegmentTree::CSegmentTree(std::istream& input, std::ostream& output, SegmentTreeData& treeData, const std::vector<int>& arr)
	: m_input(input)
	, m_output(output)
	, m_treeData(treeData)
	, m_array(arr)
{
	m_tree.resize(4 * m_array.size());
	m_add.resize(m_tree.size());
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
		else
		{
			log = ERROR_UNKNOWN_COMMAND + " " + commandName;
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
	m_tree[root] += value;
	if (tLeft + 1 < tRight)
	{
		SegmentTreeData segmentTree = GetSegmentTreeData(root, tLeft, tRight);
		long middle = segmentTree.middle;

		if (index < middle)
		{
			Add(segmentTree.left, tLeft, middle, index, value);
		}
		else
		{
			Add(segmentTree.right, middle, tRight, index, value);
		}
	}
}


void CSegmentTree::AddInt(long root, long tLeft, long tRight, long left, long right, long value)
{
	m_tree[root] += value * (right - left + 1);
	if (left == tLeft && tRight == right)
	{
		m_add[root] += value;
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
}

long CSegmentTree::Rsq(long root, long tLeft, long tRight, long left, long right)
{
	if (left == tLeft && right == tRight)
	{
		return m_tree[root];
	}
	else
	{
		SegmentTreeData segmentTree = GetSegmentTreeData(root, tLeft, tRight);
		long middle = segmentTree.middle;
		long h = m_add[root] * (right - left + 1);

		if (right <= middle)
		{
			return Rsq(segmentTree.left, tLeft, middle, left, right) + h;
		}
		else if (left > middle)
		{
			return Rsq(segmentTree.right, middle + 1, tRight, left, right) + h;
		}
		else
		{
			long elmentOne = Rsq(segmentTree.left, tLeft, middle, left, middle);
			long elmentTwo = Rsq(segmentTree.right, middle + 1, tRight, middle + 1, right);
			return elmentOne + elmentTwo + h;
		}
	}
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
