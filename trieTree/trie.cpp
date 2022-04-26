//类似子网掩码
#include <stdio.h>
#include <stdlib.h>

#define MAX_CHARACTOR_NUM 26


typedef struct tire_node{
    int count; /* 该节点的单次数量 */
    struct tire_node* child[MAX_CHARACTOR_NUM];
} Trie;

/** Initialize your data structure here. */

Trie* allocTrieNode()
{
    Trie* obj = (Trie *)malloc(sizeof(Trie));
    if (obj == NULL) {
        return NULL;
    }
    obj->count = 0;
    for (int i = 0; i <  MAX_CHARACTOR_NUM; i++) {
        obj->child[i] = NULL;
    }
    return obj;
}

Trie* trieCreate() {
    return allocTrieNode();
}

/** Inserts a word into the trie. */
void trieInsert(Trie* obj, const char * word) {
    const char *p = word;
    Trie *node = obj;
    while (*p) {
        if (node->child[*p - 'a'] == NULL) { /* 对应的节点不存在，则申请一个节点 */
            node->child[*p - 'a'] = allocTrieNode();
        }
        node = node->child[*p - 'a']; /* 指向子节点 */
        p++;
    }
    node->count++;
}

/** Returns if the word is in the trie. */
bool trieSearch(Trie* obj, const char * word) {
    Trie *node = obj;
    const char *p = word;
    unsigned int  uiNodeIndex = 0;

    while (*p && node != NULL) {
        uiNodeIndex = (unsigned int)(*p - 'a');
        node = node->child[uiNodeIndex]; /* 循环在树中查找所有节点 */
        printf("%c",'a'+uiNodeIndex);
        p++;
    }

    if (node == NULL) {
    printf(" : trieSearch  not found.\n");
        return false; /* 未找到 */
    } else {
    printf(" : trieSearch  found.\n");
        return (node->count > 0 ? (true) : (false)); /* 找到了，但是不是有效单词，只是前缀返回false */
    }
}

/** Returns if there is any word in the trie that starts with the given prefix. */
bool trieStartsWith(Trie* obj, char * prefix) {
    Trie *node = obj;
    char *p = prefix;

    while (*p && node != NULL) {
        node = node->child[*p - 'a'];
        p++;
    }

    return (node == NULL ? (false) : (true));  /* 找到了返回true，未找到返回false，这里和前面查找整个word有点点区别 */
}

void trieFree(Trie* obj) {
    if (obj != NULL) {
        free(obj);
    }
}

/**
 * Your Trie struct will be instantiated and called as such:
 * Trie* obj = trieCreate();
 * trieInsert(obj, word);
 
 * bool param_2 = trieSearch(obj, word);
 
 * bool param_3 = trieStartsWith(obj, prefix);
 
 * trieFree(obj);
*/

int main()
{
    Trie* obj = trieCreate();
    trieInsert(obj, "ada");
    trieInsert(obj, "java");
    trieInsert(obj, "deep");
    trieInsert(obj, "mind");
    trieInsert(obj, "debug");
    trieInsert(obj, "deelearning");
    bool param_2 = trieSearch(obj, "deep");
    //bool param_3 = trieStartsWith(obj, "de");
    return 0;
}

