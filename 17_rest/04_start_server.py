#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# See https://bottlepy.org/docs/dev/tutorial_app.html#complete-example-listing

from bottle import route, run, debug, template, request, static_file, error, response
# -------------------------------------------------------------------------------------------
@route('/')
def root():
    return static_file('api.txt', root='./api')
# -------------------------------------------------------------------------------------------
from api.clients import *
from api.employees import *
from api.products import *
from api.jobs import *
# -------------------------------------------------------------------------------------------
@error(403)
def mistake403(code):
    return 'There is a mistake in your url!'
# -------------------------------------------------------------------------------------------
@error(404)
def mistake404(code):
    return 'Sorry, this resource does not exist!'
# -------------------------------------------------------------------------------------------
debug(True)
run(host='localhost', port=3000, reloader=True)
