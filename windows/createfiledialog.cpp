#include "createfiledialog.h"
#include <QProcess>
#include <QDir>

CreateFileDialog::CreateFileDialog(QWidget *parent) : QDialog(parent)
{
    setFixedHeight(100);
    setFixedWidth(300);
    setWindowTitle("Создание нового ");
    setLayout(&mainLayout);

    topic.setText("Введите название нового файла:");
    mainLayout.addWidget(&topic,0,0,1,3);

    mainLayout.addWidget(&addressLine,1,0,1,3);

    createButton = new QPushButton("Создать");
    connect(createButton, &QPushButton::clicked, [=](){
        QString program = "kate";
        QStringList arguments;
        arguments << QDir::currentPath()+"/"+addressLine.text();

        auto *myProcess = new QProcess(this);
        myProcess->start(program, arguments);
        this->close();
    });
    mainLayout.addWidget(createButton,2,1);

    cancelButton = new QPushButton("Отмена");
    connect(cancelButton, &QPushButton::clicked, [=](){
        this->close();
    });
    mainLayout.addWidget(cancelButton,2,2);
}
