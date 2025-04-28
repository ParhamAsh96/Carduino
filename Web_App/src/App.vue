<script>
import { RouterLink, RouterView } from "vue-router";
import mqtt from 'mqtt';

export default {
  name: 'App',
  data() {
    return {
      
//ws://broker.hivemq.com:8000/mqtt
//use this for test
      
      client: null,
      // topic: 'adruino/buzzer/control',
      brokerUrl: 'ws://172.20.10.3:9001', // Your broker URL
    };
  },
  methods: {
    connectMQTT() {
      const clientId = 'mqtt_web_' + Math.random().toString(16).substr(2, 8);

      this.client = mqtt.connect(this.brokerUrl, {
        clientId: clientId,
        clean: true,
        connectTimeout: 4000,
        reconnectPeriod: 1000,
      });

      this.client.on('connect', () => {

        console.log('Connected to MQTT broker');
        this.client.subscribe(adruino/buzzer/control, (err) => {

          this.client.publish(adruino/buzzer/control, 'hell');
          // if (!err) {
          //   console.log('Subscribed to', this.topic);
          //   this.client.publish(adruino/buzzer/control, 'hell');
          // }
        });
      });

      this.client.on('message', (topic, message) => {

        console.log(`📬 Message received on '${topic}': ${message.toString()}`);
        this.displayMessage(message.toString());
      });

      this.client.on('error', (err) => {
        console.error('Connection error:', err);
      });

      this.client.on('reconnect', () => {
        console.log('Reconnecting...');
      });
    },

    // displayMessage(message) {
    //   const msgDiv = document.getElementById('messages');
    //   const msg = document.createElement('p');
    //   msg.textContent = `📬 on ${this.topic}: ${message}`;
    //   msgDiv.appendChild(msg);
    // },
  },
  mounted() {
    this.connectMQTT();
  },
  beforeDestroy() {
    if (this.client) {
      this.client.end();
    }
  },
};
</script>

<template>
  <header>
    <div class="wrapper">
      <HelloWorld msg="You did it!" />

      <nav>
        <RouterLink to="/">Home</RouterLink>
        <RouterLink to="/controlview"> Control </RouterLink>
        <RouterLink to="/linetrackingview"> Line-Tracking </RouterLink>
        <RouterLink to="/statisticsview">Statistics</RouterLink>
        <RouterLink to="/diagnosticsview">Diagnostics</RouterLink>
        <RouterLink to="/musicview">Music</RouterLink>
        <RouterLink to="/guideview">Guide</RouterLink>
        <RouterLink to="/about">About</RouterLink>
      </nav>
    </div>
    
  </header>

  
</template>

<style scoped>
header {
  width: 100%;
  background-color: #1d1d1b; /* Dark background color for the navigation bar */
  position: fixed; /* Fixes the header at the top */
  top: 0; /* Aligns it to the top of the page */
  left: 0;
  z-index: 1000; /* Ensures the header stays above other content */
  padding: 5px 0; /* Adjust the padding for spacing */
}

nav {
  display: flex;
  width: 100%;
  justify-content: center; /* Centers the navigation items */
  align-items: center; /* Centers the items vertically */
  text-align: center;
}

nav a {
  color: rgb(217, 217, 217); /* Text color for the links */
  text-decoration: none; /* Removes underline from links */
  margin: 0 20px; /* Spacing between the navigation items */
  font-size: 22px; /* Adjust font size */
}

nav a:hover {
  color: #ffcc00; /* Change color on hover */
}
</style>
