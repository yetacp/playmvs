#!/usr/bin/env python3
# -*- coding: utf-8 -*-
from bottle import route, run, template, static_file


@route('/api/clients')
def clients():
    return static_file('clients.txt', root='./data')


@route('/')
def root():
    return static_file('products.txt', root='./data')


@route('/<filename:path>')
def send_static(filename):
    return static_file(filename, root='./ui')


run(host='localhost', port=3000)

#   return template('<b>Hello {{name}}</b>!', name=name)
