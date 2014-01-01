#include "decode.h"
#include "encode.h"
#include "ui_decode.h"
#include "huffmanTree.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QMap>
#include <QList>
#include <QtAlgorithms>
#include <QString>

decode::decode(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::decode)
{
    ui->setupUi(this);
    /** Bağlantı ayarları **/
    connect(ui->Decode,SIGNAL(clicked()),this,SLOT(decoder()));

}

decode::~decode()
{
    delete ui;
}
void decode::decoder(){
    readAndDecode();
    qApp->exit();
}
void decode::FileLocation(){
    fileloca=QFileDialog::getOpenFileName(this, tr("Open File"),"/home",
                                          tr("Document Files (*.huff)"));
    ui->FileLoca_2->setText(fileloca);
}
void decode::on_Browse_button_2_clicked()
{
    FileLocation();
    if(!fileloca.isEmpty()){
        ui->Decode->setEnabled(true);
        ui->warningText->setVisible(false);
    }
}
void decode::readAndDecode(){
    int              sizeMap=0;
    int              lengthLast;
    QMap <QChar,int> FreqTable;
    QFile readData(ui->FileLoca_2->text());
    if(!readData.open(QFile::ReadOnly)){
        ShowMessage("File Error.Select Again...");
        return;
    }
    //read size of map
    readData.read(reinterpret_cast<char*>(&sizeMap),sizeof(int));
    //read map
    for (int i=0;i<sizeMap;i++) {
        char charofmap;
        int freq;
        readData.read(reinterpret_cast<char*>(&charofmap),sizeof(char));
        readData.read(reinterpret_cast<char*>(&freq), sizeof(int));
        FreqTable.insert(charofmap,freq);
    }
    readData.read(reinterpret_cast<char*>(&lengthLast), sizeof(int));
    while (!readData.atEnd()) {
        unsigned char ch;
        readData.read(reinterpret_cast<char*>(&ch), sizeof(unsigned char));
        codeLetter+=unschartoQString(ch);
    }
    readData.close();
    //remowe last zero
    codeLetter.remove(codeLetter.length()-(8-(int)lengthLast),(8-(int)lengthLast));
    buildHuff(FreqTable);
}
void decode::buildHuff(QMap<QChar,int> &freqt){
    QList<HuffmanTree*>Codes;
    QMap<QChar,int>::iterator it=freqt.begin();
    for(int i=0;i<freqt.size();i++){
        HuffmanTree *huffnode=new HuffmanTree();

        huffnode->frekans=it.value();
        huffnode->karakter=it.key();
        Codes.append(huffnode);++it;
    }
    qSort(Codes.begin(),Codes.end(),sortingHuffmanTree);
    while (Codes.count()>1){
        HuffmanTree *node1(Codes[0]);
        HuffmanTree *node2(Codes[1]);

        HuffmanTree *newnode=new HuffmanTree();

        newnode->frekans=node1->frekans+node2->frekans;
        newnode->isLeaf=false;
        newnode->left=node1;
        newnode->right=node2;
        newnode->karakter=node1->karakter+node2->karakter;

        node1->parent=node2->parent=newnode;

        Codes.append(newnode);
        Codes.removeOne(node1);
        Codes.removeOne(node2);

        qSort(Codes.begin(),Codes.end(),sortingHuffmanTree);
    }
    Codes[0]->root=true;
    getHuffmanCode(Codes[0]);
    for(QHash<QString,QString>::iterator it=encode::CodeHash.begin();
        it!=encode::CodeHash.end();++it){
        decodeHash.insert(it.value(),it.key());
    }
    writeOrg();
}
void decode::writeOrg(){
    QFile orginalText(ui->FileLoca_2->text()+"t");
    if(!orginalText.open(QIODevice::WriteOnly | QIODevice::Text)){
        ShowMessage("File Error.Select Again...");
        return;
    }
    QTextStream out(&orginalText);
    QString text="";
    QString symbol="";
    bool found(false);
    for(int i=0;i<codeLetter.length();i++){
        symbol+=codeLetter[i];
        QString convertdata="";
        found=false;
        if(decodeHash.contains(symbol)){
            convertdata=decodeHash.value(symbol);
            found=true;
        }
        if(found){
            text+=convertdata;
            symbol.remove(0,symbol.length());
        }
    }
    out<<text;

}
QString decode::unschartoQString(unsigned char ch){
    QString bitstring="";
    size_t total=0;
    unsigned char val=128;
    for(size_t i=0;i<8;i++,val/=2){
        if (total+val<=ch){
            bitstring+= '1';
            total+=val;
        }
        else
            bitstring+='0';
    }
    return bitstring;
}
void decode::ShowMessage(char *msg){
    QMessageBox msgBox;
    msgBox.setText(msg);
    msgBox.setWindowTitle("Decode");
    msgBox.setIcon(QMessageBox::Information);
    msgBox.exec();
}
