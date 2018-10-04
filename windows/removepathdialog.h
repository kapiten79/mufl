#ifndef REMOVEPATHDIALOG_H
#define REMOVEPATHDIALOG_H

#include <QDialog>
#include <QString>
#include <QLabel>
#include <QGridLayout>
#include <QPushButton>

class RemovePathDialog : public QDialog
{
    Q_OBJECT
public:
    RemovePathDialog(QWidget *parent = nullptr);
    void setPathOrFileToRemove(QStringList pathsList);

private:
    QString toRemovePathOrFile;
    QStringList toRemovePathsOrFiles;

    QLabel topic;
    QGridLayout mainLayout;

    QPushButton *createButton;
    QPushButton *cancelButton;

    void removePathRecursive(const QString& rmPath);
signals:
    void pathOrFileRemoved();

public slots:

private slots:
};

#endif // REMOVEPATHDIALOG_H
