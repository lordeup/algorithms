#include "CSegmentTree.h"
#include "Const.h"

CSegmentTree::CSegmentTree(std::istream& input, std::ostream& output, SegmentTreeData& treeData, const std::vector<int>& arr)
	: m_input(input)
	, m_output(output)
	, m_treeData(treeData)
	, m_array(arr)
{
	m_tree.resize(4 * (size_t)m_treeData.right);
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

		if (commandName == ADD_COMMAND)
		{
			if (size < 2)
			{
				throw InvalidArgumentError(ADD_COMMAND, "<index> <value>");
			}

			Add(root, numbers[0], numbers[1], tLeft, tRight);
		}
		else if (commandName == RSQ_COMMAND)
		{
			if (size < 2)
			{
				throw InvalidArgumentError(RSQ_COMMAND, "<index_begin> <index_end>");
			}

			long result = Rsq(root, numbers[0], numbers[1], tLeft, tRight);
			m_output << result << std::endl;
		}
		else if (commandName == ADDINT_COMMAND)
		{
			if (size < 3)
			{
				throw InvalidArgumentError(ADDINT_COMMAND, "<index_begin> <index_end> <value>");
			}

			AddInt(root, numbers[0], numbers[1], numbers[2], tLeft, tRight);
		}
		else if (commandName == UPDATE_COMMAND)
		{
			if (size < 3)
			{
				throw InvalidArgumentError(UPDATE_COMMAND, "<index_begin> <index_end> <value>");
			}

			Update(root, numbers[0], numbers[1], numbers[2], tLeft, tRight);
		}
		else if (commandName == RMQ_COMMAND)
		{
			if (size < 2)
			{
				throw InvalidArgumentError(RMQ_COMMAND, "<index_begin> <index_end>");
			}

			long result = Rmq(root, numbers[0], numbers[1], tLeft, tRight);
			m_output << result << std::endl;
		}
		else
		{
			m_output << ERROR_UNKNOWN_COMMAND << std::endl;
		}
	}
}

void CSegmentTree::PrintInfo()
{
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

void CSegmentTree::Add(long root, long index, long value, long tLeft, long tRight)
{
	if (tLeft == tRight)
	{
		m_tree[root] += value;
	}
	else
	{
		SegmentTreeData segmentTree = GetSegmentTreeData(root, tLeft, tRight);

		if (index <= segmentTree.middle)
		{
			Add(segmentTree.left, index, value, tLeft, segmentTree.middle);
		}
		else
		{
			Add(segmentTree.right, index, value, segmentTree.middle + 1, tRight);
		}

		m_tree[root] = std::max(m_tree[segmentTree.left], m_tree[segmentTree.right]);
	}
}

void CSegmentTree::AddInt(long root, long left, long right, long value, long tLeft, long tRight)
{
	if (left > right)
	{
		return;
	}

	if (left == tLeft && tRight == right)
	{
		m_tree[root] += value;
	}
	else
	{
		SegmentTreeData segmentTree = GetSegmentTreeData(root, left, right);

		AddInt(segmentTree.left, left, std::min(right, segmentTree.middle), value, tLeft, segmentTree.middle);
		AddInt(segmentTree.right, std::max(left, segmentTree.middle + 1), right, value, segmentTree.middle + 1, tRight);
	}
}

void CSegmentTree::Update(long root, long left, long right, long value, long tLeft, long tRight)
{
	if (left == tLeft && tRight == right)
	{
		//m_tree[root] = value;
	}
	else
	{
		SegmentTreeData segmentTree = GetSegmentTreeData(root, left, right);
	}
}

long CSegmentTree::Rsq(long root, long left, long right, long tLeft, long tRight)
{
	if (left == tLeft && right == tRight)
	{
		return m_tree[root];
	}
	else
	{
		SegmentTreeData segmentTree = GetSegmentTreeData(root, tLeft, tRight);

		if (right <= segmentTree.middle)
		{
			return Rsq(segmentTree.left, left, right, tLeft, segmentTree.middle);
		}
		else
		{
			if (left > segmentTree.middle)
			{
				return Rsq(segmentTree.right, left, right, segmentTree.middle + 1, tRight);
			}
			else
			{
				long elmentOne = Rsq(segmentTree.left, left, segmentTree.middle, tLeft, segmentTree.middle);
				long elmentTwo = Rsq(segmentTree.right, segmentTree.middle + 1, right, segmentTree.middle + 1, tRight);

				return elmentOne + elmentTwo;
			}
		}
	}
}

long CSegmentTree::Rmq(long root, long left, long right, long tLeft, long tRight)
{
	if (left == tLeft && right == tRight)
	{
		return m_tree[root];
	}
	else
	{
		SegmentTreeData segmentTree = GetSegmentTreeData(root, tLeft, tRight);

		if (right <= segmentTree.middle)
		{
			return Rmq(segmentTree.left, left, right, tLeft, segmentTree.middle);
		}
		else
		{
			if (left > segmentTree.middle)
			{
				return Rmq(segmentTree.right, left, right, segmentTree.middle + 1, tRight);
			}
			else
			{
				long elmentOne = Rmq(segmentTree.left, left, segmentTree.middle, tLeft, segmentTree.middle);
				long elmentTwo = Rmq(segmentTree.right, segmentTree.middle + 1, right, segmentTree.middle + 1, tRight);

				return std::max(elmentOne, elmentTwo);
			}
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
	treeData.middle = (left + right) / 2;
	treeData.left = 2 * root;
	treeData.right = 2 * root + 1;

	return treeData;
}
