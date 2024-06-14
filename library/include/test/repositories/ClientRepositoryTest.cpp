#include <boost/test/unit_test.hpp>
#include "repositories/ClientRepository.h"
#include <memory>

using namespace std;
namespace btt = boost::test_tools;

struct TestSuiteClientRepositoryFixture {
    ClientPtr client;
    ClientPtr client2;
    ClientTypePtr gold;
    ClientTypePtr silver;

    TestSuiteClientRepositoryFixture() {
        gold = make_shared<Gold>();
        silver = make_shared<Silver>();

        client = make_shared<Client>("Jon", "Arbuckle", 12345, gold);
        client2 = make_shared<Client>("Jon2", "Arbuckle2", 54321, silver);
    }

    ~TestSuiteClientRepositoryFixture() {

    }
};

BOOST_FIXTURE_TEST_SUITE(TestSuiteClientRepository, TestSuiteClientRepositoryFixture)

    BOOST_AUTO_TEST_CASE(ClientRepositoryTest) {
    ClientRepository repository;
    BOOST_CHECK_EQUAL(repository.getSize(), 0);

    repository.addClient(client);
    repository.addClient(client2);

    BOOST_CHECK_EQUAL(repository.getSize(), 2);

    repository.removeClient(client);

    BOOST_CHECK_EQUAL(repository.getSize(), 1);
    BOOST_CHECK_EQUAL(repository.findByPersonalID(54321), client2);
    BOOST_CHECK_EQUAL(repository.findByPersonalID(12354), nullptr);

    repository.removeClient(client2);

    BOOST_CHECK_EQUAL(repository.getSize(), 0);
     }

BOOST_AUTO_TEST_SUITE_END()