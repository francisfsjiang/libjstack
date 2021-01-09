#define BOOST_TEST_DYN_LINK

#include <string>
#include <exception>
#include <boost/test/unit_test.hpp>
#include <boost/bind/bind.hpp>

#include <libpq-fe.h>

#include "net/http/client/curl_easy.hpp"

using namespace boost::unit_test;


std::string libpq_test()
{
    const char conninfo[] =
            "postgresql://libjstack:libjstack@127.0.0.1?port=5432&dbname=libjstack_test";
    PGconn *conn = ::PQconnectdb(conninfo);

    if (PQstatus(conn) != CONNECTION_OK) {
        std::cout << "Connection to database failed: " << PQerrorMessage(conn)
                  << std::endl;
        PQfinish(conn);
        throw "Database connection failed.";
    }

    PGresult *res = NULL;
    res = PQexec(conn, "SELECT 2021;");

    std::string result("");

    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        throw std::string("Select failed: ") + PQresultErrorMessage(res);
    }
    else{
        result = PQgetvalue(res, 0, 0);
    }
    PQclear(res);
    return result;
}

BOOST_AUTO_TEST_SUITE(Postgres)
    BOOST_AUTO_TEST_CASE(test_pg) {
        BOOST_CHECK_EQUAL(libpq_test(), "2021");
    }
BOOST_AUTO_TEST_SUITE_END()