#include "mainwindow.h"
#include <QDebug>

/*! Конструктор основного окна*/
MainWindow::MainWindow(QApplication *a, QWidget *parent)
    : QMainWindow(parent),
      app(a)
{
    try {
        setMinimumHeight(768);
        setMinimumWidth (1280);

        setWindowTitle("MUFL Commander");

            createPathDialog    = new CreatePathDialog(this);
            removePathDialog    = new RemovePathDialog(this);
            copyFileDialog      = new CopyFileDialog(this)  ;
            findFileDialog      = new FindDialog(this)      ;
            createFileDialog    = new CreateFileDialog(this);

            commandLine         = new QLineEdit(this)                                       ;
            centralWidget       = new QWidget(this)                                         ;
            centralGridLayout   = new QGridLayout(centralWidget)                            ;
            leftPanel           = new PanelWidget(ViewType::table,"left", centralWidget)    ;
            rightPanel          = new PanelWidget(ViewType::table,"right", centralWidget)   ;

            helpWidget = new QWidget(centralWidget) ;
            helpLayout = new QHBoxLayout(helpWidget);

            helpLabelList << new QLabel("F1\nПомощь",helpWidget)                       ;
            helpLabelList << new QLabel("F2\nСоздание\nзакладки",helpWidget)           ;
            helpLabelList << new QLabel("F3\nИнформация\nо файле/каталоге",helpWidget) ;
            helpLabelList << new QLabel("F4\nРедактирование\nфайла",helpWidget)        ;
            helpLabelList << new QLabel("F5\nКопирование\nфайла/каталога",helpWidget)  ;
            helpLabelList << new QLabel("F6\nПеренос\nфайла/каталога",helpWidget)      ;
            helpLabelList << new QLabel("F7\nСоздание\nкаталога",helpWidget)           ;
            helpLabelList << new QLabel("F8\nУдаление\nфайла/каталога",helpWidget)     ;
            helpLabelList << new QLabel("F9",helpWidget)                               ;
            helpLabelList << new QLabel("F10",helpWidget)                              ;
            helpLabelList << new QLabel("F11\nСвернуть\nокно",helpWidget)              ;
            helpLabelList << new QLabel("F12\nВыход",helpWidget)                       ;

        commandLine->setText(QDir::homePath());
        setCentralWidget(centralWidget);

        leftTable = leftPanel->getPanelTableWidget();
        leftPanel->getPanelTableWidget()->setFocus();

        rightTable = rightPanel->getPanelTableWidget();
        rightTable->currentItem()->setSelected(false);

        centralGridLayout->addWidget(leftPanel, 0,0);
        centralGridLayout->addWidget(rightPanel,0,1);
        centralGridLayout->addWidget(commandLine,1,0,1,2);

        for (auto &currLabel : helpLabelList) {
            currLabel->setAlignment(Qt::AlignHCenter|Qt::AlignTop);
            helpLayout->addWidget(currLabel);
        }

        centralGridLayout->addWidget(helpWidget,2,0,1,2);
        addConnect();
    } catch (std::exception &error) {
        qDebug() << "Исключение возникло в методе MainWindow класса MainWindow " << error.what();
    }

}

MainWindow::~MainWindow()
{
    if (centralWidget != nullptr) {
        delete centralWidget;
        centralWidget = nullptr;
    }
}

void MainWindow::addConnect()
{
    try {
        connect(leftPanel, &PanelWidget::changeCurrPath, [=](){
            commandLine->setText(QDir::currentPath());
        });
        connect(rightPanel, &PanelWidget::changeCurrPath, [=](){
            commandLine->setText(QDir::currentPath());
        });

        /** Переключение табом между панелями кнопкой TAB*/
        connect(leftPanel->getPanelTableWidget(), &PanelTableWidget::changePanel, [=](){
            leftTable->currentItem()->setSelected(false);
            rightTable->currentItem()->setSelected(true);
            rightPanel->getPanelTableWidget()->setFocus();
            QDir::setCurrent(rightPanel->getCurrPath());
            commandLine->setText(QDir::currentPath());
        });
        connect(rightPanel->getPanelTableWidget(), &PanelTableWidget::changePanel, [=](){
            leftTable->currentItem()->setSelected(true);
            rightTable->currentItem()->setSelected(false);
            leftPanel->getPanelTableWidget()->setFocus();
            QDir::setCurrent(leftPanel->getCurrPath());
            commandLine->setText(QDir::currentPath());
        });

        /** Переключение между панелями мышкой */
        connect(leftPanel, &PanelWidget::changePanelMouse, [=](){
            rightTable->currentItem()->setSelected(false);
            QDir::setCurrent(leftPanel->getCurrPath());
            commandLine->setText(QDir::currentPath());
        });
        connect(rightPanel, &PanelWidget::changePanelMouse, [=](){
            leftTable->currentItem()->setSelected(false);
            QDir::setCurrent(rightPanel->getCurrPath());
            commandLine->setText(QDir::currentPath());
        });

        /** Окно создания каталогов для обоих панелей */
        connect(leftPanel->getPanelTableWidget(), &PanelTableWidget::createPath, [=](){
            createPathDialog->show();
            commandLine->setText(QDir::currentPath());
        });
        connect(rightPanel->getPanelTableWidget(), &PanelTableWidget::createPath, [=](){
            createPathDialog->show();
            commandLine->setText(QDir::currentPath());
        });

        /** Создание каталога */
        connect(createPathDialog, &CreatePathDialog::pathCreate, [=](QString newPathName){
            if (leftPanel->getCurrPath() == rightPanel->getCurrPath()) {
                bool isSelectedLeft = leftTable->currentItem()->isSelected();
                leftPanel->updatePanel(newPathName);
                if (leftTable->currentItem() != nullptr)
                    leftTable->currentItem()->setSelected(isSelectedLeft);

                bool isSelectedRight = rightTable->currentItem()->isSelected();
                rightPanel->updatePanel(newPathName);
                if (rightTable->currentItem() != nullptr)
                    rightTable->currentItem()->setSelected(isSelectedRight);
                rightPanel->getPanelTableWidget()->clearSelectedList();
                leftPanel->getPanelTableWidget()->clearSelectedList();
            }
            else {
                bool isSelectedLeft = leftTable->currentItem()->isSelected();
                if (isSelectedLeft) {
                    leftPanel->updatePanel(newPathName);
                    leftTable->currentItem()->setSelected(isSelectedLeft);
                }
                bool isSelectedRight = rightTable->currentItem()->isSelected();
                if (isSelectedRight) {
                    rightPanel->updatePanel(newPathName);
                    rightTable->currentItem()->setSelected(isSelectedRight);
                }
                rightPanel->getPanelTableWidget()->clearSelectedList();
                leftPanel->getPanelTableWidget()->clearSelectedList();
            }

        });

        /** Окно для удаления каталогов и файлов */
        connect(leftPanel->getPanelTableWidget(), &PanelTableWidget::removePath, [=](QString removePathName){
            if (leftPanel->getPanelTableWidget()->getSelectedList().count() > 0)
                removePathDialog->setPathOrFileToRemove(leftPanel->getPanelTableWidget()->getSelectedList());
            else
            {
                removePathDialog->setPathOrFileToRemove(QStringList()<<removePathName);
            }
            removePathDialog->show();
            commandLine->setText(QDir::currentPath());
        });
        connect(rightPanel->getPanelTableWidget(), &PanelTableWidget::removePath, [=](QString removePathName){
            if (rightPanel->getPanelTableWidget()->getSelectedList().count() > 0)
                removePathDialog->setPathOrFileToRemove(rightPanel->getPanelTableWidget()->getSelectedList());
            else
            {
                removePathDialog->setPathOrFileToRemove(QStringList()<<removePathName);
            }
            removePathDialog->show();
            commandLine->setText(QDir::currentPath());
        });
        connect(removePathDialog, &RemovePathDialog::pathOrFileRemoved, [=]() {
            bool isSelectedLeft = leftTable->currentItem()->isSelected();
            bool isSelectedRight = rightTable->currentItem()->isSelected();
            if (!QDir(rightPanel->getCurrPath()).exists())
                rightPanel->setCurrPath(leftPanel->getCurrPath());
            if (!QDir(leftPanel->getCurrPath()).exists())
                leftPanel->setCurrPath(rightPanel->getCurrPath());
            rightPanel->updatePanel();
            leftPanel->updatePanel();
            leftTable->currentItem()->setSelected(isSelectedLeft);
            rightTable->currentItem()->setSelected(isSelectedRight);

            rightPanel->getPanelTableWidget()->clearSelectedList();
            leftPanel->getPanelTableWidget()->clearSelectedList();
        });

        /** Окно для копирования файлов */
        connect(leftPanel->getPanelTableWidget(), &PanelTableWidget::copyPathOrFile, [=](QStringList p_selectedFileList){
            copyFileDialog->setParams(p_selectedFileList, leftPanel->getCurrPath(), rightPanel->getCurrPath());
            copyFileDialog->show();
            commandLine->setText(QDir::currentPath());
        });
        connect(rightPanel->getPanelTableWidget(), &PanelTableWidget::copyPathOrFile, [=](QStringList p_selectedFileList){
            copyFileDialog->setParams(p_selectedFileList, rightPanel->getCurrPath(), leftPanel->getCurrPath());
            copyFileDialog->show();
            commandLine->setText(QDir::currentPath());
        });

        connect(copyFileDialog, &CopyFileDialog::copyFinished, [=](QString currPath){
            leftPanel->updatePanel();
            rightPanel->updatePanel();

            rightPanel->getPanelTableWidget()->clearSelectedList();
            leftPanel->getPanelTableWidget()->clearSelectedList();

            QDir::setCurrent(currPath);
            commandLine->setText(QDir::currentPath());
        });

        /** Окно для переноса файлов */
        connect(leftPanel->getPanelTableWidget(), &PanelTableWidget::movePathOrFile, [=](QStringList p_selectedFileList){
            copyFileDialog->setParams(p_selectedFileList, leftPanel->getCurrPath(), rightPanel->getCurrPath(), true);
            copyFileDialog->show();
            commandLine->setText(QDir::currentPath());
        });
        connect(rightPanel->getPanelTableWidget(), &PanelTableWidget::movePathOrFile, [=](QStringList p_selectedFileList){
            copyFileDialog->setParams(p_selectedFileList, rightPanel->getCurrPath(), leftPanel->getCurrPath(), true);
            copyFileDialog->show();
            commandLine->setText(QDir::currentPath());
        });

        /** Создание нового файла */
        connect(leftPanel->getPanelTableWidget(), &PanelTableWidget::createFile, [=](){
            createFileDialog->show();
            commandLine->setText(QDir::currentPath());
        });
        connect(rightPanel->getPanelTableWidget(), &PanelTableWidget::createFile, [=](){
            createFileDialog->show();
            commandLine->setText(QDir::currentPath());
        });

        /** Редактирование существующего файла */
        connect(leftPanel->getPanelTableWidget(), &PanelTableWidget::editFile, [=](QString fileName){
            QString program = "kate";
            QFileInfo currItem(QDir::currentPath()+"/"+fileName);
            if (currItem.isFile()) {
                auto *editFile = new QProcess(this);
                editFile->start(program, QStringList() << QDir::currentPath()+"/"+fileName);
            }

            commandLine->setText(QDir::currentPath());
        });
        connect(rightPanel->getPanelTableWidget(), &PanelTableWidget::editFile, [=](QString fileName){
            QString program = "kate";
            QFileInfo currItem(QDir::currentPath()+"/"+fileName);
            if (currItem.isFile()) {
                auto *editFile = new QProcess(this);
                editFile->start(program, QStringList() << QDir::currentPath()+"/"+fileName);
            }

            commandLine->setText(QDir::currentPath());
        });
        /** сворачивание окна по F11 */
        connect(leftPanel->getPanelTableWidget(), &PanelTableWidget::setMinimizeWindow, [=](){
            if (this->windowState() == Qt::WindowMaximized)
                this->setWindowState(Qt::WindowMinimized);
            else
                this->setWindowState(Qt::WindowMaximized);
        });
        connect(rightPanel->getPanelTableWidget(), &PanelTableWidget::setMinimizeWindow, [=](){
            if (this->windowState() == Qt::WindowMaximized)
                this->setWindowState(Qt::WindowMinimized);
            else
                this->setWindowState(Qt::WindowMaximized);
        });

        /** Закрытие окна по F12 */
        connect(leftPanel->getPanelTableWidget(), &PanelTableWidget::setCloseWindow, [=](){
            QApplication::closeAllWindows();
        });
        connect(rightPanel->getPanelTableWidget(), &PanelTableWidget::setCloseWindow, [=](){
            QApplication::closeAllWindows();
        });
        /** Показать окно поиска */
        connect(leftPanel->getPanelTableWidget(), &PanelTableWidget::showFindWindow, [=](){
            findFileDialog->show();
        });
        connect(rightPanel->getPanelTableWidget(), &PanelTableWidget::showFindWindow, [=](){
            findFileDialog->show();
        });
    } catch (std::exception &error) {
        qDebug() << "Исключение возникло в методе addConnect класса MainWindow " << error.what();
    }

}


