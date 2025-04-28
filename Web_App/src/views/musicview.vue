@import '../assets/main.css';
<template>
  
 
    <button @click="honk">Honk</button>
  
  <button>Honk</button>



</template>

<style>
button {
  padding: 10px 20px;
  font-size: 30px;
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
export default {
  props: ['mqttClient'], // passing the mqtt instance to this view as a props

  methods: {
    honk() {
      // making sure if the client is connected
      if (this.mqttClient) {
        this.mqttClient.publish('adruino/buzzer/honk', 'hell', (err) => {
          if (err) {
            console.error('Error publishing message:', err);
          } else {
            console.log("Message 'hell' sent to Arduino'");
          }
        });
      }
    },
  },
};
</script>
