#include "CPathTree.h"

CPathTree::CPathTree(std::string str) : m_sInputStr(str),m_iLongestLength(0),m_iCurrentLength(0) {}
    
/*获取根节点*/
int CPathTree::parseRootNode(std::string input, std::string& sRemainInputStr, CPathNode& oPathNode) {
    sRemainInputStr = input;
    oPathNode.m_enNodeType = FILE_TYPE;
    oPathNode.m_iNodePathDepth = -1;
    oPathNode.m_sNodeName = "";
    
    return 0;
}

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

NodeType CPathTree::getNodeType(std::string& nodename) {
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
void CPathTree::parseTreeNode(std::string input, int iCurrentPathDepth,std::string& sRemainInputStr, 
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
void CPathTree::InitPathTree () {
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

