#ifndef _BHS_PRODUCTION_META_TEST_HPP_
#define _BHS_PRODUCTION_META_TEST_HPP_

#include <QDebug>
#include <QtTest>
#include <bhsProductionMeta.hpp>

class bhsProductionMetaTest: public QObject
{
	Q_OBJECT
private slots:
	void testContentDataRetrieval();
};

#endif