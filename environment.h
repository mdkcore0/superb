#ifndef __ENVIRONMENT_H__
#define __ENVIRONMENT_H__

#include <QGraphicsSceneWheelEvent>
#include <QGraphicsScene>
#include <QSize>

#include "lifeworld.h"

class Environment: public QGraphicsScene{
	Q_OBJECT

	public:
		Environment(const QSize size);
		~Environment();

	private:
		virtual void wheelEvent(QGraphicsSceneWheelEvent *wheelEvent);

		LifeWorld *m_lifeWorld;

	signals:
		void scale(const int delta);
};

#endif

