from django.shortcuts import render
from django.forms import TextInput

context = {
    'title' : 'INMOOV Chatbot',
    'inputs': []
}

# Create your views here.
def gui(request):
    if request.method == "POST":
        input = request.POST.get('input', None)
        try:
            context['inputs'].append(input)
            context['inputs'].append("success")
            return render(request, 'gui/gui.html', context)
        except:
            context['inputs'].append('failure')
            return render(request, 'gui/gui.html', context)

    else:
        return render(request, 'gui/gui.html', context)
