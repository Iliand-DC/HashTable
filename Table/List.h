#pragma once
#include <iostream>

template <class T>
struct Node
{
	T data;
	Node* next;
};

template<class T>
inline bool isEmpty(Node<T>* pNode)
{
	return pNode == nullptr;
}


template <class T>
class List
{
public:
	Node<T>* first;
	class Iterator
	{
		Node<T>* m_node;
	public:
		Iterator(Node<T>* node) :m_node(node) {};
		bool operator==(Iterator other)
		{
			return m_node == other.m_node;
		}
		bool operator!=(Iterator other)
		{
			return !operator==(other);
		}
		T operator*() { if (m_node) return m_node->data; }
		Node<T>* getNode() { if (m_node) return m_node; }
		void operator++()
		{
			if (m_node->next)
			{
				m_node = m_node->next;
			}
		}
	};
	List() :first(nullptr) {};
	List(const List<T>& head);
	void init(T elem);
	void append(Node<T>*& first, T data);
	void addAfterNode(Node<T>* p, T data);
	void deleteAfterNode(Node<T>* p);
	void remove();
	void show();
	Iterator begin() { return Iterator(first); }
	Iterator end()
	{
		Node<T>* p = first;
		if (p->next)
		{
			while (p->next != nullptr)
				p = p->next;
		}
		return Iterator(p);
	}
	size_t size()
	{
		size_t s = 0;
		for (Iterator it = begin(); it != end(); ++it)
			++s;
		++s;
		return s;
	}
	bool ListIsEmpty() { return first == nullptr; }
	void sort();
};

template<class T>
inline List<T>::List(const List<T>& head)
{
	first = head.first;
}

template<class T>
void List<T>::init(T elem)
{
	first = new Node<T>;
	first->next = nullptr;
	first->data = elem;
}

template<class T>
void List<T>::append(Node<T>*& first,T data)
{
	Node<T>* p = new Node<T>;
	if (first == nullptr)
	{
		init(data);
	}
	else
	{
		p->data = data;
		p->next = first;
		first = p;
		p = nullptr;
	}
}

template<class T>
void List<T>::addAfterNode(Node<T>* pNode, T data)
{
	if (pNode != nullptr)
	{
		Node<T>* p = new Node<T>;
		p->data = data;
		p->next = pNode->next;
		pNode->next = p;
	}
}

template<class T>
void List<T>::deleteAfterNode(Node<T>* pNode)
{
	if (!ListIsEmpty())
	{
		Node<T>* p = pNode->next;
		if (p != nullptr)
		{
			pNode->next = p->next;
			p->next = nullptr;
			delete p;
			p = nullptr;
		}
	}
}

template<class T>
void List<T>::show()
{
	if (!ListIsEmpty())
	{
		Node<T>* p = first;
		while (p != nullptr)
		{
			std::cout << p->data << ' ';
			p = p->next;
		}
	}
	std::cout << '\n';
}

template<class T>
void List<T>::sort()
{
	Node<T>* cur1 = first;
	Node<T>* cur2 = first;
	for (int i = 0; i < size(); i++)
	{
		for (int j = 0; j < size() - 1; j++)
		{
			if (cur1->data < cur2->data)
			{
				T temp = cur1->data;
				cur1->data = cur2->data;
				cur2->data = temp;
			}
			cur2 = cur2->next;
		}
		cur2 = first;
		cur1 = first->next;
		for (int k = 0; k < i; k++)
		{
			cur1 = cur1->next;
		}
	}
}

template<class T>
void List<T>::remove()
{
	Node<T>* p = first;
	if (!isEmpty(p))
	{
		while (p->next->next != nullptr)
		{
			p = p->next;
		}
		Node<T>* q = p->next;
		if (q != nullptr)
		{
			p->next = q->next;
			q->next = nullptr;
			delete q;
			q = nullptr;
		}
	}
}