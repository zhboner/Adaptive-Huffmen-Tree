#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <cstdlib>
#include <bitset>
#include <cmath>

using namespace std;

class Node{
public:
    Node *leftNode, *rightNode, *parentNode;
    int id, weight;
    char value;
public:
    Node(int xid, int xweight, Node *left, Node *right, Node *parent, char xvalue){
        id = xid;
        weight = xweight;
        leftNode = left;
        rightNode = right;
        parentNode = parent;
        value = xvalue;
    }
    Node(){
        id = 0;
        weight = 0;
        leftNode = NULL;
        rightNode = NULL;
        parentNode = NULL;
        value = '\0';
    }

    bool isLeaf(){
        if (!this->leftNode && !this->rightNode){
            return true;
        }
        return false;
    }
    bool isRight(){
        if (this->parentNode){
            return this->parentNode->rightNode == this;
        }
        return false;
    }
};
const int base = 257;
int availableId;
Node *root, *NYT;
string path[base + 1];          // path[base] = NYT path
string str;                     // The string that is going to be compressed

void updateId(){
    queue<Node*> q;
    int n = base;
    Node *xxxxxx;
    q.push(root);
    while (!q.empty()){
        xxxxxx = q.front();
        q.pop();
        if (!xxxxxx){
            continue;
        }
        xxxxxx->id = n--;
        if (xxxxxx->rightNode){
            q.push(xxxxxx->rightNode);
        }
        if (xxxxxx->leftNode){
            q.push(xxxxxx->leftNode);
        }
    }
}

void buildPath(string p, Node *node){
    if (node->value){
        path[node->value] = p;
    }
    else if (node->weight == 0){
        path[base] = p;
    }
    if (node->leftNode){
        p.append("0");
        buildPath(p, node->leftNode);
        p = p.substr(0, p.size() - 1);
    }
    if (node->rightNode){
        p.append("1");
        buildPath(p, node->rightNode);
        p = p.substr(0, p.size() - 1);
    }
    else{
        return;
    }
}

Node *findNode(char chr){       // Find the node
    if (path[chr] == "-1"){
        return NULL;
    }
    Node *n = root;
    for (int i = 0; i < path[chr].size(); ++i) {
        if (path[chr][i] == '0'){
            n = n->leftNode;
        }
        else{
            n = n->rightNode;
        }
    }
    return n;
}

queue<Node*> getBlock(int weight, bool leaf){
    queue<Node*> queueLeaf, queueInternal, tree;
    Node *n;

    tree.push(root);
    while (!tree.empty()){
        n = tree.front();
        tree.pop();

        if (n->weight == weight){

            if (n->isLeaf()){
                queueLeaf.push(n);
            }
            else{
                queueInternal.push(n);
            }
        }
        if (n->rightNode){
            tree.push(n->rightNode);
        }
        if (n->leftNode){
            tree.push(n->leftNode);
        }
    }

    if (leaf) return queueLeaf;
    else return queueInternal;

//    if (nextBlock){
//        if (node->isLeaf()){
//            if (!queueInternal.empty()) return queueInternal;
//            else return queueLeaf;
//        }
//        else{
//            if (!queueLeaf.empty()) return queueLeaf;
//            else return queueInternal;
//        }
//    }
//    else{
//        if (node->isLeaf()) return queueLeaf;
//        else return queueInternal;
//    }
}

void swapNodes(Node *x, Node *y){
    Node *xParent = x->parentNode;
    Node *yParent = y->parentNode;
    int tmp = x->id;

    x->id = y->id;
    y->id = tmp;

    if (xParent == yParent){
        if (x->isRight()){
            xParent->rightNode = y;
            xParent->leftNode = x;
        }
        else{
            xParent->leftNode = y;
            xParent->rightNode = x;
        }
    }
    else{
        if (x->isRight()){
            xParent->rightNode = y;
        }
        else{
            xParent->leftNode = y;
        }

        if (y->isRight()){
            yParent->rightNode = x;
        }
        else{
            yParent->leftNode = x;
        }

        x->parentNode = yParent;
        y->parentNode = xParent;
    }
}

Node* slideAndIncrement(Node *p){
    queue<Node*> b;
    if (p->isLeaf()){
        b = getBlock(p->weight, false);
    }
    else{
        b = getBlock(p->weight + 1, true);
    }
    Node *watch = b.front();
    if (!b.empty() && ((p->isLeaf() && !b.front()->isLeaf() && p->weight == b.front()->weight) ||
            (!p->isLeaf() && b.front()->isLeaf() && p->weight == b.front()->weight - 1))){
        bool r;

        // Slide
        Node *parent_bak = p->parentNode;
        if (p->isRight()){
            r = true;
        }
        else{
            r = false;
        }

        Node *x = p;
        while (!b.empty()){
            Node *y = b.front();
            b.pop();

            int tmp = x->id;
            x->id = y->id;
            y->id = tmp;

            Node *parent = y->parentNode;
            if (y->isRight()){
                parent->rightNode = x;
            }
            else{
                parent->leftNode = x;
            }
            x->parentNode = parent;

            x = y;
        }

        if (r){
            parent_bak->rightNode = x;
        }
        else{
            parent_bak->leftNode = x;
        }
        x->parentNode = parent_bak;

        p->weight++;
        if (p->isLeaf()){
            return p->parentNode;
        }
        else{
            return parent_bak;
        }
    }
    else{
        p->weight++;
        return p->parentNode;
    }
}


void updateTree(char input){
    Node *targetNode = findNode(input);
    Node *leafToIncrement = NULL;

    if (targetNode){       // The character exist
        queue<Node*> q = getBlock(targetNode->weight, true);
        Node *maxIdNode = q.front();

        swapNodes(maxIdNode, targetNode);
        if (NYT->parentNode == targetNode->parentNode){
            leafToIncrement = targetNode;
            targetNode = targetNode->parentNode;
        }
    }
    else{
        // Create new node

        Node *newLeafNode = new Node(--availableId, 0, NULL, NULL, NULL, input);
        Node *newNYT = new Node(--availableId, 0, NULL, NULL, NULL, '\0');
        Node *newInternalNode = new Node(NYT->id, 0, newNYT, newLeafNode, NULL, '\0');
        newLeafNode->parentNode = newInternalNode;
        newNYT->parentNode = newInternalNode;

        if (NYT->id == base){       // The tree is empty
            root = newInternalNode;
            NYT = newNYT;

            path[base] = "0";
            path[input] = "1";
        }
        else{
            Node *NYTParent = NYT->parentNode;
            NYTParent->leftNode = newInternalNode;
            newInternalNode->parentNode = NYTParent;
            NYT = newNYT;
            if (NYTParent->id == root->id){
                root->leftNode = newInternalNode;
            }
        }
        targetNode = newInternalNode;
        leafToIncrement = newLeafNode;
    }

    while (targetNode != root){
        targetNode = slideAndIncrement(targetNode);
    }
    targetNode->weight++;
    if (leafToIncrement){
        slideAndIncrement(leafToIncrement);
    }
    buildPath("", root);
}