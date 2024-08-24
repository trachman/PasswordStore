#pragma once

// Includes
//
#include <string>


// TODO
class TransactionStatus
{
public:
    enum class State
    {
        UNDEFINED = -1,
        IN_PROGRESS,
        PASS,
        FAIL
    };

    // Constructor
    // 
    // Description:
    // Initializes a default Transaction Status.
    // 
    // Arguments:
    // None.
    // 
    // Returns:
    // None.
    //
    TransactionStatus(void);

    // Destructor
    // 
    // Description:
    // Destructs the Transaction Status.
    // No members that need manual clean up so defaulting this.
    // 
    // Arguments:
    // None.
    // 
    // Returns:
    // None.
    //
    ~TransactionStatus(void) = default;

    // Copy Constructor
    // 
    // Description:
    // Copies the given RHS object into this one.
    // 
    // Arguments:
    // RHS - The object to copy.
    // 
    // Returns:
    // None.
    //
    TransactionStatus(const TransactionStatus& RHS) = default;

    // Move Constructor
    // 
    // Description:
    // Moves the given RHS object into this one.
    // 
    // Arguments:
    // RHS - The object to move.
    // 
    // Returns:
    // None.
    //
    TransactionStatus(TransactionStatus&& RHS) = default;

    // Copy Assignment Operator
    // 
    // Description:
    // Copies the given RHS object into this one.
    // 
    // Arguments:
    // RHS - The object to copy.
    // 
    // Returns:
    // This
    //
    TransactionStatus& operator=(const TransactionStatus& RHS) = default;

    // Move Assignment Operator
    // 
    // Description:
    // Moves the given RHS object into this one.
    // 
    // Arguments:
    // RHS - The object to move.
    // 
    // Returns:
    // This
    //
    TransactionStatus& operator=(TransactionStatus&& RHS) = default;

    // isAPass
    // 
    // Description:
    // Determines if this Transaction is a pass.
    // 
    // Arguments:
    // None.
    // 
    // Returns:
    // True if the state is pass.
    // False otherwise.
    //
    bool isAPass(void) const;

    // isAFail
    // 
    // Description:
    // Determines if this Transaction is a fail.
    // 
    // Arguments:
    // None.
    // 
    // Returns:
    // True if the state is fail.
    // False otherwise.
    //
    bool isAFail(void) const;

    // isInProgress
    // 
    // Description:
    // Determines if this Transaction is in progress.
    // 
    // Arguments:
    // None.
    // 
    // Returns:
    // True if the state is in progress.
    // False otherwise.
    //
    bool isInProgress(void) const;

    // has/set/view m_state
    // 
    // Description:
    // Accessors for m_state.
    // 
    // Arguments:
    // state - The State to set m_state to.
    //
    bool hasState(void) const;
    void setState(const State state);
    State viewState(void) const;

    // has/set/view m_errorMessage
    // 
    // Description:
    // Accessors for m_errorMessage.
    // 
    // Arguments:
    // errorMessage - The error message to set m_errorMessage to.
    //
    bool hasErrorMessage(void) const;
    void setErrorMessage(const std::string& errorMessage);
    const std::string& viewErrorMessage(void) const;

    // has/set/view m_httpResponse
    // 
    // Description:
    // Accessors for m_httpResponse.
    // 
    // Arguments:
    // httpResponse - The response to set m_httpResponse to.
    //
    bool hasHttpResponse(void) const;
    void setHttpResponse(const std::string& httpResponse);
    const std::string& viewHttpResponse(void) const;

private:
    // Private Data Members
    //
    State m_state;
    std::string m_errorMessage;
    std::string m_httpResponse;
};
