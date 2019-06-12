from django.shortcuts import render
from django.http import HttpResponse,HttpResponseRedirect
from onlineapp.models import *
from django.urls import reverse
# Create your views here.

def helloworld(request):
    print(request)
    c=College.objects.filter(acronym="vce").values('name')
    #return HttpResponse(c)
    return render(request, "hello.html",{})

def getall(request):
    c = College.objects.values('name','acronym','id')
    return render(request,"printcolleges.html",{'c':c})

    res="<table border=\"1\">"
    for i in range(len(c)):
        res+="<tr>"
        res+="<td>"
        res+=c[i]['name']
        res+="</td>"
        res += "<td>"
        res += c[i]['acronym']
        res += "</td>"
        res+="</tr>"
    res+="</table>"
    return HttpResponse(res)

def students(request,id):
    print(id)
    s=Student.objects.values('name','college__name','mocktest1__total').filter(college__id=id)
    return render(request,"student.html",{'s':s})