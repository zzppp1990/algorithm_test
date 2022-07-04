/*
* leetcodeµÿ÷∑£∫
* https://leetcode.cn/problems/rearrange-spaces-between-words/
*/

#include <iostream>
#include <vector>
#include <string>
using namespace std;

#define SPACE ' '

class Solution {
public:
	vector<string> m_vecWords;
	int m_iTotalSpaceNum;
	int m_iSpaceNumBetweenWords;
	int m_iRemainSpaceNum;
	int m_iWordsNum;
public:
	Solution() : m_iTotalSpaceNum(0), m_iSpaceNumBetweenWords(0), m_iRemainSpaceNum(0), m_iWordsNum(0){
		m_vecWords.clear();
	}

	void dumpInfo() {
		cout << " m_iTotalSpaceNum = " << m_iTotalSpaceNum
			<< " words num = " << m_vecWords.size() 
			<< " m_iRemainSpaceNum = " << m_iRemainSpaceNum 
			<< " m_iSpaceNumBetweenWords = " << m_iSpaceNumBetweenWords << endl;
	}

	void getSpaceNumBetweenWords() {
		if (m_iWordsNum == 1) {
			m_iRemainSpaceNum = m_iTotalSpaceNum;
		}
		else {
			int devideNum = m_iWordsNum - 1;
			m_iRemainSpaceNum = m_iTotalSpaceNum % devideNum;
			m_iSpaceNumBetweenWords = m_iTotalSpaceNum / devideNum;
		}
	}

	string getSpaceStr(int num) {
		string tmp = "";
		for (int i = 0; i < num; ++i) {
			tmp += SPACE;
		}
		return tmp;
	}

	string reorderSpaces(string text) {
		string tmp = "";
		string resultStr = "";
		m_vecWords.clear();
		for (int i = 0; i < text.length(); ++i) {
			if (text[i] == SPACE) {
				if (tmp.length() > 0) {
					m_vecWords.push_back(tmp);
					tmp = "";
				}
				m_iTotalSpaceNum++;
			}
			else {
				tmp += text[i];
			}
		}
		if (tmp.length() > 0) {
			m_vecWords.push_back(tmp);
			tmp = "";
		}
		m_iWordsNum = m_vecWords.size();
		getSpaceNumBetweenWords();
		string t_strBetweenWords = getSpaceStr(m_iSpaceNumBetweenWords);
		string t_strRemainSpace = getSpaceStr(m_iRemainSpaceNum);
		for (int i = 0; i < m_iWordsNum - 1; ++i) {
			resultStr += m_vecWords[i];
			resultStr += t_strBetweenWords;
		}
		int index = m_iWordsNum - 1;
		resultStr += m_vecWords[index];
		resultStr += t_strRemainSpace;

		return resultStr;
	}
};

int main() {
	Solution s;
	string result = s.reorderSpaces("  this   is  a sentence ");
	s.dumpInfo();
	cout << result << endl;

	return 0;
}