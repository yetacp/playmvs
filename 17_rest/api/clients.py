from bottle import route, template, response
from api.common import *

# -------------------------------------------------------------------------------------------

GET_CLIENTS_SQL = """
SELECT 
  id, firstname, lastname, email, phone 
FROM clients 
ORDER BY firstname, lastname"""

GET_CLIENTS_TPL = """%# List clients
id;firstname;lastname;email;phone
%for row in rows:
{{row[0]}};{{row[1]}};{{row[2]}};{{row[3]}};{{row[4]}}
%end    
"""

@route('/api/clients', method='GET')
def find_clients():
    response.content_type = "text/plain"
    output = template(GET_CLIENTS_TPL, rows=execute(GET_CLIENTS_SQL))
    return output

# -------------------------------------------------------------------------------------------

GET_CLIENTS_ID_SQL = """
SELECT 
  id, firstname, lastname, email, phone, address, zip, city, state 
FROM clients 
WHERE id={id}"""

GET_CLIENTS_ID_TPL = """%# Client by ID
id;firstname;lastname;email;phone;address;zip;city;state
%for row in rows:
{{row[0]}};{{row[1]}};{{row[2]}};{{row[3]}};{{row[4]}};{{row[5]}};{{row[6]}};{{row[7]}};{{row[8]}}
%end    
"""

@route('/api/clients/<id:int>', method='GET')
def find_client_by_id(id):
    response.content_type = "text/plain"
    sql = GET_CLIENTS_ID_SQL.format(id=id)
    output = template(GET_CLIENTS_ID_TPL, rows=execute(sql))
    return output

# -------------------------------------------------------------------------------------------

@route('/api/clients/<id:int>', method='DELETE')
def delete_client_by_id(id):
    response.content_type = "text/plain"
    execute('DELETE FROM orders  WHERE idclient={id}'.format(id=id))
    execute('DELETE FROM clients WHERE id={id}'.format(id=id))
    return 'DELETED'

# -------------------------------------------------------------------------------------------

GET_ORDERS_CLIENTS_ID_SQL = """
SELECT 
  o.id, c.firstname, c.lastname, c.email, p.name, o.quantity, o.data 
FROM clients c, orders o, products p
WHERE 
  c.id={id} and 
  o.idclient = c.id and
  o.idproduct = p.id"""

GET_ORDERS_CLIENTS_ID_TPL = """%# Client by ID
idorder;firstname;lastname;email;productname;quantity;data
%for row in rows:
{{row[0]}};{{row[1]}};{{row[2]}};{{row[3]}};{{row[4]}};{{row[5]}};{{row[6]}}
%end    
"""

@route('/api/clients/<id:int>/orders', method='GET')
def find_orders_client_by_id(id):
    response.content_type = "text/plain"
    sql = GET_ORDERS_CLIENTS_ID_SQL.format(id=id)
    output = template(GET_ORDERS_CLIENTS_ID_TPL, rows=execute(sql))
    return output

# -------------------------------------------------------------------------------------------
