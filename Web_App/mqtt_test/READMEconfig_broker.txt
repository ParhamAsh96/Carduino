The Mosquitto local broker that runs on the PC (that the WIO and the WebApp connect to)
should run on these otpions in a config.txt :

listener 1883
allow_anonymous true//to mqtt connect over WiFi

listener 9001       //websocket port for WebApp connection
protocol websockets //allows mqtt connections from the web