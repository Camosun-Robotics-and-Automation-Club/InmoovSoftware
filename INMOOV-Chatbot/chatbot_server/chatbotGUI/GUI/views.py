from django.shortcuts import render
import pyttsx3
from time import sleep

# Create your views here.

#GUI view
def gui(request):
    #initialize text-to-speech engine at a rate of 120 words per min
    engine = pyttsx3.init()
    engine.setProperty('rate', 120)

    #context dictionary for view
    context = {
    'title' : 'INMOOV Chatbot',
    'inputs': []
    }

    #main loop 
    while(True):
        if request.method == "POST": #if post request
            input = request.POST.get('input', None) #fetch the user input

            try:
                context['inputs'].append(input) #add user input to context dictionary
                sleep(0.5) #wait 500ms
                engine.say(input) #create speech file
                engine.runAndWait() #run speech file and wait for the next one
                return render(request, 'gui/gui.html', context) #render the view
            except: #error handling...
                engine.say('failure')
                context['inputs'].append('failure')
                return render(request, 'gui/gui.html', context)

        else:
            return render(request, 'gui/gui.html', context) #if no post request just render the view
