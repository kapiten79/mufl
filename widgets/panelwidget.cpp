#include "panelwidget.h"
#include <QDebug>
#include <QDateTime>
#include <QMimeDatabase>
#include <QSettings>
#include <QProcess>
#include <QWindow>
#include <utility>
#include <utility>

PanelWidget::PanelWidget(ViewType panelType, QString p_panelSide, QWidget *parent)
    : QTabWidget(parent),
      currentPath(nullptr),
      currentPathLayout(nullptr),
      info(nullptr),
      infoLayout(nullptr),
      find(nullptr),
      findLayout(nullptr),
      edit(nullptr),
      editLayout(nullptr),
      fileTable(nullptr),
      fileTree(nullptr),
      currPath(nullptr),
      panelSide(std::move(std::move(p_panelSide)))
{
    try {
        currentPath         = new QWidget(this)             ;
        currPath            = new QDir()                    ;
        currentPathLayout   = new QGridLayout(currentPath)  ;
        info                = new QWidget(this)             ;
        infoLayout          = new QGridLayout(info)         ;
        find                = new QWidget(this)             ;
        findLayout          = new QGridLayout(find)         ;
        edit                = new QWidget()                 ;
        editLayout          = new QGridLayout(edit)         ;
    } catch (bad_alloc &ba) {
        qDebug() << QString("Попа с памятью") << ba.what();
    }

    setPanelType(panelType);

    addTab(currentPath, "Текущий каталог")  ;
    addTab(info,        "Информация")       ;
    addTab(find,        "Поиск")            ;
    addTab(edit,        "Редактор")         ;
}

PanelWidget::~PanelWidget()
{
    if (currPath != nullptr) {
        delete currPath;
        currPath = nullptr;
    }
    if (fileTree != nullptr) {
        delete fileTree;
        fileTree = nullptr;
    }
    if (fileTable != nullptr) {
        delete fileTable;
        fileTable = nullptr;
    }
    if (currentPathLayout != nullptr) {
        delete currentPathLayout;
        currentPathLayout = nullptr;
    }
}

/*!
 * \brief PanelWidget::setPanelType - выбор типа панели - дерево или таблица
 * \param panelType
 */
void PanelWidget::setPanelType(ViewType panelType)
{
    switch (panelType) {
    case (table):
        if (fileTable == nullptr)
            createTable();
        break;

    case (tree):
        if (fileTree == nullptr)
            createTree();
        break;
    }
}

/*!
 * \brief PanelWidget::setCurrPath - Изменение адреса текущей папки
 * \param path - адрес папки, в которую надо попасть
 * \param pathToSet - имя папки или файла, на которое надо поставить курсор по умолчанию
 */
void PanelWidget::setCurrPath(const QString& path, const QString& pathToSet)
{
    QTableWidgetItem *defaultSelectedItem = nullptr;
    int rowBeforeUpdate = fileTable->currentRow();
    QDir::setCurrent(path);
    currPathAddress = path;
    fileTable->setRowCount(0);
    if (QDir::currentPath() != "/")
        currPath->setFilter(QDir::Dirs|QDir::Files|QDir::NoDot);
    else
        currPath->setFilter(QDir::Dirs|QDir::Files|QDir::NoDotAndDotDot);
    currPath->setSorting(QDir::Name);

    /** Заполнение таблицы панели */
    for(int i=0; i<currPath->entryInfoList().count(); i++) {
        if (QDir::currentPath() != "/" && i == 0) {
            QFileInfo currEntry = currPath->entryInfoList()[i];
            fileTable->setRowCount(fileTable->rowCount()+1);
            fileTable->setItem(i,ColumnType::name,new QTableWidgetItem(currEntry.fileName()));
            fileTable->setItem(i,ColumnType::type,new QTableWidgetItem(""));
            fileTable->setItem(i,ColumnType::size,new QTableWidgetItem(""));
            fileTable->setItem(i,ColumnType::date,new QTableWidgetItem(""));
            fileTable->setItem(i,ColumnType::rights,new QTableWidgetItem(""));
            fileTable->setItem(i,ColumnType::owner,new QTableWidgetItem(""));
            defaultSelectedItem = fileTable->item(i,ColumnType::name);
        } else {
            QFileInfo currEntry = currPath->entryInfoList()[i];
            fileTable->setRowCount(fileTable->rowCount()+1);
            fileTable->setItem(i,ColumnType::name,new QTableWidgetItem(currEntry.fileName()));
            if (currEntry.fileName() == pathToSet)
                defaultSelectedItem = fileTable->item(i,ColumnType::name);
            if (currEntry.isFile()) {
                fileTable->setItem(i,ColumnType::type,new QTableWidgetItem("file"));
                fileTable->setItem(i,ColumnType::size,new QTableWidgetItem(QString::number(currEntry.size())));
                fileTable->setItem(i,ColumnType::rights,new QTableWidgetItem(getRightsStringFile(currEntry)));
            }
            else {
                fileTable->setItem(i,ColumnType::size,new QTableWidgetItem(QString::number(currEntry.size())));
                fileTable->setItem(i,ColumnType::type,new QTableWidgetItem(" DIR"));
                fileTable->setItem(i,ColumnType::rights,new QTableWidgetItem(getRightsStringPath(currEntry)));
            }
            fileTable->setItem(i,ColumnType::date,new QTableWidgetItem(currEntry.metadataChangeTime().toString("hh:mm:ss dd.MM.yy")));
            fileTable->setItem(i,ColumnType::owner,new QTableWidgetItem(currEntry.owner()));
        }
        fileTable->item(i,ColumnType::type)->setFlags(Qt::NoItemFlags);
        fileTable->item(i,ColumnType::size)->setFlags(Qt::NoItemFlags);
        fileTable->item(i,ColumnType::date)->setFlags(Qt::NoItemFlags);
        fileTable->item(i,ColumnType::rights)->setFlags(Qt::NoItemFlags);
        fileTable->item(i,ColumnType::owner)->setFlags(Qt::NoItemFlags);
    }
    fileTable->sortByColumn(ColumnType::name,Qt::AscendingOrder);
    fileTable->sortByColumn(ColumnType::type,Qt::AscendingOrder);
    if (defaultSelectedItem != nullptr)
        fileTable->setCurrentItem(defaultSelectedItem);
    else
        if(rowBeforeUpdate < fileTable->rowCount())
            fileTable->setCurrentItem(fileTable->item(rowBeforeUpdate,ColumnType::name));
        else
            fileTable->setCurrentItem(fileTable->item(fileTable->rowCount()-1,ColumnType::name));
    emit changeCurrPath();
}

/*!
 * \brief PanelWidget::getRightsStringFile получение строки с правами для файла fileInfo
 * \param fileInfo
 * \return
 */
QString PanelWidget::getRightsStringFile(const QFileInfo& fileInfo)
{
    QString rightsString;
    (fileInfo.isReadable()) ? rightsString = rightsString+"R : ": rightsString = rightsString+"nr  : ";
    (fileInfo.isWritable()) ? rightsString = rightsString+"W : ": rightsString = rightsString+"nw  : ";
    (fileInfo.isExecutable()) ? rightsString = rightsString+"E": rightsString = rightsString+"ne";
    return rightsString;
}

/*!
 * \brief PanelWidget::getRightsStringPath - получение строки с правами для папки pathInfo
 * \param fileInfo
 * \return
 */
QString PanelWidget::getRightsStringPath(const QFileInfo& pathInfo)
{
    QString rightsString;
    (pathInfo.isReadable()) ? rightsString = rightsString+"R : ": rightsString = rightsString+"nr  : ";
    (pathInfo.isWritable()) ? rightsString = rightsString+"W ": rightsString = rightsString+"nw ";
    return rightsString;
}


/*!
 * \brief PanelWidget::createTable - инициализация таблицы с папками и файлами текущего каталога
 */
void PanelWidget::createTable()
{
    try {
        fileTable = new PanelTableWidget(this);
    } catch (bad_alloc &ba) {
        qDebug() << "Попа с памятью " << ba.what();
    }

    fileTable->setSelectionMode(QAbstractItemView::ExtendedSelection)   ;
    fileTable->setSelectionBehavior(QAbstractItemView::SelectRows)      ;
    fileTable->setEditTriggers(QAbstractItemView::NoEditTriggers)       ;

    fileTable->verticalHeader()->setVisible(false);

    currentPathLayout->addWidget(fileTable);
    fileTable->setColumnCount(6);
    fileTable->setHorizontalHeaderItem(ColumnType::name,new QTableWidgetItem(tr("Файл")))      ;
    fileTable->setHorizontalHeaderItem(ColumnType::type,new QTableWidgetItem(tr("Тип")))       ;
    fileTable->setHorizontalHeaderItem(ColumnType::size,new QTableWidgetItem(tr("Размер")))    ;
    fileTable->setHorizontalHeaderItem(ColumnType::date,new QTableWidgetItem(tr("Дата")))      ;
    fileTable->setHorizontalHeaderItem(ColumnType::rights,new QTableWidgetItem(tr("Права")))   ;
    fileTable->setHorizontalHeaderItem(ColumnType::owner,new QTableWidgetItem(tr("Владелец"))) ;

    fileTable->setColumnWidth(ColumnType::name,200);
    fileTable->setColumnWidth(ColumnType::date,130);

    setCurrPath();

    /** Переход в другой каталог по двойному клику мышкой */
    connect(fileTable, &PanelTableWidget::itemDoubleClicked,[=] (QTableWidgetItem* item){
        fileTable->setCurrentCell(item->row(),ColumnType::name);
        QFileInfo currItem(currPathAddress,item->text());
        if (currItem.isDir()) {
            if (currItem.isReadable()) {
                if (fileTable->currentRow() == 0) {
                    QString pathAddr = currPathAddress;
                    int pathNameIndexFromRight = pathAddr.length() - pathAddr.lastIndexOf("/")-1;
                    int pathNameIndexFromLeft = pathAddr.lastIndexOf("/");
                    if (pathNameIndexFromLeft == 0)
                        pathNameIndexFromLeft = 1;
                    setCurrPath(pathAddr.left(pathNameIndexFromLeft), pathAddr.right(pathNameIndexFromRight));
                }
                else {
                    if (currPathAddress == "/")
                        currPathAddress = "";
                    setCurrPath(currPathAddress+"/"+item->text());
                }
            }
        }
        else {
            openFile(item->text());
        }
        emit changePanelMouse();
    });

    /** Обработка одинарного клика мышкой */
    connect(fileTable, &PanelTableWidget::itemClicked,[=] (QTableWidgetItem* item){

        if (QFileInfo(*currPath,item->text()).isDir()) {
            fileTable->setCurrentCell(item->row(),ColumnType::name);
        }
        emit changePanelMouse();
    });

    /** Переход между каталогами по нажатию клавиш enter */
    connect(fileTable, &PanelTableWidget::enterPressed,[=] (QTableWidgetItem* item) {
        fileTable->setCurrentCell(item->row(),ColumnType::name);
        QFileInfo currItem(currPathAddress,item->text());
        if (currItem.isDir()) {
            if (currItem.isReadable()) {
                fileTable->setCurrentCell(item->row(),ColumnType::name);
                if (fileTable->currentRow() == 0 && currPathAddress != "/") {
                    QString pathAddr = currPathAddress;
                    int pathNameIndexFromRight = pathAddr.length() - pathAddr.lastIndexOf("/")-1;
                    int pathNameIndexFromLeft = pathAddr.lastIndexOf("/");
                    if (pathNameIndexFromLeft == 0)
                        pathNameIndexFromLeft = 1;
                    setCurrPath(pathAddr.left(pathNameIndexFromLeft), pathAddr.right(pathNameIndexFromRight));
                }
                else {
                    if (currPathAddress == "/")
                        currPathAddress = "";
                    setCurrPath(currPathAddress+"/"+item->text());
                }
            }
            else {
                QMessageBox::critical(this, QObject::tr("Ошибка открытия каталога"), QObject::tr("У вас нет прав для просмотра данного каталога"));
            }
        }
        else {
            openFile(item->text());
        }
    });
}

/*!
 * \brief PanelWidget::openFile - Открытие файла по mime типу
 * \param fileName - название файла
 */
void PanelWidget::openFile(const QString& fileName)
{
    /** Определяем, является ли данный файл запускаемым. Если нет, ищем mime тип */
    if (QFileInfo(currPathAddress+"/"+fileName).isExecutable()) {
        auto *myProcess = new QProcess(this);
        myProcess->start(fileName);
    }
    else {
        /** Это файл, по нажатию enter его нужно попробовать запустить */
        QMimeDatabase db;
        QMimeType type = db.mimeTypeForFile(currPathAddress+"/"+fileName);
        /** Ищем тип в локальном для пользователя списке */

        /** Ищем тип в глобальном списке  */

        QFile file("/usr/share/applications/mimeapps.list");
        QStringList commands;
        bool fileOpenFlag = false;
        if(file.open(QIODevice::ReadOnly)) {
            while(!file.atEnd()) {
                QString currLine = file.readLine();
                if (currLine.contains(type.name())) {
                    int indexBegin = currLine.indexOf("=");
                    int i = indexBegin;
                    int lastIndex = indexBegin;
                    /** Находим очередной desktop файл */
                    QString execDir(QDir::currentPath());
                    bool firstIterate = true;
                    while (i > 0) {
                        lastIndex = i;
                        i = currLine.indexOf(QString(";"), i);
                        QString desktopFileName;
                        if (firstIterate)
                            desktopFileName = currLine.mid(lastIndex+1, i-lastIndex-1);
                        else
                            desktopFileName = currLine.mid(lastIndex, i-lastIndex);
                        firstIterate = false;
                        /** Если имя desktop файла содержит "-", это означает, что файл находится
                         * по адресу <mainPath>/<префикс_перед_тире>/applications/префикс_перед_тире */
                        QString fullAddressDesktopFile;
                        if (desktopFileName.contains("-")) {
                            i += desktopFileName.indexOf("-");
                            QString prefix = desktopFileName.left(desktopFileName.indexOf("-"));
                            desktopFileName = desktopFileName.right(desktopFileName.length() - desktopFileName.indexOf("-")-1);
                            fullAddressDesktopFile = "/usr/share/"+prefix+"/applications/"+prefix;
                        }
                        else {
                            fullAddressDesktopFile = "/usr/share/applications";
                        }
                        /** Определяем его местонахождение */
                        QString trueDir =  fullAddressDesktopFile;
                        if (QFile(trueDir+"/"+desktopFileName).exists()) {
                            QSettings desktopFile(trueDir+"/"+desktopFileName, QSettings::IniFormat);
                            QString execCommand = desktopFile.value("Desktop Entry/Exec").toString();

                            int uIndex = execCommand.indexOf("%U");
                            execCommand.remove(uIndex, execCommand.length() - uIndex);
                            execCommand = "xdg-open ";
                            execCommand = execCommand + "\""+execDir+"/" + fileName+"\"";
                            qDebug() << execCommand;
                            QStringList arguments;
                            auto *myProcess = new QProcess(this);
                            myProcess->start(execCommand);
                            connect(myProcess, &QProcess::errorOccurred, [=](QProcess::ProcessError error) {
                                switch(error){
                                case 0:
                                    qDebug() << "Программа не запустилась.";
                                    break;
                                case 1:
                                    qDebug() << "Критическая ошибка. Программа закрылась аварийно.";
                                    break;
                                case 2:
                                    qDebug() << "Превышено время ожидания программы";
                                    break;
                                case 3:
                                    qDebug() << "Ошибка передачи данных в программу";
                                    break;
                                case 4:
                                    qDebug() << "Ошибка чтения данных из программы";
                                    break;
                                case 5:
                                    qDebug() << "Неизвестная ошибка";
                                    break;
                                }
                            });
                            QDir::setCurrent(execDir);
                            fileOpenFlag = true;
                            break;
                        }
                        i++;
                    }
                    break;
                }
                if(fileOpenFlag)break;
            }
            file.close();
        }
        else
        {
            qDebug() << "Файл не открылся";
        }
    }
}
/*!
 * \brief PanelWidget::createTree - инициализация дерева с файлами и папками для данного каталога (не реализовано)
 */
void PanelWidget::createTree()
{
    fileTree = new QTreeWidget(this);
}

/*!
 * \brief PanelWidget::updatePanel - обновление панели с файлами после изменения содежимого каталога
 * \param pathName - имя нового каталога если он создан. В противном случаее имя пустое.
 */
void PanelWidget::updatePanel(const QString& pathName)
{
    /** В случае, если создаётся новый каталог, курсор должен на него встать */
    if (pathName != "") {
        setCurrPath(currPathAddress, pathName);
    }
    else {
        /** Все остальные случаи - курсор остаётся на той-же позиции в списке если она существует. Если позиция была последней и удалена,
            курсор должен сдвинуться на 1 позицию вверх */
        bool selectedPanelFlag = fileTable->currentItem()->isSelected();

        /** Строка может быть удалена. Это надо проверить и, в случае если её не существует, передать текст соседней */
        QString defaultItemText;
        currPath->refresh();
        if (!QDir::searchPaths(fileTable->currentItem()->text()).count()) {
            defaultItemText = fileTable->item(fileTable->currentRow(),0)->text();
        }
        else
            defaultItemText = fileTable->currentItem()->text();

        setCurrPath(currPathAddress, defaultItemText);

        fileTable->currentItem()->setSelected(selectedPanelFlag);
    }
}
