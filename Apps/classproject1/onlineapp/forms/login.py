from onlineapp.models import *
from django import forms

class LoginForm(forms.Form):
    username=forms.CharField(
        required=True,
        widget=forms.TextInput(attrs={'class': 'input', 'placeholder': 'Enter the username'}),
    )

    password = forms.CharField(
        required=True,
        widget= forms.PasswordInput(attrs={'class': 'input', 'placeholder': 'Enter the password'}),
    )

class SignUpForm(forms.Form):
    first_name = forms.CharField(
        required=True,
        widget=forms.TextInput(attrs={'class': 'input', 'placeholder': 'Enter the firstname'}),
    )

    last_name = forms.CharField(
        required=True,
        widget=forms.TextInput(attrs={'class': 'input', 'placeholder': 'Enter the lastname'}),
    )

    username = forms.CharField(
        required=True,
        widget=forms.TextInput(attrs={'class': 'input', 'placeholder': 'Enter the username'}),
    )

    password = forms.CharField(
        required=True,
        widget=forms.PasswordInput(attrs={'class': 'input', 'placeholder': 'Enter the password'}),
    )