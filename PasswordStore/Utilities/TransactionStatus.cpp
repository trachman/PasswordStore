// Includes
//
#include "TransactionStatus.h"


// Constructor
// 
// Description:
// Initializes a default Transaction Status.
// 
TransactionStatus::TransactionStatus(void)
: m_state(TransactionStatus::State::UNDEFINED),
  m_errorMessage(""),
  m_httpResponse("")
{
    // Nothing else to do.
    //
}


// isAPass
// 
// Description:
// Determines if this Transaction is a pass.
// 
bool TransactionStatus::isAPass(void) const
{
    return m_state == State::PASS;
}


// isAFail
// 
// Description:
// Determines if this Transaction is a fail.
// 
bool TransactionStatus::isAFail(void) const
{
    return m_state == State::FAIL;
}


// isInProgress
// 
// Description:
// Determines if this Transaction is in progress.
// 
bool TransactionStatus::isInProgress(void) const
{
    return m_state == State::IN_PROGRESS;
}


// has/set/view m_state
// 
// Description:
// Accessors for m_state.
// 
bool TransactionStatus::hasState(void) const
{
    return m_state != State::UNDEFINED;
}


// has/set/view m_state
// 
// Description:
// Accessors for m_state.
// 
void TransactionStatus::setState(const State state)
{
    m_state = state;
}


// has/set/view m_state
// 
// Description:
// Accessors for m_state.
// 
TransactionStatus::State TransactionStatus::viewState(void) const
{
    return m_state;
}


// has/set/view m_errorMessage
// 
// Description:
// Accessors for m_errorMessage.
// 
bool TransactionStatus::hasErrorMessage(void) const
{
    return !m_errorMessage.empty();
}


// has/set/view m_errorMessage
// 
// Description:
// Accessors for m_errorMessage.
// 
void TransactionStatus::setErrorMessage(const std::string& errorMessage)
{
    m_errorMessage = errorMessage;
}


// has/set/view m_errorMessage
// 
// Description:
// Accessors for m_errorMessage.
// 
const std::string& TransactionStatus::viewErrorMessage(void) const
{
    return m_errorMessage;
}


// has/set/view m_httpResponse
// 
// Description:
// Accessors for m_httpResponse.
// 
bool TransactionStatus::hasHttpResponse(void) const
{
    return !m_httpResponse.empty();
}


// has/set/view m_httpResponse
// 
// Description:
// Accessors for m_httpResponse.
// 
void TransactionStatus::setHttpResponse(const std::string& httpResponse)
{
    m_httpResponse = httpResponse;
}


// has/set/view m_httpResponse
// 
// Description:
// Accessors for m_httpResponse.
// 
const std::string& TransactionStatus::viewHttpResponse(void) const
{
    return m_httpResponse;
}
