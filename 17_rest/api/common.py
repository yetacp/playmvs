import sqlite3
from bottle import route, run, debug, template, \
                   get, post, put, request, static_file, \
                   error, response

def execute(sql):
    conn = sqlite3.connect('db.sqlite3')
    cursor = conn.execute(sql)
    result = cursor.fetchall()
    conn.commit()
    conn.close()
    return result
