#include "bst.h"

#include <stack>
#include <queue>
#include <set>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <climits>

using namespace std;



//recursive alternative for isBST
//return true if current node and all subtrees are valid
bool helper(Node* curr, int min, int max)
{
	//if curr is null it is valid
	if(curr == nullptr)
	{
		return true;
	}

	if(curr->key <= max && curr->key >= min)
	{
		//if min 
		return helper(curr->left, min, curr->key) && helper(curr->right, curr->key, max);
	}

	else
	{
		return false;
	}
}


//Helper functions?
bool isBST(Node *root) 
{
	return helper(root, INT_MIN, INT_MAX);
	/*
	queue<Node*> searchqueue;
	searchqueue.push(root);
	while(!searchqueue.empty())
	{
		Node* thisnode = searchqueue.front();
		searchqueue.pop();

		//if a leaf node, go to next in queue
		if(thisnode->left == nullptr && thisnode->right == nullptr)
		{
			continue;
		}

		//if it only has a left child
		if(thisnode->left != nullptr && thisnode->key > thisnode->left->key && thisnode->right == nullptr)
		{
			searchqueue.push(thisnode->left);
			continue;
		}
		//if it is not larger than left child and it exists
		else if(thisnode->left != nullptr && thisnode->key <= thisnode->left->key && thisnode->right == nullptr)
		{
			return false;
		}

		//if it only has a right child and it satisfies conditions
		if(thisnode->right != nullptr && thisnode->key < thisnode->right->key && thisnode->left == nullptr)
		{
			searchqueue.push(thisnode->right);
			continue;
		}
		//if it is not smaller than right child and it exists
		else if(thisnode->right != nullptr && thisnode->key >= thisnode->right->key && thisnode->left == nullptr)
		{
			return false;
		}

		//at this point if it reaches here it must have 2 children, assume both exist
		//if it is larger than its left child and smaller than its right child, if both exist
		if(thisnode->key < thisnode->right->key && thisnode->key > thisnode->left->key)
		{
			searchqueue.push(thisnode->left);
			searchqueue.push(thisnode->right);
		}
		//if both exist yet left is not smaller or right is not larger	
		else
		{
			return false;
		}
	}

    return true;
    */
}





//helper for isBalanced
int treeHeight(Node* currentnode)
{
	//for the leaf nodes
	if(currentnode == nullptr)
	{
		return 0;
	}

	//left side height
	int leftheight = treeHeight(currentnode->left);
	//if left height is -1, then force return -1 so that it gets passed up the stack
	if(leftheight == -1)
	{
		return -1;
	}

	int rightheight = treeHeight(currentnode->right);
	//if left height is -1, then force return -1 so that it gets passed up the stack
	if(rightheight == -1)
	{
		return -1;
	}

	//if the right side and left side differ by 2 or more
	if(abs(rightheight - leftheight) > 1)
	{
		return -1;
	}

	//return the max height of left and right nodes if it is not a leaf node and both left and right is balanced
	return max(leftheight, rightheight) + 1;
}

//Helper functions?
bool isBalanced(Node *root) 
{
	if(treeHeight(root) == -1)
	{
		return false;
	}

	return true;
}