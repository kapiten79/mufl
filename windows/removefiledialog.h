#ifndef REMOVEFILEDIALOG_H
#define REMOVEFILEDIALOG_H

#include <QDialog>
#include <QString>
#include <QLabel>
#include <QGridLayout>
#include <QPushButton>

class RemoveFileDialog : public QDialog
{
    Q_OBJECT
public:
    explicit RemoveFileDialog(QWidget *parent = nullptr);
private:
    QString toRemovePathOrFile;

    QLabel topic;
    QGridLayout mainLayout;

    QPushButton *createButton;
    QPushButton *cancelButton;

signals:

public slots:
};

#endif // REMOVEFILEDIALOG_H
