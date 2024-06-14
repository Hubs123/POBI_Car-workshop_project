#include <boost/test/unit_test.hpp>
#include "typedefs.h"
#include "model/Repair.h"
#include "model/TyreRepair.h"
#include "model/OilChange.h"
#include "model/TimingChainRepair.h"
#include <memory>

using namespace std;
namespace btt = boost::test_tools;

struct TestSuiteRepairFixture {
    const double testBasePrice = 50.0;
    const string testNameTyre = "oponki";
    const string testNameOil = "olejek";
    const string testNameChain = "lancuszek";
    const int testEngineAge = 2010;
    const int testID = 12345;
    OilType testOilType = synthetic;
};

BOOST_FIXTURE_TEST_SUITE(TestSuiteRepair, TestSuiteRepairFixture)

    BOOST_AUTO_TEST_CASE(ConstructorTest) {
        RepairPtr repair = make_shared<TyreRepair>(testBasePrice, testNameTyre, testID, 17);

        BOOST_CHECK_EQUAL(repair->getBasePrice(), testBasePrice);
        BOOST_CHECK_EQUAL(repair->getName(), testNameTyre);
        BOOST_CHECK_EQUAL(repair->getID(), testID);
    }

    BOOST_AUTO_TEST_CASE(TyreRepairTests) {
        RepairPtr tyre = make_shared<TyreRepair>(testBasePrice, testNameTyre, testID, 17);

        BOOST_CHECK_CLOSE(tyre->getActualPrice(), 55.0, 0.0001);
    }

    BOOST_AUTO_TEST_CASE(OilChangeTest) {
        RepairPtr oil = make_shared<OilChange>(testBasePrice, testNameOil, testID, testEngineAge, testOilType);

        BOOST_CHECK_CLOSE(oil->getActualPrice(), 77.0, 0.0001);
    }

    BOOST_AUTO_TEST_CASE(TimingChainRepairTest) {
        RepairPtr chain = make_shared<TimingChainRepair>(testBasePrice, testNameChain, testID, testEngineAge);

        BOOST_CHECK_CLOSE(chain->getActualPrice(), 55.0, 0.0001);
    }


BOOST_AUTO_TEST_SUITE_END()