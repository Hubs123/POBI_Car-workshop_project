#include <boost/test/unit_test.hpp>
#include "model/Service.h"
#include "model/TyreRepair.h"
#include <memory>
#include <boost/date_time/gregorian/greg_date.hpp>

using namespace std;
namespace btt = boost::test_tools;
namespace gr = boost::gregorian;

struct TestSuiteServiceFixture {
    ServicePtr service;

    ClientPtr client;
    ClientTypePtr base;

    const string testFirstName = "imie1";
    const string testLastName = "nazwisko1";
    const int testPersonalID = 22222;

    RepairPtr repair;

    const double testBasePrice = 25.0;
    const string testName = "oponki";
    const int testID = 11111;
    pt::ptime testStartTime = pt::ptime(gr::date(2024, 4, 29), pt::hours(9));

    TestSuiteServiceFixture() {
        base = make_shared<Default>();
        client = make_shared<Client>(testFirstName, testLastName, testPersonalID, base);
        repair = make_shared<TyreRepair>(testBasePrice, testName, testID, 15);
        service = make_shared<Service>(12345, testStartTime, client, repair);
    }

    ~TestSuiteServiceFixture() {
    }
};

BOOST_FIXTURE_TEST_SUITE(TestSuiteService, TestSuiteServiceFixture)

    BOOST_AUTO_TEST_CASE(ConstructorTest) {
        BOOST_CHECK_EQUAL(service->getID(), 12345);
        BOOST_CHECK_EQUAL(service->getStartTime(), testStartTime);
        BOOST_CHECK_CLOSE(service->getServiceCost(), 27.5, 0.0001);
    }

BOOST_AUTO_TEST_SUITE_END()
