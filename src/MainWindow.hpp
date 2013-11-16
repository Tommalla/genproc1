/*
 * Tomasz [Tommalla] Zakrzewski, 2013
 * All rights reserved
 */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QImage>
#include <QMap>
#include "Map.hpp"

namespace Ui {
	class MainWindow;
}

/**
 * @brief The main window of the application
 **/
class MainWindow : public QMainWindow {
	Q_OBJECT;
	private:
		Ui::MainWindow *ui;
		QImage mapImage;
		Map* map;
		QHash<qint32, QRgb> watermap, landmap;

		void setDefaults();

	public:
		explicit MainWindow(QWidget *parent = 0);
		//virtual void resizeEvent (QResizeEvent* event);
		~MainWindow();

	private slots:
		void generateMap();
		void changeWaterBox(int state);
		void changeSmoothBox(int state);
		void save();
};


#endif // MAINWINDOW_H
