@import '../assets/main.css';
<template>
    <div :key="$route.path">
    <button @click="honk">Honk</button>
  </div>
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
button {
  position: fixed; /* Fixed position at the bottom of the screen */
  bottom: 20px; /* Distance from the bottom */
  left: 50%; /* Centers horizontally */
  transform: translateX(-50%); /* Adjusts to perfectly center the button */
  padding: 20px 40px; /* Adds space around the text */
  font-size: 24px; /* Font size */
  color: white; /* Text color */
  background-color: #3b8b9d; 
  border: none; /* No border */
  border-radius: 50%; /* Makes the button round */
  cursor: pointer; /* Change cursor to pointer on hover */
  
}

button:hover {
  background-color: #2a6a77; /* A darker shade for the hover effect */
  
}

</style>



<script>
import { mapActions } from 'vuex';  

export default {
  methods: {
    ...mapActions(['publishToTopic']),  // Map the publishToTopic action to a method

    
    honk() {
      this.publishToTopic({
        topic: 'carduino/buzzer/honk',
        message: 'honk',  
      });
    },
  },
};
</script>
