<template>
  <!-- Toggle Controls - Fixed Left -->
  <div
    class="fixed left-6 top-1/2 transform -translate-y-1/2 flex flex-col space-y-6"
  >
    <!-- Auto Brake Toggle -->
    <div
      @click="toggle('autoBrake')"
      class="flex items-center space-x-4 cursor-pointer"
    >
      <div
        :class="[
          'w-12 h-6 flex items-center rounded-full p-1 transition duration-300',
          autoBrake ? 'bg-[#ffcc00]' : 'bg-gray-400',
        ]"
      >
        <div
          :class="[
            'bg-white w-4 h-4 rounded-full shadow-md transform transition duration-300',
            autoBrake ? 'translate-x-6' : 'translate-x-0',
          ]"
        ></div>
      </div>
      <span class="text-white text-lg">Auto Brake</span>
    </div>

    <!-- Front Lights Toggle -->
    <div
      @click="toggle('frontLights')"
      class="flex items-center space-x-4 cursor-pointer"
    >
      <div
        :class="[
          'w-12 h-6 flex items-center rounded-full p-1 transition duration-300',
          frontLights ? 'bg-[#ffcc00]' : 'bg-gray-400',
        ]"
      >
        <div
          :class="[
            'bg-white w-4 h-4 rounded-full shadow-md transform transition duration-300',
            frontLights ? 'translate-x-6' : 'translate-x-0',
          ]"
        ></div>
      </div>
      <span class="text-white text-lg">Front Lights</span>
    </div>

    <!-- Brake Lights Toggle -->
    <div
      @click="toggle('brakeLights')"
      class="flex items-center space-x-4 cursor-pointer"
    >
      <div
        :class="[
          'w-12 h-6 flex items-center rounded-full p-1 transition duration-300',
          brakeLights ? 'bg-[#ffcc00]' : 'bg-gray-400',
        ]"
      >
        <div
          :class="[
            'bg-white w-4 h-4 rounded-full shadow-md transform transition duration-300',
            brakeLights ? 'translate-x-6' : 'translate-x-0',
          ]"
        ></div>
      </div>
      <span class="text-white text-lg">Brake Lights</span>
    </div>
  </div>

  <!-- Background Video Placeholder -->
  <div class="fixed inset-0 -z-10 bg-black flex items-center justify-center">
    <p
      class="text-white text-xl sm:text-2xl md:text-3xl lg:text-4xl text-center px-4"
    >
      Video not available
    </p>
  </div>

  <!-- Info Section - Top Center -->
  <div class="inset-x-0 flex justify-center space-x-6">
    <div class="bg-white shadow-md rounded-xl px-6 py-3 text-center">
      <p class="text-sm font-medium text-gray-500">Temperature</p>
      <p class="text-xl font-bold text-gray-800">{{ temperature }} °C</p>
    </div>
    <div class="bg-white shadow-md rounded-xl px-6 py-3 text-center">
      <p class="text-sm font-medium text-gray-500">Speed</p>
      <p class="text-xl font-bold text-gray-800">{{ speed }} m/s</p>
    </div>
    <div class="bg-white shadow-md rounded-xl px-6 py-3 text-center">
      <p class="text-sm font-medium text-gray-500">Distance</p>
      <p class="text-xl font-bold text-gray-800">{{ distance }} m</p>
    </div>
  </div>

  <!-- Up/Down Arrows - Bottom Right -->
  <div class="fixed bottom-6 right-6 flex flex-col items-center space-y-4">
    <!-- Up Arrow -->
    <button
      @pointerdown="onArrow('up')"
      @pointerup="letGo('up')"
      @pointercancel="letGo('up')"
      class="flex items-center justify-center size-20 bg-blue-500 text-white rounded-full shadow-lg hover:bg-blue-600 hover:text-[#ffcc00] active:scale-90 active:bg-red-900 transition-transform"
      aria-label="Arrow Up"
    >
      <svg
        xmlns="http://www.w3.org/2000/svg"
        class="h-12 w-12"
        fill="none"
        viewBox="0 0 24 24"
        stroke="currentColor"
        stroke-width="2"
      >
        <path
          stroke-linecap="round"
          stroke-linejoin="round"
          d="M5 15l7-7 7 7"
        />
      </svg>
    </button>

    <!-- Down Arrow -->
    <button
      @pointerdown="onArrow('down')"
      @pointerup="letGo('down')"
      @pointercancel="letGo('down')"
      class="flex items-center justify-center size-20 bg-blue-500 text-white rounded-full shadow-lg hover:bg-blue-600 hover:text-[#ffcc00] active:scale-90 active:bg-red-900 transition-transform"
      aria-label="Arrow Down"
    >
      <svg
        xmlns="http://www.w3.org/2000/svg"
        class="h-12 w-12"
        fill="none"
        viewBox="0 0 24 24"
        stroke="currentColor"
        stroke-width="2"
      >
        <path
          stroke-linecap="round"
          stroke-linejoin="round"
          d="M19 9l-7 7-7-7"
        />
      </svg>
    </button>
  </div>

  <!-- Left/Right Arrows - Bottom Left -->
  <div class="fixed bottom-6 left-6 flex space-x-4">
    <!-- Left Arrow -->
    <button
      @pointerdown="onArrow('left')"
      @pointerup="letGo('left')"
      @pointercancel="letGo('left')"
      class="flex items-center justify-center size-20 bg-blue-500 text-white rounded-full shadow-lg hover:bg-blue-600 hover:text-[#ffcc00] active:scale-90 active:bg-red-900 transition-transform"
      aria-label="Arrow Left"
    >
      <svg
        xmlns="http://www.w3.org/2000/svg"
        class="h-12 w-12"
        fill="none"
        viewBox="0 0 24 24"
        stroke="currentColor"
        stroke-width="2"
      >
        <path
          stroke-linecap="round"
          stroke-linejoin="round"
          d="M15 19l-7-7 7-7"
        />
      </svg>
    </button>

    <!-- Right Arrow -->
    <button
      @pointerdown="onArrow('right')"
      @pointerup="letGo('right')"
      @pointercancel="letGo('right')"
      class="flex items-center justify-center size-20 bg-blue-500 text-white rounded-full shadow-lg hover:bg-blue-600 hover:text-[#ffcc00] active:scale-90 active:bg-red-900 transition-transform"
      aria-label="Arrow Right"
    >
      <svg
        xmlns="http://www.w3.org/2000/svg"
        class="h-12 w-12"
        fill="none"
        viewBox="0 0 24 24"
        stroke="currentColor"
        stroke-width="2"
      >
        <path stroke-linecap="round" stroke-linejoin="round" d="M9 5l7 7-7 7" />
      </svg>
    </button>
  </div>
</template>

<script>
import { mapActions } from "vuex";
import { mapState } from "vuex";

export default {
  computed: {
    ...mapState(["temperature", "speed", "distance", "mqttClient"]),
  },
  mounted() {
    this.$store.dispatch("subscribeToTopic", "carduino/temperature");
    this.$store.dispatch("subscribeToTopic", "carduino/accelerometer/speed");
    this.$store.dispatch("subscribeToTopic", "carduino/accelerometer/distance");
    this.$store.dispatch("subscribeToTopic", "carduino/light");

    // Keyboard listeners
    window.addEventListener("keydown", this.KeyDown);
    window.addEventListener("keyup", this.KeyUp);
  },

  beforeUnmount() {
    window.removeEventListener("keydown", this.KeyDown);
    window.removeEventListener("keyup", this.KeyUp);
  },
  data() {
    return {
      autoBrake: false,
      frontLights: false,
      brakeLights: false,
      isRightArrowDown: false,
      isLeftArrowDown: false,
      isUpArrowDown: false,
      isDownArrowDown: false,
    };
  },

  methods: {
    ...mapActions(["publishToTopic"]), // Map the publishToTopic action to a method

    toggle(feature) {
      this[feature] = !this[feature];
      console.log(`${feature} toggled: ${this[feature]}`);
    },

    lightOn() {
      this.publishToTopic({ topic: "carduino/light", message: "light on" });
    },

    onArrow(direction) {
      switch (direction) {
        case "up":
          this.publishToTopic({
            topic: "carduino/movement",
            message: "arrowUp",
          });
          break;

        case "right":
          this.publishToTopic({
            topic: "carduino/movement",
            message: "arrowRight",
          });
          break;

        case "down":
          this.publishToTopic({
            topic: "carduino/movement",
            message: "arrowDown",
          });
          // code block
          break;

        case "left":
          this.publishToTopic({
            topic: "carduino/movement",
            message: "arrowLeft",
          });
          break;
      }
    },

    letGo(direction) {
      switch (direction) {
        case "up":
          this.publishToTopic({
            topic: "carduino/movement",
            message: "arrowUpStop",
          });
          break;

        case "right":
          this.publishToTopic({
            topic: "carduino/movement",
            message: "arrowRightStop",
          });
          break;

        case "down":
          this.publishToTopic({
            topic: "carduino/movement",
            message: "arrowDownStop",
          });
          // code block
          break;

        case "left":
          this.publishToTopic({
            topic: "carduino/movement",
            message: "arrowLeftStop",
          });
          break;

        // code block
      }
      // Add logic for handling arrow clicks here
    },

    KeyDown(direction) {
      if (direction.key === "ArrowRight" && !this.isRightArrowDown) {
        this.isRightArrowDown = true;
        this.onArrow("right");
      } else if (direction.key === "ArrowLeft" && !this.isLeftArrowDown) {
        this.isLeftArrowDown = true;
        this.onArrow("left");
      } else if (direction.key === "ArrowUp" && !this.isUpArrowDown) {
        this.isUpArrowDown = true;
        this.onArrow("up");
      } else if (direction.key === "ArrowDown" && !this.isDownArrowDown) {
        this.isDownArrowDown = true;
        this.onArrow("down");
      }
    },

    KeyUp(direction) {
      if (direction.key === "ArrowRight") {
        this.isRightArrowDown = false;
        this.letGo("right");
      } else if (direction.key === "ArrowLeft") {
        this.isLeftArrowDown = false;
        this.letGo("left");
      } else if (direction.key === "ArrowUp") {
        this.isUpArrowDown = false;
        this.letGo("up");
      } else if (direction.key === "ArrowDown") {
        this.isDownArrowDown = false;
        this.letGo("down");
      }
    },
  },
};
</script>
