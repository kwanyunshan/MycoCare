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
            console.error("Error:", error);
        });
}


// Immediately get data
getSensorData();


// Update Dashboard every 2 seconds
setInterval(getSensorData, 2000);