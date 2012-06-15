#include <QRect>
#include <QPoint>

#include "environment.h"

Environment::Environment(const QSize size): QGraphicsScene(QRect(QPoint(0 , 0), size)){
	m_lifeWorld = new LifeWorld(size);

	addItem(m_lifeWorld);
}

Environment::~Environment(){
}

void Environment::wheelEvent(QGraphicsSceneWheelEvent *wheelEvent){
	if (wheelEvent->delta() > 0)
		emit scale(1);
	else
		emit scale(-1);
}


