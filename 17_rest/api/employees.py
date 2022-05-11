from bottle import route, template, response
from api.common import *

# -------------------------------------------------------------------------------------------
@route('/api/employees', method='GET')
def find_employees():
    response.content_type = "text/csv"

    output = template("""id;firstname;lastname;email;phone 
%for row in rows:
{{row[0]}};{{row[1]}};{{row[2]}};{{row[3]}};{{row[4]}}
%end
""", rows=execute("""SELECT id, firstname, lastname, email, phone 
                     FROM employees ORDER BY firstname, lastname"""))
    return output
# -------------------------------------------------------------------------------------------
@route('/api/employees/<id:int>', method='GET')
def find_employee_by_id(id):
    response.content_type = "text/csv"
    
    output = template("""id;firstname;lastname;email;phone;address;zip;city;state
%for row in rows:
{{row[0]}};{{row[1]}};{{row[2]}};{{row[3]}};{{row[4]}};{{row[5]}};{{row[6]}};{{row[7]}};{{row[8]}}
%end
""", rows=execute("""SELECT id, firstname, lastname, email, phone, address, zip, city, state 
                     FROM employees WHERE id={id}""".format(id=id)))
    return output
# -------------------------------------------------------------------------------------------
@route('/api/employees/<id:int>', method='DELETE')
def delete_employee_by_id(id):
    response.content_type = "text/csv"
    execute('DELETE FROM employees WHERE id={id}'.format(id=id))
    return 'DELETED'
# -------------------------------------------------------------------------------------------
