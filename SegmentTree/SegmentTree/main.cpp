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
		CSegmentTree segmentTree(fileInput, fileOutput, treeData, data);
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
