#ifndef BST_H
#define BST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>

/**
* A templated class for a Node in a search tree. The getters for parent/left/right are virtual so that they
* can be overridden for future kinds of search trees, such as Red Black trees, Splay trees, and AVL trees.
*/
template <typename Key, typename Value>
class Node
{
public:
	Node(const Key& key, const Value& value, Node<Key, Value>* parent);
	virtual ~Node();

	const std::pair<Key, Value>& getItem() const;
	std::pair<Key, Value>& getItem();
	const Key& getKey() const;
	const Value& getValue() const;
	Key& getKey();
	Value& getValue();

	virtual Node<Key, Value>* getParent() const;
	virtual Node<Key, Value>* getLeft() const;
	virtual Node<Key, Value>* getRight() const;

	void setParent(Node<Key, Value>* parent);
	void setLeft(Node<Key, Value>* left);
	void setRight(Node<Key, Value>* right);
	void setValue(const Value &value);

protected:
	std::pair<Key, Value> mItem;
	Node<Key, Value>* mParent;
	Node<Key, Value>* mLeft;
	Node<Key, Value>* mRight;
};

/*
	-----------------------------------------
	Begin implementations for the Node class.
	-----------------------------------------
*/

/**
* Explicit constructor for a node.
*/
template<typename Key, typename Value>
Node<Key, Value>::Node(const Key& key, const Value& value, Node<Key, Value>* parent)
	: mItem(key, value)
	, mParent(parent)
	, mLeft(NULL)
	, mRight(NULL)
{

}

/**
* Destructor, which does not need to do anything since the pointers inside of a node
* are only used as references to existing nodes. The nodes pointed to by parent/left/right
* are freed within the deleteAll() helper method in the BinarySearchTree.
*/
template<typename Key, typename Value>
Node<Key, Value>::~Node()
{

}

/**
* A const getter for the item.
*/
template<typename Key, typename Value>
const std::pair<Key, Value>& Node<Key, Value>::getItem() const
{
	return mItem;
}

/**
* A non-const getter for the item.
*/
template<typename Key, typename Value>
std::pair<Key, Value>& Node<Key, Value>::getItem()
{
	return mItem;
}

/**
* A const getter for the key.
*/
template<typename Key, typename Value>
const Key& Node<Key, Value>::getKey() const
{
	return mItem.first;
}

/**
* A const getter for the value.
*/
template<typename Key, typename Value>
const Value& Node<Key, Value>::getValue() const
{
	return mItem.second;
}

/**
* A non-const getter for the key.
*/
template<typename Key, typename Value>
Key& Node<Key, Value>::getKey()
{
	return mItem.first;
}

/**
* A non-const getter for the value.
*/
template<typename Key, typename Value>
Value& Node<Key, Value>::getValue()
{
	return mItem.second;
}

/**
* An implementation of the virtual function for retreiving the parent.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getParent() const
{
	return mParent;
}

/**
* An implementation of the virtual function for retreiving the left child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getLeft() const
{
	return mLeft;
}

/**
* An implementation of the virtual function for retreiving the right child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getRight() const
{
	return mRight;
}

/**
* A setter for setting the parent of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setParent(Node<Key, Value>* parent)
{
	mParent = parent;
}

/**
* A setter for setting the left child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setLeft(Node<Key, Value>* left)
{
	mLeft = left;
}

/**
* A setter for setting the right child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setRight(Node<Key, Value>* right)
{
	mRight = right;
}

/**
* A setter for the value of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setValue(const Value& value)
{
	mItem.second = value;
}

/*
	---------------------------------------
	End implementations for the Node class.
	---------------------------------------
*/

/**
* A templated unbalanced binary search tree.
*/
template <typename Key, typename Value>
class BinarySearchTree
{
	public:
		BinarySearchTree(); //TODO
		virtual ~BinarySearchTree(); //TODO
  		virtual void insert(const std::pair<Key, Value>& keyValuePair); //TODO
        virtual void remove(const Key& key); //TODO
  		void clear(); //TODO
  		void print() const;
  		bool isBalanced() const; //TODO

	public:
		/**
		* An internal iterator class for traversing the contents of the BST.
		*/
		class iterator
		{
			public:
				iterator(Node<Key,Value>* ptr);
				iterator();

				std::pair<Key,Value>& operator*() const;
				std::pair<Key,Value>* operator->() const;

				bool operator==(const iterator& rhs) const;
				bool operator!=(const iterator& rhs) const;
				iterator& operator=(const iterator& rhs);

				iterator& operator++();

			protected:
				Node<Key, Value>* mCurrent;

				friend class BinarySearchTree<Key, Value>;
		};

	public:
		iterator begin() const;
		iterator end() const;
		iterator find(const Key& key) const;

	protected:
		Node<Key, Value>* internalFind(const Key& key) const; //TODO
		Node<Key, Value>* getSmallestNode() const; //TODO
		void printRoot (Node<Key, Value>* root) const;

	protected:
		Node<Key, Value>* mRoot;

	public:
		void print() {this->printRoot(this->mRoot);}

};

/*
	---------------------------------------------------------------
	Begin implementations for the BinarySearchTree::iterator class.
	---------------------------------------------------------------
*/

/**
* Explicit constructor that initializes an iterator with a given node pointer.
*/
template<typename Key, typename Value>
BinarySearchTree<Key, Value>::iterator::iterator(Node<Key,Value>* ptr)
	: mCurrent(ptr)
{

}

/**
* A default constructor that initializes the iterator to NULL.
*/
template<typename Key, typename Value>
BinarySearchTree<Key, Value>::iterator::iterator()
	: mCurrent(NULL)
{

}

/**
* Provides access to the item.
*/
template<typename Key, typename Value>
std::pair<Key, Value>& BinarySearchTree<Key, Value>::iterator::operator*() const
{
	return mCurrent->getItem();
}

/**
* Provides access to the address of the item.
*/
template<typename Key, typename Value>
std::pair<Key, Value>* BinarySearchTree<Key, Value>::iterator::operator->() const
{
	return &(mCurrent->getItem());
}

/**
* Checks if 'this' iterator's internals have the same value
* as 'rhs'
*/
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::iterator::operator==(const BinarySearchTree<Key, Value>::iterator& rhs) const
{
	return this->mCurrent == rhs.mCurrent;
}

/**
* Checks if 'this' iterator's internals have a different value
* as 'rhs'
*/
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::iterator::operator!=(const BinarySearchTree<Key, Value>::iterator& rhs) const
{
	return this->mCurrent != rhs.mCurrent;
}

/**
* Sets one iterator equal to another iterator.
*/
template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator &BinarySearchTree<Key, Value>::iterator::operator=(const BinarySearchTree<Key, Value>::iterator& rhs)
{
	this->mCurrent = rhs.mCurrent;
	return *this;
}

/**
* Advances the iterator's location using an in-order traversal.
*/
template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator& BinarySearchTree<Key, Value>::iterator::operator++()
{
	if(mCurrent->getRight() != NULL)
	{
		mCurrent = mCurrent->getRight();
		while(mCurrent->getLeft() != NULL)
		{
			mCurrent = mCurrent->getLeft();
		}
	}
	else if(mCurrent->getRight() == NULL)
	{
		Node<Key, Value>* parent = mCurrent->getParent();
		while(parent != NULL && mCurrent == parent->getRight())
		{
			mCurrent = parent;
			parent = parent->getParent();
		}
		mCurrent = parent;
	}
	return *this;
}

/*
	-------------------------------------------------------------
	End implementations for the BinarySearchTree::iterator class.
	-------------------------------------------------------------
*/

/*
	-----------------------------------------------------
	Begin implementations for the BinarySearchTree class.
	-----------------------------------------------------
*/

/**
* Default constructor for a BinarySearchTree, which sets the root to NULL.
*/
template<typename Key, typename Value>
BinarySearchTree<Key, Value>::BinarySearchTree()
{
	// TODO

	//set root as nullptr
	mRoot = NULL;
}

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::~BinarySearchTree()
{
	// TODO

	//just clear the search tree
	this->clear();
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::print() const
{
	printRoot(mRoot);
	std::cout << "\n";
}

/**
* Returns an iterator to the "smallest" item in the tree
*/
template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator BinarySearchTree<Key, Value>::begin() const
{
	BinarySearchTree<Key, Value>::iterator begin(getSmallestNode());
	return begin;
}

/**
* Returns an iterator whose value means INVALID
*/
template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator BinarySearchTree<Key, Value>::end() const
{
	BinarySearchTree<Key, Value>::iterator end(NULL);
	return end;
}

/**
* Returns an iterator to the item with the given key, k
* or the end iterator if k does not exist in the tree
*/
template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator BinarySearchTree<Key, Value>::find(const Key& key) const
{
	Node<Key, Value>* curr = internalFind(key);
	BinarySearchTree<Key, Value>::iterator it(curr);
	return it;
}

/**
* An insert method to insert into a Binary Search Tree. The tree will not remain balanced when
* inserting.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::insert(const std::pair<Key, Value>& keyValuePair)
{
	// TODO

	//if an empty BST
	if(mRoot == NULL)
	{
		//pointer to a new node, root is now initialized with a NULL parent
		mRoot = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, NULL);
		return;
	}

	
	Node<Key, Value>* currentnode = mRoot;

	bool hasBeenPlaced = false;
	//while it has at least one child slot to place our new node,
	//will be O(h) as it is just finding where it goes & placing
	while(!hasBeenPlaced)
	{
		//if key already exists, then update value
		if(keyValuePair.first == currentnode->getKey())
		{
			//update
			currentnode->setValue(keyValuePair.second);
			hasBeenPlaced = true;
			break;
		}

		//if it is smaller than our current node, move left 
		else if(keyValuePair.first < currentnode->getKey())
		{
			//if we find an empty spot for our keyValuePair, place it there
			if(currentnode->getLeft() == NULL)
			{
				//make a node with given key, value, and parent is currentnode.
				Node<Key, Value>* addnode = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, currentnode);
				//update currentnode's mLeft node
				currentnode->setLeft(addnode);
				hasBeenPlaced = true;
				break;
			}

			//otherwise, update currentnode and keep looking for an empty place to put our node
			currentnode = currentnode->getLeft();
		}

		//if it is larger than our current node, move right
		else if(keyValuePair.first > currentnode->getKey())
		{
			//if we find an empty spot for our keyValuePair, place it there
			if(currentnode->getRight() == NULL)
			{
				//make a node with given key, value, and parent is currentnode.
				Node<Key, Value>* addnode = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, currentnode);
				//update currentnode's mRight node
				currentnode->setRight(addnode);
				hasBeenPlaced = true;
				break;
			}

			//otherwise, update currentnode and keep looking for an empty place to put our node
			currentnode = currentnode->getRight();
		}
	}	
}

/**
* An remove method to remove a specific key from a Binary Search Tree. The tree may not remain balanced after
* removal.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::remove(const Key& key)
{
	// TODO

	//the node to remove, O(h) to find, rest takes constant time
	Node<Key, Value>* removeNode = internalFind(key);

	//if not in the tree or if tree is empty, do nothing
	if(removeNode == NULL || mRoot == NULL)
	{
		return;
	}


	//case where we are removing the SINGLE root node in the tree, when it has neither left nor right
	else if(removeNode == mRoot && removeNode->getLeft() == NULL && removeNode->getRight() == NULL)
	{
		mRoot = NULL;
	}

	//in the case where the removeNode is the root and only has one child (only one of the children is NULL now)
	else if(removeNode == mRoot && (removeNode->getLeft() == NULL || removeNode->getRight() == NULL))
	{
		//if the singular child is on the left
		if(removeNode->getLeft() != NULL)
		{
			mRoot = removeNode->getLeft();
			//update its parent to NULL
			removeNode->getLeft()->setParent(NULL);
		}

		//if the singular child is on the right
		else if(removeNode->getRight() != NULL)
		{
			mRoot = removeNode->getRight();
			//update its parent to NULL
			removeNode->getRight()->setParent(NULL);
		}
	}

	//in the case where it is a leaf node, has no children, just updating parent's child (will have a parent, isn't root)
	else if(removeNode != mRoot && removeNode->getLeft() == NULL && removeNode->getRight() == NULL)
	{
		//if it is parent's LEFT child, so set parent's left child to NULL
		if(removeNode == removeNode->getParent()->getLeft())
		{
			removeNode->getParent()->setLeft(NULL);
		}
		//if it is parent's RIGHT child, so set parent's right child to NULL
		else if(removeNode == removeNode->getParent()->getRight())
		{
			removeNode->getParent()->setRight(NULL);
		}
	}

	//in the case where the removeNode is NOT root and only has one child (only one of the children is NULL now)
	else if(removeNode != mRoot && (removeNode->getLeft() == NULL || removeNode->getRight() == NULL))
	{
		//if removeNode is the parent's left child 
		if(removeNode == removeNode->getParent()->getLeft())
		{
			//if the singular child is on the left
			if(removeNode->getLeft() != NULL)
			{
				//update removeNode's child's parent to removeNode's parent
				removeNode->getLeft()->setParent(removeNode->getParent());
				//update removeNode's parent's left child to removeNode's child
				removeNode->getParent()->setLeft(removeNode->getLeft());
			}

			//if the singular child is on the right
			else if(removeNode->getRight() != NULL)
			{
				//update removeNode's child's parent to removeNode's parent
				removeNode->getRight()->setParent(removeNode->getParent());
				//update removeNode's parent's left child to removeNode's child
				removeNode->getParent()->setLeft(removeNode->getRight());
			}
		}

		//if removeNode is parent's RIGHT child
		else if(removeNode == removeNode->getParent()->getRight())
		{
			//if the singular child is on the left
			if(removeNode->getLeft() != NULL)
			{
				//update removeNode's child's parent to removeNode's parent
				removeNode->getLeft()->setParent(removeNode->getParent());
				//update removeNode's parent's left child to removeNode's child
				removeNode->getParent()->setRight(removeNode->getLeft());
			}

			//if the singular child is on the right
			else if(removeNode->getRight() != NULL)
			{
				//update removeNode's child's parent to removeNode's parent
				removeNode->getRight()->setParent(removeNode->getParent());
				//update removeNode's parent's right child to removeNode's child
				removeNode->getParent()->setRight(removeNode->getRight());
			}
		}
	}


	//now we know that if none of above were true, then removeNode must have TWO children.
	else if(removeNode->getLeft() != NULL && removeNode->getRight() != NULL)
	{
		//find the predecessor to promote, start by going left one times
		Node<Key, Value>* predecessor = removeNode->getLeft();

		//then go right until we cant / until we hit a NULL, this is O(h)
		while(predecessor->getRight() != NULL)
		{
			predecessor = predecessor->getRight();
		}

		//if we didn't move right at all but only once left, promote the child left of removeNode
		if(predecessor->getParent() == removeNode)
		{
			//update right of predecessor, at this point it shouldn't have any right child
			predecessor->setRight(predecessor->getParent()->getRight());
			//update predecessor's parent's right node's parent to predecessor
			predecessor->getParent()->getRight()->setParent(predecessor);

			//if removeNode was already the root, we don't update the parents, just the mRoot
			if(removeNode == mRoot)
			{
				mRoot = predecessor;
				predecessor->setParent(NULL);
			}

			//otherwise update predecessor's parent and removeNode's parent's left child
			else if(removeNode != mRoot)
			{	
				//predecessor's parent is that which was its grandparent
				predecessor->setParent(predecessor->getParent()->getParent());
				//if removeNode was the left child
				if(removeNode->getParent()->getLeft() == removeNode)
				{
					removeNode->getParent()->setLeft(predecessor);
				}
				//if removeNode was the right child
				else if(removeNode->getParent()->getRight() == removeNode)
				{
					removeNode->getParent()->setRight(predecessor);
				}
			}
		}

		//if we moved right at least once
		else if(predecessor->getParent() != removeNode)
		{
			//set predecessor's parent's right child
			//if predecessor had a left child, transfer it over to predecessor's parent's right child
			if(predecessor->getLeft() != NULL)
			{
				//update the link between predecessor's parent and predecessor's left child
				predecessor->getParent()->setRight(predecessor->getLeft());
				predecessor->getLeft()->setParent(predecessor->getParent());
			}
			//if predecessor did not have any children, its parent's right child is null
			else if(predecessor->getLeft() == NULL)
			{
				predecessor->getParent()->setRight(NULL);
			}

			//set predecessor's updated left child and vice versa for left's parent
			removeNode->getLeft()->setParent(predecessor);
			predecessor->setLeft(removeNode->getLeft());

			//set predecessor's updated right child and vice versa for right's parent
			removeNode->getRight()->setParent(predecessor);
			predecessor->setRight(removeNode->getRight());

			//if removeNode is the root node
			if(removeNode == mRoot)
			{
				mRoot = predecessor;
				predecessor->setParent(NULL);
			}
			//if removeNode is not root node, update parent links
			else if(removeNode != mRoot)
			{
				predecessor->setParent(removeNode->getParent());
				//if removeNode was the left child
				if(removeNode->getParent()->getLeft() == removeNode)
				{
					removeNode->getParent()->setLeft(predecessor);
				}
				//if removeNode was the right child
				else if(removeNode->getParent()->getRight() == removeNode)
				{
					removeNode->getParent()->setRight(predecessor);
				}
			}
		}
	}

	//delete the allocated memory associated
	delete removeNode;
}


//helper for clear, post order traversal
template<typename Key, typename Value>
void postOrderTraversal_helper(Node<Key, Value>* start)
{
	//we have to do post order traversal and delete accordingly so we dont dereference something we deleted
	//left side
	if(start->getLeft() != NULL)
	{
		postOrderTraversal_helper(start->getLeft());
	}
	//right side
	if(start->getRight() != NULL)
	{
		postOrderTraversal_helper(start->getRight());
	}

	//will delete leaf nodes first then parent, which the order in which we want to delete
	//this way we don't try to access memory we already deleted
	delete start;
}
/**
* A method to remove all contents of the tree and reset the values in the tree
* for use again.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear()
{
	// TODO

	//we have to do post order traversal and delete accordingly so we dont dereference something we deleted
	if(mRoot != NULL)
	{
		//postorder tranversal is O(n) as it visits every node once and once only
		postOrderTraversal_helper(mRoot);
		mRoot = NULL;
	}
}

/**
* A helper function to find the smallest node in the tree.
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::getSmallestNode() const
{
	// TODO

	//edge case: if empty BST
	if(mRoot == NULL)
	{
		return NULL;
	}

	Node<Key, Value>* currentnode = mRoot;
	//keep going left as doing so gives the smallest element
	while(currentnode->getLeft() != NULL)
	{
		currentnode = currentnode->getLeft();
	}

	return currentnode;
}

/**
* Helper function to find a node with given key, k and
* return a pointer to it or NULL if no item with that key
* exists
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::internalFind(const Key& key) const
{
	// TODO

	//empty case
	if(mRoot == NULL)
	{
		return NULL;
	}

	//if it is the root
	if(key == mRoot->getKey())
	{
		return mRoot;
	}


	//at this point it is not the Root, so we don't need to check initially, we can just update immediately
	Node<Key, Value>* compareNode = mRoot;
	//compare and traverse until we find it; while we are NOT at the end of a branch, aka while not a leaf node
	while(compareNode->getLeft() != NULL || compareNode->getRight() != NULL)
	{
		//update compareNode so that it traverses tree to left if key is smaller than current node
		if(key < compareNode->getKey())
		{
			//if it is the case that it is strictly smaller yet a left child does not exist, return NULL
			if(compareNode->getLeft() == NULL)
			{
				return NULL;
			}

			//otherwise update compareNode
			compareNode = compareNode->getLeft();
		}

		//update compareNode so that it traverses tree to right if key is larger than current node
		else if(key > compareNode->getKey())
		{
			//if it is the case that it is strictly larger yet a right child does not exist, return NULL
			if(compareNode->getRight() == NULL)
			{
				return NULL;
			}

			//otherwise update compareNode
			compareNode = compareNode->getRight();
		}

		//after updating compareNode, if we have found it, return that pointer
		if(compareNode->getKey() == key)
		{
			return compareNode;
		}
	}	

	//if we are at a leaf node without children and this is not the key, then we know that the node is not in tree
	return NULL;
}


//helper for isBalanced
template<typename Key, typename Value>
int treeHeight(Node<Key, Value>* currentnode)
{
	//for the leaf nodes / end of a branch, go back up stack adding 1 every level
	if(currentnode == NULL)
	{
		return 0;
	}

	//left side height
	int leftheight = treeHeight(currentnode->getLeft());
	//if left height is -1, aka not balanced, then force return -1 so that it gets passed up the stack
	if(leftheight == -1)
	{
		return -1;
	}

	int rightheight = treeHeight(currentnode->getRight());
	//if right height is -1 aka not balanced, then force return -1 so that it gets passed up the stack
	if(rightheight == -1)
	{
		return -1;
	}

	//if the right side and left side differ by 2 or more
	if(abs(rightheight - leftheight) >= 2)
	{
		return -1;
	}

	//return the max height of left and right nodes if it is not a leaf node and both left and right is balanced
	int max = leftheight;
	if(rightheight > leftheight)
	{
		max = rightheight;
	}

	return max + 1;
}



/**
 * Return true iff the BST is an AVL Tree.
 */
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalanced() const
{
	// TODO

	//if we did not find an error (must be at least 0)
	if(treeHeight(mRoot) != -1)
	{
		return true;
	}

	//otherwise return false
	return false;
}


/**
 * Lastly, we are providing you with a print function, BinarySearchTree::printRoot().
   Just call it with a node to start printing at, e.g:
   this->printRoot(this->mRoot)

   It will print up to 5 levels of the tree rooted at the passed node, in ASCII graphics format.
   We hope it will make debugging easier!
  */

// include print function (in its own file because it's fairly long)
#include "print_bst.h"

/*
	---------------------------------------------------
	End implementations for the BinarySearchTree class.
	---------------------------------------------------
*/

#endif
