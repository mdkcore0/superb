#ifndef __LIFEWORLD_H__
#define __LIFEWORLD_H__

#include <QGraphicsPixmapItem>
#include <QPainter>
#include <QObject>
#include <QTimer>
#include <QSize>

#define FIELD_W		100
#define FIELD_L		100

class LifeWorld: public QObject, public QGraphicsPixmapItem{
	Q_OBJECT

	public:
		LifeWorld(const QSize size);
		~LifeWorld();

	private slots:
		void update();

	private:
		void drawGrid(QPainter *painter);

		QTimer *m_timer;
		QSize m_size;

		qint32 m_field[FIELD_L][FIELD_W];
		qint32 m_nextField[FIELD_L][FIELD_W];
};

#endif

