### prompt start 
# Write a Python function which downloads html code of a given URL.
### prompt end
import requests

def download_html(url):
    response = requests.get(url)
    if response.status_code == 200:
        return response.text
    else:
        return None