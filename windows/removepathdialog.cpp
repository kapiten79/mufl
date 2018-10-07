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
        for (const auto &currFileName : toRemovePathsOrFiles) {
            QDir currDir;
            if (QFileInfo(currFileName).isDir())
                removePathRecursive(currFileName);
            else {
                QFile rmFile(currFileName);
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
    for (const auto &currPath : filePathList) {
        if (currPath.isDir()) {
            if (QDir(currPath.absoluteFilePath()).count() > 2) {
                removePathRecursive(currPath.absoluteFilePath());
            }
            else {
                dir.rmdir(currPath.absoluteFilePath());
            }
        }
        else {
            QFile rmFile(currPath.absoluteFilePath());
            rmFile.remove();
        }
    }

    QDir::setCurrent(parentDirAddress);
    dir.rmdir(rmPath);
}
