#pragma once
#include <string>
#include <iostream>
#include"DoubleList.h"


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
	DoubleList<T>** mas;
protected:
	int hash(T obj);
public:
	int tableSize;
	void rehash();
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

	mas = new DoubleList<T>*[tableSize];
	for (size_t i = 0; i < tableSize; i++)
		mas[i] = nullptr;
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
	mas[place]->addToHead(mas[place], obj);
}

template<class T>
void HashTable<T>::pop(T obj) {
	int place = hash(obj);
	mas[place] = mas[place]->replaceElement(mas[place], obj);
}

template<class T>
void HashTable<T>::print() {
	for (size_t i = 0; i < tableSize; i++) {
		std::cout << "\nНомер ячейки: " << i;
		mas[i]->print(mas[i]);
		if(mas[i]==nullptr) std::cout << "\nПусто!";

	}
}

int findPrime(int tableSize)
{
	for (int i = 2; i < tableSize; i++)
	{
		while (tableSize % i == 0)
		{
			tableSize++;
		}
	}
	return tableSize;
}


template<class T>
void HashTable<T>::rehash()
{
	int oldSize = tableSize;
	DoubleList<T>** t_mas = mas;
	
	tableSize = findPrime(tableSize * 2);
	mas = new DoubleList<T>*[tableSize];
	for (size_t i = 0; i < tableSize; i++)
		mas[i] = nullptr;
	for (size_t i = 0; i < oldSize; i++)
	{
		auto it = t_mas[i]->begin(t_mas[i]);
		while (it != t_mas[i]->end(t_mas[i]))
		{
			push(*it);
			++it;

		}
	}
	delete[] t_mas;
}