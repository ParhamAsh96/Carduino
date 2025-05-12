<template>
  <h1 class="text">this is where the joystick is</h1>

  <p id="speed">{{ speed }}m/s</p>
  <p id="distance">{{ distance }}m travelled.</p>
  <p id="temperature">{{ temperature }}°C</p>

</template>

<style>
.text {
  font-size: 20px; /* Adjust the size of the text */
  color: black;
  text-align: center;
  margin-bottom: 20px; /* Adjust the margin to fit text above the bottom */
}
</style>
<script>
import { mapState } from 'vuex';

export default {
  computed: {
    ...mapState(['temperature', 'speed', 'distance'])
  },
  mounted() {
    this.$store.dispatch('subscribeToTopic', 'carduino/temperature');
    this.$store.dispatch('subscribeToTopic', 'carduino/accelerometer/speed');
    this.$store.dispatch('subscribeToTopic', 'carduino/accelerometer/distance');
  }
};
  </script>
