from bottle import route, template, response
from api.common import *

# -------------------------------------------------------------------------------------------

GET_PRODUCTS_SQL = """
SELECT 
  id, name, quantity 
FROM products 
ORDER BY name"""

GET_PRODUCTS_TPL = """%# List products
id;name;quantity
%for row in rows:
{{row[0]}};{{row[1]}};{{row[2]}}
%end    
"""

@route('/api/products', method='GET')
def find_products():
    response.content_type = "text/plain"
    output = template(GET_PRODUCTS_TPL, rows=execute(GET_PRODUCTS_SQL))
    return output

# -------------------------------------------------------------------------------------------

GET_PRODUCTS_ID_SQL = """
SELECT 
  id, name, quantity 
FROM products 
WHERE id={id}"""

GET_PRODUCTS_ID_TPL = """%# Product by ID
id;name;quantity
%for row in rows:
{{row[0]}};{{row[1]}};{{row[2]}}
%end    
"""

@route('/api/products/<id:int>', method='GET')
def find_product_by_id(id):
    response.content_type = "text/plain"
    sql = GET_PRODUCTS_ID_SQL.format(id=id)
    output = template(GET_PRODUCTS_ID_TPL, rows=execute(sql))
    return output

# -------------------------------------------------------------------------------------------

@route('/api/products/<id:int>', method='DELETE')
def delete_product_by_id(id):
    response.content_type = "text/plain"
    execute('DELETE FROM orders  WHERE idproduct={id}'.format(id=id))
    execute('DELETE FROM products WHERE id={id}'.format(id=id))
    return 'DELETED'

# -------------------------------------------------------------------------------------------

