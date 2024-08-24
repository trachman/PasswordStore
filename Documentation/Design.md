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
- Encrypted Password <mandatory>
- Wesbite URL <optional>
- Description <optional>
- 2FA Information <optional>

# Session Table <TABLE 3>:
- Username <mandatory> <FK>
- Session ID <mandatory>


## WORKFLOW:
Login
See all existing accounts
Copy usernames from existing accounts
Copy passwords from existing accounts
Sort existing accounts
Filter existing accounts
Add new account
Delete existing account
Logout


## TECH STACK:
Database: Postgresql
Backend: C++
Frontend: HTML + CSS + Javascript


## HIGH LEVEL DESIGN:
Login > Do stuff with accounts > Logout