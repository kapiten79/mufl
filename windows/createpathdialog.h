#ifndef CREATEPATHDIALOG_H
#define CREATEPATHDIALOG_H

#include <QDialog>
#include <QString>
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include <QPushButton>

class CreatePathDialog : public QDialog
{
    Q_OBJECT
public:
    explicit CreatePathDialog(QWidget *parent = nullptr);
    ~CreatePathDialog();
private:
    QLabel topic;
    QLineEdit addressLine;
    QGridLayout mainLayout;

    QPushButton *createButton{};
    QPushButton *cancelButton{};
signals:
    void pathCreate(QString pathName, bool pathCreateFlag = true);

public slots:

private slots:
};

#endif // CREATEPATHDIALOG_H
