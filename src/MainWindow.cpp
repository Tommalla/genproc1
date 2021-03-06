/* Tomasz [Tommalla] Zakrzewski, 2013
 * All rights reserved */
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QFileDialog>
#include <QDir>
#include <QKeyEvent>
#include "MainWindow.hpp"
#include "calc.hpp"
#include "ui_MainWindow.h"

const qint32 defaultWidth = 800, defaultHeight = 600, defaultStartingPoints = 120, defaultExpProb = 2525,
		defaultPointlessSize = 200, defaultForce = 3, defaultField = 2, defaultAccuracy = 3,
		defaultMinHeight = -1, defaultMaxHeight = 1, defaultFrame = 1;

void MainWindow::setDefaults() {
	ui->widthEdit->setText(QString::number(defaultWidth));
	ui->heightEdit->setText(QString::number(defaultHeight));

	ui->startingPointsEdit->setText(QString::number(defaultStartingPoints));
	ui->probabilityEdit->setText(QString::number(defaultExpProb));

	ui->accuracyEdit->setText(QString::number(defaultAccuracy));
	ui->minHEdit->setText(QString::number(defaultMinHeight));
	ui->maxHEdit->setText(QString::number(defaultMaxHeight));

	ui->pointlessSizeEdit->setText(QString::number(defaultPointlessSize));
	ui->rationalizeFieldEdit->setText(QString::number(defaultFrame));
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
	landmap[1] = qRgb(0, 139, 69);
	landmap[2] = qRgb(238, 64, 0);

	changeSmoothBox(0);
	ui->smoothenBox->setVisible(false);
	ui->smoothenCheckBox->setVisible(false);
	changeWaterBox(0);
	changeRationalize(0);

	//connect the components
	QObject::connect(ui->generateButton, &QPushButton::clicked, this, &MainWindow::generateMap);

	//checkboxes
	QObject::connect(ui->pointlessWaterCheckbox, &QCheckBox::stateChanged, this, &MainWindow::changeWaterBox);
	QObject::connect(ui->smoothenCheckBox, &QCheckBox::stateChanged, this, &MainWindow::changeSmoothBox);
	QObject::connect(ui->rationalizeCheckbox, &QCheckBox::stateChanged, this, &MainWindow::changeRationalize);

	QObject::connect(ui->actionSave, &QAction::triggered, this, &MainWindow::save);

	QObject::connect(ui->methodBox, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
			 this, &MainWindow::changeAlgorithm);
}

MainWindow::~MainWindow() {
	delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent* e) {
    QWidget::keyPressEvent(e);
    if (e->key() == Qt::Key_Return)
	    generateMap();
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
		{
			qint16 accuracy = ui->accuracyEdit->text().toUShort();
			qint8 minHeight = ui->minHEdit->text().toShort();
			qint8 maxHeight = ui->maxHEdit->text().toShort();
			generators::perlinsNoise(*map, accuracy, minHeight, maxHeight);
			break;
		}
		default:
			return;
	}

	if (ui->rationalizeCheckbox->isChecked())
		filters::rationalize(*map, ui->rationalizeFieldEdit->text().toUInt());

	switch (ui->fillerBox->currentIndex()) {
		case 0:
			fillers::standard(*map);
			break;
	}

	//TODO apply filters
	if (ui->pointlessWaterCheckbox->isChecked())
		filters::removePointlessWater(*map, ui->pointlessSizeEdit->text().toUInt());

	//generate the image from the map
	if (mapImage.width() != width || mapImage.height() != height)
		mapImage = QImage(width, height, QImage::Format_RGB32);

	for (qint32 i = 0; i < width; ++i)
		for (qint32 j = 0; j < height; ++j) {
			qint32 h = map->heightAt(i, j);
			Type t = map->typeAt(i, j);

			//FIXME this line is SLOW
			mapImage.setPixel(i, j, ((t == Type::LAND) ? landmap[h] : watermap[h]));
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

void MainWindow::changeRationalize(int state) {
	ui->rationalizeBox->setEnabled(state == 2);
}


void MainWindow::save() {
	QString filename = QFileDialog::getSaveFileName(this,
		tr("Save"), QDir::currentPath(), tr("PNG images (*.png)"));

	if (filename.length() == 0)
		return;

	mapImage.save(filename + ".png");
}

void MainWindow::changeAlgorithm(qint32 id) {
	ui->algOptsStackedWidget->setCurrentIndex(id);
}


