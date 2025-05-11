<template>
	<h1 class="text">🌡️⏱️🗺️</h1>

 
  <div v-for="(entries, type) in diagnostics" :key="type" class="section">
    <h2>{{ type.toUpperCase() }}</h2>
    <ul>
      <li v-for="(entry, index) in entries" :key="index">
        {{ entry.timestamp }} - {{ entry.value }}
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


.section {
  margin: 20px;
}

</style>

<script>
import { mapGetters } from 'vuex';

export default {
  computed: {
    ...mapGetters(['getDiagnostics']),
    
    diagnostics() {
      return this.getDiagnostics;
    }
    
  },
  mounted() {
    
    const data = JSON.parse(localStorage.getItem('diagnostics')) || {};
    for (const [type, entries] of Object.entries(data)) {
      entries.forEach(entry => {
        this.$store.commit('updateDiagnostics', {
          type,
          value: entry.value,
          timestamp: entry.timestamp
        });
      });
    }

    this.$store.dispatch('initializeMqttClient');
    
  }
};
</script>
