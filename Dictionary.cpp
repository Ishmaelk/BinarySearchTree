#include "Dictionary.h"

// Node Implementation
template<class KeyType, class Value>
Node<KeyType, Value>::Node(void) {
	parent = nullptr;
	left = nullptr;
	right = nullptr;
}

template <class KeyType, class Value>
Node<KeyType, Value>::Node(const KeyType & newKey) {
	parent = nullptr;
	left = nullptr;
	right = nullptr;
	key = newKey;
}

template<class KeyType, class Value>
Node<KeyType, Value>::~Node() {
	delete left;
	delete right;
}

template <class KeyType, class Value>
Node<KeyType, Value> * Node<KeyType, Value>::GetParent() const {
	return parent;
}

template<class KeyType, class Value>
Node<KeyType, Value> * Node<KeyType, Value>::GetLeft() const {
	return left;
}

template <class KeyType, class Value>
Node<KeyType, Value> * Node<KeyType, Value>::GetRight() const {
	return right;
}

template <class KeyType, class Value>
Node<KeyType, Value> *& Node<KeyType, Value>::RefParent() {
	return parent;
}

template <class KeyType, class Value>
Node<KeyType, Value> *& Node<KeyType, Value>::RefLeft() {
	return left;
}

template <class KeyType, class Value>
Node<KeyType, Value> *& Node<KeyType, Value>::RefRight() {
	return right;
}

template <class KeyType, class Value>
Node<KeyType, Value> * Node<KeyType, Value>::GetThis() {
	return this;
}

template <class KeyType, class Value>
Node<KeyType, Value> *& Node<KeyType, Value>::RefThis() {
	return this;
}

template <class KeyType, class Value>
KeyType Node<KeyType, Value>::GetKey() const {
	return key;
}

template<class KeyType, class Value>
KeyType& Node<KeyType, Value>::RefKey() {
	return key;
}

template <class KeyType, class Value>
Value Node<KeyType, Value>::GetValue()  const {
	return value;
}

template <class KeyType, class Value>
Value& Node<KeyType, Value>::RefValue() {
	return value;
}

template <class KeyType, class Value>
void Node<KeyType, Value>::SetValue(const Value & newValue) {
	value = newValue;
}

template <class KeyType, class Value>
void Node<KeyType, Value>::SetParent(Node<KeyType, Value> * const node) {
	parent = node;
}

template <class KeyType, class Value>
void Node<KeyType, Value>::SetLeft(Node<KeyType, Value> * const node) {
	left = node;	
}

template <class KeyType, class Value>
void Node<KeyType, Value>::SetRight(Node<KeyType, Value> * const node) {
	right = node;
}


// Dictionary Implementation

template<class KeyType, class Value>
Dictionary<KeyType, Value>::Dictionary() {
        root = nullptr;
        size = 0;
        height = 0;
        tempIndex = 0;
}

template <class KeyType, class Value>
Dictionary<KeyType, Value>::Dictionary(const KeyType & key) {
        Node<KeyType, Value> * rootNode = new Node<KeyType, Value>(key);
        root = rootNode;
        size = 0;
        height = 0;
        tempIndex = 0;
}

// Uses Recursion to go through all the nodes and delete them
template <class KeyType, class Value>
Dictionary<KeyType, Value>::~Dictionary() {
        Clear();
}

// Recursively traverses tree in order and populates a temporary array for Balance Function //
template<class KeyType, class Value>
void Dictionary<KeyType, Value>::Trav_InOrder(Node<KeyType, Value> * items, Node<KeyType, Value> *& curr) {
        if (curr == nullptr)
                return;
        Trav_InOrder(items, curr->RefLeft());
        items[tempIndex] = *curr;
        tempIndex++;
        Trav_InOrder(items, curr->RefRight());
}

// Balance _util function that is called in Balance () //
template <class KeyType, class Value>
Node<KeyType, Value> * Dictionary<KeyType, Value>::utilBalance(Node<KeyType, Value> * const items, Node<KeyType, Value> * const parent, int small, int large) {
        if (small > large) // dict is empty or we hit a stop condition
                return nullptr;
        
        Node<KeyType, Value> * newNode = new Node<KeyType, Value>(items[(small+large)/2]);
	newNode->RefParent() = parent; // assign parent
	newNode->RefLeft() = utilBalance(items, newNode->GetThis(), small,((small+large)/2)-1);
	newNode->RefRight() = utilBalance(items, newNode->GetThis(), ((small+large) / 2) + 1, large);
        return newNode;
}

// Clears the old tree and repopulates a more balanced tree //
template<class KeyType, class Value>
void Dictionary<KeyType, Value>::Balance() {
        // position of the temporary array storage held in tempIndex class member
	Size(); // update size
        tempIndex = 0;
	Node<KeyType, Value> * items = new Node<KeyType, Value>[size]; // create temp storage
	Trav_InOrder(items, root);
	Clear();
        root = utilBalance(items, nullptr, 0, size-1); // begin recursion
	items = nullptr;
}

// Clears Tree Recursively //
template<class KeyType, class Value>
void Dictionary<KeyType, Value>::Clear() {
	_Clear(root); // need to pass a reference to the root to keep changes
}

// _util method for Clear () //
template<class KeyType, class Value>
void Dictionary<KeyType, Value>::_Clear(Node<KeyType, Value> *& root) {
	// when a leaf node is reached (evenutally all will be leaf nodes)
	if (root == nullptr)
		return;	
	_Clear(root->RefLeft());
	_Clear(root->RefRight());
	delete root;
	root = nullptr;	
}

template <class KeyType, class Value>
Node<KeyType, Value>*& Dictionary<KeyType, Value>::RefRoot() {
	return root;
}

// Checks if tree is empty //
template <class KeyType, class Value>
bool Dictionary<KeyType, Value>::IsEmpty() const {
	if (root == nullptr)
		return true;
	else
		return false;
}

// Searches for a key and removes it if in the tree // 
template <class KeyType, class Value>
void Dictionary<KeyType, Value>::Remove(const KeyType & key) {
	if (root == nullptr)
		return;

	Node<KeyType, Value> * pos = root;
	Node<KeyType, Value> * prev = root;
        
	while (pos->GetKey() != key) {
                if (key < pos->GetKey()) {
                        if (pos->GetLeft() != nullptr) {
				prev = pos;
                                pos = pos->GetLeft();
                        } else	
				return;
                        
                } else if (key > pos->GetKey()) {
                        if (pos->GetRight() != nullptr) {
				prev = pos;
                                pos = pos->GetRight();
                        } else
				return;
                        
                } else // key == pos->GetKey();
                        break;
        }
	utilRemover(prev, pos);
}

// _util method used to remove an element //
template<class KeyType, class Value>
void Dictionary<KeyType, Value>::utilRemover (Node<KeyType, Value> *& prev, Node<KeyType, Value> *& pos) {
	// Leaf Node Case
	if (pos->GetLeft() == nullptr && pos->GetRight() == nullptr) {
		if (pos->GetKey() < prev->GetKey())
			prev->SetLeft(nullptr);
		else
			prev->SetRight(nullptr);
                if (pos == root)
			root = nullptr;
		delete pos;
        }
	// Single child case 
	else if (pos->GetLeft() == nullptr && pos->GetRight() != nullptr) {
		if (pos == root) {
			root = pos->GetRight();
			root->SetParent(nullptr);	
		} 
		if (pos->GetRight()->GetKey() > prev->GetKey()) {
			prev->SetRight(pos->GetRight());
			pos->GetRight()->SetParent(prev);
		} else {
			prev->SetLeft(pos->GetRight());
			pos->GetRight()->SetParent(prev);
		}
		delete pos;
        } else if (pos->GetLeft() != nullptr && pos->GetRight() == nullptr) { 
		if (pos == root) {
			root = pos->GetLeft();
			std::cout << RefRoot() << std::endl;
		}
		if (pos->GetLeft()->GetKey() < prev->GetKey()) {
			prev->SetLeft(pos->GetLeft());
			pos->GetLeft()->SetParent(prev);
		} else {
			prev->SetRight(pos->GetLeft());
			pos->GetLeft()->SetParent(prev);
		}
		delete pos;
        } else { // Two Children case
		// find the minimum node of the left subtree
		Node<KeyType, Value> * copy = utilMinimumNode(pos->GetRight());
		
		if (root == pos) { // if we're removing the root
			root->RefKey() = copy->GetKey(); // copy the key and value from the node into root
			root->RefValue() = copy->GetValue();
			root->SetParent(nullptr); // root parent is always null
			
			if (root->GetRight() == copy) {
				if (copy->GetRight() == nullptr)
					root->SetRight(nullptr);
				else
					root->SetRight(copy->GetRight()); // if there is more on the right
			} else
				copy->GetParent()->SetLeft(nullptr);
			
                } else { // if we're not removing the root node
			pos->RefKey() = copy->GetKey(); // copy only the key and value from the node into pos
			pos->RefValue() = copy->GetValue();
			if (pos->GetRight() == copy) { // for the case where pos->GetRight() is the minimum node on right subtree
				if (copy->GetRight() == nullptr)
					pos->SetRight(nullptr);
				else // if there is more on the right
					pos->SetRight(copy->GetRight());// connect them
			} else
				copy->GetParent()->SetLeft(nullptr); // set copy's left ptr to the nullptr
		
		}
		//release memory for copy
		delete copy;
	}
}

// _util method that finds the minimum node recursively // 
template <class KeyType, class Value>
Node<KeyType, Value> * Dictionary<KeyType, Value>::utilMinimumNode(Node<KeyType, Value> * tree) const {
	if (tree->GetLeft() == nullptr)
		return tree;
        utilMinimumNode(tree->GetLeft());

}

// _util method that is called in Size() //
template <class KeyType, class Value>
int Dictionary<KeyType, Value>::utilSize(Node<KeyType, Value> * ptr) const {
	if (ptr == nullptr)
		return 0;
	return 1 + utilSize (ptr->GetLeft()) + utilSize(ptr->GetRight()); // 1+ is important here
}

// Calculates the size of the tree recursively //
template<class KeyType, class Value>
int Dictionary<KeyType, Value>::Size() {
	size = utilSize(root);
	return size;
}

// _util Method that is called in Height() //
template <class KeyType, class Value>
int Dictionary<KeyType, Value>::utilHeight(Node<KeyType, Value> * ptr) const {
	if (ptr == nullptr)
		return 0;
	return 1+std::max(utilHeight(ptr->GetLeft()), utilHeight(ptr->GetRight()));
}

// Calculates Height of the tree recursively //
template<class KeyType, class Value>
int Dictionary<KeyType, Value>::Height() {
	height = utilHeight(root);	
	return height;
}

// _util method that is called in Count //
template <class KeyType, class Value>
int Dictionary<KeyType, Value>::utilSearch (const KeyType & searchKey, Node<KeyType, Value> * ptr) const {
	if (ptr == nullptr)
		return 0;

	if (searchKey < ptr->GetKey())
		utilSearch(searchKey, ptr->GetLeft());
	else if (searchKey > ptr->GetKey())
		utilSearch(searchKey, ptr->GetRight());
	else
		return 1;	
}

// If Key is in tree returns 1 else 0 //
template <class KeyType, class Value>
int Dictionary<KeyType, Value>::Count (const KeyType & searchKey) const {
	return utilSearch(searchKey, root);
}

// returns value stored at key if exists, otherwise creates the key and places in tree //
template <class KeyType, class Value>
Value& Dictionary<KeyType, Value>::operator[] (const KeyType & newKey) {
	if (root == nullptr) {
		root = new Node<KeyType, Value>(newKey);
		return root->RefValue();
	}
	Node<KeyType, Value> * pos = root;
	Node<KeyType, Value> * prev = root;
	while (pos != nullptr) {
		if (newKey < pos->GetKey()) {
			if (pos->GetLeft() != nullptr) {
				prev = pos;
				pos = pos->GetLeft();
			} else {
				Node<KeyType, Value> * newNode = new Node<KeyType, Value>(newKey);	
				pos->SetLeft(newNode);
				prev = pos;
				pos = pos->GetLeft();
				pos->SetParent(prev);
				return pos->RefValue();
			}
		} else if (newKey > pos->GetKey()) {
			if (pos->GetRight() != nullptr) {
				prev = pos;
				pos = pos->GetRight();
			} else {
				Node<KeyType, Value> * newNode = new Node<KeyType, Value>(newKey);
				prev = pos;
				pos->SetRight(newNode);
				pos = pos->GetRight();
				pos->SetParent(prev);
				return pos->RefValue();
			}
		} else // if key already exists in dictionary
			return pos->RefValue();
		
	}
	
}

// _util print method that gets called in Print () //
template <class KeyType, class Value>
void Dictionary<KeyType, Value>::utilPrint(Node<KeyType, Value> * ptr) const {
	if (ptr == nullptr)
		return;
	utilPrint(ptr->GetLeft());
	std::cout << ptr->GetKey() << " ";
	utilPrint(ptr->GetRight());
}

// Prints the tree in order //
template <class KeyType, class Value>
void Dictionary<KeyType, Value>::Print() const {
	utilPrint(root);
	std::cout << std::endl;	
}
