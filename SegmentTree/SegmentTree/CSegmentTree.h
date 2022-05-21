#pragma once
#include <algorithm>
#include <sstream>
#include <vector>
#include "InvalidArgumentError.h"

struct SegmentTreeData
{
	long root = 1;
	long left{};
	long right{};
	long middle{};
};

class CSegmentTree
{
public:
	CSegmentTree(std::istream& input, std::ostream& output, SegmentTreeData& treeData, const std::vector<int>& arr);

	void BuildTree();
	void HandleCommand();
	void PrintInfo();

private:
	void Build(long root, long left, long right);

	void Add(long root, long tLeft, long tRight, long index, long value);
	void AddInt(long root, long tLeft, long tRight, long left, long right, long value);

	long Rsq(long root, long tLeft, long tRight, long left, long right);

	std::vector<long> GetNumbersFromStream(std::istringstream& iss);

	SegmentTreeData GetSegmentTreeData(long root, long left, long right);
	long GetLeftIndex(long root);
	long GetRightIndex(long root);

private:
	std::istream& m_input;
	std::ostream& m_output;

	SegmentTreeData& m_treeData;
	std::vector<long> m_tree;
	std::vector<long> m_add;

	std::vector<std::string> m_logger;

	const std::vector<int> m_array;
};

