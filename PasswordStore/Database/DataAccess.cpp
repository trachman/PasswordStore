#include "DataAccess.h"


DataAccess::DataAccess(void)
: m_pqxx(std::make_unique<pqxx::connection>())
{
}


DataAccess::~DataAccess(void)
{
    m_pqxx.reset();
}
