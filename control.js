// ========================================
// Variables
// ========================================

let currentPumpState = "OFF";


// ========================================
// Get Current Sensor Data
// ========================================

function getControlData() {

    fetch("get_data.php")

        .then(response => response.json())

        .then(data => {

            if (data.error) {
                return;
            }

            let humidity = parseFloat(data.humidity);

            document.getElementById("currentHumidity").innerText =
                humidity.toFixed(1) + " %";


            // ========================================
            // AUTOMATIC CONTROL
            // ========================================

            if (humidity < 75) {

                // Pump should be ON
                if (currentPumpState !== "ON") {

                    automaticPump("start");

                }

            } 
            else if (humidity > 80) {

                // Pump should be OFF
                if (currentPumpState !== "OFF") {

                    automaticPump("stop");

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

            console.log("Automatic:", data.message);

            if (action === "start") {

                currentPumpState = "ON";

                document.getElementById("pumpStatus").innerText = "ON";
                document.getElementById("manualPumpStatus").innerText = "ON";

            } 
            else {

                currentPumpState = "OFF";

                document.getElementById("pumpStatus").innerText = "OFF";
                document.getElementById("manualPumpStatus").innerText = "OFF";
            }

        })

        .catch(error => {

            console.error("Automatic Pump Error:", error);

        });
}


// ========================================
// Start Pump - Manual
// ========================================

function startPump() {

    fetch("control.php?device=pump&action=start")

        .then(response => response.json())

        .then(data => {

            alert(data.message);

            currentPumpState = "ON";

            document.getElementById("pumpStatus").innerText = "ON";
            document.getElementById("manualPumpStatus").innerText = "ON";

        })

        .catch(error => {

            console.error("Pump Error:", error);

        });

}


// ========================================
// Stop Pump - Manual
// ========================================

function stopPump() {

    fetch("control.php?device=pump&action=stop")

        .then(response => response.json())

        .then(data => {

            alert(data.message);

            currentPumpState = "OFF";

            document.getElementById("pumpStatus").innerText = "OFF";
            document.getElementById("manualPumpStatus").innerText = "OFF";

        })

        .catch(error => {

            console.error("Pump Error:", error);

        });

}


// ========================================
// Start
// ========================================

getControlData();

setInterval(getControlData, 2000);