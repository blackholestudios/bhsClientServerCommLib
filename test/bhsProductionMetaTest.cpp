#include "bhsProductionMetaTest.hpp"

void bhsProductionMetaTest::testContentDataRetrieval() {
	BhsProductionMeta::DB db{"./testproj"};
	const BhsProductionMeta::ConverData converData{db.getContentVersionData("shot/001/layout/v001")};
	QCOMPARE(converData.status, BhsProductionMeta::ConverData::ASSIGNED);
	QCOMPARE(converData.assignee, "gmartell");
	QCOMPARE(converData.deadline, QDateTime::fromString("2017-07-24T15:46:29", Qt::ISODate));
	QCOMPARE(converData.commitDate, QDateTime());
}


int main(int argc, char** argv) {
	bhsProductionMetaTest* t{new bhsProductionMetaTest};
	QTest::qExec(t, argc, argv);
}