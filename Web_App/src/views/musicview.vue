<template>
    <div class = "container">
    <button class = "button fixed_button" @click="honk">Honk</button>
    <button class = "button" @click="tune">tune</button>
    <button class = "button" @click="anthem">anthem</button>

  </div>
</template>

<style>

.button:hover {
  background-color: #45a049;
}
.button {
  width: 150px;  /* Fixed width for all buttons */
  height: 75px;  /* Fixed height for all buttons */
  padding: 10px 20px; /* Optional: adjust padding to control text inside */
  font-size: 18px; /* Consistent font size */
  color: white;
  background-color: #3b8b9d;
  border: none;
  border-radius: 50%;
  cursor: pointer;
  display: flex;
  justify-content: center;
  align-items: center;
}

.fixed-button {
  position: fixed;
  
  left: 50%;
  transform: translateX(-50%);
  padding: 20px 40px;
  font-size: 24px;
  
 
}

button:hover {
  background-color: #2a6a77; /* A darker shade for the hover effect */
  transform: scale(1.1);
  
}

.container 
  {
    display: flex;
  flex-direction: column; /* Stack buttons vertically */
  justify-content: center; /* Align to the top of the container */
  gap: 10px; /* Space between buttons */
  align-items: center; /* Center buttons horizontally */
  margin-bottom: 20px; /* Optional: gives space from the bottom */
}



</style>



<script>
import { mapActions } from 'vuex';  

export default {
  methods: {
    ...mapActions(['publishToTopic']),  // Map the publishToTopic action to a method

    
    honk() {
      this.publishToTopic({
        topic: 'carduino/buzzer',
        message: 'honk',  
      });
    },
    tune(){
      this.publishToTopic({
        topic : 'carduino/buzzer',
        message : 'tune'
      })
    },
    anthem(){
      this.publishToTopic({
        topic : 'carduino/buzzer',
        message : 'anthem'
      })
    }
  },
};
</script>
