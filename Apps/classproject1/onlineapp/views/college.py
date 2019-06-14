from django.views import View
from onlineapp.models import *
from django.shortcuts import render
from django.contrib.auth.mixins import LoginRequiredMixin
from django.http import HttpResponse

class CollegeView(LoginRequiredMixin,View):
    login_url = 'login'
    def get(self,request,*args,**kwargs):
        if kwargs:
            s = Student.objects.values('name', 'college__name', 'mocktest1__total','id').filter(
                college__id=kwargs['id']).order_by('-mocktest1__total')
            return render(request, "student.html", {'s': s,'college':kwargs['id'],'permissions':request.user.get_all_permissions()})
        print(request.user.get_all_permissions())
        colleges=College.objects.all()
        return render(request,"printcolleges.html",{'colleges':colleges,'permissions':request.user.get_all_permissions()})

class TestView(View):
    def get(self,request,*args,**kwargs):
        return HttpResponse("hello world")





