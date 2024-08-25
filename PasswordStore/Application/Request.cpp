#include "Request.h"

#include "StringServices.h"


Request::Request(const std::string& theRequestString)
{
    this->parse(theRequestString);
}


Command Request::viewCommand(void) const
{
    return m_command;
}


void Request::parse(const std::string& theRequestString)
{
    m_data = String::explodeRequest(theRequestString);

    const std::string endPoint = String::endPoint(m_data.at("Endpoint"));
    const bool endPointIsValid = !endPoint.empty() && EndPointToCommand.count(endPoint);

    m_command = endPointIsValid ? EndPointToCommand.at(endPoint) : Command::UNDEFINED;
}
