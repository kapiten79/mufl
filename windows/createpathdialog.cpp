#include "createpathdialog.h"
#include <QDir>
#include <QDebug>

CreatePathDialog::CreatePathDialog(QWidget *parent)
    : QDialog(parent)
{
    try {
        setFixedHeight(100);
        setFixedWidth(300);
        setWindowTitle("Создание нового каталога");
        setLayout(&mainLayout);

        topic.setText("Введите название нового каталога:");
        mainLayout.addWidget(&topic,0,0,1,3);

        mainLayout.addWidget(&addressLine,1,0,1,3);

        createButton = new QPushButton("Создать");
        connect(createButton, &QPushButton::clicked, [=](){
            QDir dir;
            dir.mkdir(addressLine.text());
            emit this->pathCreate(addressLine.text());
            this->close();
        });
        mainLayout.addWidget(createButton,2,1);

        cancelButton = new QPushButton("Отмена");
        connect(cancelButton, &QPushButton::clicked, [=](){
            this->close();
        });
        mainLayout.addWidget(cancelButton,2,2);
    } catch (std::exception &error) {
        qDebug() << "Исключение возникло в методе CreatePathDialog класса CreatePathDialog " << error.what();
    }
}

CreatePathDialog::~CreatePathDialog()
{
    if (createButton != nullptr)
    {
        delete createButton;
        createButton = nullptr;
    }
    if (cancelButton != nullptr)
    {
        delete cancelButton;
        cancelButton = nullptr;
    }
}
