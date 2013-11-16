/* Tomasz [Tommalla] Zakrzewski, 2013
 * All rights reserved */
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include "MainWindow.hpp"
#include "calc.hpp"
#include "ui_MainWindow.h"

const qint32 defaultWidth = 1920, defaultHeight = 800, defaultStartingPoints = 20, defaultExpProb = 2500,
		defaultPointlessSize = 100, defaultForce = 3, defaultField = 2;

void MainWindow::setDefaults() {
	ui->widthEdit->setText(QString::number(defaultWidth));
	ui->heightEdit->setText(QString::number(defaultHeight));
	ui->startingPointsEdit->setText(QString::number(defaultStartingPoints));
	ui->probabilityEdit->setText(QString::number(defaultExpProb));

	ui->pointlessSizeEdit->setText(QString::number(defaultPointlessSize));
	ui->forceEdit->setText(QString::number(defaultForce));
	ui->fieldEdit->setText(QString::number(defaultField));
}


MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
	ui->setupUi(this);

	map = nullptr;

	QGraphicsScene* scene = new QGraphicsScene();
	ui->graphicsView->setScene(scene);

	setDefaults();

	watermap[-1] = qRgb(0, 127, 255);
	landmap[0] = qRgb(123, 216, 69);

	changeSmoothBox(0);
	changeWaterBox(0);

	//connect the components
	QObject::connect(ui->generateButton, &QPushButton::clicked, this, &MainWindow::generateMap);

	//checkboxes
	QObject::connect(ui->pointlessWaterCheckbox, &QCheckBox::stateChanged, this, &MainWindow::changeWaterBox);
	QObject::connect(ui->smoothenCheckBox, &QCheckBox::stateChanged, this, &MainWindow::changeSmoothBox);
}

MainWindow::~MainWindow() {

	delete ui;
}

void MainWindow::generateMap() {
	qint32 width, height;
	width = ui->widthEdit->text().toUInt();
	height = ui->heightEdit->text().toUInt();

	delete map;
	map = new Map(width, height);

	//creating a new map
	switch (ui->methodBox->currentIndex()) {
		case 0:
		{
			qint32 startingPoints = ui->startingPointsEdit->text().toUInt();
			qint32 expProb = ui->probabilityEdit->text().toUInt();
			generators::cellular(*map, startingPoints, expProb);
			break;
		}
		case 1:
			//TODO perlin's
			break;
		default:
			return;
	}

	//TODO apply filters

	if (mapImage.width() != width || mapImage.height() != height)
		mapImage = QImage(width, height, QImage::Format_RGB32);

	for (qint32 i = 0; i < width; ++i)
		for (qint32 j = 0; j < height; ++j) {
			qint32 h = map->heightAt(i, j);
			Type t = map->typeAt(i, j);
			mapImage.setPixel(i, j, (t == Type::LAND) ? landmap[h] : watermap[h]);
		}

	//add the image to the scene
	QGraphicsScene* scene = ui->graphicsView->scene();
	if (scene->items().empty() == false)
		scene->removeItem(scene->items().first());
	scene->addItem(new QGraphicsPixmapItem(QPixmap::fromImage(mapImage)));
}

void MainWindow::changeWaterBox(int state) {
	ui->waterBox->setEnabled(state == 2);
}

void MainWindow::changeSmoothBox(int state) {
	ui->smoothenBox->setEnabled(state == 2);
}

