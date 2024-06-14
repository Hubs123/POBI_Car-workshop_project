#include "managers/ServiceManager.h"
#include "typedefs.h"
#include "model/TyreRepair.h"
#include "model/Client.h"
#include "model/ClientType.h"
#include <boost/test/unit_test.hpp>
#include <memory>
#include <boost/date_time/gregorian/greg_date.hpp>
#include "model/Service.h"

using namespace std;
namespace btt = boost::test_tools;
namespace gr = boost::gregorian;

struct TestSuiteServiceManagerFixture {
    ServiceManager manager;
    ClientPtr client1;
    ClientPtr client2;
    ClientTypePtr base;
    RepairPtr repair1;
    RepairPtr repair2;
    ServicePtr service1;
    ServicePtr service2;

    const string testFirstName1 = "imie1";
    const string testLastName1 = "nazwisko1";
    const int testPersonalID1 = 11111;

    const string testFirstName2 = "imie2";
    const string testLastName2 = "nazwisko2";
    const int testPersonalID2 = 22222;

    const double testBasePrice1 = 25.0;
    const string testName1 = "oponki";
    const int testID1 = 33333;

    const double testBasePrice2 = 50.0;
    const string testName2 = "silniczek";
    const int testID2 = 44444;

    pt::ptime testStartTime1 = pt::ptime(gr::date(2024, 4, 29), pt::hours(9));
    pt::ptime testStartTime2 = pt::ptime(gr::date(1410, 7, 15), pt::hours(6));

    TestSuiteServiceManagerFixture() {
        base = make_shared<Default>();

        client1 = make_shared<Client>(testFirstName1, testLastName1, testPersonalID1, base);
        client2 = make_shared<Client>(testFirstName2, testLastName2, testPersonalID2, base);

        repair1 = make_shared<TyreRepair>(testBasePrice1, testName1, testID1, 17);
        repair2 = make_shared<TyreRepair>(testBasePrice2, testName2, testID2, 15);
    }

    ~TestSuiteServiceManagerFixture() {
    }
};

BOOST_FIXTURE_TEST_SUITE(TestSuiteServiceManager, TestSuiteServiceManagerFixture)

    BOOST_AUTO_TEST_CASE (TestRegister) {
        service1 = manager.registerService(testID1, testStartTime1, client1, repair1);
        service2 = manager.registerService(testID2, testStartTime2, client2, repair2);

        BOOST_CHECK_EQUAL(manager.findAllServices().size(), 2);

        try {
            manager.registerService(testID1, testStartTime1, client1, repair1);
        } catch (std::exception& e) {
            BOOST_TEST(std::string(e.what()) == "Service o podanym ID juz istnieje.");
        }

        BOOST_CHECK_EQUAL(manager.findAllServices().size(), 2);

        manager.unregisterService(service1);

        BOOST_CHECK_EQUAL(manager.findAllServices().size(), 1);
        BOOST_CHECK_EQUAL(manager.findAllArchivedServices().size(), 1);

        manager.unregisterService(service2);

        BOOST_CHECK_EQUAL(manager.findAllServices().size(), 0);
        BOOST_CHECK_EQUAL(manager.findAllArchivedServices().size(), 2);
    }

    BOOST_AUTO_TEST_CASE(TestGetService) {
        service1 = manager.registerService(testID1, testStartTime1, client1, repair1);
        service2 = manager.registerService(testID2, testStartTime2, client2, repair2);

        BOOST_CHECK_EQUAL(manager.getService(testID1), service1);
        BOOST_CHECK_EQUAL(manager.getService(testID2), service2);

        manager.unregisterService(service1);

        try {
            manager.unregisterService(service1);
        } catch (std::exception& e) {
            BOOST_TEST(std::string(e.what()) == "Service nie istnieje");
        }
    }

    BOOST_AUTO_TEST_CASE(TestFindServices) {
        service1 = manager.registerService(testID1, testStartTime1, client1, repair1);
        service2 = manager.registerService(testID2, testStartTime2, client2, repair2);

        BOOST_CHECK_EQUAL(manager.findAllServices().size(), 2);

        manager.unregisterService(service2);

        BOOST_CHECK_EQUAL(manager.findAllServices().size(), 1);
        BOOST_CHECK_EQUAL(manager.findAllArchivedServices().size(), 1);

        manager.unregisterService(service1);

        BOOST_CHECK_EQUAL(manager.findAllServices().size(), 0);
        BOOST_CHECK_EQUAL(manager.findAllArchivedServices().size(), 2);
    }

BOOST_AUTO_TEST_SUITE_END()
