#include <QtGlobal>
#include <QImage>
#include <QTime>

#include "lifeworld.h"

LifeWorld::LifeWorld(const QSize size): m_size(size){
	m_timer = new QTimer();

	qsrand(QTime::currentTime().msec());

	int i, j, population = 0;
	// criando o ambiente inicial
	for (i = 0; i < FIELD_L; i++){
		for (j = 0; j < FIELD_W; j++){
			if ((qrand() % 2)){
			//if ((random() % 2) && seeds_counter){
				m_field[i][j] = m_nextField[i][j] = 1;
				population++;
				//seeds_counter--;
			} else{
				m_field[i][j] = m_nextField[i][j] = 0;
			}
		}
	}

	connect(m_timer, SIGNAL(timeout()), this, SLOT(update()));
	m_timer->start(1000);
}

LifeWorld::~LifeWorld(){
}

void LifeWorld::update(){
	QImage temp(m_size, QImage::Format_ARGB32_Premultiplied);
	QColor bg(Qt::black);
	QColor fg(Qt::white);

	QVector<QPoint> fgPoints;
	temp.fill(bg.rgb());

	QPainter p(&temp);
	p.setPen(fg);

	// rotina de criação/atualização do mundo
	int i, j, alives = 0, new_population = 0;
		for (i = 0; i < FIELD_L; i++){
			for (j = 0; j < FIELD_W; j++){
				// verifica as células vizinhas
				if (m_field[(i - 1) % FIELD_L][(j - 1) % FIELD_W])
					alives++;
				if (m_field[(i - 1) % FIELD_L][j])
					alives++;
				if (m_field[(i - 1) % FIELD_L][(j + 1) % FIELD_W])
					alives++;
				if (m_field[i][(j - 1) % FIELD_W])
					alives++;
				if (m_field[i][(j + 1) % FIELD_W])
					alives++;
				if (m_field[(i + 1) % FIELD_L][(j - 1) % FIELD_W])
					alives++;
				if (m_field[(i + 1) % FIELD_L][j])
					alives++;
				if (m_field[(i + 1) % FIELD_L][(j + 1) % FIELD_W])
					alives++;

				// regra 1: Any live cell with fewer than two live neighbours dies, as if caused by underpopulation.
				if ((m_field[i][j]) && (alives < 2)){
					m_nextField[i][j] = 0; // mórréu
				}
				// regra 2: Any live cell with more than three live neighbours dies, as if by overcrowding.
				else if ((m_field[i][j]) && (alives > 3)){
					m_nextField[i][j] = 0; // mórréu
				}
				// regra 3: Any live cell with two or three live neighbours lives on to the next generation.
				else if ((m_field[i][j]) && ((alives == 2) || (alives == 3))){
					m_nextField[i][j] = 1;
					fgPoints.append(QPoint(i, j));
					new_population++;
				}
				// regra 4: Any dead cell with exactly three live neighbours becomes a live cell.
				else if ((!m_field[i][j]) && (alives == 3)){
					m_nextField[i][j] = 1; // nasceu! \o/
					fgPoints.append(QPoint(i, j));
					new_population++;
				} else{
					m_nextField[i][j] = m_field[i][j]; // nada
					if (m_nextField[i][j])
						fgPoints.append(QPoint(i, j));
					//new_population++; // ?
				}

				alives = 0;
			}
		}

		// TODO: achar solução melhor para isso:
		for (i = 0; i < FIELD_L; i++)
			for (j = 0; j < FIELD_W; j++)
				m_field[i][j] = m_nextField[i][j];

		//printf("Generation: %d\n", generation);
		//generation++;

		//printf("Population: %d\n", population);
		//population = new_population;
		new_population = 0;

		p.drawPoints(fgPoints);

		fgPoints.clear();

		//drawGrid(&p);
	p.end();


	setPixmap(QPixmap::fromImage(temp));
}

void LifeWorld::drawGrid(QPainter *painter){
	int zoomLevel = 320; // 1600%
	//int zoomLevel = 1600; // 1600%
	int zoomFactor = zoomLevel / 100;

	QPen pen(Qt::lightGray);

	painter->save();
		painter->setPen(pen);
		
		// Y
		int starty = 0;

		if (starty % zoomFactor)
			starty = (starty + zoomFactor) / (zoomFactor * zoomFactor);

		for (int y = starty; y <= m_size.height(); y += zoomFactor)
			painter->drawLine(0, y, m_size.width(), y);
		////

		// X
		int startx = 0;

		if (startx % zoomFactor)
			startx = (startx + zoomFactor) / (zoomFactor * zoomFactor);

		for (int x = startx; x <= m_size.width(); x += zoomFactor)
			painter->drawLine(x, 0, x, m_size.height());
		////
	painter->restore();
}

