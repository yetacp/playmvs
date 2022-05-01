#!/usr/bin/python3
# -*- coding: utf-8 -*-

from faker import Faker
fake = Faker()

MAX_JOB = 10
MAX_EMPLOYEE = 20
MAX_CLIENT = 30
MAX_ORDER = 100
MAX_PRODUCT = 50

with open("jobs.txt", "w") as output:    
    for id in range(1,MAX_JOB + 1):
        line = 'J{:02} {:15}\n'.format(id, fake.unique.job())
        output.write(line)

with open("employees.txt", "w") as output:
    for id in range(1, MAX_EMPLOYEE + 1):
        first   = fake.first_name()
        last    = fake.unique.last_name()
        birth   = fake.date_of_birth(minimum_age=18, maximum_age=60).strftime('%Y-%m-%d')
        email   = '{last} email.com'.format(last=last.lower())
        phone   = fake.phone_number()
        address = fake.street_address()
        zip     = fake.postcode()
        city    = fake.city()
        state   = fake.state()
        job     = fake.pyint(min_value=1, max_value=MAX_JOB)
        line =  'E{id:03} {first:12} {last:12} {birth:5} {email:20} {phone:22} {address:42} {zip:5} {city:24} {state:15} J{job:02}\n'.format(
            id = id,
            first = first,
            last = last,
            birth = birth,
            email = email,
            phone = phone,
            address = address,
            zip = zip,
            city = city,
            state = state,
            job = job)
        output.write(line)

with open("clients.txt", "w") as output:
    for id in range(1,MAX_CLIENT + 1):
        first_name = fake.first_name()
        last_name  = fake.unique.last_name()
        email   = '{last_name} email.com'.format(last_name=last_name.lower())
        phone   = fake.phone_number()
        address = fake.street_address()
        zip     = fake.postcode()
        city    = fake.city()
        state   = fake.state()
        line =  'C{id:05} {first_name:12} {last_name:12} {email:20} {phone:22} {address:42} {zip:5} {city:24} {state:15}\n'.format(
            id = id, 
            first_name = first_name,
            last_name = last_name,
            email = email,
            phone = phone,
            address = address,
            zip = zip,
            city = city,
            state = state
        )
        output.write(line)

with open("products.txt", "w") as output:
    for id in range(1, MAX_PRODUCT + 1):
        product_id = fake.pyint(min_value=1, max_value=MAX_PRODUCT)
        n_me       = fake.unique.text(max_nb_chars=20)[:-1]
        quantity   = fake.pyint(min_value=1, max_value=MAX_PRODUCT)
        line =  'P{id:03} {n_me:20} {quantity:05}\n'.format(
            id         = id,
            n_me       = n_me,
            quantity   = quantity
        )
        output.write(line)

with open("orders.txt", "w") as output:
    for id in range(1, MAX_ORDER + 1):
        client_id = fake.pyint(min_value=1, max_value=MAX_CLIENT)
        product_id = fake.pyint(min_value=1, max_value=MAX_PRODUCT)
        quantity   = fake.pyint(min_value=1, max_value=1000)
        data       = fake.date_of_birth(minimum_age=0, maximum_age=3).strftime('%Y-%m-%d')
        line =  'O{id:05} {data} C{client_id:05} P{product_id:04} {quantity:05}\n'.format(
            id         = id,
            client_id = client_id,
            product_id = product_id,
            quantity   = quantity,
            data       = data
        )
        output.write(line)
