<script setup>
  import { RouterLink, RouterView } from "vue-router";
</script>

<template>
  <header>
    <div class="wrapper">
      <nav >
        <RouterLink class = "transition delay-150 duration-300 ease-in-out hover:scale-110" to="/">Home</RouterLink>
        <RouterLink class = "transition delay-150 duration-300 ease-in-out hover:scale-110" to="/controlview"> Control </RouterLink>
        <RouterLink class = "transition delay-150 duration-300 ease-in-out hover:scale-110" to="/linetrackingview"> Line-Tracker </RouterLink>
        <RouterLink class = "transition delay-150 duration-300 ease-in-out hover:scale-110" to="/diagnosticsview">Diagnostics</RouterLink>
        <RouterLink class = "transition delay-150 duration-300 ease-in-out hover:scale-110" to="/musicview">Music</RouterLink>
        <RouterLink class = "transition delay-150 duration-300 ease-in-out hover:scale-110" to="/guideview">Guide</RouterLink>
        <RouterLink class = "transition delay-150 duration-300 ease-in-out hover:scale-110" to="/about">About</RouterLink>
      </nav>
    </div>
  </header>

  <RouterView />
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
    flex-wrap: wrap;
    width: 100%; /* Allow links to wrap onto new lines */
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
    background-color: #1d1d1b;
    
    /* Border */
    border: 3px solid rgb(8, 233, 254);
    padding: 10px; /* Add padding so text isn't cramped inside the border */
    transition: border-color 0.3s, color 0.3s; /* Smooth hover effect */
    min-height: 80px
  }


  nav a:hover {
    color: #ffcc00; /* Change color on hover */
    border-color: #ffcc00; /* make border change color on hover */
  }




</style>
