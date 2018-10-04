#include "processcopyfile.h"
#include <QFile>
#include <QFileInfo>
#include <QDebug>
#include <QDir>
#include <utility>
#include <utility>

ProcessCopyFile::ProcessCopyFile(QStringList &p_fileList, QString p_fromAddress, QString p_toAddress, QProgressBar *p_progressBar, bool isMoving, QObject *parent)
    : QObject(parent),
      progressBar(p_progressBar),
      fileList(p_fileList),
      fromAddress(std::move(std::move(p_fromAddress))),
      toAddress(std::move(std::move(p_toAddress))),
      mainPathLen(0),
      deleteSource(isMoving)
{

}

void ProcessCopyFile::copyFile(int index)
{
    QFile fileCpy(fromAddress+"/"+fullAddressFileList[index]);
    QFile destCpy(toAddress+"/"+fullAddressFileList[index]);

    qint64 nCopySize = QFileInfo(fileCpy).size();
     qint64 size = 0;
     double divider = static_cast<double>(nCopySize)/5;
     if(destCpy.exists())
     {
         destCpy.remove();
     }
     if(!destCpy.open(QIODevice::ReadWrite))
     {
         emit report("Can't create file");
     }
     if(!fileCpy.open(QIODevice::ReadWrite))
     {
         emit report("Can't read file");
     }
     while(nCopySize > size)
     {
         
         if(destCpy.write(fileCpy.read(size)))
         {
             emit report(QString::number(size/divider));
         }
         size += divider;
         emit precent((size/divider)/(nCopySize/divider/100), index);
     }
     if(nCopySize < size){
         size = size - nCopySize;
         destCpy.write(fileCpy.read(size));
         destCpy.close();
     }else{
         destCpy.close();
     }
     if (deleteSource)
         fileCpy.remove();
     fileCpy.close();

}

void ProcessCopyFile::recursiveCopyPath(const QString& subPath)
{
    QString parentPath = QDir::currentPath();
    QDir::setCurrent(subPath);
    QDir currDir;
    QStringList fileList = currDir.entryList();
    for(int i=2; i<fileList.count(); i++)
    {
        if (QFileInfo(QDir::currentPath()+"/"+fileList[i]).isFile())
        {
            QString currFileFullAddress = QDir::currentPath()+"/"+fileList[i];
            fullAddressFileList << currFileFullAddress.right(currFileFullAddress.length() - mainPathLen);
        }
        else
        {
            pathList << QDir::currentPath()+"/"+fileList[i];
            const QString newSubPath = QDir::currentPath()+"/"+fileList[i];
            recursiveCopyPath(newSubPath);
        }
    }
    QDir::setCurrent(parentPath);
}

void ProcessCopyFile::startCopy()
{
    fullAddressFileList.clear();
    pathList.clear();
    mainPathLen = QDir::currentPath().length();
    for(int i=0; i<fileList.count(); i++)
    {
        if (QFileInfo(QDir::currentPath()+"/"+fileList[i]).isFile())
        {
            QString currFileFullAddress = QDir::currentPath()+"/"+fileList[i];
            fullAddressFileList << currFileFullAddress.right(currFileFullAddress.length() - mainPathLen);
        }
        else
        {
            //QString mainPath = QDir::currentPath();
            pathList << QDir::currentPath()+"/"+fileList[i];
            recursiveCopyPath(QDir::currentPath()+"/"+fileList[i]);
        }
    }

    /** Создаём структуру копируемых каталогов в целевой папке */
    for (int i=0; i<pathList.count(); i++)
    {
        QString nextPath =  toAddress + pathList[i].right(pathList[i].length() - mainPathLen);
        if (!QDir(nextPath).exists())
        {
            QDir dir;
            dir.mkdir(nextPath);
        }
    }


    progressBar->setMaximum(fullAddressFileList.count()*100);
    for (int i=0; i<fullAddressFileList.count(); i++)
    {
        copyFile(i);
    }

    if (deleteSource)
    {
        for (int i=pathList.count()-1; i>=0; i--)
        {
            fromAddress+pathList[i].right(pathList[i].length() - mainPathLen);
            if(deleteSource)
                QDir().rmdir(fromAddress+pathList[i].right(pathList[i].length() - mainPathLen));
        }
    }

}
