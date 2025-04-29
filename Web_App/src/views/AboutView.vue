@import '../assets/main.css';
<template>
  <div class="flex flex-wrap justify-evenly pt-[100px]">
    
    <!-- Item 1 -->
    <div class="flex items-center space-x-2">
      <img src="/Mikey.png" class="flex w-75 h-75 object-contain rounded-full hover:grayscale transition duration-300" />
      
      <div class = "flex flex-col">
        <h1 class="flex text-xl text-cyan-700 hover:text-cyan-900 hover:text-2xl transition duration-300">Makan Ajdadi</h1>
        <h2 class="flex text-base text-white hover:text-gray-400 hover:text-lg transition duration-300">SCRUM Master</h2>
      </div>
    </div>

    <!-- Item 2 -->
    <div class="flex items-center space-x-2">
      <img src="/person_lock_filled_icon_202008.webp" class="flex w-75 h-75 object-contain rounded-full hover:grayscale transition duration-300" />
      
      <div class = "flex flex-col">
        <h1 class="flex text-xl text-cyan-700 hover:text-cyan-900 hover:text-2xl transition duration-300">Sivert Bronebakk</h1>
        <h2 class="flex text-base text-white hover:text-gray-400 hover:text-lg transition duration-300">Product Owner</h2>
      </div>
    </div>

    <!-- Item 3 -->
    <div class="flex items-center space-x-2">
      <img src="/person_lock_filled_icon_202008.webp" class="flex w-75 h-75 object-contain rounded-full hover:grayscale transition duration-300" />
      
      <div class = "flex flex-col">
        <h1 class="flex text-xl text-cyan-700 hover:text-cyan-900 hover:text-2xl transition duration-300">Mobin Salehi</h1>
        <h2 class="flex text-base text-white hover:text-gray-400 hover:text-lg transition duration-300">Developer</h2>
      </div>
    </div>

    </div>

  <div class="flex justify-evenly pt-[25px]">
    <!-- Item 4 -->
    <div class="flex items-center space-x-2">
      <img src="/person_lock_filled_icon_202008.webp" class="flex w-75 h-75 object-contain rounded-full hover:grayscale transition duration-300" />
      
      <div class = "flex flex-col">
        <h1 class="flex text-xl text-cyan-700 hover:text-cyan-900 hover:text-2xl transition duration-300">Parham Ashrafzadeh</h1>
        <h2 class="flex text-base text-white hover:text-gray-400 hover:text-lg transition duration-300">Developer</h2>
      </div>
    </div>

    <!-- Item 5 -->
    <div class="flex items-center space-x-2">
      <img src="/person_lock_filled_icon_202008.webp" class="flex w-75 h-75 object-contain rounded-full hover:grayscale transition duration-300" />
      
      <div class = "flex flex-col">
        <h1 class="flex text-xl text-cyan-700 hover:text-cyan-900 hover:text-2xl transition duration-300">Dorin Calmis</h1>
        <h2 class="flex text-base text-white hover:text-gray-400 hover:text-lg transition duration-300">Developer</h2>
      </div>
    </div>



  </div>



</template>


<style>
@media (min-width: 1024px) {
  .about {
    min-height: 100vh;
    display: flex;
    align-items: center;
  }
}
</style>
