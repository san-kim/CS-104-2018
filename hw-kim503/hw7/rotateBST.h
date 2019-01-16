#ifndef rotateBST_H
#define rotateBST_H

#include "bst.h"


template <typename Key, typename Value>
class rotateBST : public BinarySearchTree<Key, Value> {
public:
	rotateBST();
	~rotateBST();
	bool sameKeys(const rotateBST& t2) const;
	void transform(rotateBST& t2) const;

protected:
	void leftRotate(Node<Key, Value>* r);
	void rightRotate(Node<Key, Value>* r);
	void transformHelper(Node<Key, Value>* r, Node<Key, Value>* p, rotateBST& t2) const;

};

template<typename Key, typename Value>
rotateBST<Key, Value>::rotateBST()
{

}

template<typename Key, typename Value>
rotateBST<Key, Value>::~rotateBST()
{

}

template<typename Key, typename Value>
void rotateBST<Key, Value>::leftRotate(Node<Key, Value>* rotateNode)
{
	//let's declare rotateNode's rotateNode's right initial child and its parent
	//get parent, if it's null, it means rotateNode is mRoot
	Node<Key, Value>* rParent = rotateNode->getParent();
	Node<Key, Value>* rRightChild = rotateNode->getRight();

	//if the right child does not exist or wrong input, do nothing
	if(rRightChild == NULL || rotateNode == NULL)
	{
		return;
	}

	//keep track right child's left child as it gets abandoned/picked up, could be NULL
	Node<Key, Value>* rRightChildsLeftChild = rotateNode->getRight()->getLeft();

	//rotateNode's left child is unchanged

	//update left and parent of rRightChild after rotation, its right node is unchanged
	rRightChild->setLeft(rotateNode);
	rRightChild->setParent(rParent); //will set to NULL if it is root node now
	//if it was the root we were rotating over and it has no parent
	if(this->mRoot == rotateNode)
	{
		this->mRoot = rRightChild;
	}

	//otherwise update parent's child node
	else if(rParent != NULL)
	{
		//if the rotateNode was its parent's left node
		if(rParent->getLeft() == rotateNode)
		{
			rParent->setLeft(rRightChild);
		}
		//if the rotateNode was its parent's right node
		else if(rParent->getRight() == rotateNode)
		{
			rParent->setRight(rRightChild);
		}
	}

	//update rotateNode's right and parent, rotateNode's left is unchanged
	//pick up abandoned right child's left child
	rotateNode->setRight(rRightChildsLeftChild);
	rotateNode->setParent(rRightChild);

	//if the right child's left child existed, update its parent 
	if(rRightChildsLeftChild != NULL)
	{
		rRightChildsLeftChild->setParent(rotateNode);
	}
}


template<typename Key, typename Value>
void rotateBST<Key, Value>::rightRotate(Node<Key, Value>* rotateNode)
{
	//let's declare rotateNode's left initial child and its parent
	//get parent, if it's null, it means rotateNode is mRoot
	Node<Key, Value>* rParent = rotateNode->getParent();
	Node<Key, Value>* rLeftChild = rotateNode->getLeft();

	//if the left child does not exist or wrong input, do nothing
	if(rLeftChild == NULL || rotateNode == NULL)
	{
		return;
	}

	//keep track left child's right child as it gets abandoned/picked up, could be NULL
	Node<Key, Value>* rLeftChildsRightChild = rotateNode->getLeft()->getRight();


	//rotateNode's right child is unchanged

	//update right and parent of rLeftChild after rotation, its left node is unchanged
	rLeftChild->setRight(rotateNode);
	rLeftChild->setParent(rParent); //will set to NULL if it is the root node now

	//if it was the ROOT we were rotating over and it has no parent
	if(this->mRoot == rotateNode)
	{
		this->mRoot = rLeftChild;
	}

	//otherwise update parent's child node
	else if(rParent != NULL)
	{
		//if the rotateNode was its parent's left node
		if(rParent->getLeft() == rotateNode)
		{
			rParent->setLeft(rLeftChild);
		}
		//if the rotateNode was its parent's right node
		else if(rParent->getRight() == rotateNode)
		{
			rParent->setRight(rLeftChild);
		}
	}

	//update rotateNode's left and parent, rotateNode's right is unchanged
	//pick up abandoned right child's left child
	rotateNode->setLeft(rLeftChildsRightChild);
	rotateNode->setParent(rLeftChild);

	//if the right child's left child existed, update its parent 
	if(rLeftChildsRightChild != NULL)
	{
		rLeftChildsRightChild->setParent(rotateNode);
	}
}


template<typename Key, typename Value>
bool rotateBST<Key, Value>::sameKeys(const rotateBST& t2) const
{
	//use iterators; if they are not the same key at the same in-order iterator, will be different
	typename BinarySearchTree<Key, Value>::iterator BST_iterator_this;
	typename BinarySearchTree<Key, Value>::iterator BST_iterator_t2 = t2.begin();
	for(BST_iterator_this = this->begin(); BST_iterator_this != this->end(); ++BST_iterator_this)
	{
		//if t2 is smaller than this BST
		if(BST_iterator_t2 == t2.end())
		{
			return false;
		}

		//if the keys do not match in inorder traversal
		if((*BST_iterator_this).first != (*BST_iterator_t2).first)
		{
			return false;
		}

		//increment iterator for t2 as well
		++BST_iterator_t2;
	}

	//if BST iterator for t2 is not finished; if size of t2 is larger than size of this BST
	if(BST_iterator_t2 != t2.end())
	{
		return false;
	}

	//otherwise return true
	return true;
}


//recursive helper for transform step 5
template<typename Key, typename Value>
void rotateBST<Key, Value>::transformHelper(Node<Key, Value>* rootNode, Node<Key, Value>* parallelNode, rotateBST& t2) const
{
	//catch if we passed a NULL rootNode
	if(rootNode == NULL)
	{
		return;
	}

	//if a leaf node, then will have no rotations to do
	if(rootNode->getLeft() == NULL && rootNode->getRight() == NULL)
	{
		return;
	}

	//if left child exists, do rotations on it accordingly
	if(rootNode->getLeft() != NULL)
	{
		//while it is not what it should be if we followed the parallelNode in our original BST
		while(rootNode->getLeft()->getKey() != parallelNode->getLeft()->getKey())
		{
			//if it is currently smaller than the target, we want to do a left rotation
			if(rootNode->getLeft()->getKey() < parallelNode->getLeft()->getKey())
			{
				t2.leftRotate(rootNode->getLeft());
			}

			//if it is currently larger than the target, we want to do a right rotation
			if(rootNode->getLeft()->getKey() > parallelNode->getLeft()->getKey())
			{
				t2.rightRotate(rootNode->getLeft());
			}
		}
	}

	//if right child exists, do rotations on it accordingly
	if(rootNode->getRight() != NULL)
	{
		//while it is not what it should be if we followed the parallelNode in our original BST
		while(rootNode->getRight()->getKey() != parallelNode->getRight()->getKey())
		{
			//if it is currently smaller than the target, we want to do a left rotation
			if(rootNode->getRight()->getKey() < parallelNode->getRight()->getKey())
			{
				t2.leftRotate(rootNode->getRight());
			}

			//if it is currently larger than the target, we want to do a right rotation
			if(rootNode->getRight()->getKey() > parallelNode->getRight()->getKey())
			{
				t2.rightRotate(rootNode->getRight());
			}
		}
	}


	//at this point rootNode's left and right are what they should be (same as parallelNode's left & right)

	//left child recursion
	transformHelper(rootNode->getLeft(), parallelNode->getLeft(), t2);
	//right child recursion
	transformHelper(rootNode->getRight(), parallelNode->getRight(), t2);
}


template<typename Key, typename Value>
void rotateBST<Key, Value>::transform(rotateBST& t2) const
{
	//if not the same keys contained
	if(this->sameKeys(t2) == false)
	{
		return;
	}

	//if both are empty, nothing to do
	if(this->begin() == this->end() && t2.begin() == t2.end())
	{
		return;
	}

	//step 1: do right rotations on root node until it doesnt have a left child, until its left child is NULL
	while((t2.mRoot)->getLeft() != NULL)
	{
		t2.rightRotate(t2.mRoot);
	}

	//step 2: recursively move to the right child and repeat the above operation.
	Node<Key, Value>* current = t2.mRoot;
	//while it is not at the last right child
	while(current->getRight() != NULL)
	{
		//do right rotations until the current right child doesn't have any left children, will constantly update
		while(current->getRight()->getLeft() != NULL)
		{
			t2.rightRotate(current->getRight());
		}	

		//only after all of the rotations do we update current to the next updated right value
		current = current->getRight();
	}

	//step 3: This should produce a tree which is effectively a linked list.

	//step 4: Now perform left rotations on the root node of t2, until the root of t2 is the same as the root of this.
	while(this->mRoot->getKey() != t2.mRoot->getKey())
	{
		t2.leftRotate(t2.mRoot);
	}

	//step 5: Recursively rotations on left child and right child until they match the node at that position of this.
	//these do nothing if left child or right child does not exist and is NULL
	transformHelper(t2.mRoot, this->mRoot, t2);
}


#endif
