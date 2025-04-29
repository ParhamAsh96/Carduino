import { createStore } from 'vuex';
import mqtt from 'mqtt';  

const store = createStore({
  state() {
    return {
      mqttClient: null,
    };
  },
  mutations: {
    setMqttClient(state, client) {
      state.mqttClient = client;
    },
  },
  actions: {
    //ws://broker.hivemq.com:8000/mqtt
//use this for test
    initializeMqttClient({ commit }) {
      const mqttClient = mqtt.connect('ws://test.mosquitto.org:8081');  
      mqttClient.on('connect', () => {
        console.log('Connected to MQTT broker');
      });
      mqttClient.on('error', (err) => {
        console.error('MQTT connection error:', err);
      });

      commit('setMqttClient', mqttClient);  // Store the mqttClient in Vuex state
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
  },
  getters: {
    getMqttClient(state) {
      return state.mqttClient;
    },
  },
});

export default store; 
