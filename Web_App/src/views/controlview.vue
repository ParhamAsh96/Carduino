<template>
  <h1 class="text">this is where the joystick is</h1>

  <p id="speed">{{ speed }}m/s</p>
  <p id="distance">{{ distance }}m travelled.</p>
  <p id="temperature">{{ temperature }}°C</p>

  <button
    class="button fixed_button bg-black hover:active:bg-amber-50 p-10 m-20"
    @click="lightOn"
  >
    Light
  </button>
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
import { mapActions } from "vuex";
import { mapState } from "vuex";

export default {
  methods: {
    ...mapActions(["publishToTopic"]), // Map the publishToTopic action to a method

    lightOn() {
      this.publishToTopic({ topic: "carduino/light", message: "light on" });
    },
  },
  computed: {
    ...mapState(["temperature", "speed", "distance", "mqttClient"]),
  },
  mounted() {
    this.$store.dispatch("subscribeToTopic", "carduino/temperature");
    this.$store.dispatch("subscribeToTopic", "carduino/accelerometer/speed");
    this.$store.dispatch("subscribeToTopic", "carduino/accelerometer/distance");

    this.$store.dispatch("subscribeToTopic", "carduino/light");
  },
};
</script>
