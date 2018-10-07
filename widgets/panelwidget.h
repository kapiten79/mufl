#ifndef PANELWIDGET_H
#define PANELWIDGET_H

#include <QTabWidget>
#include <QTreeWidget>
#include "paneltablewidget.h"
#include <QGridLayout>
#include <QFileInfoList>
#include <QHeaderView>
#include <QMouseEvent>
#include <QDir>

#include <QMessageBox>

enum ViewType {
    tree,
    table
};



using namespace std;

class PanelWidget : public QTabWidget
{
    Q_OBJECT
public:
    explicit PanelWidget(ViewType panelType, QString p_panelSide, QWidget *parent = nullptr);
    ~PanelWidget();
    void setPanelType(ViewType panelType);
    void setCurrPath(const QString& path = QDir::homePath(), const QString& pathToSet = "..");

    QString             getCurrPath()           {return currPathAddress;}
    PanelTableWidget*   getPanelTableWidget()   {return fileTable;}
private:
    QWidget             *currentPath{};
    QGridLayout         *currentPathLayout{};

    QWidget             *info{};
    QGridLayout         *infoLayout{};

    QWidget             *find{};
    QGridLayout         *findLayout{};

    QWidget             *edit{};
    QGridLayout         *editLayout{};

    PanelTableWidget    *fileTable{}  ;
    QTreeWidget         *fileTree{}   ;
    QDir                *currPath{};
    QString             currPathAddress{};

    void createTable();
    void createTree();

    QString getRightsStringFile(const QFileInfo& fileInfo);
    QString getRightsStringPath(const QFileInfo& pathInfo);
    void openFile(const QString& fileName);

    QString panelSide{};

    QMessageBox openDirErr;

signals:
    void changePanelMouse();
    void changeCurrPath();

public slots:
    void updatePanel(const QString& pathName = "");
protected:

protected slots:

};

#endif // PANELWIDGET_H
