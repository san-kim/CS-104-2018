#ifndef AVLBST_H
#define AVLBST_H

#include <iostream>
#include <cstdlib>
#include <string>
#include <algorithm>
#include "rotateBST.h"

/**
* A special kind of node for an AVL tree, which adds the height as a data member, plus 
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
	// Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int getHeight() const;
    void setHeight(int height);

    // Getters for parent, left, and right. These need to be redefined since they 
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int mHeight;
};

/*
--------------------------------------------
Begin implementations for the AVLNode class.
--------------------------------------------
*/

/**
* Constructor for an AVLNode. Nodes are initialized with a height of 0.
*/
template<typename Key, typename Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent)
    : Node<Key, Value>(key, value, parent)
    , mHeight(0)
{

}

/**
* Destructor.
*/
template<typename Key, typename Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* Getter function for the height. 
*/
template<typename Key, typename Value>
int AVLNode<Key, Value>::getHeight() const
{
    return mHeight;
}

/**
* Setter function for the height. 
*/
template<typename Key, typename Value>
void AVLNode<Key, Value>::setHeight(int height)
{
    mHeight = height;
}

/**
* Getter function for the parent. Used since the node inherits from a base node.
*/
template<typename Key, typename Value>
AVLNode<Key, Value>* AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key,Value>*>(this->mParent);
}

/**
* Getter function for the left child. Used since the node inherits from a base node.
*/
template<typename Key, typename Value>
AVLNode<Key, Value>* AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key,Value>*>(this->mLeft);
}

/**
* Getter function for the right child. Used since the node inherits from a base node.
*/
template<typename Key, typename Value>
AVLNode<Key, Value>* AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key,Value>*>(this->mRight);
}

/*
------------------------------------------
End implementations for the AVLNode class.
------------------------------------------
*/

/**
* A templated balanced binary search tree implemented as an AVL tree.
*/
template <class Key, class Value>
class AVLTree : public rotateBST<Key, Value>
{
public:
	// Methods for inserting/removing elements from the tree. You must implement
	// both of these methods. 
    virtual void insert(const std::pair<Key, Value>& keyValuePair) override;
    void remove(const Key& key);

private:
	/* Helper functions are strongly encouraged to help separate the problem
	   into smaller pieces. You should not need additional data members. */
    AVLNode<Key, Value>* BST_insert_helper(const std::pair<Key, Value>& keyValuePair);
    AVLNode<Key, Value>* BST_remove_helper(const Key& key);
    int getMaxChildHeight(AVLNode<Key, Value>* parentNode);
};

/*
--------------------------------------------
Begin implementations for the AVLTree class.
--------------------------------------------
*/

/**
* Insert function for a key value pair. Finds location to insert the node and then balances the tree. 
*/
template<typename Key, typename Value>
void AVLTree<Key, Value>::insert(const std::pair<Key, Value>& keyValuePair)
{
    // TODO

    //if it is an empty AVL tree
    if(this->mRoot == NULL)
    {
        //set it as the root, set key and value, and set parent to NULL, height is initialized to 0
        //parent ptr = child ptr is legal
        this->mRoot = new AVLNode<Key,Value>(keyValuePair.first, keyValuePair.second, NULL);
        return;
    }

    //do BST insert on the key, val pair, return the pointer of the created node
    AVLNode<Key, Value>* insertedNode = this->BST_insert_helper(keyValuePair);

    //if we just updated and didn't insert
    if(insertedNode == NULL)
    {
        //do nothing, no heights are changed
        return;
    }

    //otherwise update heights
    AVLNode<Key, Value>* updateHeightNode = insertedNode;
    //history of left or right traversal from added to unbalanced, most recent is stored at front
    std::string LRhistory = "";
    //it cannot be the root node anyways at this point, but we will still check the height balance of the root
    while(updateHeightNode->getParent() != NULL)
    {
        //for iteration storage purposes
        AVLNode<Key, Value>* updateHeightNode_parent = updateHeightNode->getParent();

        //get parent's height
        int parentHeight = updateHeightNode->getParent()->getHeight();
        //check if we need to update at all, if the height = height of updateHeightNode, then update parent by adding 1 
        if(parentHeight == updateHeightNode->getHeight())
        {
            updateHeightNode->getParent()->setHeight(parentHeight+1);
            //if this is parent's left child
            if(updateHeightNode->getParent()->getLeft() == updateHeightNode)
            {
                //record that we have traversed left to the parent
                LRhistory = "L" + LRhistory;
            }
            //if this is parent's right child
            else if(updateHeightNode->getParent()->getRight() == updateHeightNode)
            {
                LRhistory = "R" + LRhistory;
            }
        }

        //if it doesn't change the parent's height, we know all heights above will be unchanged, so break
        //if parent's height is already 1 or more (should be max 1 greater) than our updating node
        else if(parentHeight >= updateHeightNode->getHeight() + 1)
        {
            //this means we have added to the shorter branch and so we don't have to rotate then
            break;
        }

        //find left and right heights of the parent, if it is NULL, it has height -1 as height 0 is the height for one leaf node
        int leftheight = -1;
        if(updateHeightNode->getParent()->getLeft() != NULL)
        {
            leftheight = updateHeightNode->getParent()->getLeft()->getHeight();
        }
        int rightheight = -1;
        if(updateHeightNode->getParent()->getRight() != NULL)
        {
            rightheight = updateHeightNode->getParent()->getRight()->getHeight();
        }

        //if the difference between the two children of its PARENT is 2 or more (taking into account no child means -1)
        if(abs(leftheight - rightheight) >= 2)
        {
            //at this point our "Z" or unbalanced node would be our updateHeightNode's parent, Y and X we find by LRhistory breadcrumb trail
            //our history will have at least 2 at this point because at minimum, one side is height -1 and other side is 1 so
            //it means our added node was on 1's side, traversed TWICE to get here
            //start from LRhistory[0] to trace back steps from Z to Y to X.
            AVLNode<Key, Value>* Z = updateHeightNode->getParent();

            //if zig-zig R-R traversal configuration from Z -> do LEFT rotate on "Z"
            if(LRhistory[0] == 'R' && LRhistory[1] == 'R')
            {
                //get pointer to Y
                AVLNode<Key, Value>* Y = Z->getRight();
                //rotate
                this->leftRotate(Z);
                //update heights for Y and Z, height for X is unchanged
                Z->setHeight(getMaxChildHeight(Z) + 1);
                Y->setHeight(getMaxChildHeight(Y) + 1);
            }

            //if zig-zig L-L traversal configuration from Z -> do RIGHT rotate on "Z"
            else if(LRhistory[0] == 'L' && LRhistory[1] == 'L')
            {
                //get pointer to Y
                AVLNode<Key, Value>* Y = Z->getLeft();
                //rotate
                this->rightRotate(Z);
                //update heights for Y and Z, height for X is unchanged
                Z->setHeight(getMaxChildHeight(Z) + 1);
                Y->setHeight(getMaxChildHeight(Y) + 1);
            }

            //if zig-zag R-L traversal configuration from Z -> do RIGHT rotate on "Y" then LEFT rotate on "Z"
            else if(LRhistory[0] == 'R' && LRhistory[1] == 'L')
            {
                //node Y is node Z's RIGHT child that follows traversal path, store the pointer as "Y"
                AVLNode<Key, Value>* Y = Z->getRight();
                //get pointer to X as well
                AVLNode<Key, Value>* X = Y->getLeft();
                //rotate
                this->rightRotate(Y);
                this->leftRotate(Z);

                //update heights for X, Y, and Z after rotation
                Z->setHeight(getMaxChildHeight(Z) + 1);
                Y->setHeight(getMaxChildHeight(Y) + 1);
                X->setHeight(getMaxChildHeight(X) + 1);
            }

            //if zig-zag L-R traversal configuration from Z -> do LEFT rotate on "Y" then RIGHT rotate on "Z"
            else if(LRhistory[0] == 'L' && LRhistory[1] == 'R')
            {
                //node Y is node Z's LEFT child that follows traversal path, store the pointer as "Y"
                AVLNode<Key, Value>* Y = Z->getLeft();
                //get pointer to X as well
                AVLNode<Key, Value>* X = Y->getRight();
                //rotate
                this->leftRotate(Y);
                this->rightRotate(Z);

                //update heights for X, Y, and Z after rotation
                Z->setHeight(getMaxChildHeight(Z) + 1);
                Y->setHeight(getMaxChildHeight(Y) + 1);
                X->setHeight(getMaxChildHeight(X) + 1);
            }
        }

        //update to the next parent
        updateHeightNode = updateHeightNode_parent;
    }
}


//BST insert helper function, returns where pointer to the inserted new node
template<typename Key, typename Value>
AVLNode<Key, Value>* AVLTree<Key, Value>::BST_insert_helper(const std::pair<Key, Value>& keyValuePair)
{
    //node we are traversing
    AVLNode<Key, Value>* currentnode = static_cast<AVLNode<Key,Value>*>(this->mRoot);

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
            //if we are just updating, return NULL so we know at the main insert function
            return NULL;
        }

        //if it is smaller than our current node, move left 
        else if(keyValuePair.first < currentnode->getKey())
        {
            //if we find an empty spot for our keyValuePair, place it there
            if(currentnode->getLeft() == NULL)
            {
                //make a node with given key, value, and parent is currentnode.
                AVLNode<Key, Value>* addnode = new AVLNode<Key, Value>(keyValuePair.first, keyValuePair.second, currentnode);
                //update currentnode's mLeft node
                currentnode->setLeft(addnode);
                hasBeenPlaced = true;
                //return the pointer to the added node
                return addnode;
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
                AVLNode<Key, Value>* addnode = new AVLNode<Key, Value>(keyValuePair.first, keyValuePair.second, currentnode);
                //update currentnode's mRight node
                currentnode->setRight(addnode);
                hasBeenPlaced = true;
                //return the pointer to the added node
                return addnode;
            }

            //otherwise, update currentnode and keep looking for an empty place to put our node
            currentnode = currentnode->getRight();
        }
    }   

    //should not reach here but just a catch all
    return NULL;
}

/**
* Remove function for a given key. Finds the node, reattaches pointers, and then balances when finished. 
*/
template<typename Key, typename Value>
void AVLTree<Key, Value>::remove(const Key& key)
{
    // TODO

    //remove node with that key from the tree and return the first node that needs to be checked
    AVLNode<Key, Value>* checkNode = BST_remove_helper(key);
    //error or last remove case, do nothing
    if(checkNode == NULL)
    {
        return;
    }

    //if it was an error case or it deleted the last remaining node, does not enter while loop--no need to check
    //while we are not at the root node, keep checking up the parents until we have checked the root node and reach NULL
    while(checkNode != NULL)
    {
        //for storing the next iteration's parent of our current checkNode as we will rotate over or below checkNode
        AVLNode<Key, Value>* checkNodeParent = checkNode->getParent();

        int leftheight = -1;
        if(checkNode->getLeft() != NULL)
            leftheight = checkNode->getLeft()->getHeight();
        int rightheight = -1;
        if(checkNode->getRight() != NULL)
            rightheight = checkNode->getRight()->getHeight();

        //when unbalanced, when difference is 2 or more
        if(abs(leftheight-rightheight) >= 2)
        {
            //Z is the checkNode, Y is the heavier child of checkNode, X is the heavier child of Y
            AVLNode<Key, Value>* Y = NULL;
            AVLNode<Key, Value>* X = NULL;

            //traverse to the heavier LEFT, must be at least height 1, must have at least one child of its own
            if(leftheight > rightheight)
            {
                //instantiate Y
                Y = checkNode->getLeft();

                //get the heights for left and right of Y, -1 if it's not there
                int YLheight = -1;
                if(Y->getLeft() != NULL)
                    YLheight = Y->getLeft()->getHeight();
                int YRheight = -1;
                if(Y->getRight() != NULL)
                    YRheight = Y->getRight()->getHeight();

                //if tie or if Y's left is heavier, go to LEFT for zig zig LEFT-LEFT traversal
                if(YLheight >= YRheight)
                {
                    //set X value
                    X = Y->getLeft();
                    //right rotate
                    this->rightRotate(checkNode);
                    //get maximum child height of checkNode Z
                    int maxchildZ = getMaxChildHeight(checkNode);
                    //set height for Z
                    checkNode->setHeight(maxchildZ + 1);
                    //set height for Y, the max of Z and X
                    Y->setHeight(getMaxChildHeight(Y) + 1);
                    //X height is unchanged
                    //update checkNode
                    checkNode = checkNodeParent;
                }

                //if right is heavier, this is a zig zag, LEFT-RIGHT traversal
                else if(YLheight < YRheight)
                {
                    X = Y->getRight();
                    //do left rotate on Y, the right rotate on Z (checkNode)
                    this->leftRotate(Y);
                    this->rightRotate(checkNode);
                    //get maximum child height of checkNode Z
                    int maxchildZ = getMaxChildHeight(checkNode);
                    //set height for Z
                    checkNode->setHeight(maxchildZ + 1);
                    //get maximum child height of Y
                    int maxchildY = getMaxChildHeight(Y);
                    //set height for Z
                    Y->setHeight(maxchildY + 1);
                    //update height of X, which is max of Z and Y
                    X->setHeight(getMaxChildHeight(X) + 1);
                    //update checkNode
                    checkNode = checkNodeParent;
                }
            }

            //traverse to the heavier RIGHT, must be at least height 1, must have at least one child of its own
            else if (leftheight < rightheight)
            {
                //instantiate Y
                Y = checkNode->getRight();

                //get the heights for left and right of Y, -1 if it's not there
                int YLheight = -1;
                if(Y->getLeft() != NULL)
                    YLheight = Y->getLeft()->getHeight();
                int YRheight = -1;
                if(Y->getRight() != NULL)
                    YRheight = Y->getRight()->getHeight();

                //if tie or if Y's right is heavier, go to RIGHT for zig zig RIGHT-RIGHT traversal
                if(YLheight <= YRheight)
                {
                    X = Y->getRight();
                    //left rotate for zig zig
                    this->leftRotate(checkNode);
                    //get maximum child height of checkNode Z
                    int maxchildZ = getMaxChildHeight(checkNode);
                    //set height for Z
                    checkNode->setHeight(maxchildZ + 1);
                    //set height for Y, the max of Z and X + 1
                    Y->setHeight(getMaxChildHeight(Y) + 1);
                    //X height is unchanged
                    //update checkNode
                    checkNode = checkNodeParent;
                }

                //if left is heavier, this is a zig zag, RIGHT-LEFT traversal
                else if(YLheight > YRheight)
                {
                    X = Y->getLeft();
                    //do right rotate on Y, the left rotate on Z (checkNode)
                    this->rightRotate(Y);
                    this->leftRotate(checkNode);
                    //get maximum child height of checkNode Z
                    int maxchildZ = getMaxChildHeight(checkNode);
                    //set height for Z
                    checkNode->setHeight(maxchildZ + 1);
                    //get maximum child height of Y
                    int maxchildY = getMaxChildHeight(Y);
                    //set height for Y
                    Y->setHeight(maxchildY + 1);
                    //update height of X, which is max of Z and Y
                    X->setHeight(getMaxChildHeight(X) + 1);

                    //update checkNode
                    checkNode = checkNodeParent;
                }
            }
        }

        //otherwise is balanced at this node, go to next parent
        else 
        {
            checkNode = checkNodeParent;
        }
    }
}

//helper function returns the maximum height of both of its children
template<typename Key, typename Value>
int AVLTree<Key, Value>::getMaxChildHeight(AVLNode<Key, Value>* parentNode)
{
    //start at assuming NULL
    int maxchild = -1;
    if(parentNode->getLeft() != NULL)
    {
        maxchild = parentNode->getLeft()->getHeight();
    }

    if(parentNode->getRight() != NULL)
    {
        if(parentNode->getRight()->getHeight() > maxchild)
        {
            maxchild = parentNode->getRight()->getHeight();
        }
    }

    return maxchild;
}


//BST remove helper, removes node and returns the next node that needs to be reevaluated for height after removing node, 
//if it was the root we are removing return NULL
template<typename Key, typename Value>
AVLNode<Key, Value>* AVLTree<Key, Value>::BST_remove_helper(const Key& key)
{
    //the node to remove, O(h) to find, rest takes constant time
    AVLNode<Key, Value>* removeNode = static_cast<AVLNode<Key,Value>*>(this->internalFind(key));

    //if not in the tree or if tree is empty, do nothing
    if(removeNode == NULL || this->mRoot == NULL)
    {
        return NULL;
    }


    //case where we are removing the SINGLE root node in the tree, when it has neither left nor right
    else if(removeNode == this->mRoot && removeNode->getLeft() == NULL && removeNode->getRight() == NULL)
    {
        delete removeNode;
        this->mRoot = NULL;
        return NULL;
    }


    //in the case where the removeNode is the root and only has one child (only one of the children is NULL now)
    else if(removeNode == this->mRoot && (removeNode->getLeft() == NULL || removeNode->getRight() == NULL))
    {
        //if the singular child is on the left
        if(removeNode->getLeft() != NULL)
        {
            this->mRoot = removeNode->getLeft();
            //update its parent to NULL
            removeNode->getLeft()->setParent(NULL);
        }

        //if the singular child is on the right
        else if(removeNode->getRight() != NULL)
        {
            this->mRoot = removeNode->getRight();
            //update its parent to NULL
            removeNode->getRight()->setParent(NULL);
        }

        delete removeNode;
        //the next node that needs to be reevaluated for height is the new mRoot
        //will already be height adjusted
        return static_cast<AVLNode<Key,Value>*>(this->mRoot);
    }

    //in the case where it is a leaf node, has no children, just updating parent's child (will have a parent, isn't root)
    else if(removeNode != this->mRoot && removeNode->getLeft() == NULL && removeNode->getRight() == NULL)
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

        //the next node that needs to be reevaluated for height is removeNode's parent node
        AVLNode<Key, Value>* returnParent = removeNode->getParent();
        //set height of parent
        returnParent->setHeight(getMaxChildHeight(returnParent)+1);
        delete removeNode;
        return returnParent;
    }

    //in the case where the removeNode is NOT root and only has one child (only one of the children is NULL now)
    else if(removeNode != this->mRoot && (removeNode->getLeft() == NULL || removeNode->getRight() == NULL))
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

        //the next node that needs to be reevaluated for height is removeNode's parent node
        AVLNode<Key, Value>* returnParent = removeNode->getParent();
        //set height of parent
        returnParent->setHeight(getMaxChildHeight(returnParent)+1);
        delete removeNode;
        return returnParent;
    }


    //now we know that if none of above were true, then removeNode must have TWO children.
    else if(removeNode->getLeft() != NULL && removeNode->getRight() != NULL)
    {
        //find the predecessor to promote, start by going left one times
        AVLNode<Key, Value>* predecessor = removeNode->getLeft();

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
            if(removeNode == this->mRoot)
            {
                this->mRoot = predecessor;
                predecessor->setParent(NULL);
            }

            //otherwise update predecessor's parent and removeNode's parent's left child
            else if(removeNode != this->mRoot)
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

            //the next node that needs to be reevaluated for height is predecessor as it has to recompare children
            delete removeNode;
            //set height of predecessor
            predecessor->setHeight(getMaxChildHeight(predecessor)+1);
            return predecessor;
        }

        //if we moved right at least once
        else if(predecessor->getParent() != removeNode)
        {
            //value we want to return
            AVLNode<Key, Value>* predecessors_initial_parent = predecessor->getParent();

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
            if(removeNode == this->mRoot)
            {
                this->mRoot = predecessor;
                predecessor->setParent(NULL);
            }
            //if removeNode is not root node, update parent links
            else if(removeNode != this->mRoot)
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

            //the next node that needs to be reevaluated for height is predecessor as it has to recompare children
            delete removeNode;
            //set height of predecessor's original parent
            predecessors_initial_parent->setHeight(getMaxChildHeight(predecessors_initial_parent)+1);            
            return predecessors_initial_parent;
        }
    }

    //should never get here but catch all just in case
    delete removeNode;
    return NULL;
}


/*
------------------------------------------
End implementations for the AVLTree class.
------------------------------------------
*/

#endif
