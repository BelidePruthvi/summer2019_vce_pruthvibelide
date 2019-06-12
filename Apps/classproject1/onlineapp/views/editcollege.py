from django.views import View
from onlineapp.models import *
from django.shortcuts import render,redirect
from onlineapp.forms import *
from django.urls import resolve
from django.contrib.auth.mixins import LoginRequiredMixin,PermissionRequiredMixin

class AddCollegeView(PermissionRequiredMixin,LoginRequiredMixin,View):
    login_url = 'login'
    permission_required = ('onlineapp.add_college', 'onlineapp.delete_college', 'onlineapp.change_college')

    def get(self,request,*args,**kwargs):
        form = CollegeForm()
        if kwargs:
            if resolve(request.path_info).url_name == "delete_college":
                College.objects.get(**kwargs).delete()
                return redirect("printcolleges")
            college=College.objects.get(**kwargs)
            form=CollegeForm(instance=college)
        return render(request, 'addcollege.html', {'form': form})

    def post(self,request,*args,**kwargs):

        # if resolve(request.path_info).url_name == "delete_college":
        #     College.objects.get(**kwargs).delete()
        #     return redirect("printcolleges")

        if resolve(request.path_info).url_name == "edit_college":
            college=College.objects.get(**kwargs)
            form=CollegeForm(request.POST,instance=college)
            if form.is_valid():
                form.save(commit=True)
                return redirect("printcolleges")

        form = CollegeForm(request.POST)
        if form.is_valid():
            form.save(commit=True)
            return redirect("printcolleges")
        form = CollegeForm()
        return render(request, 'addcollege.html', {'form': form})