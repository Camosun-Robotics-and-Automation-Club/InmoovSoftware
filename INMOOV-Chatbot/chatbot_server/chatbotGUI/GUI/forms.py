from django import forms

class InputForm(forms.Form):
    userInput = forms.CharField(label="Talk", max_length=200)