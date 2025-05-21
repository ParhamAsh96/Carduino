<script>
import { RouterLink, RouterView } from "vue-router";

import { mapActions } from 'vuex';

export default {
  name: 'App',
  created() {
    // create client when app is created
    this.initializeMqttClient(); 
  },
  
    
      

   
    methods: {
    ...mapActions(['initializeMqttClient'])  // Map the initializeMqttClient action to a method
  }
  
  }
  

</script>

<template>
    <div class="div-class">
      <nav>
        <RouterLink class = "transition delay-150 duration-300 ease-in-out hover:scale-110" to="/">Home</RouterLink>
        <RouterLink class = "transition delay-150 duration-300 ease-in-out hover:scale-110" to="/controlview"> Control </RouterLink>
        
        <RouterLink class = "transition delay-150 duration-300 ease-in-out hover:scale-110" to="/diagnosticsview">Diagnostics</RouterLink>
        <RouterLink class = "transition delay-150 duration-300 ease-in-out hover:scale-110" to="/musicview">Music</RouterLink>
        
        <RouterLink class = "transition delay-150 duration-300 ease-in-out hover:scale-110" to="/about">About</RouterLink>
      </nav>
    </div>

  <RouterView />
</template>



<style scoped>

  nav {
    display: flex;
    flex-wrap: wrap;
    justify-content: center; /* Centers the navigation items */
    align-items: center; /* Centers the items vertically */
    text-align: center;
  }


  nav a {
    color: rgb(217, 217, 217); /* Text color for the links */
    text-decoration: none; /* Removes underline from links */
    font-weight: bold;
    font-size: 22px; /* Adjust font size */
    flex: 0 0 14.285%; /* 12.5% = 7 items per row normally */
    box-sizing: border-box; /* So padding/margin don't break layout */
    background-color: #0f0f0f;

    /* Border */
    padding: 10px; /* Add padding so text isn't cramped inside the border */
    transition: border-color 0.3s, color 0.3s; /* Smooth hover effect */
    min-height: 80px
  }

  .div-class {
    background-color: #0f0f0f;
  }


  nav a:hover {
    color: #ffcc00; /* Change color on hover */
  }




</style>
