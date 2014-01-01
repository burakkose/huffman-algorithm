#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H

#include "encode.h"
#include "decode.h"
#include <QString>

class HuffmanTree
{
private:

    HuffmanTree   *left;

    HuffmanTree  *right;

    HuffmanTree *parent;

    QString    karakter;

    QString        Code;

    int         frekans;

    bool           root;

    bool         isLeaf;


public:

    HuffmanTree();
    friend void encode::getHuffmanTree(int *, QString *);
    friend void encode::writedata(QString *);
    friend void decode::buildHuff(QMap<QChar,int> &);
    friend bool sortingHuffmanTree(const HuffmanTree * , const HuffmanTree *);
    friend void getHuffmanCode(HuffmanTree *);

};
bool sortingHuffmanTree(const HuffmanTree * , const HuffmanTree * );
#endif // HUFFMANTREE_H
