#include "syntaxAnalysis.h"
#include<iostream>
#include<ctype.h>
#include<stack>
#include<unordered_set>

TreeNode::TreeNode(std::string val)
{
	this->val = val;
	this->left = nullptr;
	this->right = nullptr;
}
TreeNode::TreeNode(char val)
{
	this->val.push_back(val);
	this->left = nullptr;
	this->right = nullptr;
}
TreeNode::TreeNode()
{
	this->val = "";
	this->left = nullptr;
	this->right = nullptr;
}
generalTreeNode::generalTreeNode(std::string val)
{
	this->val = val;
	this->first_son = nullptr;
	this->next_bro = nullptr;
}
generalTreeNode::generalTreeNode()
{
	this->val = "";
	this->first_son = nullptr;
	this->next_bro = nullptr;
}
bool generic::priority(char a, char b)
{
	if (b == '*' || b == '/')return false;
	if (a == '*' || a == '/')return true;
	return false;
}
bool generic::priority(size_t a, size_t b) {
	if (b == 21 || b == 22)return false;
	if (a == 21 || a == 22)return true;
	return false;
}
TreeNode* generic::genericExp(std::string str) {
	std::stack<char> op;
	std::stack<TreeNode*> exp;
	auto genericMiniTree = [&]() {
		TreeNode* tmp = new TreeNode(op.top());
		op.pop();
		tmp->right = exp.top();
		exp.pop();
		tmp->left = exp.top();
		exp.pop();
		exp.push(tmp);
	};
	for (auto i : str) {
		if (i == '+' || i == '-' || i == '*' || i == '/') {
			if (!op.empty() && op.top() != '(')
				if (!priority(i, op.top()))genericMiniTree();
			op.push(i);
		}
		else if (i == '(') {
			op.push(i);
		}
		else if (i == ')') {
			while (op.top() != '(')genericMiniTree();
			op.pop();
		}
		else if (isalpha(i) || isdigit(i)) {
			exp.push(new TreeNode(i));
		}
		else {
			std::cerr << "wrong expression!";
			return NULL;
		}
	}
	while (!op.empty())genericMiniTree();
	return exp.top();
}
TreeNode* generic::genericExp(std::list<std::pair<size_t, std::string>> list)
{	
	std::stack<size_t> op;
	std::stack<TreeNode*> exp;
	auto genericMiniTree = [&]() {
		TreeNode* tmp = new TreeNode(std::to_string(op.top()));
		op.pop();
		tmp->right = exp.top();
		exp.pop();
		tmp->left = exp.top();
		exp.pop();
		exp.push(tmp);
	};
	for (auto i : list) {
		if (i.first == 19 || i.first == 20 || i.first == 21 || i.first == 22) {
			if (!op.empty() && op.top() != 17)
				if (!priority(i.first, op.top()))genericMiniTree();
			op.push(i.first);
		}
		else if (i.first == 17) {
			op.push(i.first);
		}
		else if (i.first == 18) {
			while (op.top() != 17)genericMiniTree();
			op.pop();
		}
		else if (i.first == 100 ||i.first == 101) {
			exp.push(new TreeNode(i.second));
		}
		else {
			std::cerr << "wrong expression!";
			return nullptr;
		}
	}
	while (!op.empty())genericMiniTree();
	return exp.top();
	return nullptr;
}
TreeNode* generic::genericStatement(std::list<std::pair<size_t, std::string>> list)
{
	return nullptr;
}
