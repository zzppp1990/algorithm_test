/*
* 文件最长绝对路径
* 存在的问题：耗时较高，消耗内存较多
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>


enum NodeType {
    DIR_TYPE,
    FILE_TYPE
};

const char TABCHAR = '\t';
const char ENTERCHAR = '\n';
const char SEPRATORCHAR = '.';
const int INPUTERR = -1;

/*
孩子节点用vector<CPathNode> 来保存 待修改
*/
class CPathNode {
public:
    NodeType m_enNodeType;
    std::string m_sNodeName;
    CPathNode* m_poParentPathNode;
    std::vector<CPathNode> m_vecChildPathNode;
    int m_iNodePathDepth;

public:
    CPathNode () : m_enNodeType(DIR_TYPE),m_sNodeName(""),m_iNodePathDepth(0),m_poParentPathNode(nullptr) {
        m_vecChildPathNode.clear();
    }

    friend std::ostream& operator<<(std::ostream& os, CPathNode& oPathNode) {
        return os << "NodeName = " << oPathNode.m_sNodeName 
                  << "\t NodeType = " << oPathNode.m_enNodeType
                  << "\t ChildNodeNum = " << oPathNode.m_vecChildPathNode.size() 
                  << "\t NodePathDepth = "<< oPathNode.m_iNodePathDepth;
    }
};

class CPathTree {
public:
    CPathNode m_oRoot;
    std::string m_sInputStr;
    int m_iLongestLength;
    int m_iCurrentLength;

public:
    CPathTree(std::string str="") : m_sInputStr(str),m_iLongestLength(0),m_iCurrentLength(0) {}
    
    /*获取根节点*/
    int parseRootNode(std::string input, std::string& sRemainInputStr, CPathNode& oPathNode) {
        sRemainInputStr = input;
        oPathNode.m_enNodeType = FILE_TYPE;
        oPathNode.m_iNodePathDepth = -1;
        oPathNode.m_sNodeName = "";
        
        return 0;
    }

    void getNodeName(std::string& input, std::string& nodeName, std::string& t_sRemainInputStr) {
        int iPos = 0;
        int iIputStrlen = input.length();
        
        for(iPos = 0; iPos < iIputStrlen; ++iPos) {
            if(input[iPos] == ENTERCHAR)
                break;
        }

        nodeName = input.substr(0, iPos);
        if(iPos == iIputStrlen) {
            t_sRemainInputStr = "";
        }
        else {
            t_sRemainInputStr = input.substr(iPos, iIputStrlen - iPos);
        }
    }

    NodeType getNodeType(std::string& nodename) {
        std::size_t ulFound = nodename.find(SEPRATORCHAR);
        if(std::string::npos != ulFound) {
            return FILE_TYPE;
        }
        else {
            return DIR_TYPE;
        }
    }

    /*解析其他节点
      返回值：当前的pos值
    */
    void parseTreeNode(std::string input, int iCurrentPathDepth,std::string& sRemainInputStr, 
                        CPathNode& oParentPathNode, CPathNode& oCurrentPathNode) {
        std::cout << "--------" << input << std::endl;
        CPathNode t_oPathNode;
        int iIputStrlen = input.length();
        int iSepratorPos = 0;
        int iTabCharNum = 0;

        for(int i = 0; i < iIputStrlen; ++i) {
            if( input[i] == ENTERCHAR) {
                continue;
            }
            else if ( input[i] == TABCHAR) {
                ++iTabCharNum;
            }
            else {
                iSepratorPos = i;
                break;
            }
        }
        
        if(iTabCharNum == iCurrentPathDepth) {
            std::string tmpStr = input.substr(iSepratorPos, iIputStrlen - iSepratorPos);
            std::string t_sNodeName = "";
            std::string t_sRemainInputStr = "";
            getNodeName( tmpStr, t_sNodeName, t_sRemainInputStr);
            t_oPathNode.m_sNodeName = t_sNodeName;
            t_oPathNode.m_iNodePathDepth = iTabCharNum;
            t_oPathNode.m_enNodeType = getNodeType(t_sNodeName);
            t_oPathNode.m_poParentPathNode = &oParentPathNode;
            oParentPathNode.m_vecChildPathNode.push_back(t_oPathNode);
            sRemainInputStr = t_sRemainInputStr;
            
            /*准备下次递归初始条件*/
            if(t_sRemainInputStr.length()) {
                int t_iSize = oParentPathNode.m_vecChildPathNode.size();
                parseTreeNode ( t_sRemainInputStr, iCurrentPathDepth, sRemainInputStr, oParentPathNode,
                            oParentPathNode.m_vecChildPathNode[t_iSize-1]);
            }
        }
        else if(iTabCharNum > iCurrentPathDepth) {
            parseTreeNode ( input, iTabCharNum, sRemainInputStr, oCurrentPathNode, oCurrentPathNode);
        }
        else {
            parseTreeNode (input, --iCurrentPathDepth, sRemainInputStr, *(oParentPathNode.m_poParentPathNode),oParentPathNode);
        }
    }
    
    /*初始化树*/
    void InitPathTree () {
        std::string t_sRemainStr;
        int iCurrentDepth = 0;
        int iLen = parseRootNode (m_sInputStr, t_sRemainStr, m_oRoot);

        //iCurrentDepth = m_oRoot.m_iNodePathDepth + 1;
        std::string fullstr = "\n";
        fullstr += t_sRemainStr;
        t_sRemainStr = fullstr;
        
        iCurrentDepth = m_oRoot.m_iNodePathDepth;
        while(t_sRemainStr.length()) {
            parseTreeNode ( t_sRemainStr, iCurrentDepth, t_sRemainStr, m_oRoot, m_oRoot);
        }
    }

    /*输出树 层序*/
    void printPathTree ( CPathNode& node) {
        std::cout << "node.depth = " << node.m_iNodePathDepth << std::endl;
        std::cout << "\t node = " << node << std::endl;
        
        for(auto it = node.m_vecChildPathNode.begin(); 
            it != node.m_vecChildPathNode.end(); ++it) {
            printPathTree ( *it);
        }
    }

    /*输出文件绝对路径*/
    void getFileAbsPath(CPathNode& node, std::string filePathStr) {
        filePathStr += node.m_sNodeName;
        if(node.m_enNodeType == DIR_TYPE) {
            filePathStr += '/';
        }
        else {
            std::cout << filePathStr << std::endl;
            int len = filePathStr.length();
            m_iLongestLength = std::max(m_iLongestLength, len);
        }

        for(auto it = node.m_vecChildPathNode.begin(); 
            it != node.m_vecChildPathNode.end(); ++it) {
            getFileAbsPath ( *it, filePathStr);
        }
    }
};

class Solution {
public:
    
    int lengthLongestPath(std::string input) {
        
        CPathTree t_oPathTree(input);
        t_oPathTree.InitPathTree();
        t_oPathTree.printPathTree(t_oPathTree.m_oRoot);
        
        std::string filePathStr = "";
        t_oPathTree.getFileAbsPath(t_oPathTree.m_oRoot, filePathStr);
        std::cout << "---------- longest length is " << t_oPathTree.m_iLongestLength << std::endl;
        return t_oPathTree.m_iLongestLength;
    }
};

int main ()
{
    Solution s;
    //s.lengthLongestPath("dir\n\tsubdir1\n\t\tfile1.ext\n\t\tsubsubdir1\n\tsubdir2\n\t\tsubsubdir2\n\t\t\tfile2.ext");
    //s.lengthLongestPath("a");
    s.lengthLongestPath("file1.txt\nfile2.txt\nlongfile.txt");
    return 0;
}

