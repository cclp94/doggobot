import os
from flask import Flask
app = Flask(__name__)

@app.route('/doggo/<command>')
def commandDoggo(command):
   os.system('python spiCommandSender.py '+command)
   return command

app.run(host='0.0.0.0')
