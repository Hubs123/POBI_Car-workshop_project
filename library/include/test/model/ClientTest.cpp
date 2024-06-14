#include <boost/test/unit_test.hpp>
#include "typedefs.h"
#include "model/Client.h"

using namespace std;
namespace btt = boost::test_tools;

struct TestSuiteClientFixture {
    const string testFirstName = "Jon";
    const string testLastName = "Arbuckle";
    const int testPersonalID = 123456789;

    ClientTypePtr base;
    ClientTypePtr silver;
    ClientTypePtr gold;
    ClientTypePtr platinum;

    TestSuiteClientFixture() {
        base = make_shared<Default>();
        silver = make_shared<Silver>();
        gold = make_shared<Gold>();
        platinum = make_shared<Platinum>();
    }

    ~TestSuiteClientFixture() {
    }
};

BOOST_FIXTURE_TEST_SUITE(TestSuiteClient, TestSuiteClientFixture)

    BOOST_AUTO_TEST_CASE(ConstructorTest) {
        Client client(testFirstName, testLastName, testPersonalID, gold);

        BOOST_TEST(client.getFirstName() == testFirstName);
        BOOST_TEST(client.getLastName() == testLastName);
        BOOST_TEST(client.getPersonalID() == testPersonalID);
    }

    BOOST_AUTO_TEST_CASE(testSetFirstName) {
        Client client(testFirstName, testLastName, testPersonalID, gold);

        client.setFirstName("imie2");
        BOOST_CHECK_EQUAL(client.getFirstName(), "imie2");

        client.setFirstName("");
        BOOST_CHECK_EQUAL(client.getFirstName(), "imie2");
    }

    BOOST_AUTO_TEST_CASE(testSetLastName) {
        Client client(testFirstName, testLastName, testPersonalID, gold);

        client.setLastName("nazwisko2");
        BOOST_TEST(client.getLastName() == "nazwisko2");
        client.setLastName("");
        BOOST_TEST(client.getLastName() == "nazwisko2");
    }

    BOOST_AUTO_TEST_CASE(testSetClientType) {
        Client client(testFirstName, testLastName, testPersonalID, gold);

        client.setClientType(platinum);
        BOOST_CHECK_EQUAL(client.getClientType(), platinum);
        client.setClientType(nullptr);
        BOOST_CHECK_EQUAL(client.getClientType(), platinum);
    }

BOOST_AUTO_TEST_SUITE_END()