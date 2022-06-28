#ifndef __BINNODE_H__
#define __BINNODE_H__

#include <iostream>
#include <stdlib.h>

#define BinNodePosi(T) BinNode<T>*
#define stature(p) ((p) ? (p)->height : -1)
typedef enum {RB_RED, RB_BLACK} RBColor;

/*二叉树节点类*/
template <typename T> struct BinNode {
    T data; //数值
    BinNodePosi(T) parent; //父节点
    BinNodePosi(T) lc; //左孩子
    BinNodePosi(T) rc; //右孩子
    int height; //高度
    int npl;  //null path length 左式堆，也可直接用height代替
    RBColor color; //颜色(红黑树)

    //构造函数
    BinNode() :
        parent(NULL), lc(NULL), rc(NULL), height(0), npl(1), color(RB_RED) {}

    BinNode (T e, BinNodePosi(T) p = NULL, BinNodePosi(T) lc = NULL, BinNodePosi(T) rc = NULL,
        int h = 0, int l = 1, RBColor c = RB_RED) :
        data(e), parent(p), lc(lc), rc(rc), height(h), npl(l), color(c) {}

    //统计当前节点的后代总数，亦即以其为根的子树的规模
    int size() {
        return 0;
    }

    //作为当前节点的左孩子插入新节点
    BinNodePosi(T) insertAsLC(T const& e) {
        return lc = new BinNode( e, this);
    }
    //作为当前节点的右孩子插入新节点
    BinNodePosi(T) insertAsRC(T const& e) {
        return rc = new BinNode( e, this);
    }
    //取当前节点的直接后继
    BinNodePosi(T) succ() {
        return NULL;
    }

    void visit(T const& e) {
        std::cout << e << std::endl;
    }
    //子树层次遍历
    //template <typename VST> void travLevel( VST&) ;
    //子树先序遍历
    //template <typename VST> void travPre( VST&) ;
    void travPre_R( BinNodePosi(T) x) {
        if(!x)
            return;
        visit(x->data);
        travPre_R( x->lc);
        travPre_R( x->rc);
    }

    void travPre() {
        switch( rand() % 5) {
            case 1: travPre_R(this); break;
            default: travPre_R(this); break;
        }
    }
    //子树中序遍历
    //template <typename VST> void travIn( VST&) ;
    void travIn() {

    }
    //子树后序遍历
    //template <typename VST> void travPost( VST&) ;
    void travPost() {

    }

    bool operator< (BinNode const& bn) {
        return data < bn.data;
    }

    bool operator= (BinNode const& bn) {
        return data == bn.data;
    }
};

#define IsRoot(x) ( !( (x).parent))
#define IsLChild(x) ( !IsRoot(x) && ( &(x) == (x).parent->lc))
#define IsRChild(x) ( !IsRoot(x) && ( &(x) == (x).parent->rc))
#define HasParent(x) ( !IsRoot(x))
#define HasLChild(x) ( (x).lc)
#define HasRChild(x) ( (x).rc)
#define HasChild(x) ( HasLChild(x) || HasRChild(x))
#define HasBothChild(x) ( HasLChild(x) && HasRChild(x))
#define IsLeaf(x) (!HasChild(x))
/*兄弟*/
#define sibling(p) \
    (IsLChild( *(x) ) ? (p)->parent->rc : (p)->parent->lc)
/*叔叔*/
#define uncle(x) \
    ( IsLChild(*( (x)->parent)) ? (x)->parent->parent->rc) : (x)->parent->parent->lc)
/*来自父亲的引用*/
#define FromParentTo(x) \
    ( IsRoot(x) ? _root : ( IsLChild(x) ? (x).parent->lc : (x).parent->rc ) )

#endif
