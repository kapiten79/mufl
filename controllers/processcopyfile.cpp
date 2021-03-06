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
    try {
        QFile fileCpy(fromAddress+"/"+fullAddressFileList[index]);
        QFile destCpy(toAddress+"/"+fullAddressFileList[index]);

        qint64 nCopySize = QFileInfo(fileCpy).size();
         qint64 size = 0;
         double divider = static_cast<double>(nCopySize)/5;
         if(destCpy.exists()) {
             destCpy.remove();
         }
         if(!destCpy.open(QIODevice::ReadWrite)) {
             emit report("Can't create file");
         }
         if(!fileCpy.open(QIODevice::ReadWrite)) {
             emit report("Can't read file");
         }
         while(nCopySize > size) {
             if(destCpy.write(fileCpy.read(size))) {
                 emit report(QString::number(size/divider));
             }
             size += divider;
             emit precent((size/divider)/(nCopySize/divider/100), index);
         }
         if(nCopySize < size){
             size = size - nCopySize;
             destCpy.write(fileCpy.read(size));
             destCpy.close();
         } else {
             destCpy.close();
         }
         if (deleteSource)
             fileCpy.remove();
         fileCpy.close();
    } catch (std::exception &error) {
        qDebug() << "Исключение возникло в методе copyFile класса ProcessCopyFile " << error.what();
    }

}

void ProcessCopyFile::recursiveCopyPath(const QString& subPath)
{
    try {
        QString parentPath = QDir::currentPath();
        QDir::setCurrent(subPath);
        QDir currDir;
        QStringList fileList = currDir.entryList();

        for(const auto &currFile : fileList) {
            if (QFileInfo(QDir::currentPath()+"/"+currFile).isFile()) {
                QString currFileFullAddress = QDir::currentPath()+"/"+currFile;
                fullAddressFileList << currFileFullAddress.right(currFileFullAddress.length() - mainPathLen);
            }
            else {
                pathList << QDir::currentPath()+"/"+currFile;
                const QString newSubPath = QDir::currentPath()+"/"+currFile;
                recursiveCopyPath(newSubPath);
            }
        }
        QDir::setCurrent(parentPath);
    } catch (std::exception &error) {
        qDebug() << "Исключение возникло в методе recursiveCopyPath класса ProcessCopyFile " << error.what();
    }

}

void ProcessCopyFile::startCopy()
{
    try {
        fullAddressFileList.clear();
        pathList.clear();
        mainPathLen = QDir::currentPath().length();

        for(const auto &currFileName : fileList){
            if (QFileInfo(QDir::currentPath()+"/"+currFileName).isFile()) {
                QString currFileFullAddress = QDir::currentPath()+"/"+currFileName;
                fullAddressFileList << currFileFullAddress.right(currFileFullAddress.length() - mainPathLen);
            }
            else {
                pathList << QDir::currentPath()+"/"+currFileName;
                recursiveCopyPath(QDir::currentPath()+"/"+currFileName);
            }
        }

        /** Создаём структуру копируемых каталогов в целевой папке */
        for (const auto& currPath : pathList) {
            QString nextPath =  toAddress + currPath.right(currPath.length() - mainPathLen);
            if (!QDir(nextPath).exists()) {
                QDir dir;
                dir.mkdir(nextPath);
            }
        }


        progressBar->setMaximum(fullAddressFileList.count()*100);
        for (int i=0; i<fullAddressFileList.count(); i++) {
            copyFile(i);
        }

        if (deleteSource)
        {
            for (int i=pathList.count()-1; i>=0; i--) {
                fromAddress+pathList[i].right(pathList[i].length() - mainPathLen);
                if(deleteSource)
                    QDir().rmdir(fromAddress+pathList[i].right(pathList[i].length() - mainPathLen));
            }
        }
    } catch (std::exception &error) {
        qDebug() << "Исключение возникло в методе startCopy класса ProcessCopyFile " << error.what();
    }


}
