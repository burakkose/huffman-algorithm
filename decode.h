#ifndef DECODE_H
#define DECODE_H

#include <QDialog>
#include <QString>
#include <QMap>
#include <QHash>

namespace Ui {
class decode;
}

class decode : public QDialog
{
    Q_OBJECT

public:
    explicit decode(QWidget *parent = 0);
    ~decode();

private:
    Ui::decode *ui;
private slots:
    void FileLocation();
    void on_Browse_button_2_clicked();
    void decoder();

public:
    QString codeLetter;
    QString fileloca;
    QHash <QString,QString> decodeHash;
    void writeOrg();
    void readAndDecode();
    void buildHuff(QMap<QChar,int> &);
    void ShowMessage(char *);
    QString unschartoQString(unsigned char);
};

#endif // DECODE_H
