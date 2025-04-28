@import '../assets/main.css';
<template>
  
  <div>
    
    <button @click="sendHonkCommand">Play Honk Sound</button>
  </div>



</template>

<style>
button {
  padding: 10px 20px;
  font-size: 16px;
  background-color: #4CAF50;
  color: white;
  border: none;
  cursor: pointer;
  margin-top: 20px;
  
}
button:hover {
  background-color: #45a049;
}
</style>
<script>
import mqtt from "mqtt";

export default {
  data() {
    console.log("data");
    return {
      // it seems like this is the MQTT instance but why null?
      client: null,  
    };
  },
  methods: {
    sendHonkCommand() {
      //if the client is initialized
      if (this.client) {
        // Send  message to the topic 
        //topic is buzzer/control
        this.client.publish("adruino/buzzer/control", "hell");  
      }
    },
  },
  created() {
    // initializing the MQTT client 
    console.log("created");
    server = 'test.mosquitto.org'
port = 1883
client.setServer(server, 1883);
    this.client = mqtt.connect("ws:test.mosquitto.org:1883"); //the IP has to change every time(ask duro)
    
    this.client.on("connect", () => {
      console.log("Connected to MQTT for buzzer control");
      
    });

    //error handling for connection
    this.client.on("error", (err) => {
      //to print the error for debugging
      console.error("MQTT Connection Error:", err);
    });
  },
};







</script>
