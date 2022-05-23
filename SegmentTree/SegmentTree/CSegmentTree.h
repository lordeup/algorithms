#pragma once
#include <algorithm>
#include <sstream>
#include <vector>
#include "InvalidArgumentError.h"

struct SegmentTreeData
{
	long long root = 1;
	long long left{};
	long long right{};
	long long middle{};
};

class CSegmentTree
{
public:
	CSegmentTree(std::istream& input, std::ostream& output, SegmentTreeData& treeData, const std::vector<long long>& arr);

	void BuildTree();
	void HandleCommand();
	void PrintInfo();

private:
	void Build(long long root, long long left, long long right);

	void Add(long long root, long long tLeft, long long tRight, long long index, long long value);
	void AddInt(long long root, long long tLeft, long long tRight, long long left, long long right, long long value);

	long long Rsq(long long root, long long tLeft, long long tRight, long long left, long long right);

	std::vector<long long> GetNumbersFromStream(std::istringstream& iss);

	SegmentTreeData GetSegmentTreeData(long long root, long long left, long long right);
	long long GetLeftIndex(long long root);
	long long GetRightIndex(long long root);

private:
	std::istream& m_input;
	std::ostream& m_output;

	SegmentTreeData& m_treeData;
	std::vector<long long> m_tree;
	std::vector<long long> m_add;

	std::vector<std::string> m_logger;

	const std::vector<long long> m_array;
};

