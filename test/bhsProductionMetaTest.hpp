#ifndef _BHS_PRODUCTION_META_TEST_HPP_
#define _BHS_PRODUCTION_META_TEST_HPP_

#include <QDebug>
#include <QtTest>
#include <bhsProductionMeta.hpp>

class BhsProductionMetaTest: public QObject
{
	Q_OBJECT

private slots:
	void initTestCase();
	void testGetContentVersionData();
	void testGetAllUsers();

private:
	BhsProductionMeta::DB* db;

};

#endif