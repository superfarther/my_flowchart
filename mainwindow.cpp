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
    QAction *pCppToChartAction = pToolsMenu->addAction("打开C代码转流程图");
    QAction *pChartToCppAction = pToolsMenu->addAction("流程图转C代码并另存");
}

void MainWindow::createToolBar(){
    pToolbar = this->addToolBar("tool");
    pToolbar->setMovable(false);
    pToolbar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon); //设置ToolBar中Action的显示样式

    QAction *pTextBoxAction = pToolbar->addAction(QIcon(":/img/textbox.jpg"), "文本框");
    QAction *pFontSizeAction = pToolbar->addAction(QIcon(":/img/FontSize.jpg"), "字体大小");
    QAction *pColourAction = pToolbar->addAction(QIcon(":/img/colour.jpg"), "颜色");
}

void MainWindow::createGraphicalDock(){
    pGraphicScroll = new QScrollArea(this);
    pGraphicScroll->setMaximumWidth(295);
    //创建幕布
    QWidget *widget = new QWidget(this);

    //创建基础图形的groupbox
    QGroupBox *baseGraBox = new QGroupBox("基础图形", pGraphicScroll);
    baseGraBox->setAlignment(Qt::AlignCenter); //标题居中
    baseGraBox->setMinimumSize(250, 600);
    //创建基础图形lable
    initialOrEndLab = new MyLabel(this);
    initialOrEndLab->mylabtype = MyLabel::initial_end_item;
    initialOrEndLab->setMinimumSize(40, 40);
    initialOrEndLab->setMaximumSize(60, 60);
    initialOrEndLab->setPixmap(QPixmap(":/img/Rounded_Rectangle.png"));
    initialOrEndLab->setScaledContents(1);  //设置pixmap自适应lable大小
    initialOrEndLab->setToolTip("开始或结束");   //设置鼠标悬停提示
    initialOrEndLab->setCursor(Qt::PointingHandCursor);

    procedureLab = new MyLabel(this);
    procedureLab->mylabtype = MyLabel::procedure_item;
    procedureLab->setMinimumSize(40, 40);
    procedureLab->setMaximumSize(60, 60);
    procedureLab->setPixmap(QPixmap(":/img/rectangle.png"));
    procedureLab->setScaledContents(1);  //设置pixmap自适应lable大小
    procedureLab->setToolTip("流程");   //设置鼠标悬停提示
    procedureLab->setCursor(Qt::PointingHandCursor);

    judgeLab = new MyLabel(this);
    judgeLab->mylabtype = MyLabel::judge_item;
    judgeLab->setMinimumSize(40, 40);
    judgeLab->setMaximumSize(60, 60);
    judgeLab->setPixmap(QPixmap(":/img/diamond.png"));
    judgeLab->setScaledContents(1);  //设置pixmap自适应lable大小
    judgeLab->setToolTip("判断");   //设置鼠标悬停提示
    judgeLab->setCursor(Qt::PointingHandCursor);
    //创建baseGrabox的网格布局
    QGridLayout *baseGri = new QGridLayout;
    baseGri->addWidget(initialOrEndLab, 0, 0, Qt::AlignTop);
    baseGri->addWidget(procedureLab, 0, 1, Qt::AlignTop);
    baseGri->addWidget(judgeLab, 0, 2, Qt::AlignTop);
    baseGraBox->setLayout(baseGri);

    //创建自定义图形的groupbox
    QGroupBox *customGraBox = new QGroupBox("自定义图形", pGraphicScroll);
    customGraBox->setAlignment(Qt::AlignCenter);
    customGraBox->setMinimumSize(200, 600);

    //创建幕布的垂直布局，并将上述两个groupbox添加至其中
    QVBoxLayout *widgetVBoxLatOut = new QVBoxLayout;
    widgetVBoxLatOut->addWidget(baseGraBox);
    widgetVBoxLatOut->addWidget(customGraBox);
    //将widgetVBoxLatOut添加到widget中
    widget->setLayout(widgetVBoxLatOut);
    //将幕布添加到pGraphicScroll中
    pGraphicScroll->setWidget(widget);
}

void MainWindow::createScene(){
    pMyScene = new My_graphicsscene();

    /*
    Adsorption_point *mypoint = new Adsorption_point();
    mypoint->setPos(QPointF(0,0));
    qreal radius = mypoint->getRadius();
    mypoint->setRect(-radius, -radius, 2*radius, 2*radius);
    pMyScene->addItem(mypoint);
    */

    //点击标签并在scene中产生图元
    QObject::connect(initialOrEndLab, &MyLabel::myLabClick, pMyScene, &My_graphicsscene::on_myLabClick);
    QObject::connect(procedureLab, &MyLabel::myLabClick, pMyScene, &My_graphicsscene::on_myLabClick);
    QObject::connect(judgeLab, &MyLabel::myLabClick, pMyScene, &My_graphicsscene::on_myLabClick);
}

void MainWindow::createView(){
    int width = this->width();
    int height = this->height();

    pMyView = new My_graphicsview();
    pMyView->setSceneRect(-3*width/2,-3*height/2, 3*width, 3*height);
}
