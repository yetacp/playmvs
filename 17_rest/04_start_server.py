#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# See https://bottlepy.org/docs/dev/tutorial_app.html#complete-example-listing

import sqlite3
from bottle import route, run, debug, template, request, static_file, error, response

@route('/api/clients')
def clients():
    conn = sqlite3.connect('db.sqlite3')
    cursor = conn.execute(
        "SELECT firstname,lastname, email, phone FROM clients")
    result = cursor.fetchall()
    conn.close()
    output = template("""%# Template to generate clients
%for row in rows:
{{row[0]}} {{row[1]}} {{row[2]}} {{row[3]}}
%end    
    """, rows=result)
    response.content_type = "text/plain"
    return output

@route('/')
def root():
    return static_file('api.txt', root='./api')

@error(403)
def mistake403(code):
    return 'There is a mistake in your url!'

@error(404)
def mistake404(code):
    return 'Sorry, this page does not exist!'

debug(True)
run(host='localhost', port=3000, reloader=True)
