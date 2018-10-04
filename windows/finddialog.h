#ifndef FINDDIALOG_H
#define FINDDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QCheckBox>
#include <QTableWidget>
#include <QGridLayout>

class FindDialog : public QDialog
{
    Q_OBJECT
public:
    explicit FindDialog(QWidget *parent = nullptr);

    QGridLayout mainFindWidgetLayout;

    QLabel findPathLabel;
    QLabel findMaskLabel;

    QLineEdit findPathLineEdit;
    QLineEdit findMaskLineEdit;

    QCheckBox findRecursive;

    QPushButton findButton;
    QPushButton cancelButton;

    QTableWidget resultTableWidget;
signals:

public slots:
    void findFile(const QString& subPath = "", bool recursiveFlag = false );
};

#endif // FINDDIALOG_H
