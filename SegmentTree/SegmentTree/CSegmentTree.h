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
	void Add(int index, long value); // прибавление к элементу Ak величины d;
	void Rsq(int indexBegin, int indexEnd); // нахождение суммы Ai + Ai+1 + Е + Aj;
	void AddInt(int indexBegin, int indexEnd, long value); // прибавление к каждому из элементов Ai, Ai+1, Е Aj   величины d;
	void Update(int indexBegin, int indexEnd, long value); // присвоение  каждому  из  элементов  Ai, Ai+1, Е Aj  значени€ v;
	void Rmq(int indexBegin, int indexEnd); // нахождение минимума из элементов Ai, Ai+1, Е Aj.
	std::vector<int> GetNumbersFromStream(std::istringstream& iss);

private:
	std::istream& m_input;
	std::ostream& m_output;

	const size_t m_count = 0;
	std::vector<long long> m_tree;
	const std::vector<int> m_array;
};

