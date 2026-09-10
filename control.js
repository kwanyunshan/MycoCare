// ========================================
// MycoCare Control System
// ========================================

// Current pump state
let currentPumpState = "OFF";


// ========================================
// Get Current Sensor Data
// ========================================

function getControlData() {

    fetch("get_data.php")

        .then(response => response.json())

        .then(data => {

            // Check for error
            if (data.error) {
                console.error("Sensor Data Error:", data.error);
                return;
            }


            // ========================================
            // TEMPERATURE
            // ========================================

            let temperature = parseFloat(data.temperature);

            if (!isNaN(temperature)) {

                document.getElementById("currentTemperature").innerText =
                    temperature.toFixed(1) + " °C";

            }


            // ========================================
            // HUMIDITY
            // ========================================

            let humidity = parseFloat(data.humidity);

            if (!isNaN(humidity)) {

                document.getElementById("currentHumidity").innerText =
                    humidity.toFixed(1) + " %";

            }


            // ========================================
            // AUTOMATIC CONTROL
            // ========================================

            if (!isNaN(humidity)) {

                // Humidity below 75%
                // Pump ON

                if (humidity < 75) {

                    if (currentPumpState !== "ON") {

                        automaticPump("start");

                    }

                }


                // Humidity above 80%
                // Pump OFF

                else if (humidity > 80) {

                    if (currentPumpState !== "OFF") {

                        automaticPump("stop");

                    }

                }


                // Humidity between 75% and 80%
                // Keep current pump state

                else {

                    console.log(
                        "Humidity is within normal range. Keep current pump state."
                    );

                }

            }

        })

        .catch(error => {

            console.error("Control Data Error:", error);

        });

}


// ========================================
// Automatic Pump Control
// ========================================

function automaticPump(action) {

    fetch("control.php?device=pump&action=" + action)

        .then(response => response.json())

        .then(data => {

            console.log("Automatic Control:", data);


            // ========================================
            // Pump ON
            // ========================================

            if (action === "start") {

                currentPumpState = "ON";

                document.getElementById("pumpStatus").innerText =
                    "ON";

                document.getElementById("manualPumpStatus").innerText =
                    "ON";

            }


            // ========================================
            // Pump OFF
            // ========================================

            else if (action === "stop") {

                currentPumpState = "OFF";

                document.getElementById("pumpStatus").innerText =
                    "OFF";

                document.getElementById("manualPumpStatus").innerText =
                    "OFF";

            }

        })

        .catch(error => {

            console.error("Automatic Pump Error:", error);

        });

}


// ========================================
// Manual Start Pump
// ========================================

function startPump() {

    fetch("control.php?device=pump&action=start")

        .then(response => response.json())

        .then(data => {

            console.log("Manual Start:", data);

            alert(data.message);


            // Update pump state

            currentPumpState = "ON";


            // Update Automatic Control status

            document.getElementById("pumpStatus").innerText =
                "ON";


            // Update Manual Control status

            document.getElementById("manualPumpStatus").innerText =
                "ON";

        })

        .catch(error => {

            console.error("Manual Start Pump Error:", error);

        });

}


// ========================================
// Manual Stop Pump
// ========================================

function stopPump() {

    fetch("control.php?device=pump&action=stop")

        .then(response => response.json())

        .then(data => {

            console.log("Manual Stop:", data);

            alert(data.message);


            // Update pump state

            currentPumpState = "OFF";


            // Update Automatic Control status

            document.getElementById("pumpStatus").innerText =
                "OFF";


            // Update Manual Control status

            document.getElementById("manualPumpStatus").innerText =
                "OFF";

        })

        .catch(error => {

            console.error("Manual Stop Pump Error:", error);

        });

}


// ========================================
// Start System
// ========================================

getControlData();


// ========================================
// Update Sensor Data Every 2 Seconds
// ========================================

setInterval(getControlData, 2000);