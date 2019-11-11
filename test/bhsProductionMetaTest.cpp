#include "bhsProductionMetaTest.hpp"

void BhsProductionMetaTest::initTestCase() {
	db = new BhsProductionMeta::DB("./testproj");
}

void BhsProductionMetaTest::testGetContentVersionData() {
	const BhsProductionMeta::ConverData converData{db->getContentVersionData("shot/001/layout/v001")};
	QCOMPARE(converData.status, BhsProductionMeta::ConverData::ASSIGNED);
	QCOMPARE(converData.assignee, "gmartell");
	QCOMPARE(converData.deadline, QDateTime::fromString("2017-07-24T15:46:29", Qt::ISODate));
	QCOMPARE(converData.commitDate, QDateTime());
}

void BhsProductionMetaTest::testGetAllUsers() {
	const QStringList read{db->getAllUsers()};
	const QStringList expected{"dsirota", "gmartell"};
	QCOMPARE(read, expected);
}

void BhsProductionMetaTest::testGetUserResponsibilities() {
	const QStringList read{db->getUserResponsibilities("gmartell")};
	const QStringList expected{"/content/shot/001/layout/v001"};
	QCOMPARE(read, expected);
}

int main(int argc, char** argv) {
	BhsProductionMetaTest* t{new BhsProductionMetaTest()};
	QTest::qExec(t, argc, argv);
}