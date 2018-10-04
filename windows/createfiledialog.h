#ifndef CREATEFILEDIALOG_H
#define CREATEFILEDIALOG_H

#include <QDialog>
#include <QString>
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include <QPushButton>

class CreateFileDialog : public QDialog
{
    Q_OBJECT
public:
    explicit CreateFileDialog(QWidget *parent = nullptr);
private:
    QLabel topic;
    QLineEdit addressLine;
    QGridLayout mainLayout;

    QPushButton *createButton;
    QPushButton *cancelButton;
signals:

public slots:
};

#endif // CREATEFILEDIALOG_H
