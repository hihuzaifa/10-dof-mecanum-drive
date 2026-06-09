from flask import Flask, render_template
import serial
import time

app = Flask(__name__)

# Replace with your actual port from the 'ls /dev/tty*' check (e.g., /dev/ttyACM0)
ARDUINO_PORT = '/dev/ttyUSB0'

try:
    bot = serial.Serial(ARDUINO_PORT, 115200, timeout=1)
    time.sleep(2)
    print("Link to Arduino established.")
except Exception as e:
    print(f"Error connecting to serial: {e}")
    bot = None

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/command/<int:cmd>')
def send_command(cmd):
    if bot:
        bot.write(f"{cmd}\n".encode('utf-8'))
        return {"status": "success", "command": cmd}
    return {"status": "error", "message": "No serial connection"}

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000, debug=False)