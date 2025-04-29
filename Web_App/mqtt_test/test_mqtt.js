
// uses mqtt from "https://unpkg.com/mqtt/dist/mqtt.min.js"
// mqtt is imported in the html <script src=...>

// const brokerUrl = 'ws://192.168.0.138:8883'; // change IP (and port if needed) 
const brokerUrl = 'wss://test.mosquitto.org:8081'; 
const clientId = 'mqtt_web_' + Math.random().toString(16).substr(2, 8); // Name that you connect with

// client.on('condition', func()); - will run func() when condition is true
const client = mqtt.connect(brokerUrl, {
  clientId: clientId,
  clean: true,
  connectTimeout: 4000,
  reconnectPeriod: 1000,
});

topic = 'carduino/urmom';

client.on('connect', () => {
  console.log('Connected to MQTT broker');
  
  // Subscribe to a topic
  client.subscribe( topic , (err) => {
    if (!err) {
      console.log('Subscribed to ', topic);
      
      // Publish
      client.publish(topic, 'Hello Arduino')
    }
  });

});

                      // 'topic' and 'message' are passed from 'client'
client.on('message', (topic, message) => {
  // Print message to console
  const msgStr = message.toString();
  console.log(`📬 Message received on '${topic}': ${msgStr}`);

  // Print message to the html page
  const msgDiv = document.getElementById('messages');
  const msg = document.createElement('p');
  msg.textContent = `📬 on ${topic}: ${msgStr}`;
  msgDiv.appendChild(msg);
});

client.on('error', (err) => {
  console.error('Connection error: ', err);
});

client.on('reconnect', () => {
  console.log('Reconnecting...');
});