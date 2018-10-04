#ifndef COPYFILEDIALOG_H
#define COPYFILEDIALOG_H

#include <QDialog>
#include <QString>
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include <QPushButton>
#include <QListWidget>
#include <QFile>
#include <QThread>
#include <QProgressBar>

#include "controllers/processcopyfile.h"

class CopyFileDialog : public QDialog
{
    Q_OBJECT
public:
    explicit CopyFileDialog(QWidget *parent = nullptr);
    void setParams(const QStringList& p_fileList, const QString& fromAddress, const QString& toAddress, bool isMoved = false);

private:
    QLabel topicFrom;
    QLineEdit addressLineFrom;
    QListWidget fileToCopyList;

    QLabel topicTo;
    QLineEdit addressLineTo;

    QGridLayout mainLayout;

    QPushButton *copyButton;
    QPushButton *cancelButton;

    QThread progressThread;
    ProcessCopyFile *processCopyFile{};

    QStringList fileList;

    QLabel currectFile;
    QLabel total;

    QProgressBar copyFileProgressBar;
    QProgressBar copyTotalProgressBar;

    bool isMove{};

    void copyFile();
signals:
    void pathCreate(QString pathName, bool pathCreateFlag = true);
    void copyFinished(QString currPath);
public slots:

private slots:
    void startCopy();

};

#endif // COPYFILEDIALOG_H
