#ifndef __BINTREE_H__
#define __BINTREE_H__

#include "BinNode.h"

/*二叉树模板类*/
template <typename T> class BinTree {
protected:
    /*规模*/
    int _size;
    /*根节点*/
    BinNodePosi(T) _root;

    /*更新节点x的高度*/
    virtual int updateHeight(BinNodePosi(T) x) {
        return x->height = 1 + std::max( stature(x->lc), stature(x->rc));
    }
    /*更新节点x及其祖先的高度*/
    void updateHeightAbove(BinNodePosi(T) x) {
        while(x) {
            updateHeight(x);
            x = x->parent;
        }
    }

public:
    BinTree() : _size(0), _root(NULL) {}
    ~BinTree() {
        if(0 < _size) {
    //        remove(_root);
        }
    }

    int size() const {
        return _size;
    }

    bool empty() const {
        return !_root;
    }

    BinNodePosi(T) root() const {
        return _root;
    }

    /*插入根节点*/
    BinNodePosi(T) insertAsRoot(T const& e) {
        _size = 1;
        return _root = new BinNode<T>(e);
    }

    /*e作为x的左孩子插入*/
    BinNodePosi(T) insertAsLC(BinNodePosi(T) x, T const& e) {
        _size++;
        x->insertAsLC(e);
        updateHeightAbove(x);
        return x->lc;
    }
    /*e作为x的右孩子插入*/
    BinNodePosi(T) insertAsRC(BinNodePosi(T) x, T const& e) {
        _size++;
        x->insertAsRC(e);
        updateHeightAbove(x);
        return x->rc;
    }

    /*T作为x的左子树接入*/
    BinNodePosi(T) attachAsLC(BinNodePosi(T) x, BinTree<T>*& S) {
        if(x->lc = S->root) {
            x->lc->parent = x;
        }
        _size += S->size();
        updateHeightAbove(x);
        /*释放原树返回接入位置*/
        S->root = NULL;
        S->_size = 0;
        S = NULL;
        return x;
    }
    /*T作为x的右子树接入*/
    BinNodePosi(T) attachAsRC(BinNodePosi(T) x, BinTree<T>*& S) {
        if(x->rc = S->root) {
            x->rc->parent = x;
        }
        _size += S->_size;
        updateHeightAbove(x);
        return x;
    }
    /*先序遍历*/
    void travPre() {
        if (_root) {
            _root->travPre();
        }
    }

    /*中序遍历*/
    void travIn() {
        if(_root) {
            _root->travIn();
        }
    }
};

#endif