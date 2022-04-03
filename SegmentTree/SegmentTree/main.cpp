#include <iostream>
#include <fstream>
#include "CSegmentTree.h"
#include "Const.h"

std::vector<int> getArr(std::string line, int n)
{
	std::vector<int> arr;

	std::istringstream ist(line);
	std::string element;

	for (int i = 0; i < n; i++)
	{
		ist >> element;
		arr.push_back(std::stoi(element));
	}
	return arr;
}

int main(int argc, char* argv[])
{
	int parametersNumber = argc;

	if (parametersNumber != 2)
	{
		std::cout << ERROR_INVALID_ARGUMENTS << std::endl;
		return 1;
	}

	std::string fileName = argv[1];

	std::ifstream fin(fileName);

	if (!fin.is_open())
	{
		std::cout << ERROR_FAILED_OPEN_FILE << std::endl;
		return 1;
	}

	std::string nLine;
	std::getline(fin, nLine);
	int n = std::stoi(nLine);

	std::string arrLine;
	std::getline(fin, arrLine);
	std::vector<int> arr = getArr(arrLine, n);

	CSegmentTree segmentTree(fin, std::cout, n, arr);
	segmentTree.BuildTree(1, 0, n - 1);
	segmentTree.HandleCommand();
	segmentTree.PrintInfo();

	return 0;
}
