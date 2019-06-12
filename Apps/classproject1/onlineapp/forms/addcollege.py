from onlineapp.models import *
from django import forms

class CollegeForm(forms.ModelForm):
    class Meta:
        exclude = ['id']
        model = College
        widgets = {
            'name': forms.TextInput(attrs={'class': 'input', 'placeholder': 'Enter Student name'}),
            'location': forms.TextInput(attrs={'class': 'input', 'placeholder': 'Enter the location'}),
            'acronym': forms.TextInput(attrs={'class': 'input', 'placeholder': 'Enter the acronym'}),
            'contact': forms.EmailInput(attrs={'class': 'input', 'placeholder': 'Enter Student email'}),
        }
