#include "HashTable.h"

int main()
{
	setlocale(LC_ALL, "rus");

	int countElem = 0;
	std::cout << "Введите размер: ";
	std::cin >> countElem;

	HashTable<std::string> table(countElem);
	std::string example;
	for (size_t i = 0; i < countElem; i++)
	{
		std::cout << "Введите элемент: ";
		std::cin >> example;
		table.push(example);
	}
	table.print();
	table.rehash();
	table.print();
}