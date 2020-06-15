/*****************************************************************************
*  OpenST Basic tool library                                                 *
*  Copyright (C) 2020 Delta Delta37@qq.com			                         *
*                                                                            *
*  This file is part of OST.                                                 *
*                                                                            *
*  This program is free software; you can redistribute it and/or modify      *
*  it under the terms of the GNU General Public License version 3 as         *
*  published by the Free Software Foundation.                                *
*                                                                            *
*  You should have received a copy of the GNU General Public License         *
*  along with OST. If not, see <http://www.gnu.org/licenses/>.               *
*                                                                            *
*  Unless required by applicable law or agreed to in writing, software       *
*  distributed under the License is distributed on an "AS IS" BASIS,         *
*  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  *
*  See the License for the specific language governing permissions and       *
*  limitations under the License.                                            *
*                                                                            *
*  @file     translator.h                                                    *
*  @brief    Turn the syntax-analysis-tree to pseudo-assembly language.      *
*  Details.  Consist of the translation of expression and statement, the	 *
*            result only contains basic operating and transfer statement.    *
*  @author   Delta                                                           *
*  @email    Delta37@qq.com													 *
*  @version  1.0.0.1														 *
*  @date     2020/06/15		                                                 *
*  @license  GNU General Public License (GPL)                                *
*                                                                            *
*----------------------------------------------------------------------------*
*  Remark         : Description                                              *
*----------------------------------------------------------------------------*
*  Change History :                                                          *
*  <Date>     | <Version> | <Author>       | <Description>                   *
*----------------------------------------------------------------------------*
*  2020/06/15 | 1.0.0.1   | Delta          | define the virtual address      *
*----------------------------------------------------------------------------*
*                                                                            *
*****************************************************************************/

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

