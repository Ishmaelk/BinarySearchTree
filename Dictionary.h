#ifndef __dictionary__
#define __dictionary__

#include <iostream>
#include <typeinfo>
#include <locale>
#include <string>
#include<algorithm>

template<class KeyType, class Value>
class Node {
	private:
		Node<KeyType, Value> * parent;
		Node<KeyType, Value> * left;
		Node<KeyType, Value> * right;
		KeyType key;
		Value value;
	public:
		Node();
		Node(const KeyType & item);
		~Node();
		Node<KeyType, Value> * GetParent() const;
		Node<KeyType, Value> * GetLeft() const;
		Node<KeyType, Value> * GetRight() const;
		Node<KeyType, Value> *& RefParent();
		Node<KeyType, Value> *& RefLeft();
		Node<KeyType, Value> *& RefRight();
		Node<KeyType, Value> * GetThis();
		Node<KeyType, Value> *& RefThis();
		KeyType GetKey() const;
		KeyType& RefKey();
		void SetKey(const KeyType & newKey);
		Value GetValue() const;
		Value& RefValue();
		void SetValue(const Value & newValue);
		void SetParent(Node<KeyType, Value> * const node);
		void SetLeft(Node<KeyType, Value> * const node);
		void SetRight(Node<KeyType, Value> * const node);
};

template <class KeyType, class Value>
class Dictionary {
	private:
		Node<KeyType, Value> * root;
		void Trav_InOrder(Node<KeyType, Value> * items, Node<KeyType, Value> *& curr);
		Node<KeyType, Value> * utilBalance(Node<KeyType, Value> * const items, Node<KeyType, Value> * const parent , int small, int large);
		void _Clear(Node<KeyType, Value> *& root);
		int size;
		int height;
		int tempIndex;
		int utilHeight(Node<KeyType, Value> * ptr) const;
		int utilSearch(const KeyType & searchKey, Node<KeyType, Value> * ptr) const;
		
		int utilSize(Node<KeyType, Value> * ptr) const;
		void utilRemover(Node<KeyType, Value> *& prev, Node<KeyType, Value> *& curr);
		void utilPrint(Node<KeyType, Value> * ptr) const;
		
	public:
		Dictionary();
		Dictionary(const KeyType & newKey);
		~Dictionary();
		Node<KeyType, Value>*& RefRoot ();
		Node<KeyType, Value> * utilMinimumNode(Node<KeyType, Value> * tree) const;
		bool IsEmpty() const;
		void Remove(const KeyType & delKey);
		void Clear(); //empties the container
		int Size(); //returns the number of items stored in the container and updates the size of dict
		int Height(); // returns the height of the binary search tree and updates height
		int Count(const KeyType & searchKey) const; // returns 1 if item exists in container, else0
		void Balance();
		Value& operator[](const KeyType & key);//if item doesnt exist it gets created
	 	void Print() const;	
};
#include"Dictionary.cpp"
#endif

