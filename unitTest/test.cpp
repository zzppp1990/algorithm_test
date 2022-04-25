/*
* 单元测试
*/

#include <stdexcept>
#include <catch.hpp>
#include <CPathNode.h>
#include <CPathTree.h>

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



void test(int n)
{
  if (n == 42) {
    return;
  }
  throw std::runtime_error(
    "Not the answer");
}

/*CPathNode类构造函数测试*/
TEST_CASE("CPathNode test", "[1]")
{
  INFO("CPathNode test");
  CPathNode t_oPathNode;
  CHECK(t_oPathNode.m_vecChildPathNode.size() == 0);
  CHECK(t_oPathNode.m_iNodePathDepth == -1);
  CHECK(t_oPathNode.m_enNodeType == FILE_TYPE);
  CHECK(t_oPathNode.m_poParentPathNode == nullptr);
  CHECK(t_oPathNode.m_sNodeName == "");
}

/*CPathTree::getNodeName 函数测试*/
TEST_CASE("CPathTree test getNodeName", "[my]")
{
  INFO("CPathTree test getNodeName");
  CPathTree t_oPathTree;

  std::string input = "file1.txt";
  std::string nodeName = "file1.txt";
  std::string t_sRemainInputStr = "";
  t_oPathTree.getNodeName(input, nodeName, t_sRemainInputStr);
  CHECK(nodeName == "file1.txt");
  CHECK(t_sRemainInputStr == "");

  input = "file1.txt\nfile2.txt\nlongfile.txt";
  nodeName = "file1.txt";
  t_sRemainInputStr = "";
  t_oPathTree.getNodeName(input, nodeName, t_sRemainInputStr);
  CHECK(nodeName == "file1.txt");
  CHECK(t_sRemainInputStr == "\nfile2.txt\nlongfile.txt");

  input = "";
  nodeName = "";
  t_sRemainInputStr = "";
  t_oPathTree.getNodeName(input, nodeName, t_sRemainInputStr);
  CHECK(nodeName == "");
  CHECK(t_sRemainInputStr == "");
}

/*CPathTree::getNodeName 函数测试*/
TEST_CASE("CPathTree test getNodeType", "[my]")
{
  INFO("CPathTree test getNodeType");
  CPathTree t_oPathTree;

  std::string nodeName = "file1.txt";
  NodeType ret = t_oPathTree.getNodeType(nodeName);
  CHECK(ret == FILE_TYPE);

  nodeName = "dir";
  ret = t_oPathTree.getNodeType(nodeName);
  CHECK(ret == DIR_TYPE);
}

/*Solution::lengthLongestPath 函数测试*/
TEST_CASE("Solution test lengthLongestPath", "[my]")
{
  INFO("Solution test lengthLongestPath");
  Solution s;
  int ret = s.lengthLongestPath("file1.txt\nfile2.txt\nlongfile.txt");
  CHECK(ret == 12);

  ret = s.lengthLongestPath("dir\n\tsubdir1\n\t\tfile1.ext\n\t\tsubsubdir1\n\tsubdir2\n\t\tsubsubdir2\n\t\t\tfile2.ext");
  CHECK(ret == 32);

  ret = s.lengthLongestPath("a");
  CHECK(ret == 0);

  ret = s.lengthLongestPath("dir\n\tsubdir1\n\tsubdir2\n\t\tfile.ext");
  CHECK(ret == 20);
}


