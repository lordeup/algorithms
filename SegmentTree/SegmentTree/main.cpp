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

	std::string nLine;
	std::getline(fileInput, nLine);
	int n = std::stoi(nLine);

	std::string arrLine;
	std::getline(fileInput, arrLine);
	std::vector<int> arr = getArr(arrLine, n);

	CSegmentTree segmentTree(fileInput, fileOutput, n, arr);
	segmentTree.BuildTree(1, 0, n - 1);
	segmentTree.HandleCommand();
	segmentTree.PrintInfo();

	return 0;
}
