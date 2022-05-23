/*
	Генератор тестового файла для дерева отрезков

	На вход подаются: имя файла, размер дерева, кол-во команд и необязательный параметр максимальное значение для числа (если не передан, но присваивается размер дерева).
	Например: TestGenerator.exe inputTest.txt 100000 100000 15

	На выходе заполненный файл (который указали в "имя файла"), который можно использовать как входной файл для программы SegmentTree.exe
*/

#include <iostream>
#include <fstream>
#include "../SegmentTree/Const.h";

int main(int argc, char* argv[])
{
	if (argc < 4)
	{
		std::cerr << ERROR_INVALID_ARGUMENTS_TEST;
		return 1;
	}

	std::ofstream fileOutput(argv[1]);
	auto treeSize = std::stoi(argv[2]);
	auto commandLength = std::stoi(argv[3]);
	auto maxNumberValue = argc == 5 ? std::stoi(argv[4]) : treeSize;

	fileOutput << treeSize << std::endl;

	for (auto i = 0; i < treeSize; i++)
	{
		fileOutput << rand() % maxNumberValue + 1 << " ";
	}

	fileOutput << std::endl;

	for (auto i = 0; i < commandLength; i++)
	{
		auto firstIndex_ = rand() % treeSize + 1;
		auto secondIndex_ = rand() % treeSize + 1;

		auto firstIndex = std::min(firstIndex_, secondIndex_);
		auto secondIndex = std::max(firstIndex_, secondIndex_);

		auto value = rand() % maxNumberValue + 1;

		switch (rand() % 3)
		{
			case 0:
				fileOutput << ADD_COMMAND << " " << firstIndex << " " << value << std::endl;
				break;
			case 1:
				fileOutput << ADDINT_COMMAND << " " << firstIndex << " " << secondIndex << " " << value << std::endl;
				break;
			case 2:
				fileOutput << RSQ_COMMAND << " " << firstIndex << " " << secondIndex << std::endl;
				break;
			default:
				break;
		}
	}

	return 0;
}
