#pragma once
#include <algorithm>
#include <sstream>
#include <vector>
#include "InvalidArgumentError.h"

struct SegmentTreeData
{
	long root{};
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

	void Add(long root, long index, long value, long tLeft, long tRight);
	void AddInt(long root, long left, long right, long value, long tLeft, long tRight);

	void Update(long root, long left, long right, long value, long tLeft, long tRight);

	long Rsq(long root, long left, long right, long tLeft, long tRight);
	long Rmq(long root, long left, long right, long tLeft, long tRight);

	std::vector<long> GetNumbersFromStream(std::istringstream& iss);

	SegmentTreeData GetSegmentTreeData(long root, long left, long right);

private:
	std::istream& m_input;
	std::ostream& m_output;

	SegmentTreeData& m_treeData;
	std::vector<long> m_tree;
	const std::vector<int> m_array;
};

