<template>
    <div class="diagnostics-page">
        <h1 class="title">🌡️⏱️🗺️</h1>

        <div class="history-container">
            
            <div class="history-section">
                <h2>Temperature History</h2>
                <ul>
                    <li v-for="(item, index) in temperatureHistory.slice().reverse()" :key="index">
                        {{ item.time }} - {{ item.value }}°C
                    </li>
                </ul>
            </div>

            <div class="history-section">
                <h2>Speed History</h2>
                <ul>
                    <li v-for="(item, index) in speedHistory.slice().reverse()" :key="index">
                        {{ item.time }} - {{ item.value }} m/s
                    </li>
                </ul>
            </div>

            <div class="history-section">
                <h2>Distance History</h2>
                <ul>
                    <li v-for="(item, index) in distanceHistory.slice().reverse()" :key="index">
                        {{ item.time }} - {{ item.value }} m
                    </li>
                </ul>
            </div>

        </div>
    </div>    
</template>

<style scoped>
.diagnostics-page {
  background-color: #1f1f1f; /* Dark grey */
}

h2 {
    /* font-weight: bold; */
    margin-bottom: 15px;
}

.title {
    font-size: 25px;
    color: black;
    text-align: center;
    margin-bottom: 20px;
}

.history-container {
    display: flex;
    justify-content: space-between;
    gap: 20px;
    padding: 20px;
    font-family: sans-serif;
}

.history-section {
    flex: 1;
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
            this.temperatureHistory = JSON.parse(localStorage.getItem('temperatureHistory') || '[]');
            this.speedHistory = JSON.parse(localStorage.getItem('speedHistory') || '[]');
            this.distanceHistory = JSON.parse(localStorage.getItem('distanceHistory') || '[]');
        }
    }
};
</script>
