#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QToolBar>
#include <QAction>
#include <QScrollArea>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QWidget>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QGroupBox>
#include <Qt>

#include "my_graphicsscene.h"
#include "my_graphicsview.h"
#include "MyGraphicsItem/initial_end_item.h"
#include "MyClass/mylabel.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void newFile();
    void openFile();
    void saveFileAs();

private:
    void createMenuBar();
    void createToolBar();
    void createGraphicalDock();
    void createScene();
    void createView();

    QMenuBar *pMenuBar = nullptr;               //MenuBar
    QToolBar *pToolbar = nullptr;               //ToolBar
    QScrollArea *pGraphicScroll = nullptr;      //GraphicsDock
    My_graphicsscene *pMyScene = nullptr;       //scene
    My_graphicsview *pMyView = nullptr;         //view
    MyLabel *initialOrEndLab = nullptr;         //圆角矩形
    MyLabel *procedureLab = nullptr;            //矩形
    MyLabel *judgeLab = nullptr;                //菱形
};

#endif // MAINWINDOW_H
