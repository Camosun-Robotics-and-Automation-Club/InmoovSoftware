import pyttsx3

engine = pyttsx3.init()
rate = engine.getProperty('rate')
engine.setProperty('rate', rate-50)
print(engine.getProperty('rate'))

while(True):
    userInput = input("Say something: ")
    if userInput == 'end':
        break
    engine.say(userInput)
    engine.runAndWait()