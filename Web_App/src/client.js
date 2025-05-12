import { createStore } from 'vuex';
import mqtt from 'mqtt';

const store = createStore({
  state() {
    return {
      mqttClient: null
    };
  },
  mutations: {
    setMqttClient(state, client) {
      state.mqttClient = client;
    },
    setDistance(state, value) {
      state.distance = value;
    },
    setSpeed(state, value) {
      state.speed = value;
    },
    setTemperature(state, value) {
      state.temperature = value;
    },
  },
  actions: {
    // Some teammates had issues connecting to a broker from the web app. Try one of the first 2 brokers. 3rd is a local broker:
    // ws://broker.hivemq.com:8000/mqtt
    // ws://test.mosquitto.org:8081
    // ws://172.20.10.3:1883
    initializeMqttClient({ commit }) {
      const mqttClient = mqtt.connect('ws://broker.hivemq.com:8000/mqtt');
      mqttClient.on('connect', () => {
        console.log('Connected to MQTT broker');
      });
      mqttClient.on('error', (err) => {
        console.error('MQTT connection error:', err);
      });

      // ADDED START — Setup message handler once
      mqttClient.on('message', (topic, message) => { // ADDED
        console.log(`Message received on topic ${topic}:`, message.toString()); // ADDED

        const msg = message.toString(); // ADDED
        const now = new Date(); // ADDED
        const timestamp = now.getHours().toString().padStart(2, '0') + ':' + now.getMinutes().toString().padStart(2, '0'); // ADDED

        if (topic == 'carduino/temperature') { // ADDED
          store.commit('setTemperature', msg); // ADDED
          saveToLocalStorage('temperatureHistory', msg, timestamp); // ADDED
        } else if (topic == 'carduino/accelerometer/speed') { // ADDED
          store.commit('setSpeed', msg); // ADDED
          saveToLocalStorage('speedHistory', msg, timestamp); // ADDED
        } else if (topic == 'carduino/accelerometer/distance') { // ADDED
          store.commit('setDistance', msg); // ADDED
          saveToLocalStorage('distanceHistory', msg, timestamp); // ADDED
        } // ADDED
      }); // ADDED
      // ADDED END

      commit('setMqttClient', mqttClient); // Store the mqttClient in Vuex state
    },

    // Publish message to a specific topic
    publishToTopic({ state }, { topic, message }) {
      const mqttClient = state.mqttClient;

      if (mqttClient) {
        mqttClient.publish(topic, message, (err) => {
          if (err) {
            console.error(`Error publishing message to ${topic}:`, err);
          } else {
            console.log(`Message \"${message}\" sent to ${topic}`);
          }
        });
      } else {
        console.error('MQTT client is not initialized');
      }
    },


    /*
    Use "this.$store.dispatch('subscribeToTopic', 'the topic you want')" 
    in any component to subscribe to a topic
    
    If you want to subscribe when the component is added to the DOM , call the SUB function inside the "mount" 
    (which is inside the export default in script):
    mounted() {
    this.$store.dispatch('subscribeToTopic', 'your/topic');
    */


    subscribeToTopic({ state }, topic) {
      const mqttClient = state.mqttClient;

      if (mqttClient) {
        mqttClient.subscribe(topic, (err) => {
          if (err) {
            console.error(`Error subscribing to ${topic}:`, err);
          } else {
            console.log(`Successfully subscribed to ${topic}`);
          }
        });
      } else {
        console.error('MQTT client is not initialized');
      }
    }, // ADDED: removed message handler from here
  },
  getters: {
    getMqttClient(state) {
      return state.mqttClient;
    }
  },
});

// Helper to save MQTT values with timestamp to localStorage // ADDED
function saveToLocalStorage(key, value, time) { // ADDED
  let data = JSON.parse(localStorage.getItem(key) || '[]'); // ADDED
  data.push({ value, time }); // ADDED
  localStorage.setItem(key, JSON.stringify(data)); // ADDED
} // ADDED

export default store; 
