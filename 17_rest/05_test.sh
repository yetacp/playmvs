#!/bin/bash

TOKEN="eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9" # Fake authentication token

send_GET(){
  curl -X GET     -s -H "Authorization: Bearer $TOKEN" localhost:3000$1 > test_$2.csv
  echo "$2 GET    $1 => `cat test_$2.csv | wc -l` line(s) # $3"
}

send_DELETE(){
  curl -X DELETE  -s -H "Authorization: Bearer $TOKEN" localhost:3000$1 > test_$2.csv
  echo "$2 DELETE $1 => `cat test_$2.csv` # $3"  
}

send_PUT(){
  curl -X PUT     -s -H "Authorization: Bearer $TOKEN" localhost:3000$1 -d "$3" > test_$2.csv
  echo "$2 PUT    $1 => `cat test_$2.csv` # $4" 
}

send_POST(){
  curl -X POST    -s -H "Authorization: Bearer $TOKEN" localhost:3000$1 -d "$3" > test_$2.csv
  echo "$2 POST   $1 => `cat test_$2.csv` # $4" 
}

send_token(){
  curl -X GET  localhost:3000$1
}

clear

./03_initdb_sqlite.py

cd test
rm -f *.csv

echo "......................................................................."
echo 'Clients API'
echo "......................................................................."
send_GET    '/api/clients   ' 'clients_01' 'all clients'
send_GET    '/api/clients/1 ' 'clients_02' 'find client 1'
send_DELETE '/api/clients/1 ' 'clients_03' 'delete client 1'
send_DELETE '/api/clients/10' 'clients_04' 'delete client 10'
send_GET    '/api/clients   ' 'clients_05' 'all clients'
send_GET    '/api/clients/1 ' 'clients_06' 'try to find client 1'
send_GET    '/api/clients/2 ' 'clients_07' 'find client 2'
send_PUT    '/api/clients/2 ' 'clients_08' '2;Peter;Cooler;cooler email.com;555-1234' 'update client 2'
send_GET    '/api/clients/2 ' 'clients_09' 'find client 2'
send_POST   '/api/clients   ' 'clients_10' '0;Aaron;Cooke;cooke email.com;555-7890' 'new client'
send_GET    '/api/clients   ' 'clients_11' 'all clients'

echo "......................................................................."
echo "Employees API"
echo "......................................................................."
send_GET    '/api/employees   ' 'employees_01' 'all employees'
send_GET    '/api/employees/1 ' 'employees_02' 'find employee 1'
send_DELETE '/api/employees/1 ' 'employees_03' 'delete employee 2'
send_DELETE '/api/employees/10' 'employees_04' 'delete employee 10'
send_GET    '/api/employees   ' 'employees_05' 'all employees'
send_GET    '/api/employees/1 ' 'employees_06' 'try to find employee 1'

echo "......................................................................."
echo "Jobs API"
echo "......................................................................."
send_GET    '/api/jobs   ' 'jobs_01' 'all jobs'
send_GET    '/api/jobs/1 ' 'jobs_02' 'find job 1'
send_DELETE '/api/jobs/1 ' 'jobs_03' 'delete job 2'
send_DELETE '/api/jobs/10' 'jobs_04' 'delete job 10'
send_GET    '/api/jobs   ' 'jobs_05' 'all jobs'
send_GET    '/api/jobs/1 ' 'jobs_06' 'try to find job 1'

echo "......................................................................."
echo 'Products API'
echo "......................................................................."
send_GET    '/api/products   ' 'products_01' 'all products'
send_GET    '/api/products/1 ' 'products_02' 'get product 1'
send_DELETE '/api/products/1 ' 'products_03' 'delete product 1'
send_DELETE '/api/products/10' 'products_04' 'delete product 10'
send_GET    '/api/products   ' 'products_05' 'all products'
send_GET    '/api/products/1 ' 'products_06' 'try to find product 1'



echo "......................................................................."
echo "See results in test folder"
echo "......................................................................."
