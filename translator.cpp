#include "translator.h"
#include<stack>
#include<queue>
#include<sstream>
#include <iostream>

translator::translator()
{
}

translator::~translator()
{
}

inline size_t translator::to_number(std::string str)
{
	if (!str.size() || !isdigit(str[0]))return 0;
	std::stringstream ss;
	size_t res;
	ss << str;
	ss >> res;
	return res;
}

std::vector<std::vector<std::pair<size_t, std::string>>> translator::getExpTuple(generalTreeNode* root)
{
	if (root->val.first == 100) {
		return { 
			{ root->val,{0,"-"},{0,"-"},{0,"-"} } 
		};
	}
	std::vector<std::vector<std::pair<size_t, std::string>>> res;
	std::stack<generalTreeNode*> father;
	std::stack<std::pair<size_t, std::string>> tmp;
	size_t count = 0;
	auto cur = root;
	auto genericQuaternion = [&]() {
		std::pair<size_t, std::string> parameter_1, parameter_2, parameter_3;
		if (cur->first_son->val.second == "�����") {
			parameter_1 = tmp.top();
			tmp.pop();
		}
		else {
			parameter_1 = cur->first_son->val;
		}
		if (cur->val.first != 35) {
			if (cur->first_son->next_bro->val.second == "�����") {
				parameter_2 = tmp.top();
				tmp.pop();
			}
			else {
				parameter_2 = cur->first_son->next_bro->val;
			}
		}
		else {
			parameter_2 = { 0,"-" };
		}

		if (cur->val.first == 32) {
			parameter_3 = parameter_1;
		}
		else {
			parameter_3 = { ++count,TEMPORARY };
			tmp.push(parameter_3);
		}
		std::vector<std::pair<size_t, std::string>> quaternion = { 
			cur->val,
			parameter_1,
			parameter_2,
			parameter_3
		};
		res.push_back(quaternion);
	};
	//��һ�������������
	while (cur || !father.empty()) {
		if (cur) {
			father.push(cur);
			cur = cur->first_son;
		}
		else {
			cur = father.top();
			father.pop();
			//����
			if (cur->val.second == "�����")genericQuaternion();
			//std::cout << "(" << cur->val.first << "," << cur->val.second << ")" << std::endl;
			cur = cur->next_bro;
		}
	}
	return res;
}

size_t translator::count_instruction(generalTreeNode* root)
{
	size_t count = 0;
	auto q = root;
	std::stack<generalTreeNode*> s;
	while (q||!s.empty()) {
		if (q) {
			s.push(q);
			q = q->first_son;
		}
		else {
			q = s.top();
			s.pop();
			if (q->val.second == "�ؼ���" || q->val.second == "�����") {
				++count;
			}
			q = q->next_bro;
		}
	}
	return count;
}

std::vector<std::vector<std::pair<size_t, std::string>>> translator::getTuple(generalTreeNode* root) {
	std::vector<std::vector<std::pair<size_t, std::string>>> res;
	size_t address = 0;
	auto p = root;
	std::stack<generalTreeNode*> father;
	std::stack<std::pair<generalTreeNode*, std::vector<size_t>>> loop;
	bool output = false;
	while (p||!father.empty()) {
		if (p) {
			if (p->val.second == "�ؼ���") {
				if (p->val.first < 5) {
					auto q = p->first_son;
					size_t count = 1;
					//���qΪ�� �׳��쳣
					while (q) {
						q = q->next_bro;
						++count;
					}
					res.push_back({
							p->val,
							{count,"������ʶ������"},
							{0,"-"},
							{++address,"��һ��ָ���ַ"}
						});
				}
				else if (p->val.first < 6) {
					//return -->meanless end of program
					res.push_back({
							p->val,
							{0,"�������"},
							{0,"-"},
							{0,"-"}
						});
				}
				else if (p->val.first < 7) {
					//if���
					/*
							�˴������һ���������ʽ
					*/
					res.push_back({
						{0,"jmp"},
						{0,"-"},
						{++address,"Ϊ��"},
						{count_instruction(p) + address,"Ϊ��"}
						});
				}
				else if (p->val.first < 8) {
					//else ���

				}
				else if (p->val.first < 9) {
					//while���
					size_t sum = count_instruction(p);
					size_t judge = count_instruction(p->first_son);
					loop.push({ p->first_son , {address,judge,sum} });
				}
				else if (p->val.first < 10) {
					//break
					res.push_back({
						{0,"jmp"},
						{0,"-"},
						{0,"-"},
						{loop.top().second[0] + loop.top().second[2],"��һ��ָ���ַ"},
						});
				}
				else if (p->val.first < 11) {
					//continue
					res.push_back({
						{0,"jmp"},
						{0,"-"},
						{0,"-"},
						{loop.top().second[0]+ loop.top().second[2]- loop.top().second[1],"��һ��ָ���ַ"},
						});
				}
				else if (p->val.first < 12) {
					//print
					output = true;
				}
				father.push(p);
				p = p->first_son;
			}
			else if (p->val.second == "�����") {
				/*
				�������ʽ����
				*/
				p = father.top();
				father.pop();
				p = p->next_bro;
			}
			else if (p->val.first>99) {
				std::vector<std::vector<std::pair<size_t, std::string>>> exp;
				if (p->val.first == 103)exp = getExpTuple(p->first_son);
				else exp = getExpTuple(p);
				res.insert(res.end(), exp.begin(), exp.end());
				p = p->next_bro;
			}
			else if (p->val.second == "main") {
				father.push(p);
				p = p->first_son;
			}
			else{
				std::cerr <<p->val.first<<","<<p->val.second<< "�﷨����" << std::endl;
				exit(0);
			}
		}
		else {
			//�������ѭ������
			if (!loop.empty()) {
				auto q = loop.top().first;
				size_t destination = loop.top().second[0];
				loop.pop();
				/*
					����ѭ���жϱ��ʽ
				*/
				res.push_back({
						{0,"jmp"},
						{0,"-"},
						{destination,"Ϊ��"},
						{++address,"Ϊ��"},
					});

			}
			//�����Ҫ������
			if (output) {
				res.push_back({
					{0,"output"},
					{0,res.back()[3].second},
					{0,"-"},
					{++address,"��һ��ָ���ַ"}
					});
			}

			p = father.top();
			father.pop();
			p = p->next_bro;
		}
		++address;
	}
	return res;
}
