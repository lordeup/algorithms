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
	void Add(int index, long value); // прибавление к элементу Ak величины d;
	void Rsq(int index_begin, int index_end); // нахождение суммы Ai + Ai+1 + Е + Aj;
	void AddInt(int index_begin, int index_end, long value); // прибавление к каждому из элементов Ai, Ai+1, Е Aj   величины d;
	void Update(int index_begin, int index_end, long value); // присвоение  каждому  из  элементов  Ai, Ai+1, Е Aj  значени€ v;
	void Rmq(int index_begin, int index_end); // нахождение минимума из элементов Ai, Ai+1, Е Aj.

private:
	std::istream& m_input;
	std::ostream& m_output;

	const long m_count = 0;
	std::vector<long long> m_tree;
	const std::vector<int> m_array;
};

