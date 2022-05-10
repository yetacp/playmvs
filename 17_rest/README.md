# REST API

** NOT WORKING **
Author: Frank

Project target is to implement a REST API for C in MVS3.8j

## Checklist
1. Create Python backend (70%)
2. Create MVS client (0%)

## Warning
- This project is not safety for production. It is vulnerable to SQL Injection.

## Files
- Install Python package 'Faker': $ pip3 install Faker
- Run ./03_initdb_sqlite.py to init db.sqlite3 database.
- Run ./04_start_server.py to start REST API server.
- Navigate to http://localhost:3000/ to see API
- Run 'make test' to test REST API. Results in test folder.
- Run 'make' to install program into MVS.
- Run 'make execute' to execute program in MVS :)
- See response in prt00e.txt
