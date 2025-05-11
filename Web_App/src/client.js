import { createStore } from 'vuex';
import mqtt from 'mqtt';  

// get timestamp
function getCurrentTimestamp() {
  const now = new Date();
  return `${now.getHours()}:${now.getMinutes()}/${now.getDate()}/${now.getMonth() + 1}/${now.getFullYear()}`;
}

//▽ save diagnostics data to localStorage in a JSON format
function saveToLocal(type, value, timestamp) {
  let diagnostics = JSON.parse(localStorage.getItem('diagnostics')) || {
    temperature: [],
    speed: [],
    distance: []
  };

  diagnostics[type].push({ value, timestamp });

  localStorage.setItem('diagnostics', JSON.stringify(diagnostics));
}
//△

const store = createStore({
  state() {
    return {
      mqttClient: null,
    //▽ for diagnostics
      diagnostics: {
        temperature: [],
        speed: [],
        distance: []
      }
    //△
    };
  },
  mutations: {
    setMqttClient(state, client) {
      state.mqttClient = client;
    },
    //▽ for diagnostics
    updateDiagnostics(state, { type, value, timestamp }) {
      if (state.diagnostics[type]) {
        state.diagnostics[type].push({ value, timestamp });
      }
    }
    //△
  },
  actions: {
    // Some teammates had issues connecting to a broker from the web app. Try one of the first 2 brokers. 3rd is a local broker:
    // ws://broker.hivemq.com:8000/mqtt
    // ws://test.mosquitto.org:8081
    // ws://172.20.10.3:1883
    initializeMqttClient({ dispatch, commit }) {
      const mqttClient = mqtt.connect('ws://broker.hivemq.com:8000/mqtt');  
      mqttClient.on('connect', () => {
        console.log('Connected to MQTT broker');

        // to subscribe by default to these topics:
        dispatch('subscribeToTopic', 'carduino/temperature');
        dispatch('subscribeToTopic', 'carduino/accelerometer/speed');
        dispatch('subscribeToTopic', 'carduino/accelerometer/distance');
 
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
    
    
    /* 
    Use "this.$store.dispatch('subscribeToTopic', 'the topic you want')" 
    in any component to subscribe to a topic.

    If you want to subscribe when the component is added to the DOM , call the SUB function inside the "mount" 
    (which is inside the export default in script):
         mounted() {
         this.$store.dispatch('subscribeToTopic', 'your/topic');
    */
  
    
    subscribeToTopic({ state, commit }, topic) {
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

          //▽ Save diagnostics data in localStorage
          const value = message.toString();
          const timestamp = getCurrentTimestamp();

          let type;
          if (topic === 'carduino/temperature') type = 'temperature';
          else if (topic === 'carduino/accelerometer/speed') type = 'speed';
          else if (topic === 'carduino/accelerometer/distance') type = 'distance';
          else return;

          commit('updateDiagnostics', { type, value, timestamp });
          saveToLocal(type, value, timestamp);
          //△ 
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
    //▽ for diagnostics
    getDiagnostics(state) {
      return state.diagnostics;
    }
    //△
  },
});

export default store; 
