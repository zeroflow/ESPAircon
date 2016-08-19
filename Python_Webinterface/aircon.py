import time
import json
import paho.mqtt.client as mqtt
from bottle import route, run, template, static_file, request, redirect

def on_connect(client, userdata, flags, rc):
    print("Connected with resultcode {}".format(rc))

def on_message(client, userdata, msg):
    print("Update from ESP")
    global aircon_data
    
    aircon_data = json.loads(msg.payload.decode("ASCII"))

client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message

client.connect("localhost", 1883, 60)

client.subscribe("aircon/status")

client.loop_start()

global aircon_data
aircon_data = {
        "on":True,
        "temperature": 23,
        "mode": 8,
        "fan": 2,
        "timer": False,
        "timer_value": 1,
        "unitF": False,
    }


@route('/aircon')
def index():
    global aircon_data
    return template("dashboard", data=aircon_data)
    
@route('/aircon/set', method="POST")
def set():
    global aircon_data
    aircon_data = dict(request.forms)
    
    if "on" not in aircon_data: aircon_data["on"] = False
    if aircon_data["on"] == "on": aircon_data["on"] = True
    
    if "timer" not in aircon_data: aircon_data["timer"] = False
    if aircon_data["timer"] == "on": aircon_data["timer"] = True
    
    if "unitF" not in aircon_data: aircon_data["unitF"] = False
    
    aircon_data["fan"] = int(aircon_data["fan"])
    aircon_data["mode"] = int(aircon_data["mode"])
    
    client.publish("aircon/set", payload=json.dumps(aircon_data)+"\r\n")
    
    redirect("/aircon")
    
@route("css/<filepath:path>")
def serve_css(filepath):
    return static_file(filepath, root="resources/css")

@route("js/<filepath:path>")
def serve_js(filepath):
    print(filepath)
    return static_file(filepath, root="resources/js")

@route("fonts/<filepath:path>")
def serve_font(filepath):
    return static_file(filepath, root="resources/fonts")

run(host='', port=1276)

