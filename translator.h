#pragma once
#include<vector>
#include<string>
#include"lexicalAnalysis.h"
#include"syntaxAnalysis.h"

#define TEMPORARY "ͨ�üĴ���"

#define DECLARE_TYPE "��������"
#define DECLARE_NUMBER "��������"
#define END_OF_PROGRAM "�������"
#define UNCONDITIONAL "������ת��"
#define RESULT "����Ĵ���"
#define IS_TRUE "����Ĵ���Ϊ����ת����"
#define IS_FALSE "����Ĵ���Ϊ����ת����"
#define OUTPUT "���"
#define JUMP_TO "��ת����ַ"

class translator
{
public:
	translator();
	~translator();
	size_t to_number(std::string str);
	std::vector<std::vector<std::pair<size_t,std::string>>> getExpTuple(generalTreeNode* root);
	std::vector<std::vector<std::pair<size_t, std::string>>> getTuple(generalTreeNode* root);
	size_t count_instruction(generalTreeNode* root);
private:
	std::pair<size_t, std::string > result;
};

