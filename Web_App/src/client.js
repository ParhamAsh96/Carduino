import { createStore } from 'vuex';
import mqtt from 'mqtt';

class PrevDiagSes { // for Diagnostics
  constructor(hiTemp, lowTemp, speed, distance, startTime) {
    this.hiTemp = hiTemp;
    this.lowTemp = lowTemp;
    this.speed = speed;
    this.distance = distance;
    this.startTime = startTime;
  }
}

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
      
      // ADDED - store recieved messaged locally, in JSON format. The mqttClient.on('message') actions from subscribeToTopic run 6 times, while here it runs only once(1).
      mqttClient.on('message', (topic, message) => {
        console.log(`Message received on topic ${topic}:`, message.toString());

        const msg = message.toString();
        const now = new Date();
        const timestamp = `${now.getDate()} ${now.toLocaleString('default', { month: 'short' })} ${now.getHours().toString().padStart(2, '0')}:${now.getMinutes().toString().padStart(2, '0')}`;

        if (topic === 'carduino/temperature') {
          updateDiagnostics('temperatureHistory', msg, timestamp);
        } 
        else if (topic === 'carduino/accelerometer/speed') {
          updateDiagnostics('speedHistory', msg, timestamp);
        } 
        else if (topic === 'carduino/accelerometer/distance') {
          updateDiagnostics('distanceHistory', msg, timestamp);
        }
      });
      // END - Diagnostics

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
            // console.log(`Successfully subscribed to ${topic}`);
          }
        });
    
        // Set up message listener
        mqttClient.on('message', (topic, message) => {  // NOTE: This will run 3 or 6 times per recieved message. (idk why)

          // console.log(`Message received on topic ${topic}:`, message.toString());
          
          if (topic == 'carduino/temperature') {
            store.commit('setTemperature', message.toString());
          } else if (topic == 'carduino/accelerometer/speed') {
            store.commit('setSpeed', message.toString());
          } else if (topic == 'carduino/accelerometer/distance') {
            store.commit('setDistance', message.toString());
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
    }
  },
});

// Helper to save MQTT values with timestamp to localStorage
// PrevDiagSes() CLASS is used to create JSON {} block, then pushed to localStorage. Same block will be overwritten with recieved values from mqtt, until distance becomes '0.00 m' again.
function updateDiagnostics(key, msg /*mqtt message*/, time) {
  let sessions = JSON.parse(localStorage.getItem('diagnosticSessions') || '[]');
  let lastSession = sessions[sessions.length - 1]; // gets latest saved JSON block of the Diagnostics, from localStorage
  // Start new diagnostics session if:
  // 1. No sessions exist yet, OR
  // 2. Current topic is distance AND value is "0.00 m" AND previous distance was > 0
  const shouldStartNewSession = !lastSession || (key === 'distanceHistory' && 
                                                      msg === '0.00 m' && 
                                                      lastSession.distance && 
                                                      parseFloat(lastSession.distance) > 0);

  if (shouldStartNewSession) {
    const newSession = new PrevDiagSes( 
      null, // hiTemp
      null, // lowTemp
      null, // speed
      key === 'distanceHistory' ? msg : null, //Ensures distance isn't accidentally set for temperature/speed updates
      time
    );
    sessions.push(newSession);
  } 
  else if (lastSession) { // Otherwise, update the last session
    if (key === 'temperatureHistory') {
      const numValue = parseFloat(msg);
      lastSession.hiTemp = lastSession.hiTemp ? Math.max(lastSession.hiTemp, numValue) : numValue;
      lastSession.lowTemp = lastSession.lowTemp ? Math.min(lastSession.lowTemp, numValue) : numValue;
    }
    else if (key === 'speedHistory') {
      lastSession.speed = msg;
    } 
    else if (key === 'distanceHistory') {
      lastSession.distance = msg;
    }
  }

  localStorage.setItem('diagnosticSessions', JSON.stringify(sessions)); // sets JSON saved data as 'diagnosticSessions':{} in localStorage
}

export default store; 
