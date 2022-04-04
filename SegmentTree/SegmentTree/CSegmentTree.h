#pragma once
#include <algorithm>
#include <sstream>
#include <vector>

class CSegmentTree
{
public:
	CSegmentTree(std::istream& input, std::ostream& output, const size_t size, const std::vector<int>& arr);

	void BuildTree(int root, int left, int right);
	void HandleCommand();
	void PrintInfo();

private:
	void Add(int index, long value); // ����������� � �������� Ak �������� d;
	void Rsq(int indexBegin, int indexEnd); // ���������� ����� Ai + Ai+1 + � + Aj;
	void AddInt(int indexBegin, int indexEnd, long value); // ����������� � ������� �� ��������� Ai, Ai+1, � Aj   �������� d;
	void Update(int indexBegin, int indexEnd, long value); // ����������  �������  ��  ���������  Ai, Ai+1, � Aj  �������� v;
	void Rmq(int indexBegin, int indexEnd); // ���������� �������� �� ��������� Ai, Ai+1, � Aj.
	std::vector<int> GetNumbersFromStream(std::istringstream& iss);

private:
	std::istream& m_input;
	std::ostream& m_output;

	const size_t m_count = 0;
	std::vector<long long> m_tree;
	const std::vector<int> m_array;
};

