from bottle import route, template, response
from api.common import *

# -------------------------------------------------------------------------------------------
@route('/api/products', method='GET')
def find_products():
    response.content_type = "text/csv"

    output = template("""id;name;quantity
%for row in rows:
{{row[0]}};{{row[1]}};{{row[2]}}
%end    
""", rows=execute("""SELECT id, name, quantity 
                     FROM products ORDER BY name"""))
    return output
# -------------------------------------------------------------------------------------------
@route('/api/products/<id:int>', method='GET')
def find_product_by_id(id):
    response.content_type = "text/csv"

    output = template("""id;name;quantity
%for row in rows:
{{row[0]}};{{row[1]}};{{row[2]}}
%end    
""", rows=execute("""SELECT id, name, quantity 
                     FROM products WHERE id={id}""".format(id=id)))
    return output
# -------------------------------------------------------------------------------------------
@route('/api/products/<id:int>', method='DELETE')
def delete_product_by_id(id):
    response.content_type = "text/csv"

    execute('DELETE FROM orders  WHERE idproduct={id}'.format(id=id))
    execute('DELETE FROM products WHERE id={id}'.format(id=id))
    return 'DELETED'
# -------------------------------------------------------------------------------------------

