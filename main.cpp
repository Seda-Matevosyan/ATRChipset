

#include <QtWidgets/QApplication>
#include <QDebug>
#include "configuration.h"


int main(int argc, char *argv[])
{

	QApplication a(argc, argv);
	

	CConfiguration config;
	// Fill config description
	config.setName("Person");
	config.setType("Human");
	config.setVersion(1);

	// Fill config  parameters
	config.setParameter("firstname", QVariant("Mesrop"));
	config.setParameter("lastname", QVariant("Gevorgyan"));
	config.setParameter("age", QVariant(20));
	config.setParameter("location", QVariant("Artashat"));
	config.setParameter("height", QVariant(80));
	config.setParameter("weight", QVariant(175.5));

	// Save config
	config.save("config.json");


	// Loading saved config
	config.reset();
	config.load("config.json");

	qDebug() << "Name: " << config.getName();
	qDebug() << "Type: " << config.getType();
	qDebug() << "Version: " << config.getVersion();

	qDebug() << "Is empty: " << config.isEmpty();
	qDebug() << "Param count: " << config.getParamCount();
	qDebug() << "Is contained 'age' parameter: " << config.isContained("string");

	QVariant value;
	value = config.getParameter("firstname");
	if (value.isValid())
		qDebug() << value.toString();

	value = config.getParameter("lastname");
	if (value.isValid())
		qDebug() << value.toString();

	value = config.getParameter("age");
	if (value.isValid())
		qDebug() << value.toInt();

	value = config.getParameter("location");
	if (value.isValid())
		qDebug() << value.toDouble();

	value = config.getParameter("height");
	if (value.isValid())
		qDebug() << value.toDouble();

	value = config.getParameter("weight");
	if (value.isValid())
		qDebug() << value.toDouble();


	return a.exec();
}
