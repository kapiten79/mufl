#include "copyfiledialog.h"
#include <QDir>
#include <QDebug>
#include <QMessageBox>

CopyFileDialog::CopyFileDialog(QWidget *parent) : QDialog(parent)
{
    try {
        setFixedHeight(150);
        setFixedWidth(600);
        setWindowTitle("Копирование");
        setLayout(&mainLayout);

        topicFrom.setText("Откуда");
        mainLayout.addWidget(&topicFrom,0,0,1,3);

        addressLineFrom.setEnabled(false);
        mainLayout.addWidget(&addressLineFrom,1,0,1,3);

        topicTo.setText("Куда");
        mainLayout.addWidget(&topicTo,2,0,1,3);

        mainLayout.addWidget(&addressLineTo,3,0,1,3);
        addressLineTo.setFocus();

        copyButton = new QPushButton("Копировать");
        connect(copyButton, &QPushButton::clicked, this, &CopyFileDialog::startCopy);
        mainLayout.addWidget(copyButton,4,3);

        cancelButton = new QPushButton("Отмена");
        connect(cancelButton, &QPushButton::clicked, [=](){this->close();});
        mainLayout.addWidget(cancelButton,5,3);

        fileToCopyList.setFixedWidth(150);

        currectFile.setText("Текущий файл:");
        mainLayout.addWidget(&currectFile,4,0);
        copyFileProgressBar.setMinimum(0);
        copyFileProgressBar.setMaximum(100);
        mainLayout.addWidget(&copyFileProgressBar,4,1,1,2);

        total.setText("Осталось скопировать всего:");
        mainLayout.addWidget(&total,5,0);
        copyTotalProgressBar.setMinimum(0);
        copyTotalProgressBar.setMaximum(100);
        mainLayout.addWidget(&copyTotalProgressBar,5,1,1,2);

        mainLayout.addWidget(&fileToCopyList, 0,3,4,1);
    } catch (std::exception &error) {
        qDebug() << "Исключение возникло в методе CopyFileDialog класса CopyFileDialog " << error.what();
    }
}

void CopyFileDialog::setParams(const QStringList& p_fileList, const QString& fromAddress, const QString& toAddress, bool isMoved)
{
    try {
        isMove = isMoved;
        isMove ? setWindowTitle("Перенос") : setWindowTitle("Копирование");
        fileList = p_fileList;
        fileToCopyList.clear();
        fileToCopyList.insertItems(0,p_fileList);
        addressLineFrom.setText(fromAddress);
        addressLineTo.setText(toAddress);
    } catch (std::exception &error) {
        qDebug() << "Исключение возникло в методе setParams класса CopyFileDialog " << error.what();
    }
}


void CopyFileDialog::startCopy()
{
    try {
        if (addressLineFrom.text() != addressLineTo.text())
        {
            copyFileProgressBar.reset();
            copyTotalProgressBar.reset();
            copyTotalProgressBar.setMaximum(fileList.count()*100);

            processCopyFile = new ProcessCopyFile(fileList,addressLineFrom.text(),addressLineTo.text(), &copyTotalProgressBar, isMove);
            connect(processCopyFile, &ProcessCopyFile::precent, [=](double p_precent, int index){
                copyFileProgressBar.setValue(static_cast<int>(p_precent));
                copyTotalProgressBar.setValue(index * 100 + static_cast<int>(p_precent));
            });
            processCopyFile->moveToThread(&progressThread);
            progressThread.start();

            processCopyFile->startCopy();
            progressThread.quit();
            progressThread.wait();
            delete processCopyFile;
            QDir::setCurrent(addressLineFrom.text());
            this->close();
            emit copyFinished(addressLineFrom.text());
            copyFileProgressBar.reset();
            copyTotalProgressBar.reset();
        }
        else
        {
            QMessageBox::critical(this, QObject::tr("Ошибка при копировании"), QObject::tr("Нельзя копировать в тот же каталог. Измените целевой каталог или имя копируемого файла (каталога)"));
        }
    } catch (std::exception &error) {
        qDebug() << "Исключение возникло в методе startCopy класса CopyFileDialog " << error.what();
    }
}
