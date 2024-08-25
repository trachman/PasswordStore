## Password Store
# The idea is to create a Secure Password Storage application without any external libraries.
# From database to frontend.


## DATA:
# Account: <TABLE 1>
- Username <mandatory> <PK>
- Password <mandatory>

# For Each Account: <TABLE 2>
- Username <mandatory> <FK>
- Service Name <mandatory>
- Service Username <mandatory>
- Service Password <mandatory>
- Service URL <optional>
- Service Description <optional>

# Session Table <TABLE 3>:
- Username <mandatory> <FK>
- Session ID <mandatory>


## WORKFLOW:
Login
See all existing accounts
Copy usernames from existing accounts
Copy passwords from existing accounts
Add new account
Delete existing account
Logout
Sort existing accounts   - Front End Feature
Filter existing accounts - Front End Feature


## TECH STACK:
Database: Postgresql
Backend: C++
Frontend: HTML + CSS + Javascript


## HIGH LEVEL DESIGN:
Login > Do stuff with accounts > Logout

## Commands

NOT LOGGED IN
1.  Login:
    Username, Password

2.  Create New Account:
    Username, Password

LOGGED IN
1.  Logout:
    Username

2.  Delete Account:
    Username

3.  Copy Service Password:
    Username, Service Name

4.  Copy Service Username:
    Username, Service Name

5.  Add New Service:
    Username, Service Name, Service Username, Service Password, Service URL, Service Description

6. Delete Existing Service:
    Username, Service Name

8 Commands To Write