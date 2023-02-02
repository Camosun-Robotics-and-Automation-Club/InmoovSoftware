from django.shortcuts import render
import pyttsx3
from time import sleep

# Create your views here.


#context dict to store user inputs
context = {
'title' : 'INMOOV Chatbot',
'inputs': []
}
    
#GUI view
def gui(request):
    #initialize text-to-speech engine at a rate of 120 words per min
    engine = pyttsx3.init()
    engine.setProperty('rate', 120) 

    if request.method == "POST": #if post request
        input = request.POST.get('input', None) #fetch the user input
        reset = request.POST.get('Reset', None)
        if reset:
            context['inputs'].clear()
            return render(request, 'gui/gui.html', context)
        
        if input:
            context['inputs'].append(input) #add user input to context dictionary
            sleep(0.5) #wait 500ms
            engine.say(input) #create speech file
            engine.runAndWait() #run speech file and wait for the next one
            return render(request, 'gui/gui.html', context) #render the view
    else:
        return render(request, 'gui/gui.html', context) #if no post request just render the view
