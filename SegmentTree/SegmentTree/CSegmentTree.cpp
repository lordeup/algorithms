#include "CSegmentTree.h"
#include "Const.h"

CSegmentTree::CSegmentTree(std::istream& input, std::ostream& output, SegmentTreeData& treeData, const std::vector<long long>& arr)
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
	long long root = m_treeData.root;
	long long tLeft = m_treeData.left;
	long long tRight = m_treeData.right;

	while (std::getline(m_input, commandLine))
	{
		std::istringstream ist(commandLine);
		std::string commandName;
		ist >> commandName;

		std::vector<long long> numbers = GetNumbersFromStream(ist);
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

			long long result = Rsq(root, tLeft, tRight, numbers[0], numbers[1]);
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

void CSegmentTree::Build(long long root, long long left, long long right)
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

void CSegmentTree::Add(long long root, long long tLeft, long long tRight, long long index, long long value)
{
	if (index < tLeft || tRight < index)
	{
		return;
	}

	m_tree[root] += value;

	if (tLeft == tRight)
	{
		return;
	}

	SegmentTreeData segmentTree = GetSegmentTreeData(root, tLeft, tRight);
	long long middle = segmentTree.middle;

	Add(segmentTree.left, tLeft, middle, index, value);
	Add(segmentTree.right, middle + 1, tRight, index, value);
}


void CSegmentTree::AddInt(long long root, long long tLeft, long long tRight, long long left, long long right, long long value)
{
	m_tree[root] += value * (right - left + 1);
	if (left == tLeft && tRight == right)
	{
		m_add[root] += value;
	}
	else
	{
		SegmentTreeData segmentTree = GetSegmentTreeData(root, tLeft, tRight);
		long long middle = segmentTree.middle;

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

long long CSegmentTree::Rsq(long long root, long long tLeft, long long tRight, long long left, long long right)
{
	if (left == tLeft && right == tRight)
	{
		return m_tree[root];
	}
	else
	{
		SegmentTreeData segmentTree = GetSegmentTreeData(root, tLeft, tRight);
		long long middle = segmentTree.middle;
		long long h = m_add[root] * (right - left + 1);

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
			long long elmentOne = Rsq(segmentTree.left, tLeft, middle, left, middle);
			long long elmentTwo = Rsq(segmentTree.right, middle + 1, tRight, middle + 1, right);
			return elmentOne + elmentTwo + h;
		}
	}
}

std::vector<long long> CSegmentTree::GetNumbersFromStream(std::istringstream& iss)
{
	std::vector<long long> numbers;
	numbers.assign(std::istream_iterator<long long>(iss), std::istream_iterator<long long>());
	return numbers;
}

SegmentTreeData CSegmentTree::GetSegmentTreeData(long long root, long long left, long long right)
{
	SegmentTreeData treeData;

	treeData.root = root;
	treeData.middle = (left + right) / 2;
	treeData.left = GetLeftIndex(root);
	treeData.right = GetRightIndex(root);

	return treeData;
}

long long CSegmentTree::GetLeftIndex(long long root)
{
	return 2 * root;
}

long long CSegmentTree::GetRightIndex(long long root)
{
	return 2 * root + 1;
}
