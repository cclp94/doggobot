import speech_recognition as sr
import requests

def getCommand(command):
    if command == 'walk':
        print("Walk!")
    elif command == 'back':
        print('Reverse')
    elif command == 'stop':
        print('Stop!')
    elif command == 'left':
        print('Turn Left')
    elif command == 'right':
        print('Turn Right')
    requests.get("http://192.168.7.2:5000/doggo/"+command)

# obtain audio from the microphone
r = sr.Recognizer()
while True:
    with sr.Microphone() as source:
        r.adjust_for_ambient_noise(source)
        print("Say something!")
        audio = r.listen(source)

    # recognize speech using Google Speech Recognition
    try:
        # for testing purposes, we're just using the default API key
        # to use another API key, use `r.recognize_google(audio, key="GOOGLE_SPEECH_RECOGNITION_API_KEY")`
        # instead of `r.recognize_google(audio)`
        #print("Google Speech Recognition thinks you said " + r.recognize_google(audio))
        getCommand(r.recognize_google(audio))
    except sr.UnknownValueError:
        print("Google Speech Recognition could not understand audio")
    except sr.RequestError as e:
        print("Could not request results from Google Speech Recognition service; {0}".format(e))
