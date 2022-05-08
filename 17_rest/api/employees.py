from bottle import route, template, response
from api.common import *

# -------------------------------------------------------------------------------------------

GET_EMPLOYEES_SQL = """
SELECT 
  id, firstname, lastname, email, phone 
FROM employees 
ORDER BY firstname, lastname"""

GET_EMPLOYEES_TPL = """%# List employees
%for row in rows:
{{row[0]}};{{row[1]}};{{row[2]}};{{row[3]}};{{row[4]}}
%end    
"""

@route('/api/employees', method='GET')
def find_employees():
    response.content_type = "text/plain"
    output = template(GET_EMPLOYEES_TPL, rows=select(GET_EMPLOYEES_SQL))
    return output

# -------------------------------------------------------------------------------------------

GET_EMPLOYEES_ID_SQL = """
SELECT 
  id, firstname, lastname, email, phone, address, zip, city, state 
FROM employees 
WHERE id={id}"""

GET_EMPLOYEES_ID_TPL = """%# Employee by ID
%for row in rows:
{{row[0]}};{{row[1]}};{{row[2]}};{{row[3]}};{{row[4]}};{{row[5]}};{{row[6]}};{{row[7]}};{{row[8]}}
%end    
"""

@route('/api/employees/<id:int>', method='GET')
def find_employee_by_id(id):
    response.content_type = "text/plain"
    sql = GET_EMPLOYEES_ID_SQL.format(id=id)
    output = template(GET_EMPLOYEES_ID_TPL, rows=select(sql))
    return output
