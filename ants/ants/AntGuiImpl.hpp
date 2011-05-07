#ifndef _ANT_GUI_IMPL_H_
#define _ANT_GUI_IMPL_H_

#include "IAntGui.h"

namespace antgui 
{
	class QFieldObject
	{
	protected:
		QPixmap pix;
		QFieldObject()  : pix(ANT_SIZE, ANT_SIZE) {}
	public:
		const QPixmap& pixmap() const
		{
			return pix;
		}
	};

	class QAntPainter : public QFieldObject
	{
	protected:
		QAntPainter(){};
		const Ant *ant;
	public:
		void setAnt(const Ant& ant) 
		{
			this->ant = &ant;
		}

		virtual void draw()
		{
			QPainter painter(&pix);
			painter.fillRect(0, 0, ANT_SIZE, ANT_SIZE, QColor(Qt::red));
			painter.end();
		}

		static QAntPainter* getAntPainter(const Ant& ant);
	};

	class QFrozenAntPainter : public QAntPainter
	{
	public:
		QFrozenAntPainter() {}
		virtual void draw()
		{
			QAntPainter::draw();
		}

	};

	class QFoodAntPainter : public QAntPainter
	{
	public:
		QFoodAntPainter() {}
		virtual void draw()
		{
			QAntPainter::draw();
		}
	};

	QAntPainter* QAntPainter::getAntPainter(const Ant& ant)
	{
		QAntPainter *res;
		if (ant.hasFood()) 
		{
			res = new QFoodAntPainter();
		} 
		else if (ant.isFrozen()) 
		{
			res = new QFrozenAntPainter();
		} 
		else 
		{
			res = new QAntPainter();
		}
		res->setAnt(ant);
		return res;
	}

	struct PaintFood 
	{
		void operator() (const map<Point,const Food*>::value_type& p) 
		{
			const Food* food = p.second;
//			widget->paintBox()
		}
		PaintFood(AntWidget * widget, AntGuiQtImpl& antGuiImpl) : widget(widget), antGuiImpl(antGuiImpl) {}
	private:
		AntWidget * widget;
		IAntGuiQtImpl& antGuiImpl;
	};

	struct PaintAnt 
	{
		void operator() (const map<Point,const Ant*>::value_type& p) 
		{
			const Ant* ant = p.second;
			QAntPainter *antPainter = QAntPainter::getAntPainter(*ant);
			widget->drawObject(ant->getPoint(), antPainter->pixmap());
			delete antPainter;
		}
		PaintAnt(AntWidget * widget, IAntGuiQtImpl& antGuiImpl) : widget(widget), antGuiImpl(antGuiImpl) {}
	private:
		AntWidget * widget;
		IAntGuiQtImpl& antGuiImpl;
	};

	class AntGuiQtImpl : IAntGui
	{
		AntWidget * widget;
		map<Point, const Food*> foodMap;
		map<Point, const Ant*> antMap;
		map<int, QColor> teamColor;
	public:

		void SetTeamScore(int teamId, int score) {}

		AntGuiQtImpl(AntWidget* widget, int size) : widget(widget)
		{
			teamColor.insert(pair<int, QColor>::pair(0, QColor(Qt::red)));
			teamColor.insert(pair<int, QColor>::pair(1, QColor(Qt::green)));
			teamColor.insert(pair<int, QColor>::pair(2, QColor(Qt::blue)));
			teamColor.insert(pair<int, QColor>::pair(3, QColor(Qt::yellow)));
		}

		AntGuiQtImpl(AntWidget* widget, int size) : widget(widget)
		{
			teamColor.insert(pair<int, QColor>::pair(0, QColor(Qt::red)));
			teamColor.insert(pair<int, QColor>::pair(1, QColor(Qt::green)));
			teamColor.insert(pair<int, QColor>::pair(2, QColor(Qt::blue)));
			teamColor.insert(pair<int, QColor>::pair(3, QColor(Qt::yellow)));
		}

		virtual void SetAnt(const Ant &ant)
		{
			map<Point,const Ant*>::iterator it = antMap.find(ant.getPoint());

			if (it != antMap.end() && it->second->getTeamId() != ant.getTeamId()) 
			{
				throw GUIException("Point is used by another team ants");
			}

			if (it == antMap.end() || *(it->second) < ant) 
			{
				antMap.insert(pair<Point, const Ant*>::pair(ant.getPoint(), &ant));
			}
		}

		virtual void SetFood(const Food &food)
		{
			foodMap.insert(pair<Point, const Food*>::pair(food.getPoint(), &food));
		}

		virtual void Paint()
		{
			PaintFood paintFood(widget, *this);
			PaintAnt paintAnt(widget, *this);
			for_each(foodMap.begin(), foodMap.end(), paintFood);
			for_each(antMap.begin(), antMap.end(), paintAnt);
		}
	};
}

#endif