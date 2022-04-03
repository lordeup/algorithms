#pragma once
#include <sstream>
#include <vector>

class CSegmentTree
{
public:
	CSegmentTree(std::istream& fin, std::ostream& fout, const int n, const std::vector<int> arr);

	void BuildTree(int v, int l, int r);
	void HandleCommand();
	void PrintInfo();

private:
	void Add(int index, long value); // ����������� � �������� Ak �������� d;
	void Rsq(int index_begin, int index_end); // ���������� ����� Ai + Ai+1 + � + Aj;
	void AddInt(int index_begin, int index_end, long value); // ����������� � ������� �� ��������� Ai, Ai+1, � Aj   �������� d;
	void Update(int index_begin, int index_end, long value); // ����������  �������  ��  ���������  Ai, Ai+1, � Aj  �������� v;
	void Rmq(int index_begin, int index_end); // ���������� �������� �� ��������� Ai, Ai+1, � Aj.

private:
	std::istream& m_input;
	std::ostream& m_output;

	const long m_count = 0;
	std::vector<long long> m_tree;
	const std::vector<int> m_array;
};

