#include "bhsProductionMetaTest.hpp"

void bhsProductionMetaTest::firsttest() {
	int res = testfn();
	QCOMPARE(res, 2);
}


int main(int argc, char** argv) {
	bhsProductionMetaTest* t{new bhsProductionMetaTest};
	QTest::qExec(t, argc, argv);
}