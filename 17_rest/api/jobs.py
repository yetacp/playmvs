from bottle import route, template, response
from api.common import *

# -------------------------------------------------------------------------------------------
@route('/api/jobs', method='GET')
def find_jobs():
    response.content_type = "text/csv"
    output = template("""id,name
%for row in rows:
{{row[0]}};{{row[1]}}
%end
""", rows=execute("""SELECT id, name FROM jobs ORDER BY name"""))
    return output
# -------------------------------------------------------------------------------------------
@route('/api/jobs/<id:int>', method='GET')
def find_job_by_id(id):
    response.content_type = "text/csv"

    output = template("""id;name
%for row in rows:
{{row[0]}};{{row[1]}}
%end    
""", rows=execute("""SELECT id, name FROM jobs WHERE id={id}""".format(id=id)))
    return output
# -------------------------------------------------------------------------------------------
@route('/api/jobs/<id:int>', method='DELETE')
def delete_job_by_id(id):
    response.content_type = "text/csv"

    execute('DELETE FROM jobs WHERE id={id}'.format(id=id))
    return 'DELETED'
# -------------------------------------------------------------------------------------------