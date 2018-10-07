#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QProcess>
#include <QHBoxLayout>
#include "widgets/panelwidget.h"
#include "windows/createpathdialog.h"
#include "windows/removepathdialog.h"
#include "windows/copyfiledialog.h"
#include "windows/createfiledialog.h"
#include "windows/finddialog.h"

using namespace std;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QApplication *a, QWidget *parent = nullptr);
    ~MainWindow();

private:

    QApplication *app;

    PanelWidget     *leftPanel{}          ;
    PanelWidget     *rightPanel{}         ;

    QTableWidget *leftTable{};
    QTableWidget *rightTable{};

    CreatePathDialog *createPathDialog{};
    RemovePathDialog *removePathDialog{};
    CopyFileDialog   *copyFileDialog{};
    CreateFileDialog *createFileDialog{};
    FindDialog       *findFileDialog{};

    QLineEdit *commandLine{};

    QWidget     *centralWidget{}      ;
    QGridLayout *centralGridLayout{}  ;

    QWidget     *helpWidget{};
    QHBoxLayout *helpLayout{};

    QList<QLabel*> helpLabelList{};

    void copyFile(QFile fileCpy, QFile destCpy);
    void addConnect();

};

#endif // MAINWINDOW_H
