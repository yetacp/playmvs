#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import sqlite3

from faker import Faker
fake = Faker()

MAX_JOB = 10
MAX_EMPLOYEE = 20
MAX_CLIENT = 200
MAX_ORDER = 1000
MAX_PRODUCT = 50

conn = sqlite3.connect('db.sqlite3')
print("Recreating database")

conn.execute("DELETE FROM roles")
conn.execute("DELETE FROM users")
conn.execute("DELETE FROM jobs")
conn.execute("DELETE FROM employees")
conn.execute("DELETE FROM clients")
conn.execute("DELETE FROM products")
conn.execute("DELETE FROM orders")

conn.execute("INSERT INTO roles(id, name) VALUES(1,'Admin')")
conn.execute("INSERT INTO roles(id, name) VALUES(2,'User')")

conn.execute(
    "INSERT INTO users(login, password, idrole) VALUES('admin','admin',1)")
conn.execute(
    "INSERT INTO users(login, password, idrole) VALUES('hmvs01','cul8tr',2)")
conn.execute(
    "INSERT INTO users(login, password, idrole) VALUES('hmvs02','pass4u',2)")

for id in range(1, MAX_JOB + 1):
    sql = "INSERT INTO jobs(id, name) VALUES({},'{}')".format(
        id, fake.unique.job())
    conn.execute(sql)

for id in range(1, MAX_EMPLOYEE + 1):
    firstname = fake.first_name()
    lastname = fake.unique.last_name()
    birth = fake.date_of_birth(
        minimum_age=18, maximum_age=60).strftime("%Y-%m-%d")
    email = '{lastname} email.com'.format(lastname=lastname.lower())
    phone = fake.phone_number()
    address = fake.street_address()
    zip = fake.postcode()
    city = fake.city()
    state = fake.state()
    job = fake.pyint(min_value=1, max_value=MAX_JOB)
    sql = """INSERT INTO employees(
                id, firstname, lastname, birth, email, phone, address, zip, city, state, idjob) 
             VALUES ({id}, '{firstname}', '{lastname}', '{birth}', '{email}', 
                   '{phone}', '{address}', '{zip}', '{city}', '{state}', {job})""".format(
        id=id,
        firstname=firstname,
        lastname=lastname,
        birth=birth,
        email=email,
        phone=phone,
        address=address,
        zip=zip,
        city=city,
        state=state,
        job=job)
    conn.execute(sql)

for id in range(1, MAX_CLIENT + 1):
    firstname = fake.first_name()
    lastname = fake.unique.last_name()
    email = '{lastname} email.com'.format(lastname=lastname.lower())
    phone = fake.phone_number()
    address = fake.street_address()
    zip = fake.postcode()
    city = fake.city()
    state = fake.state()
    sql = """INSERT INTO clients(id, firstname, lastname, email, phone,
                    address, zip, city, state)
              VALUES ({id}, '{firstname}', '{lastname}', '{email}', 
                      '{phone}', '{address}', '{zip}', '{city}', '{state}')""".format(
        id=id,
        firstname=firstname,
        lastname=lastname,
        email=email,
        phone=phone,
        address=address,
        zip=zip,
        city=city,
        state=state
    )
    conn.execute(sql)

for id in range(1, MAX_PRODUCT + 1):
    idproduct = fake.pyint(min_value=1, max_value=MAX_PRODUCT)
    n_me = fake.unique.text(max_nb_chars=20)[:-1]
    quantity = fake.pyint(min_value=1, max_value=1000)
    sql = "INSERT INTO products(id, name, quantity) VALUES ({id}, '{n_me}', {quantity})".format(
        id=id,
        n_me=n_me,
        quantity=quantity
    )
    conn.execute(sql)

for id in range(1, MAX_ORDER + 1):
    idclient = fake.pyint(min_value=1, max_value=MAX_CLIENT)
    idproduct = fake.pyint(min_value=1, max_value=MAX_PRODUCT)
    quantity = fake.pyint(min_value=1, max_value=10)
    data = fake.date_of_birth(
        minimum_age=0, maximum_age=7).strftime("%Y-%m-%d")
    sql = """INSERT INTO orders(id, data, idclient, idproduct, quantity) 
             VALUES ({id}, '{data}', {idclient}, {idproduct}, {quantity})""".format(
        id=id,
        idclient=idclient,
        idproduct=idproduct,
        quantity=quantity,
        data=data
    )
    conn.execute(sql)

conn.commit()
conn.close()
