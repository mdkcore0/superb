#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QWidget(parent){
	resize(640, 480); // temp

	m_env = new Environment(QSize(200, 200));
	connect(m_env, SIGNAL(scale(int)), this, SLOT(scaleView(int)));
	//m_env = new Environment(QSize(640, 480));
	m_view = new QGraphicsView(m_env, this);

	m_view->setDragMode(QGraphicsView::ScrollHandDrag);
	//m_view->scale(1600 / 100, 1600 / 100);
	//m_view->scale(50.0, 50.0);
	//m_view->scale(30.0, 30.0);
	//m_view->scale(10.0, 10.0);
}

MainWindow::~MainWindow(){
}

void MainWindow::scaleView(const int delta){
	if (delta > 0)
		m_view->scale(1.2, 1.2);
	else
		m_view->scale(1 / 1.2, 1 / 1.2);
}

