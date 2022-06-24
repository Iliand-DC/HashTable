#pragma once
#pragma once
#include <string>
#include <iostream>
#include"List.h"


class Polynom {
	int* letters;
	int size;
public:
	Polynom(std::string polynom) {
		size = polynom.size();
		letters = new int[size];

		for (size_t i = 0; i < size; i++)
			letters[i] = polynom[i];
	};

	~Polynom() {
		delete[] letters;
	};

	int hashPolynom() {
		int mult = letters[0];
		for (size_t i = 1; i < size - 1; i++) {

			mult = mult * 2 + letters[i];
		}
		return abs(mult);
	};
};



template <class T>
class HashTable {
	List<T>** mas;
	int tableSize;
	int count;
protected:
	int hash(T obj);
public:
	HashTable<T> rehash();
	HashTable(int size);
	~HashTable();
	void push(T obj);
	void pop(T obj);
	void print();
};

template<class T>
HashTable<T>::HashTable(int size) {
	size = abs(size);
	if (size == 0) size++;
	tableSize = size;

	mas = new List<T>*[tableSize];
	for (size_t i = 0; i < tableSize; i++)
		mas[i] = nullptr;
	count = 0;
}

template<class T>
HashTable<T>::~HashTable() {
	for (size_t i = 0; i < tableSize; i++)
		delete mas[i];
	delete[] mas;
}

template<class T>
int HashTable<T>::hash(T obj) {
	Polynom example(obj);
	return example.hashPolynom() % tableSize;
}

template<class T>
void HashTable<T>::push(T obj) {
	int place = hash(obj);
	mas[place]->append(mas[place]->first,obj);
	count++;
}

template<class T>
void HashTable<T>::pop(T obj) {
	int place = hash(obj);
	mas[place] = mas[place]->remove(obj);
}

template<class T>
void HashTable<T>::print() {
	for (size_t i = 0; i < tableSize; i++) {
		std::cout << "\nНомер ячейки: " << i;
		if (mas[i] != nullptr) {
			mas[i]->show();
		}
		else std::cout << "\nПусто!";

	}
}

int findPrime(int tableSize)
{
	bool prime = true;
	while (1)
	{
		for (int i = 2; i < tableSize - 1; i++)
		{
			if (tableSize % i == 0) prime = false;
		}
		if (prime == false)
			tableSize++;
		else return tableSize;
	}
}


//template<class T>
//HashTable<T> HashTable<T>::rehash()
//{
//	int newSize = findPrime(tableSize * 2);
//	T line;
//	HashTable<T> newTable(newSize);
//	for (size_t i = 0; i < tableSize; i++)
//	{
//		std::ofstream stream = mas[i]->toStream(mas[i]);
//		while (getline(stream, line))
//		{
//			newTable.push(line);
//		}
//	}
//	return newTable;
//}