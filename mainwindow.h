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

    QMenuBar *pMenuBar = nullptr; 
    QToolBar *pToolbar = nullptr; 
    QScrollArea *pGraphicScroll = nullptr; 
    My_graphicsscene *pMyScene = nullptr; 
    My_graphicsview *pMyView = nullptr; 
    MyLabel *initialOrEndLab = nullptr; 
    MyLabel *procedureLab = nullptr; 
    MyLabel *judgeLab = nullptr; 

    QAction *ChartToCppAction = nullptr; 
};

#endif 
