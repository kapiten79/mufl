#include "finddialog.h"
#include <QDir>
#include <QDebug>

FindDialog::FindDialog(QWidget *parent) : QDialog(parent)
{
    setWindowTitle("Поиск");

    setLayout(&mainFindWidgetLayout);
    mainFindWidgetLayout.addWidget(&findPathLabel,0,0,1,2);
    mainFindWidgetLayout.addWidget(&findPathLineEdit,1,0,1,2);
    mainFindWidgetLayout.addWidget(&findMaskLabel,2,0,1,2);
    mainFindWidgetLayout.addWidget(&findMaskLineEdit,3,0,1,2);
    mainFindWidgetLayout.addWidget(&resultTableWidget,4,0,1,2);
    mainFindWidgetLayout.addWidget(&findButton,5,0,1,1);
    mainFindWidgetLayout.addWidget(&cancelButton,5,1,1,1);

    findPathLabel.setText("Введите адрес каталога поиска:");
    findMaskLabel.setText("Введите маску для поиска файла:");

    findButton.setText("Найти");
    connect(&findButton, &QPushButton::clicked, [=](bool){
       this->findFile(findPathLineEdit.text(), false);
    });
    cancelButton.setText("Закрыть");

    findPathLineEdit.setText(QDir::current().absolutePath());
    findMaskLineEdit.setText("*.*");
    findMaskLineEdit.setFocus();
}

void FindDialog::findFile(const QString& subPath, bool recursiveFlag)
{
    QString currPathAddress = QDir::current().absolutePath();
    QDir::setCurrent(subPath);
    QDir dir;
    QFileInfoList entryList = dir.entryInfoList();
    if (!recursiveFlag) {
        for (const auto &currFile : entryList) {
            if (currFile.fileName() == findMaskLineEdit.text()) {
                qDebug() << "Нашелся";
            }
        }
    } else {
        for (const auto &currFile : entryList) {
            if (currFile.isFile()) {
                if (currFile.fileName() == findMaskLineEdit.text()) {
                    qDebug() << "Нашелся";
                }
            } else {
                findFile(subPath+"/"+currFile.fileName());
            }
        }
    }
    QDir::setCurrent(currPathAddress);
}
