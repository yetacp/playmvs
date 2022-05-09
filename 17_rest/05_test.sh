#!/bin/bash

test_get(){
   curl -s localhost:3000$1 > test_$2.out
   count=`cat test_$2.out | wc -l`
   echo "$2 GET    $1 => $count line(s)"
}

test_delete(){
   curl -X DELETE -s localhost:3000$1 > test_$2.out
   echo "$2 DELETE $1 =>" `cat test_$2.out`
}

clear

./03_initdb_sqlite.py

cd test
rm -f *.out

echo "......................................................................."
echo 'Clients API'
echo "......................................................................."
test_get    '/api/clients   ' 'api_clients_01'
test_get    '/api/clients/1 ' 'api_clients_02'
test_delete '/api/clients/1 ' 'api_clients_03'
test_delete '/api/clients/10' 'api_clients_04'
test_get    '/api/clients   ' 'api_clients_05'
test_get    '/api/clients/1 ' 'api_clients_06'

echo "......................................................................."
echo "Employees API"
echo "......................................................................."
test_get    '/api/employees   ' 'api_employees_01'
test_get    '/api/employees/1 ' 'api_employees_02'
test_delete '/api/employees/1 ' 'api_employees_03'
test_delete '/api/employees/10' 'api_employees_04'
test_get    '/api/employees   ' 'api_employees_05'
test_get    '/api/employees/1 ' 'api_employees_06'

echo "......................................................................."
echo 'Products API'
echo "......................................................................."
test_get    '/api/products   ' 'api_products_01'
test_get    '/api/products/1 ' 'api_products_02'
test_delete '/api/products/1 ' 'api_products_03'
test_delete '/api/products/10' 'api_products_04'
test_get    '/api/products   ' 'api_products_05'
test_get    '/api/products/1 ' 'api_products_06'

echo "......................................................................."
echo 'Orders API'
echo "......................................................................."
test_get    '/api/clients/2/orders' 'api_orders_01'
test_get    '/api/orders/100      ' 'api_orders_02'

echo "......................................................................."
echo "See results in test folder"
echo "......................................................................."
