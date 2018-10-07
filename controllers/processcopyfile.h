#ifndef PROCESSCOPYFILE_H
#define PROCESSCOPYFILE_H

#include <QObject>
#include <QProgressBar>

class ProcessCopyFile : public QObject
{
    Q_OBJECT
    void copyFile();
public:
    explicit ProcessCopyFile(QStringList &p_fileList, QString p_fromAddress, QString p_toAddress, QProgressBar *p_progressBar, bool isMoving = false, QObject *parent = nullptr);

private:
    QProgressBar *progressBar{};
    QStringList fileList{};
    QStringList fullAddressFileList{};
    QStringList pathList{};
    QString fromAddress{};
    QString toAddress{};

    int mainPathLen{};

    bool deleteSource{};

    void copyFile(int index);
    void recursiveCopyPath(const QString &subPath);

signals:    
    void report(QString str);
    void precent(double prec, int index);
public slots:
    void startCopy();
};

#endif // PROCESSCOPYFILE_H
