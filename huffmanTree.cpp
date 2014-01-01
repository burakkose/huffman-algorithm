#include "huffmanTree.h"
#include "encode.h"
QHash<QString,QString> encode::CodeHash;
HuffmanTree::HuffmanTree()
{
    left=NULL;
    right=NULL;
    parent=NULL;
    isLeaf=true;
    root=false;
    Code="";
}
bool sortingHuffmanTree(const HuffmanTree *s1, const HuffmanTree *s2)
{
    return s1->frekans<s2->frekans;
}
void getHuffmanCode(HuffmanTree *Tree){
    HuffmanTree *leftnode(Tree->left);
    HuffmanTree *rightnode(Tree->right);
    QString key,code;

    if(leftnode==NULL && rightnode==NULL)
        Tree->Code="1";
    if(Tree->root==true)
    {
        if(leftnode!=NULL)
            leftnode->Code="0";
        if(rightnode!=NULL)
            rightnode->Code="1";
    }
    else{
        if(leftnode!=NULL)
            leftnode->Code=leftnode->parent->Code+"0";
        if(rightnode!=NULL)
            rightnode->Code=rightnode->parent->Code+"1";
    }
    if(leftnode!=NULL){
        if(!leftnode->isLeaf)
            getHuffmanCode(leftnode);
        else{
            key=leftnode->karakter;
            code=leftnode->Code;
            encode::CodeHash.insert(key,code);
        }
    }
    if(rightnode!=NULL){
        if(!rightnode->isLeaf)
            getHuffmanCode(rightnode);
        else{
            key=rightnode->karakter;
            code=rightnode->Code;
            encode::CodeHash.insert(key,code);
        }
    }

}
