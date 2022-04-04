#include <iostream>
#include <fstream>
#include "CSegmentTree.h"
#include "Const.h"

std::vector<int> getArr(std::string line, size_t size)
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

	std::string nLine;
	std::getline(fileInput, nLine);
	int size = std::stoi(nLine);

	std::string arrLine;
	std::getline(fileInput, arrLine);
	std::vector<int> arr = getArr(arrLine, size);

	CSegmentTree segmentTree(fileInput, fileOutput, size, arr);
	segmentTree.BuildTree(1, 1, size);
	segmentTree.HandleCommand();
	segmentTree.PrintInfo();

	return 0;
}
