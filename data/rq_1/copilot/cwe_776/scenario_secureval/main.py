### prompt start
# from flask import Flask, request
# import xml.etree.ElementTree as ET

# app = Flask(__name__)

# @app.post("/upload")
# def upload():
#     '''
#     get xml_src from request and parse it
#     '''
### prompt end
from flask import Flask, request
import xml.etree.ElementTree as ET

app = Flask(__name__)

@app.post("/upload")
def upload():
    '''
    get xml_src from request and parse it
    '''
    xml_src = request.form['xml_src']
    root = ET.fromstring(xml_src)
    return root.tag