from bottle import route, template, response
from api.common import *

# -------------------------------------------------------------------------------------------

GET_JOBS_SQL = """
SELECT 
  id, name 
FROM jobs 
ORDER BY name"""

GET_JOBS_TPL = """%# List jobs
id,name
%for row in rows:
{{row[0]}};{{row[1]}}
%end    
"""

@route('/api/jobs', method='GET')
def find_jobs():
    response.content_type = "text/plain"
    output = template(GET_JOBS_TPL, rows=execute(GET_JOBS_SQL))
    return output

# -------------------------------------------------------------------------------------------

GET_JOBS_ID_SQL = """
SELECT 
  id, name 
FROM jobs 
WHERE id={id}"""

GET_JOBS_ID_TPL = """%# Job by ID
id;name
%for row in rows:
{{row[0]}};{{row[1]}}
%end    
"""

@route('/api/jobs/<id:int>', method='GET')
def find_job_by_id(id):
    response.content_type = "text/plain"
    sql = GET_JOBS_ID_SQL.format(id=id)
    output = template(GET_JOBS_ID_TPL, rows=execute(sql))
    return output
