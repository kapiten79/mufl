#ifndef PANELTABLEWIDGET_H
#define PANELTABLEWIDGET_H

#include <QTableWidget>
#include <QString>
#include <QKeyEvent>

enum ColumnType {
    name,
    size,
    date,
    rights,
    owner
};

class PanelTableWidget : public QTableWidget
{
    Q_OBJECT
public:
    PanelTableWidget(QWidget *parent = nullptr);

    void        clearSelectedList() ;
    QStringList getSelectedList()   ;

private:
    bool isSelectAll    ;
    bool isShift        ;

    QStringList selectedList;
protected:
    void keyPressEvent(QKeyEvent *event)    ;
    void keyReleaseEvent(QKeyEvent *event)  ;

signals:
    void createFile()                           ;
    void editFile(QString fileName)             ;
    void enterPressed(QTableWidgetItem* item)   ;
    void changePanel()                          ;
    void createPath()                           ;
    void removePath(QString pathName)           ;
    void copyPathOrFile(QStringList p_selectedFileList);
    void movePathOrFile(QStringList p_selectedFileList);
    void setMinimizeWindow()                    ;
    void setCloseWindow()                       ;
    void insertPressed()                        ;
    void showFindWindow()                       ;
};

#endif // PANELTABLEWIDGET_H
