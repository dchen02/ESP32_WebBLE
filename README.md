What's in the Arduino code

Start BLE communication Advertising 

Once connected, you can press "Boot Botton" or GPIO 0 to send text to the chrome browser via WebBle

The code receives that data from the Chrome / WebBLE, the parse the 123,123,123 to RGB value for the onboard NeoPixel, you can connect to external one if you like

Optional: OLED displays messages
------------------------------------------


What's in the html + javascript Code

Jquery Library for the color picker

Connects the BLE service with filter (so you don't have a huge list, so it's easy to find)
in app.js file you will see
filters: [{ name: "DKC BLE 1" },],optionalServices: [bleNusServiceUUID], acceptAllDevices: false
this is how we filter out BLE names

Sends and receives BLE data and display in the console.log()
