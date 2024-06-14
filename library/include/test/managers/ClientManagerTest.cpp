#include "managers/ClientManager.h"
#include "model/ClientType.h"
#include <boost/test/unit_test.hpp>
#include <memory>

using namespace std;
namespace btt = boost::test_tools;

struct TestSuiteClientManagerFixture {
    ClientManager manager;
    ClientTypePtr base;

    const string testFirstName = "Jon";
    const string testLastName = "Arbuckle";
    const int testPersonalID = 123456789;

    const string testFirstName2 = "Jon2";
    const string testLastName2 = "Arbuckle2";
    const int testPersonalID2 = 987654321;

    TestSuiteClientManagerFixture() {
        base = make_shared<Default>();
    }

    ~TestSuiteClientManagerFixture() {
    }
};

BOOST_FIXTURE_TEST_SUITE(TestSuiteClientManager, TestSuiteClientManagerFixture)

    BOOST_AUTO_TEST_CASE(TestRegister) {
        ClientPtr client = manager.registerClient(testFirstName, testLastName, testPersonalID, base);
        ClientPtr client2 = manager.registerClient(testFirstName2, testLastName2, testPersonalID2, base);

        BOOST_CHECK_EQUAL(manager.findAllClients().size(), 2);

        try {
            ClientPtr client2 = manager.registerClient(testFirstName, testLastName, testPersonalID, base);
        } catch (std::exception& e) {
            BOOST_TEST(std::string(e.what()) == "Klient o podanym ID juz istnieje");
        }

        BOOST_CHECK_EQUAL(manager.findAllClients().size(), 2);

        manager.unregisterClient(client2);

        BOOST_CHECK_EQUAL(manager.findAllClients().size(), 1);
        BOOST_CHECK_EQUAL(manager.findAllArchivedClients().size(), 1);

        manager.unregisterClient(client);

        BOOST_CHECK_EQUAL(manager.findAllClients().size(), 0);
        BOOST_CHECK_EQUAL(manager.findAllArchivedClients().size(), 2);
    }

    BOOST_AUTO_TEST_CASE(TestGetClient) {
        ClientPtr client = manager.registerClient(testFirstName, testLastName, testPersonalID, base);
        ClientPtr client2 = manager.registerClient(testFirstName2, testLastName2, testPersonalID2, base);

        BOOST_CHECK_EQUAL(manager.getClient(testPersonalID), client);
        BOOST_CHECK_EQUAL(manager.getClient(testPersonalID2), client2);

        try {
            manager.unregisterClient(client);
        } catch (std::exception& e) {
            BOOST_TEST(std::string(e.what()) == "Nie znaleziono osoby o podanym ID");
        }
        BOOST_CHECK_EQUAL(manager.getClient(testPersonalID2), client2);

        try {
            manager.unregisterClient(client2);
        } catch (std::exception& e) {
            BOOST_TEST(std::string(e.what()) == "Nie znaleziono osoby o podanym ID");
        }
    }

    BOOST_AUTO_TEST_CASE(TestFindClients) {
        ClientPtr client = manager.registerClient(testFirstName, testLastName, testPersonalID, base);
        ClientPtr client2 = manager.registerClient(testFirstName2, testLastName2, testPersonalID2, base);

        BOOST_CHECK_EQUAL(manager.findAllClients().size(), 2);

        manager.unregisterClient(client2);

        BOOST_CHECK_EQUAL(manager.findAllClients().size(), 1);
        BOOST_CHECK_EQUAL(manager.findAllArchivedClients().size(), 1);

        manager.unregisterClient(client);

        BOOST_CHECK_EQUAL(manager.findAllClients().size(), 0);
        BOOST_CHECK_EQUAL(manager.findAllArchivedClients().size(), 2);
    }

BOOST_AUTO_TEST_SUITE_END()