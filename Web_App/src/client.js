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
    
    
    /*use 
    "this.$store.dispatch('subscribeToTopic', 'the topic you want')" 
    in any component to subscribe to a topic

    if you want to subscribe when the component is added to the DOM , call the SUB function inside the "mount" 
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
    
        // Set up message listener
        mqttClient.on('message', (topic, message) => {
          console.log(`Message received on topic ${topic}:`, message.toString());
          // You can commit the message to Vuex or handle it directly here
        });
      } else {
        console.error('MQTT client is not initialized');
      }
    }
  },
  getters: {
    getMqttClient(state) {
      return state.mqttClient;
    },
  },
});

export default store; 
