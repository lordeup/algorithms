/*
	Дерево отрезков

	Задан массив целых чисел A0, A1, …, AN-1. Требуется построить по нему дерево отрезков и реализовать следующие операции:
	Add(k, d) - прибавление к элементу Ak величины d;
	Rsq(i, j) – нахождение суммы Ai + Ai+1 + … + Aj;
	AddInt(i, j, d) - прибавление к каждому из элементов Ai, Ai+1, … Aj   величины d;
	Update (i, j, v) – присвоение  каждому  из  элементов  Ai, Ai+1, … Aj  значения v;
	Rmq(i, j) – нахождение минимума из элементов Ai, Ai+1, … Aj.
	Ввод из файла INPUT.TXT. В первой строке задается N. Во второй строке содержатся элементы массива A0, A1, …, AN-1. Далее следуют команды Add(k, d) и Rsq(i, j) по одной в строке. 
	
	Формат команд:
	add <index> <value>
	rsq <index_begin> <index_end>
	addint <index_begin> <index_end> <value>
	update <index_begin> <index_end> <value>
	rmq <index_begin> <index_end>
	
	Вывод в файл OUTPUT.TXT. Команды Add, AddInt и Update должны просто выводиться в выходной поток, а результат команд Rsq и Rmq должен отображаться в виде:
	rsq <index_begin> <index_end> <result> или
	rmq <index_begin> <index_end> <result>.
	Примечание. Дерево отрезков строится либо по сумме, либо по минимуму. Должна быть реализована одна из операций AddInt или Update. 
	На тесте из n = 105 чисел и n = 105 команд программа должна работать почти мгновенно, так как сложность вычислений имеет оценку O(n log n).
*/


#include <iostream>
#include <fstream>
#include "CSegmentTree.h"
#include "Const.h"

std::vector<int> GetData(std::string line, size_t size)
{
	std::vector<int> arr(size + 1);
	std::istringstream ist(line);

	for (int i = 1; i <= size; i++)
	{
		ist >> arr[i];
	}
	return arr;
}

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		std::cerr << ERROR_INVALID_ARGUMENTS;
		return 1;
	}

	std::ifstream fileInput(argv[1]);
	std::ofstream fileOutput(argv[2]);

	if (!fileInput.is_open())
	{
		std::cerr << ERROR_FAILED_OPEN_FILE;
		return 1;
	}

	std::string nLine, arrLine;
	std::getline(fileInput, nLine);
	int size = std::stoi(nLine);

	std::getline(fileInput, arrLine);
	std::vector<int> data = GetData(arrLine, size);

	SegmentTreeData treeData;
	treeData.root = 1;
	treeData.left = 1;
	treeData.right = size;

	try
	{
		CSegmentTree segmentTree(fileInput, std::cout, treeData, data);
		segmentTree.BuildTree();
		segmentTree.HandleCommand();
		segmentTree.PrintInfo();
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}
