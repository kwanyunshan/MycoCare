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

        })

        .catch(error => {

            console.error("Control Data Error:", error);

        });
}


// ========================================
// Start Pump
// ========================================

function startPump() {

    fetch("control.php?device=pump&action=start")

        .then(response => response.json())

        .then(data => {

            alert(data.message);

            document.getElementById("pumpStatus").innerText = "ON";

        })

        .catch(error => {

            console.error("Pump Error:", error);

        });

}


// ========================================
// Stop Pump
// ========================================

function stopPump() {

    fetch("control.php?device=pump&action=stop")

        .then(response => response.json())

        .then(data => {

            alert(data.message);

            document.getElementById("pumpStatus").innerText = "OFF";

        })

        .catch(error => {

            console.error("Pump Error:", error);

        });

}


// ========================================
// Update Humidity
// ========================================

getControlData();

setInterval(getControlData, 2000);