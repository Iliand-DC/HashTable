#pragma once
#include <iostream>
#include <fstream>

template <class T>
struct DoubleList
{
private:
	T data;
	DoubleList* next;
	DoubleList* prev;
public:
	class Iterator
	{
		DoubleList<T>* m_node;
	public:
		Iterator(DoubleList<T>* node) :m_node(node) {};
		bool operator==(Iterator other)
		{
			return m_node == other.m_node;
		}
		bool operator!=(Iterator other)
		{
			return !operator==(other);
		}
		T operator*() { if (m_node) return m_node->data; }
		void operator++()
		{
			if (m_node!=nullptr)
			{
				m_node = m_node->next;
			}
		}
	};
	Iterator begin(DoubleList<T>*& head) { return Iterator(head); }
	Iterator end(DoubleList*& head)
	{
		DoubleList<T>* p = head;
		if (p != nullptr)
		{
			if (p)
			{
				while (p!= nullptr)
					p = p->next;
			}
			return Iterator(p);
		}
	}
	size_t size()
	{
		size_t s = 0;
		for (Iterator it = begin(); it != end(); ++it)
			++s;
		++s;
		return s;
	}
	void init(DoubleList*& head, T elem);
	bool isEmpty(DoubleList* head);

	void addToHead(DoubleList*& head, T value);
	void addAfterNode(DoubleList*& place, T value);
	void addToTail(DoubleList*& tail, T value);

	DoubleList<T>* replaceElement(DoubleList*& head, T elem);
	void deleteHead(DoubleList*& head);
	void deleteAfterNode(DoubleList*& place);
	void deleteTail(DoubleList*& tail);

	bool isElemInList(DoubleList* head, T elem);
	DoubleList* FindPlaceInList(DoubleList* head, T elem);

	void clearList(DoubleList*& head);

	void print(DoubleList* head);
	void reversePrint(DoubleList* tail);
	std::ofstream toStream(DoubleList* head);
};

template<class T>
void inline DoubleList<T>::init(DoubleList*& head, T elem)
{
	head = new DoubleList;
	head->next = nullptr;
	head->prev = nullptr;
	head->data = elem;
}

template<class T>
inline bool DoubleList<T>::isEmpty(DoubleList* head)
{
	return head == nullptr;
}



template<class T>
inline void DoubleList<T>::addToHead(DoubleList*& head, T value)
{
	DoubleList* add = new DoubleList;
	if (head != nullptr) {
		add->data = value;
		add->next = head;
		if (head != nullptr) head->prev = add;
		add->prev = nullptr;
		head = add;
		add = nullptr;
	}
	else init(head, value);
}

template<class T>
inline void DoubleList<T>::addAfterNode(DoubleList*& place, T value)
{
	DoubleList* add = new DoubleList;

	add->data = value;

	add->next = place->next;
	place->next->prev = add;

	place->next = add;
	add->prev = place;
	add = nullptr;
	delete add;
}

template<class T>
inline void DoubleList<T>::addToTail(DoubleList*& tail, T value)
{
	DoubleList* add = new DoubleList;

	add->data = value;
	add->prev = tail;
	tail->next = add;
	add->next = nullptr;
	tail = add;
	add = nullptr;
}



template<class T>
inline DoubleList<T>* DoubleList<T>::replaceElement(DoubleList*& head, T elem)
{
	DoubleList<T>* dop = isElemInList(head, elem);
	if (dop == head) dop = deleteHead(head);
	else deleteAfterNode(dop->prev);
	return head;
}

template<class T>
inline void DoubleList<T>::deleteHead(DoubleList*& head)
{
	if (!isEmpty(head))
	{
		DoubleList* del = head;

		if (head->nex != nullptr)
		{
			head = head->next;
			head->prev = nullptr;
		}

		head->prev = nullptr;
		del->next = nullptr;

		delete del;
		del = nullptr;
	}
}

template<class T>
inline void DoubleList<T>::deleteAfterNode(DoubleList*& place)
{
	if (place->next != nullptr)
	{
		DoubleList* del = place->next;

		place->next = del->next;
		if (del->next != nullptr) del->next->prev = place;

		del->next = nullptr;
		del->prev = nullptr;
		delete del;
		del = nullptr;
	}
}

template<class T>
inline void DoubleList<T>::deleteTail(DoubleList*& tail)
{
	if (tail != nullptr)
	{
		DoubleList* del = tail;
		if (tail->prev != nullptr)
		{
			tail = tail->prev;
			tail->next = nullptr;
		}
		del->prev = nullptr;

		delete del;
		del = nullptr;
	}
}



template<class T>
inline bool DoubleList<T>::isElemInList(DoubleList* head, T elem)
{
	bool find = false;

	while ((head->next != nullptr) && (!find))
	{
		if (head->data == elem) find = true;
		else head = head->next;
	}
	return find;
}

template<class T>
inline DoubleList<T>* DoubleList<T>::FindPlaceInList(DoubleList* head, T elem)
{
	while (head != nullptr || head->data != elem)
		head = head->next;

	DoubleList* place = head;

	return place;
}

template<class T>
inline void DoubleList<T>::clearList(DoubleList*& head)
{
	if (!isEmpty(head))
	{
		while (head->next != nullptr)
		{
			deleteAfterNode(head);
		}
		delete head;
		head = nullptr;
	}
}



template<class T>
inline void DoubleList<T>::print(DoubleList* head)
{
	while (head != nullptr)
	{
		std::cout << "\nЭлемент: " << head->data;
		head = head->next;
	}
}

template<class T>
inline void DoubleList<T>::reversePrint(DoubleList* tail)
{
	while (tail != nullptr)
	{
		std::cout << "\nЭлемент: " << tail->data;
		tail = tail->prev;
	}
}

template<class T>
inline std::ofstream DoubleList<T>::toStream(DoubleList* head)
{
	std::ofstream stream;
	while (head != nullptr)
	{
		stream << head->data<<"\n";
		head = head->next;
	}
	return stream;
}

