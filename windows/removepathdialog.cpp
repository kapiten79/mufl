#include "removepathdialog.h"
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QDebug>
#include <utility>
RemovePathDialog::RemovePathDialog(QWidget *parent):QDialog (parent)
{
    setFixedHeight(100);
    setFixedWidth(500);

    setLayout(&mainLayout);
    mainLayout.addWidget(&topic,0,0,1,3);
    createButton = new QPushButton("Удалить");
    connect(createButton, &QPushButton::clicked, [=](){
        for (int i=0; i<toRemovePathsOrFiles.count(); i++)
        {
            QDir currDir;
            if (QFileInfo(toRemovePathsOrFiles[i]).isDir())
                removePathRecursive(toRemovePathsOrFiles[i]);
            else
            {
                QFile rmFile(toRemovePathsOrFiles[i]);
                rmFile.remove();
            }
        }

        emit this->pathOrFileRemoved();
        this->close();
    });
    mainLayout.addWidget(createButton,2,1);

    cancelButton = new QPushButton("Отмена");
    connect(cancelButton, &QPushButton::clicked, [=](){
        this->close();
    });
    mainLayout.addWidget(cancelButton,2,2);
}

void RemovePathDialog::setPathOrFileToRemove(QStringList pathsList)
{
    toRemovePathsOrFiles = std::move(pathsList);
    setWindowTitle(tr("Удаление"));
}

void RemovePathDialog::removePathRecursive(const QString& rmPath)
{
    QDir dir;
    QString parentDirAddress = QDir::currentPath();

    QDir::setCurrent(rmPath);
    QFileInfoList filePathList = dir.entryInfoList();
    for (int i=2; i<filePathList.count(); i++)
    {
        if (filePathList[i].isDir())
        {
            if (QDir(filePathList[i].absoluteFilePath()).count() > 2)
            {
                removePathRecursive(filePathList[i].absoluteFilePath());
            }
            else
            {
                dir.rmdir(filePathList[i].absoluteFilePath());
            }
        }
        else
        {
            QFile rmFile(filePathList[i].absoluteFilePath());
            rmFile.remove();
        }
    }

    QDir::setCurrent(parentDirAddress);
    dir.rmdir(rmPath);
}
