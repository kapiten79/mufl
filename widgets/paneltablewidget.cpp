#include "paneltablewidget.h"
#include <QDebug>

PanelTableWidget::PanelTableWidget(QWidget *parent):
    QTableWidget (parent),
    isSelectAll(false),
    isShift(false)
{

}

/*!
 * \brief PanelTableWidget::clearSelectedList - отмена выбора файлов
 */
void PanelTableWidget::clearSelectedList()
{
    for (int i=0; i<selectedList.count(); i++) {
        if (findItems(selectedList[i],Qt::MatchFixedString).count() > 0) {
            findItems(selectedList[i],Qt::MatchFixedString)[0]->setTextColor(QColor(Qt::white));
            selectedList.removeAt(i);
        }
    }
    selectedList.clear();
}

/*!
 * \brief PanelTableWidget::getSelectedList - запрс списка выбранных файлов
 * \return QStringList - список выбранных файлов
 */
QStringList PanelTableWidget::getSelectedList()
{
    return selectedList;
}

/*!
 * \brief PanelTableWidget::keyPressEvent - отлов событий, связанных с нажатием кнопки клавиатуры
 * \param event
 */
void PanelTableWidget::keyPressEvent(QKeyEvent *event)
{
    switch(event->key()) {
    case Qt::Key_Enter:
        emit enterPressed(currentItem());
        clearSelectedList();
        break;
    case Qt::Key_Return:
        emit enterPressed(currentItem());
        clearSelectedList();
        break;
    case Qt::Key_Tab:
        emit changePanel();
        break;
    case Qt::Key_Home:
        setCurrentItem(item(0,ColumnType::name));
        break;
    case Qt::Key_End:
        setCurrentItem(item(rowCount()-1,ColumnType::name));
        break;
    case Qt::Key_Delete:
        if (currentItem()->text() != "..")
            emit removePath(currentItem()->text());
        break;
    case Qt::Key_Asterisk:
        if (selectedList.count() < rowCount()-1) {
            for (int i = 1; i<rowCount(); i++) {
                selectedList << item(i,ColumnType::name)->text();
                item(i,0)->setTextColor(QColor(Qt::yellow));
            }
        }
        else {
            for (int i = 1; i<rowCount(); i++) {
                item(i,0)->setTextColor(QColor(Qt::white));
            }
            selectedList.clear();
        }
        break;
    case Qt::Key_Shift: {
        isShift = true;
        break;
    }
    case Qt::Key_Insert:{
        bool isRemoved = false;
        for (int i = 0; i<selectedList.count(); i++) {
            if (selectedList[i] == currentItem()->text()) {
                selectedList.removeAt(i);
                currentItem()->setTextColor(QColor(Qt::white));
                setCurrentItem(item(currentRow()+1,ColumnType::name));
                isRemoved = true;
                break;
            }
        }
        if (!isRemoved) {
            selectedList << currentItem()->text();
            currentItem()->setTextColor(QColor(Qt::yellow));
            setCurrentItem(item(currentRow()+1,ColumnType::name));
            emit insertPressed();
        }

        break;
    }
    case Qt::Key_F4: {
        if (isShift) {
            emit createFile();
        }
        else {
            emit editFile(currentItem()->text());
        }
        break;
    }
    case Qt::Key_F5: {
        if (currentItem()->text() != "..") {
            if (selectedList.count() == 0) {
                selectedList << currentItem()->text();
            }
            emit copyPathOrFile(selectedList);
        }
        break;
    }
    case Qt::Key_F6:
        if (currentItem()->text() != "..") {
            if (selectedList.count() == 0) {
                selectedList << currentItem()->text();
            }
            emit movePathOrFile(selectedList);
        }
        break;
    case Qt::Key_F7:
        if (isShift) {
            emit showFindWindow();
        }
        else {
            emit createPath();
        }

        break;
    case Qt::Key_F8:
        if (currentItem()->text() != "..")
            emit removePath(currentItem()->text());
        break;
    case Qt::Key_F11:
        emit setMinimizeWindow();
        break;
    case Qt::Key_F12:
        emit setCloseWindow();
        break;
    default:
        QTableWidget::keyPressEvent(event);
        break;
    }
}

/*!
 * \brief PanelTableWidget::keyReleaseEvent - отлов событий связанных с отпусканием кнопки клавиатуры
 * \param event
 */
void PanelTableWidget::keyReleaseEvent(QKeyEvent *event)
{
    switch(event->key()) {
    case Qt::Key_Shift: {
        isShift = false;
        break;
    }
    }
}
