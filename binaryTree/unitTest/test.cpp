/*
* 单元测试
*/

#include <stdexcept>
#include <catch.hpp>
#include <BinTree.h>


TEST_CASE("case_1", "[my]")
{
  INFO("Testing");
  srand((unsigned)time(NULL));
  BinTree<char> testTree;
  char t_cNode1 = 'i';
  BinNodePosi(char) x = testTree.insertAsRoot(t_cNode1);
  CHECK(testTree.size() == 1);
  CHECK(x->height == 0);

  char t_cNode2 = 'd';
  char t_cNode3 = 'l';
  BinNodePosi(char) xl = testTree.insertAsLC(x, t_cNode2);
  BinNodePosi(char) xr = testTree.insertAsRC(x, t_cNode3);
  CHECK(testTree.size() == 3);
  CHECK(x->height == 1);

  char t_cNode4 = 'c';
  char t_cNode5 = 'h';
  BinNodePosi(char) xll = testTree.insertAsLC(xl, t_cNode4);
  BinNodePosi(char) xrr = testTree.insertAsRC(xl, t_cNode5);
  CHECK(testTree.size() == 5);
  CHECK(x->height == 2);
  CHECK(xl->height == 1);
  testTree.travPre(); /*i d c h l*/
  std::cout << std::endl;
  testTree.travIn(); /*c d h i l*/
  std::cout << std::endl;
}


