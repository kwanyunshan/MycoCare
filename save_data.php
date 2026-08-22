<?php

include "db_connect.php";

if (
    isset($_GET["temperature"]) &&
    isset($_GET["humidity"]) &&
    isset($_GET["air_quality"])
) {

    $temperature = $_GET["temperature"];
    $humidity = $_GET["humidity"];
    $air_quality = $_GET["air_quality"];

    $sql = "INSERT INTO sensor_data (temperature, humidity, air_quality)
            VALUES ('$temperature', '$humidity', '$air_quality')";

    if ($conn->query($sql) === TRUE) {

        echo "Data saved successfully";

    } else {

        echo "Error: " . $conn->error;

    }

} else {

    echo "No sensor data received";

}

$conn->close();

?>