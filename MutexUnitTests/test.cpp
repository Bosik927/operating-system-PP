#define BOOST_TEST_MODULE Unit_Test_Mutex
#include <boost/test/included/unit_test.hpp>
#include "../syslib/operating-system-PP/Mutex.h"

BOOST_FIXTURE_TEST_SUITE(MutexTest, Mutex)
BOOST_AUTO_TEST_CASE(LockUnlock) {
	PCB process1("proc_1", 1), process2("proc_2", 2), process3("proc_3", 3);

	BOOST_TEST(this->lock(process1) == true);
	BOOST_TEST(this->isBlock() == true);
	BOOST_TEST(this->lock(process2) == false);
	BOOST_TEST(this->isBlock() == true);

	this->unlock(process1);
	BOOST_TEST(this->lock(process3) == false);

	this->unlock(process2);
	BOOST_TEST(this->isBlock() == true);

	this->unlock(process3);
	BOOST_TEST(this->isBlock() == false);
}
BOOST_AUTO_TEST_CASE(LockUnlockPtr) {
	PCB process1("proc_1", 1);
	PCB* process_ptr = &process1;

	this->lock(*process_ptr);
	BOOST_TEST(this->isBlock() == true);
	this->unlock(process1);
	BOOST_TEST(this->isBlock() == false);
}
BOOST_AUTO_TEST_CASE(LockUnlockRef) {
	PCB process1("proc_1", 1);
	PCB& process_ref = process1;

	this->lock(process1);
	BOOST_TEST(this->isBlock() == true);
	this->unlock(process_ref);
	BOOST_TEST(this->isBlock() == false);
}
BOOST_AUTO_TEST_CASE(ToString) {
	PCB process1("proc_1", 1), process2("proc_2", 1), process3("proc_3", 1);

	BOOST_TEST(this->toString() == "Zamek otwarty;");

	this->lock(process1);
	BOOST_TEST(this->toString() == "Zamek zamkniety przez proces proc_1;");
	this->lock(process1);
	BOOST_TEST(this->toString() == "Zamek zamkniety przez proces proc_1;");

	this->lock(process2);
	BOOST_TEST(this->toString() == "Zamek zamkniety przez proces proc_1; ilosc oczekujacych procesow: 1;");

	this->lock(process3);
	BOOST_TEST(this->toString() == "Zamek zamkniety przez proces proc_1; ilosc oczekujacych procesow: 2;");

	this->unlock(process1);
	BOOST_TEST(this->toString() == "Zamek zamkniety przez proces proc_2; ilosc oczekujacych procesow: 1;");
}
BOOST_AUTO_TEST_CASE(UsingProcess) {
	PCB process1("proc_1", 1);

	BOOST_CHECK(this->getUsingProcess() == nullptr);
	this->lock(process1);
	BOOST_CHECK(this->getUsingProcess() == &process1);
}
BOOST_AUTO_TEST_CASE(WaitingProcesses) {
	PCB process1("proc_1", 1), process2("proc_2", 1), process3("proc_3", 1);
	std::vector<PCB*> tmpVector;

	BOOST_TEST(this->getWaitingProcesses()->size() == 0);

	this->lock(process1);
	this->lock(process2);
	tmpVector.push_back(&process2);
	auto testVector = this->getWaitingProcesses();
	BOOST_TEST(testVector->size() == tmpVector.size());
	for (int i = 0; i < testVector->size(); i++) {
		BOOST_CHECK(testVector->at(i) == tmpVector.at(i));
	}

	this->lock(process3);
	tmpVector.push_back(&process3);
	BOOST_TEST(testVector->size() == tmpVector.size());
	for (int i = 0; i < testVector->size(); i++) {
		BOOST_CHECK(testVector->at(i) == tmpVector.at(i));
	}
}
BOOST_AUTO_TEST_SUITE_END()