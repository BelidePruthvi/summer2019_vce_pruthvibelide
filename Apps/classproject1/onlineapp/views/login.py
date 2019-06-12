from django.views import View
from onlineapp.models import *
from django.shortcuts import render,redirect
from onlineapp.forms import *
from django.urls import resolve
from django.contrib.auth import authenticate,login,logout
from django.contrib import messages
from django.contrib.auth.models import User

def logout_user(request):
    logout(request)
    return redirect('printcolleges')

class LoginView(View):
    def get(self,request,*args,**kwargs):
        if request.user.is_authenticated:
            return redirect('printcolleges')

        form=LoginForm()
        return render(request, 'login.html', {'form': form})

    def post(self,request,*args,**kwargs):
        form=LoginForm(request.POST)
        if form.is_valid():
            username = request.POST['username']
            password = request.POST['password']
            user = authenticate(request, username=username, password=password)
            if user is not None:
                login(request, user)
                return redirect('printcolleges')
            else:
                messages.error(request,"Invalid credentials")
                return render(request,"login.html",{'form':form})
        else:
            return redirect('login')


class SignUpView(View):
    def get(self,request,*args,**kwargs):
        form = SignUpForm()
        return render(request, 'signup.html', {'form': form})

    def post(self,request,*args,**kwargs):
        form=SignUpForm(request.POST)
        if form.is_valid():
            user=User.objects.create_user(**form.cleaned_data)
            user.save()
            if user is not None:
                login(request, user)
                return redirect('printcolleges')
            else:
                messages.error(request, "error in signing up")
                return render(request, "signup.html", {'form': form})

        return redirect('signup')

