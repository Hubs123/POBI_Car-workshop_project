#include <boost/test/unit_test.hpp>
#include "repositories/ServiceRepository.h"
#include "model/TyreRepair.h"
#include <memory>
#include <boost/date_time/gregorian/greg_date.hpp>

using namespace std;
namespace btt = boost::test_tools;
namespace gr = boost::gregorian;

struct TestSuiteServiceRepositoryFixture {
    ServicePtr service;
    ServicePtr service2;

    ClientPtr client;
    ClientPtr client2;

    RepairPtr repair;
    RepairPtr repair2;

    const double testBasePrice = 50.0;
    const string testName = "oponki";
    const int testID = 12345;

    const double testBasePrice2 = 25.0;
    const string testName2 = "silniczek";
    const int testID2 = 54321;


    TestSuiteServiceRepositoryFixture() {
        repair = make_shared<TyreRepair>(testBasePrice, testName, testID, 15);
        repair2 = make_shared<TyreRepair>(testBasePrice2, testName2, testID2, 17);

        service = make_shared<Service>(testID, pt::ptime(gr::date(2024, 4, 29), pt::hours(9)), client, repair);
        service2 = make_shared<Service>(testID2, pt::ptime(gr::date(1410, 7, 15), pt::hours(3)), client2, repair2);
    }

    ~TestSuiteServiceRepositoryFixture() {
    }
};

BOOST_FIXTURE_TEST_SUITE(TestSuiteServiceRepository, TestSuiteServiceRepositoryFixture)

    BOOST_AUTO_TEST_CASE(ServiceRepositoryTest) {
        ServiceRepository repository;
        int testID3 = 12345;

        BOOST_CHECK_EQUAL(repository.getSize(), 0);

        repository.addService(service);
        repository.addService(service2);

        BOOST_CHECK_EQUAL(repository.getSize(), 2);

        auto foundServices = repository.findBy([testID3](const ServicePtr& ptr)->bool{
            return ptr->getID() == testID3;
        });

        BOOST_TEST(foundServices.size() == 1);
        BOOST_TEST(foundServices[0] == service);

        repository.removeService(service);

        BOOST_CHECK_EQUAL(repository.getSize(), 1);

        repository.removeService(service2);
        BOOST_CHECK_EQUAL(repository.getSize(), 0);
    }

BOOST_AUTO_TEST_SUITE_END()