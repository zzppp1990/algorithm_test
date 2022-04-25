#include "CPathTree.h"
#include <sstream>

CPathTree::CPathTree(std::string str) : m_sInputStr(str),m_iLongestLength(0) {}

/*
* 获取节点的名称
*/
void CPathTree::getNodeName(std::string& input, std::string& nodeName, std::string& t_sRemainInputStr) {
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

/*
* 获取节点类型
*/
NodeType CPathTree::getNodeType(std::string& nodename) {
    std::size_t ulFound = nodename.find(SEPRATORCHAR);
    if(std::string::npos != ulFound) {
        return FILE_TYPE;
    }
    else {
        return DIR_TYPE;
    }
}

void CPathTree::addTreeNodeChild(std::string& in_nodeName, int in_nodeDepth, 
                          NodeType in_nodeType, CPathNode& oParentPathNode) {

  CPathNode t_oPathNode;
  t_oPathNode.m_sNodeName = in_nodeName;
  t_oPathNode.m_iNodePathDepth = in_nodeDepth;
  t_oPathNode.m_enNodeType = in_nodeType;
  t_oPathNode.m_poParentPathNode = &oParentPathNode;
  oParentPathNode.m_vecChildPathNode.push_back(t_oPathNode);
  
}

/*
* 初始化以初始节点为根的树，挂到入参oParentPathNode上
*/
void CPathTree::parseTreeNode( int iCurrentPathDepth,std::string& sRemainInputStr, 
                    CPathNode& oParentPathNode, CPathNode& oCurrentPathNode) {
    int iIputStrlen = sRemainInputStr.length();
    int iSepratorPos = 0;
    int iTabCharNum = 0;

    for(int i = 0; i < iIputStrlen; ++i) {
        if( sRemainInputStr[i] == ENTERCHAR) {
            continue;
        }
        else if ( sRemainInputStr[i] == TABCHAR) {
            ++iTabCharNum;
        }
        else {
            iSepratorPos = i;
            break;
        }
    }
    
    if(iTabCharNum == iCurrentPathDepth) {
        std::string tmpStr = sRemainInputStr.substr(iSepratorPos, iIputStrlen - iSepratorPos);
        std::string t_sNodeName = "";
        std::string t_sRemainInputStr = "";
        getNodeName( tmpStr, t_sNodeName, t_sRemainInputStr);
        NodeType t_enNodeType = getNodeType(t_sNodeName);
        addTreeNodeChild( t_sNodeName, iTabCharNum, t_enNodeType, oParentPathNode);
        sRemainInputStr = t_sRemainInputStr;
        
        /*准备下次递归初始条件*/
        if(t_sRemainInputStr.length()) {
            int t_iSize = oParentPathNode.m_vecChildPathNode.size();
            parseTreeNode ( iCurrentPathDepth, sRemainInputStr, oParentPathNode,
                        oParentPathNode.m_vecChildPathNode[t_iSize-1]);
        }
    }
    else if(iTabCharNum > iCurrentPathDepth) {
        parseTreeNode ( iTabCharNum, sRemainInputStr, oCurrentPathNode, oCurrentPathNode);
    }
    else {
        parseTreeNode (--iCurrentPathDepth, sRemainInputStr, *(oParentPathNode.m_poParentPathNode),oParentPathNode);
    }
}

/*初始化整个树*/
void CPathTree::Init (std::string input) {
    std::string t_sRemainStr;
    int iCurrentDepth = 0;
    m_sInputStr = input;
    t_sRemainStr = m_sInputStr;
    m_iLongestLength = 0;
    m_oRoot.m_vecChildPathNode.clear();

    std::string fullstr = "\n";
    fullstr += t_sRemainStr;
    t_sRemainStr = fullstr;
    
    iCurrentDepth = m_oRoot.m_iNodePathDepth;
    while(t_sRemainStr.length()) {
        parseTreeNode ( iCurrentDepth, t_sRemainStr, m_oRoot, m_oRoot);
    }
}

/*输出树 层序*/
void CPathTree::printPathTree ( CPathNode& node) {
    std::cout << "node.depth = " << node.m_iNodePathDepth << std::endl;
    std::cout << "\t node = " << node << std::endl;
    
    for(auto it = node.m_vecChildPathNode.begin(); 
        it != node.m_vecChildPathNode.end(); ++it) {
        printPathTree ( *it);
    }
}

/*输出文件绝对路径*/
void CPathTree::getFileAbsPath(CPathNode& node, std::string filePathStr) {
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

int CPathTree::getFileAbsPath() {
    std::string filePathStr = "";
    getFileAbsPath(m_oRoot, filePathStr);
    return m_iLongestLength;
}

void CEasyStrategy::Init(std::string input) {
    m_sInputStr = input;
}

int CEasyStrategy::getFileAbsPath() {
    std::istringstream iss(m_sInputStr);
    std::vector<std::string> dirs;
    std::string str;
    while (getline(iss, str)) {
        dirs.push_back(str);
    }
    std::vector<int> pathLen(dirs.size()+1,0);
    int maxLen = 0;
    for (const std::string& s : dirs) {
        int i = 0;
        while (i < s.size() && s[i] == '\t') ++i;
        pathLen[i + 1] = pathLen[i] + s.size() - i+1;
        if (s.find('.') != std::string::npos) {
            maxLen = std::max(maxLen, pathLen[i + 1] - 1);
        }
    }
    return maxLen;
}


