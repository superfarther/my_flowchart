#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    createMenuBar();
    createToolBar();
    createGraphicalDock();

    createScene();
    createView();
    pMyView->setScene(pMyScene);

    QHBoxLayout *horlayout = new QHBoxLayout();
    horlayout->addWidget(pGraphicScroll);
    horlayout->addWidget(pMyView);

    QWidget *my_centralWidget = new QWidget(this);
    this->setCentralWidget(my_centralWidget);
    this->centralWidget()->setLayout(horlayout);

    pMyView->setMouseTracking(1);
    this->setMouseTracking(1);
}

MainWindow::~MainWindow()
{

}

void MainWindow::newFile(){

}

void MainWindow::openFile(){

}

void MainWindow::saveFileAs(){

}

void MainWindow::createMenuBar(){
    pMenuBar = this->menuBar();

    QMenu *pFileMenu = pMenuBar->addMenu("文件");
    QAction *pNewFileAction = pFileMenu->addAction("新建", this, &MainWindow::newFile);
    QAction *pOpenFileAction = pFileMenu->addAction("打开");
    QAction *pSaveFileAsAction = pFileMenu->addAction("另存为");

    QMenu *pToolsMenu = pMenuBar->addMenu("工具");
    QAction *pCppToChartAction = pToolsMenu->addAction("c语言生成流程图");
    QAction *pChartToCppAction = pToolsMenu->addAction("流程图转为c语言");

    ChartToCppAction = pChartToCppAction;
}

void MainWindow::createToolBar(){
    pToolbar = this->addToolBar("tool");
    pToolbar->setMovable(false);
    pToolbar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon); 

    QAction *pTextBoxAction = pToolbar->addAction(QIcon(":/img/textbox.jpg"), "文本框");
    QAction *pFontSizeAction = pToolbar->addAction(QIcon(":/img/FontSize.jpg"), "字体大小");
    QAction *pColourAction = pToolbar->addAction(QIcon(":/img/colour.jpg"), "颜色");
}

void MainWindow::createGraphicalDock(){
    pGraphicScroll = new QScrollArea(this);
    pGraphicScroll->setMaximumWidth(295);
 
    QWidget *widget = new QWidget(this);

 
    QGroupBox *baseGraBox = new QGroupBox("基础图形", pGraphicScroll);
    baseGraBox->setAlignment(Qt::AlignCenter); 
    baseGraBox->setMinimumSize(250, 600);
 
    initialOrEndLab = new MyLabel(this);
    initialOrEndLab->mylabtype = MyLabel::initial_end_item;
    initialOrEndLab->setMinimumSize(40, 40);
    initialOrEndLab->setMaximumSize(60, 60);
    initialOrEndLab->setPixmap(QPixmap(":/img/Rounded_Rectangle.png"));
    initialOrEndLab->setScaledContents(1); 
    initialOrEndLab->setToolTip("开始或结束"); 
    initialOrEndLab->setCursor(Qt::PointingHandCursor);

    procedureLab = new MyLabel(this);
    procedureLab->mylabtype = MyLabel::procedure_item;
    procedureLab->setMinimumSize(40, 40);
    procedureLab->setMaximumSize(60, 60);
    procedureLab->setPixmap(QPixmap(":/img/rectangle.png"));
    procedureLab->setScaledContents(1); 
    procedureLab->setToolTip("流程"); 
    procedureLab->setCursor(Qt::PointingHandCursor);

    judgeLab = new MyLabel(this);
    judgeLab->mylabtype = MyLabel::judge_item;
    judgeLab->setMinimumSize(40, 40);
    judgeLab->setMaximumSize(60, 60);
    judgeLab->setPixmap(QPixmap(":/img/diamond.png"));
    judgeLab->setScaledContents(1); 
    judgeLab->setToolTip("判断"); 
    judgeLab->setCursor(Qt::PointingHandCursor);
 
    QGridLayout *baseGri = new QGridLayout;
    baseGri->addWidget(initialOrEndLab, 0, 0, Qt::AlignTop);
    baseGri->addWidget(procedureLab, 0, 1, Qt::AlignTop);
    baseGri->addWidget(judgeLab, 0, 2, Qt::AlignTop);
    baseGraBox->setLayout(baseGri);

 
    QGroupBox *customGraBox = new QGroupBox("自定义图形", pGraphicScroll);
    customGraBox->setAlignment(Qt::AlignCenter);
    customGraBox->setMinimumSize(200, 600);

 
    QVBoxLayout *widgetVBoxLatOut = new QVBoxLayout;
    widgetVBoxLatOut->addWidget(baseGraBox);
    widgetVBoxLatOut->addWidget(customGraBox);
 
    widget->setLayout(widgetVBoxLatOut);
 
    pGraphicScroll->setWidget(widget);
}

void MainWindow::createScene(){
    pMyScene = new My_graphicsscene();

     

 
    QObject::connect(initialOrEndLab, &MyLabel::myLabClick, pMyScene, &My_graphicsscene::on_myLabClick);
    QObject::connect(procedureLab, &MyLabel::myLabClick, pMyScene, &My_graphicsscene::on_myLabClick);
    QObject::connect(judgeLab, &MyLabel::myLabClick, pMyScene, &My_graphicsscene::on_myLabClick);
 
    QObject::connect(ChartToCppAction, &QAction::triggered, pMyScene, &My_graphicsscene::flowChart_C);
}

void MainWindow::createView(){
    int width = this->width();
    int height = this->height();

    pMyView = new My_graphicsview();
    pMyView->setSceneRect(-6*width/2,-6*height/2, 6*width, 6*height);
}
