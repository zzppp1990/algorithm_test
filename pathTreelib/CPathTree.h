#ifndef _CPATHTREE_H_
#define _CPATHTREE_H_

#include "CPathNode.h"

class CStrategy {
public:
    virtual ~CStrategy() {}
    virtual int getFileAbsPath() = 0;
    virtual void Init(std::string input) = 0;
};

class CPathTree : public CStrategy{
public:
    CPathNode m_oRoot;
    std::string m_sInputStr;
    int m_iLongestLength;

public:
    CPathTree(std::string str="");

    void getNodeName(std::string& input, std::string& nodeName, std::string& t_sRemainInputStr);

    NodeType getNodeType(std::string& nodename);

    void addTreeNodeChild(std::string& in_nodeName, int in_nodeDepth, 
                          NodeType in_nodeType, CPathNode& oParentPathNode);
    
    void parseTreeNode( int iCurrentPathDepth,std::string& sRemainInputStr,
                        CPathNode& oParentPathNode, CPathNode& oCurrentPathNode);
    
    /*初始化树*/
    void Init (std::string input) override;

    /*输出树 层序*/
    void printPathTree ( CPathNode& node);

    /*输出文件绝对路径*/
    void getFileAbsPath(CPathNode& node, std::string filePathStr);
    int  getFileAbsPath() override;
};

class CEasyStrategy : public CStrategy {
public:
    std::string m_sInputStr;
public:
    virtual int getFileAbsPath() override;
    virtual void Init(std::string input) override;
};



#endif //_CPATHTREE_H_

