from django.shortcuts import render

# Create your views here.
def gui(request):
    return render(request, 'gui/gui.html')