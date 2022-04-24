#ifndef _CPATHNODE_H_
#define _CPATHNODE_H_

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "Util.h"

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
    CPathNode();
    ~CPathNode();
    friend std::ostream& operator<<(std::ostream& os, CPathNode& oPathNode);
};

#endif //_CPATHNODE_H_