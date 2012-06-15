#ifndef __MAINWINDOW_H__
#define __MAINWINDOW_H__

#include <QWidget>
#include <QGraphicsView>

#include "environment.h"

class MainWindow: public QWidget{
	Q_OBJECT

	public:
		MainWindow(QWidget *parent = 0);
		~MainWindow();

	private:
		QGraphicsView *m_view;
		Environment *m_env;

	private slots:
		void scaleView(const int delta);
};

#endif

