<template>
  <h1 class="text">🌡️⏱️🗺️</h1>

  <div class="history">
      <h2>Temperature History</h2>
      <ul>
          <li v-for="(item, index) in temperatureHistory" :key="index">
              {{ item.time }} - {{ item.value }}°C
          </li>
      </ul>

      <h2>Speed History</h2>
      <ul>
          <li v-for="(item, index) in speedHistory" :key="index">
              {{ item.time }} - {{ item.value }} m/s
          </li>
      </ul>

      <h2>Distance History</h2>
      <ul>
          <li v-for="(item, index) in distanceHistory" :key="index">
              {{ item.time }} - {{ item.value }} m
          </li>
      </ul>
  </div>
</template>

<style>
.text {
  font-size: 20px;
  /* Adjust the size of the text */
  color: black;
  text-align: center;
  margin-bottom: 20px;
  /* Adjust the margin to fit text above the bottom */
}
.history {
  padding: 20px;
  font-family: sans-serif;
}
</style>

<script>
export default {
  data() {
      return {
          temperatureHistory: [],
          speedHistory: [],
          distanceHistory: []
      };
  },
  mounted() {
      this.loadHistory();
  },
  methods: {
      loadHistory() {
          this.temperatureHistory = JSON.parse(localStorage.getItem('temperatureHistory') || '[]'); // ADDED
          this.speedHistory = JSON.parse(localStorage.getItem('speedHistory') || '[]'); // ADDED
          this.distanceHistory = JSON.parse(localStorage.getItem('distanceHistory') || '[]'); // ADDED
      } // ADDED
  }
};
</script>
