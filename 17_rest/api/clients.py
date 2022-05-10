from bottle import route, template, response, request
from api.common import *

# -------------------------------------------------------------------------------------------
@route('/api/clients', method='GET')
def find_clients():
    response.content_type = "text/csv"

    output = template("""id;firstname;lastname;email;phone
%for row in rows:
{{row[0]}};{{row[1]}};{{row[2]}};{{row[3]}};{{row[4]}}
%end    
""", rows=execute("""SELECT id, firstname, lastname, email, phone 
                     FROM clients ORDER BY firstname, lastname"""))
    return output
# -------------------------------------------------------------------------------------------
@route('/api/clients/<id:int>', method='GET')
def find_client_by_id(id):
    response.content_type = "text/csv"

    output = template("""id;firstname;lastname;email;phone;address;zip;city;state
%for row in rows:
{{row[0]}};{{row[1]}};{{row[2]}};{{row[3]}};{{row[4]}};{{row[5]}};{{row[6]}};{{row[7]}};{{row[8]}}
%end    
""", rows=execute("""SELECT id, firstname, lastname, email, phone, address, zip, city, state 
                     FROM clients WHERE id={id}""".format(id=id)))
    return output
# -------------------------------------------------------------------------------------------
@route('/api/clients/<id:int>', method='DELETE')
def delete_client_by_id(id):
    response.content_type = "text/csv"

    execute('DELETE FROM orders  WHERE idclient={id}'.format(id=id))
    execute('DELETE FROM clients WHERE id={id}'.format(id=id))
    return 'DELETED'
# -------------------------------------------------------------------------------------------
@route('/api/clients/<id:int>', method='PUT')
def update_client_by_id(id):
    response.content_type = "text/csv"
    content = request.body.readlines()[0].decode("utf-8")
    id, firstname, lastname, email, phone = content.split(';')
    execute("""UPDATE clients 
             SET firstname='{firstname}', 
               lastname='{lastname}', 
               email='{email}', 
               phone='{phone}' 
             WHERE id={id}""".format(id=id, firstname=firstname, lastname=lastname, email=email, phone=phone))
    return 'UPDATED'
# -------------------------------------------------------------------------------------------
@route('/api/clients', method='POST')
def insert_client_by_id():
    response.content_type = "text/csv"
    content = request.body.readlines()[0].decode("utf-8")
    id, firstname, lastname, email, phone = content.split(';')
    execute("""INSERT INTO clients (firstname, lastname, email, phone)
             VALUES('{firstname}','{lastname}','{email}','{phone}')""".format(
               firstname=firstname, lastname=lastname, email=email, phone=phone))
    return 'INSERTED'
# -------------------------------------------------------------------------------------------
@route('/api/clients/<id:int>/orders', method='GET')
def find_orders_client_by_id(id):
    response.content_type = "text/csv"

    output = template("""idorder;firstname;lastname;email;productname;quantity;data
%for row in rows:
{{row[0]}};{{row[1]}};{{row[2]}};{{row[3]}};{{row[4]}};{{row[5]}};{{row[6]}}
%end    
""", rows=execute("""SELECT o.id, c.firstname, c.lastname, c.email, p.name, o.quantity, o.data 
                     FROM clients c, orders o, products p 
                     WHERE
                        c.id={id} and 
                        o.idclient = c.id and
                        o.idproduct = p.id""".format(id=id)))
    return output
# -------------------------------------------------------------------------------------------
