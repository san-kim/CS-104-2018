#include "traversal.h"

//include what you need :D
#include <vector>
#include <queue>
#include <set>
#include <iostream>

using namespace std;

void PreOrder(vector<int>& result, Node *start) 
{
	result.push_back(start->val);

	if(start->left != nullptr) 
	{
        PreOrder(result, start->left);
    }

    if(start->right != nullptr) 
    {
        PreOrder(result, start->right);
    }
}

void InOrder(vector<int>& result, Node *start) 
{
	if(start->left != nullptr) 
	{
        InOrder(result, start->left);
    }

	result.push_back(start->val);

    if(start->right != nullptr) 
    {
        InOrder(result, start->right);
    }
}

void PostOrder(vector<int>& result, Node *start) 
{
	if(start->left != nullptr) 
	{
        PostOrder(result, start->left);
    }

    if(start->right != nullptr) 
    {
        PostOrder(result, start->right);
    }

    result.push_back(start->val);
}

//helper functions are encouraged :D
void LevelOrder(vector<int>& result, Node *start) 
{
	queue<Node*> levelq;
	levelq.push(start);

	while(!levelq.empty())
	{
		Node* currentNode = levelq.front();
		levelq.pop();
		result.push_back(currentNode->val);

		if(currentNode->left != nullptr)
		{
			levelq.push(currentNode->left);
		}

		if(currentNode->right != nullptr)
		{
			levelq.push(currentNode->right);
		}
	}
}

//helper functions are encouraged :D
bool checkSymmetrical(Node *root) 
{
	queue<Node*> leftq;
	leftq.push(root->left);
	
	queue<Node*> rightq;
	rightq.push(root->right);

	//if the roots of each tree are not equal
	if(rightq.front()->val != leftq.front()->val)
	{
		return false;
	}

	while(!leftq.empty() && !rightq.empty())
	{
		Node* rightNode = rightq.front();
		Node* leftNode = leftq.front();
		rightq.pop();
		leftq.pop();

		if(rightNode->left != nullptr)
		{
			rightq.push(rightNode->left);
		}

		if(rightNode->right != nullptr)
		{
			rightq.push(rightNode->right);
		}

		if(leftNode->right != nullptr)
		{
			leftq.push(leftNode->right);
		}

		if(leftNode->left != nullptr)
		{
			leftq.push(leftNode->left);
		}

		//if the left values are not populated in the same way
		if((leftNode->left == nullptr && rightNode->left != nullptr) || 
			(leftNode->left != nullptr && rightNode->left == nullptr))
		{
			return false;
		}

		//if the right values are not populated in the same way
		if((leftNode->right == nullptr && rightNode->right != nullptr) || 
			(leftNode->right != nullptr && rightNode->right == nullptr))
		{
			return false;
		}
		
		if(leftNode->right != nullptr && leftNode->left != nullptr && rightNode->right != nullptr && rightNode->left != nullptr)
		{
			if(leftNode->right->val != rightNode->left->val || leftNode->left->val != rightNode->right->val)
			{
				return false;
			}
		}
	}

	return true;
}