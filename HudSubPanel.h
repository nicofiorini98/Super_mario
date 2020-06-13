#pragma once

#include <QGraphicsItemGroup>


class HudSubPanel : public QGraphicsItemGroup
{

	//Q_OBJECT
	
	private:

		// NVI idiom
		virtual void doUpdate(const std::string& update_info) = 0;

	public:

		HudSubPanel();

		// NVI idiom we pass an update info if any
		void update(const std::string& update_info = "")
		{
			doUpdate(update_info);
		}

		// pure virtual method 
		virtual void reset() = 0;

};