#ifndef ENCODE_H
#define ENCODE_H

#include <QDialog>
#include <QString>
#include <QHash>

#define  Char_Limit 256

namespace Ui {
class encode;
}

class encode : public QDialog
{
    Q_OBJECT

public:
    explicit encode(QWidget *parent = 0);
    ~encode();
private:
    Ui::encode *ui;

private slots:
    //Dosya lokasyonunu bulmak için.
    void FileLocation();
    //Browse butonuna tıklanırsa
    void on_Browse_button_clicked();
    //Ana fonksiyon
    void encoder();

public:
    //Dosyayı okumak
    void readFile();
    //Frekansları bulmak
    void findFrekans(QString);
    //Ağacı oluşturmak
    void getHuffmanTree(int *,QString *);
    void ShowMessage(const char *);
    void writedata(QString *);
    static QHash<QString,QString>CodeHash;
    QString fileloca;//dosya adresi
    int *frekList;
};

#endif // ENCODE_H
