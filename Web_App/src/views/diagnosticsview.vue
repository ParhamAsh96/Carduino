<template>
    <div class="diagnostics-page">
        <h1 class="title">🏎️ Diagnostic History 🏎️</h1>

        <!-- Reverse loop with sessions.length - 1 - index -->
        <div v-for="(session, index) in sessions" :key="index" class="session-card">
            <h2>Session {{ sessions.length - index }} ({{ session.startTime }})</h2>
            <div class="session-data">
                <div>
                    <h3>🌡️ Temperature</h3>
                    <p>High: {{ session.hiTemp || 'N/A' }}°C</p>
                    <p>Low: {{ session.lowTemp || 'N/A' }}°C</p>
                </div>
                <div>
                    <h3>⏱️ Speed</h3>
                    <p>{{ session.speed || 'N/A' }} m/s</p>
                </div>
                <div>
                    <h3>🗺️ Distance</h3>
                    <p>{{ session.distance || 'N/A' }} m</p>
                </div>
            </div>
        </div>
    </div>
</template>

<script>
// localStorage.clear();
export default {
    data() {
        return {
            sessions: []
        }
    },
    mounted() {
        // Load sessions and reverse the array once
        this.sessions = JSON.parse(localStorage.getItem('diagnosticSessions') || []).reverse();
    }
};
</script>

<style scoped>
.diagnostics-page {
    background-color: #1f1f1f;
    padding: 20px;
}

.title {
    font-size: 25px;
    text-align: center;
    margin-bottom: 20px;
}

.session-card {
    background-color: #2d2d2d;
    border-radius: 8px;
    padding: 15px;
    margin-bottom: 20px;
}

.session-card h2 {
    color: #42b988;
    margin-bottom: 15px;
    font-size: 18px;
    border-bottom: 1px solid #42b988;
    padding-bottom: 5px;
}

.session-data {
    display: flex;
    gap: 30px;
}

.session-data div {
    flex: 1; /*flex div components to the entire page*/
}

.session-data h3 {
    color: #42b988;
    margin-bottom: 8px;
    font-size: 16px;
}

.session-data p {
    margin: 5px 0;
}
</style>