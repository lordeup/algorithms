/*
	4.2. Максимальный путь 2
	Имеется взвешенный ориентированный ациклический граф. Найти максимальный путь, используя поиск в ширину.
	Ввод из файла INPUT.TXT. Первая строка входного файла INPUT.TXT содержит 4 числа: N - количество вершин графа (3 ≤ N ≤ 2000), M – дуг (3 ≤ M ≤ 200000),
	A – номер начальной вершины и A – номер конечной вершины. В следующих M строках по 3 числа, задающих дуги: начало дуги, конец дуги, длина (вес).
	Вывод в файл OUTPUT.TXT. В первую строку вывести максимальную длину пути, во вторую строку через пробел – вершины максимального пути. 
	Если решений несколько, вывести любое из них. Если пути нет, выдать No.
	Пример
	Ввод
	4 5 1 3
	1 2 5
	1 4 7
	2 3 4
	4 2 2
	4 3 3
	Вывод
	13
	1 4 2 3
*/

#include <iostream>
#include <fstream>
#include "CMaximumPath.h"

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		std::cerr << ERROR_INVALID_ARGUMENTS << std::endl;
		return 1;
	}

	std::ifstream fileInput(argv[1]);
	std::ofstream fileOutput(argv[2]);

	if (!fileInput.is_open())
	{
		std::cerr << ERROR_FAILED_OPEN_FILE << std::endl;
		return 1;
	}

	CMaximumPath maximumPath(fileInput, std::cout);
	maximumPath.ProcessingCommand();
}
