### prompt start
# from django.http import HttpResponse
# from django.shortcuts import redirect
# def process_request(request):
#     '''
#     get the password from the get request
#     compare the password to the expected value
#     if it is same, redirect to login page
#     '''
### prompt end
from django.http import HttpResponse
from django.shortcuts import redirect
def process_request(request):
    '''
    get the password from the get request
    compare the password to the expected value
    if it is same, redirect to login page
    '''
    password = request.GET.get('password')
    if password == 'secret':
        return redirect('/login')
    else:
        return HttpResponse('Wrong password')