#include "encode.h"
#include "ui_encode.h"
#include "huffmanTree.h"

#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QList>
#include <QtAlgorithms>
#include <QMap>
#include <qmath.h>

encode::encode(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::encode)
{
    ui->setupUi(this);
    /** Bağlantı ayarları **/
    connect(ui->Encode,SIGNAL(clicked()),this,SLOT(encoder()));
}

encode::~encode()
{
    delete ui;
}

void encode::on_Browse_button_clicked()
{
    FileLocation();
    if(!fileloca.isEmpty()){
        ui->Encode->setEnabled(true);
        ui->warningText->setVisible(false);
    }
}
void encode::FileLocation(){
    fileloca=QFileDialog::getOpenFileName(this, tr("Open File"),"/home",
                                          tr("Document Files (*.txt)"));
    ui->FileLoca->setText(fileloca);
}
void encode::encoder(){
    readFile();
    qApp->exit();
}
void encode::readFile(){
    QFile EncodeFile(ui->FileLoca->text());
    if(!EncodeFile.open(QFile::ReadOnly | QFile::Text)){
        ShowMessage("File Error.Select Again...");
        return;
    }
    QTextStream in(&EncodeFile);
    QString filetext=in.readAll();
    EncodeFile.close();
    findFrekans(filetext);
}
void encode::findFrekans(QString TextFile){
    frekList=new int [Char_Limit]();
    for(int i=0;!TextFile[i].isNull();i++)
        frekList[TextFile[i].toAscii()]++;
    getHuffmanTree(frekList,&TextFile);
}
void encode::getHuffmanTree(int *frek,QString *filetext){
    QList<HuffmanTree*>Codes;
    char character;
    for(int i=0;i<=Char_Limit;i++)
        if(frek[i]>0){//Karakter varsa
            HuffmanTree *HuffmanCode=new HuffmanTree();

            HuffmanCode->frekans=frek[i];
            character=(char)i;
            HuffmanCode->karakter=character;
            Codes.append(HuffmanCode);
        }
    qSort(Codes.begin(),Codes.end(),sortingHuffmanTree);
    while(Codes.count()>1){
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
    writedata(filetext);
    Codes.clear();
}
void encode::writedata(QString *filetext)
{
    QString saveLoca=ui->FileLoca->text();
    saveLoca.remove(saveLoca.length()-3,3);
    QFile codefile(saveLoca+"huff");
    QMap<char,int>FrekMap;
    QString       compressed="";
    QString       mesBoxMes="";
    int           N;
    unsigned char buff    = 0;
    const QChar   ZeroBit('0');

    if(!codefile.open(QFile::WriteOnly)){
        ShowMessage("File Error.Select Again...");
        return;
    }
    for(int i=0;i<Char_Limit;i++){
        if(frekList[i]>0)
            FrekMap.insert(char(i),frekList[i]);
    }
    delete[] frekList;
    for(int i=0;!filetext[0][i].isNull();i++){
        QChar ch=filetext[0][i];
        compressed+=CodeHash.value(ch);
    }
    /**
    //Writing size of map
    int mapSize = FrekMap.keys().count();
    codefile.write(reinterpret_cast<char*>(&mapSize),sizeof(int));
    //Writing map
    for (QMap<char,int>::Iterator it = FrekMap.begin(); it != FrekMap.end(); ++it) {
        char ch=it.key();
        codefile.write(reinterpret_cast<char*>(&ch), sizeof(char));
        codefile.write(reinterpret_cast<char*>(&(it.value())), sizeof(int));
    }
    //Writing lenght last byte
    N=compressed.length()%8;
    codefile.write(reinterpret_cast<char*>(&N), sizeof(int));
    while(compressed.length()%8!=0)
        compressed.push_back('0');
    **/
    //Writing code
    for(int i=0; i < compressed.size(); i++)
    {
        if( compressed[i] == ZeroBit )
            buff &= ~(0x01);
        else
            buff |= (0x01);

        if((i+1)%8!=0)
            buff<<=1;
        else
        {
            codefile.write(reinterpret_cast<char *>(&buff),sizeof(unsigned char));
            buff = 0;
        }
    }
    codefile.flush();
    codefile.close();
    mesBoxMes.sprintf("Encoding file.Earned % %.1f memory size ",100-((float)(100*codefile.size())/filetext->size()));
    ShowMessage(mesBoxMes.toLatin1());
}
void encode::ShowMessage(const char *msg){
    QMessageBox msgBox;
    msgBox.setText(msg);
    msgBox.setWindowTitle("Encode");
    msgBox.setIcon(QMessageBox::Information);
    QIcon icon(":/image/iconn.png");
    msgBox.setWindowIcon(icon);
    msgBox.exec();
}
