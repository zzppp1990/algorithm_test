#include "CPathNode.h"

CPathNode::CPathNode () : m_enNodeType(DIR_TYPE),m_sNodeName(""),
                          m_iNodePathDepth(0),m_poParentPathNode(nullptr) {
        m_vecChildPathNode.clear();
}

CPathNode::~CPathNode() {

}


std::ostream& operator<<(std::ostream& os, CPathNode& oPathNode) {
    return os << "NodeName = " << oPathNode.m_sNodeName 
              << "\t NodeType = " << oPathNode.m_enNodeType
              << "\t ChildNodeNum = " << oPathNode.m_vecChildPathNode.size() 
              << "\t NodePathDepth = "<< oPathNode.m_iNodePathDepth;
}

