<script setup>
import { RouterLink, RouterView } from "vue-router";
</script>

<template>
  <header>
    <div class="wrapper">
      <HelloWorld msg="You did it!" />

      <nav>
        <RouterLink to="/">Home</RouterLink>
        <RouterLink to="/controlview"> Control </RouterLink>
        <RouterLink to="/statisticsview">Statistics</RouterLink>
        <RouterLink to="/guideview">Guide</RouterLink>
        <RouterLink to="/about">About</RouterLink>
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
