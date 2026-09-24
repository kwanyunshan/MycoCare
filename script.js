// ========================================
// Get Sensor Data
// ========================================

function getSensorData() {

    fetch("get_data.php")

        .then(response => response.json())

        .then(data => {

            // Temperature
            document.getElementById("temperature").innerText =
                parseFloat(data.temperature).toFixed(1) + " °C";


            // Humidity
            document.getElementById("humidity").innerText =
                parseFloat(data.humidity).toFixed(1) + " %";


            // Air Quality
            document.getElementById("airQuality").innerText =
                data.air_quality;


            // Water Level
            document.getElementById("waterLevel").innerText =
                data.water_level;


            // Check Water Level
            checkWaterLevel(data.water_level);

        })

        .catch(error => {

            console.error("Sensor Data Error:", error);

        });
}


// ========================================
// Check Water Level
// ========================================

function checkWaterLevel(level) {

    const waterStatus =
        document.getElementById("waterStatus");


    // Change this value after testing sensor
    const LOW_WATER_LEVEL = 1500;


    if (level <= LOW_WATER_LEVEL) {

        waterStatus.innerText = "⚠️ Low Water Level";

        waterStatus.style.color = "red";

        showWaterAlert();

    } else {

        waterStatus.innerText = "Normal Water Level";

        waterStatus.style.color = "green";

        closeWaterAlert();

    }

}


// ========================================
// Show Water Alert
// ========================================

function showWaterAlert() {

    const alertBox =
        document.getElementById("waterAlert");

    alertBox.style.display = "flex";

}


// ========================================
// Close Water Alert
// ========================================

function closeWaterAlert() {

    const alertBox =
        document.getElementById("waterAlert");

    alertBox.style.display = "none";

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
// Immediately Get Data
// ========================================

getSensorData();


// ========================================
// Update Every 2 Seconds
// ========================================

setInterval(getSensorData, 2000);