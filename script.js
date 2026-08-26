// ========================================
// Get Sensor Data
// ========================================

function getSensorData() {

    fetch("get_data.php")

        .then(response => response.json())

        .then(data => {

            document.getElementById("temperature").innerText =
                parseFloat(data.temperature).toFixed(1) + " °C";


            document.getElementById("humidity").innerText =
                parseFloat(data.humidity).toFixed(1) + " %";


            document.getElementById("airQuality").innerText =
                data.air_quality;

        })

        .catch(error => {
            console.error("Sensor Data Error:", error);
        });
}


// ========================================
// Control Pump
// ========================================

function controlPump() {

    fetch("control.php?device=pump&action=start")

        .then(response => response.json())

        .then(data => {

            console.log(data);

            alert(data.message);

        })

        .catch(error => {

            console.error("Pump Control Error:", error);

        });
}


// ========================================
// Control Fan
// ========================================

function controlFan() {

    fetch("control.php?device=fan&action=toggle")

        .then(response => response.json())

        .then(data => {

            console.log(data);

            alert(data.message);

        })

        .catch(error => {

            console.error("Fan Control Error:", error);

        });
}


// ========================================
// Immediately Get Data
// ========================================

getSensorData();


// ========================================
// Update Every 2 Seconds
// ========================================

setInterval(getSensorData, 2000);