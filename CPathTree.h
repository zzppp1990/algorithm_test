#ifndef _CPATHTREE_H_
#define _CPATHTREE_H_

#include "CPathNode.h"

class CPathTree {
public:
    CPathNode m_oRoot;
    std::string m_sInputStr;
    int m_iLongestLength;
    int m_iCurrentLength;

public:
    CPathTree(std::string str="");
    
    /*获取根节点*/
    int parseRootNode(std::string input, std::string& sRemainInputStr, CPathNode& oPathNode);

    void getNodeName(std::string& input, std::string& nodeName, std::string& t_sRemainInputStr);

    NodeType getNodeType(std::string& nodename);

    /*解析其他节点
      返回值：当前的pos值
    */
    void parseTreeNode(std::string input, int iCurrentPathDepth,std::string& sRemainInputStr,
                        CPathNode& oParentPathNode, CPathNode& oCurrentPathNode);
    
    /*初始化树*/
    void InitPathTree ();

    /*输出树 层序*/
    void printPathTree ( CPathNode& node);

    /*输出文件绝对路径*/
    void getFileAbsPath(CPathNode& node, std::string filePathStr);
};

#endif //_CPATHTREE_H_

