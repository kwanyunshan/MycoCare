<?php

include "db_connect.php";

if (
    isset($_GET["temperature"]) &&
    isset($_GET["humidity"]) &&
    isset($_GET["air_quality"]) &&
    isset($_GET["water_level"])
) {

    $temperature = filter_input(
        INPUT_GET,
        "temperature",
        FILTER_VALIDATE_FLOAT
    );

    $humidity = filter_input(
        INPUT_GET,
        "humidity",
        FILTER_VALIDATE_FLOAT
    );

    $air_quality = filter_input(
        INPUT_GET,
        "air_quality",
        FILTER_VALIDATE_INT
    );

    $water_level = filter_input(
        INPUT_GET,
        "water_level",
        FILTER_VALIDATE_INT
    );


    if (
        $temperature === false ||
        $humidity === false ||
        $air_quality === false ||
        $water_level === false
    ) {

        echo "Invalid sensor data";
        exit();
    }


    $sql = "INSERT INTO sensor_data
            (temperature, humidity, air_quality, water_level)
            VALUES (?, ?, ?, ?)";


    $stmt = $conn->prepare($sql);


    if ($stmt) {

        $stmt->bind_param(
            "ddii",
            $temperature,
            $humidity,
            $air_quality,
            $water_level
        );


        if ($stmt->execute()) {

            echo "Data saved successfully";

        } else {

            echo "Error saving data";
        }


        $stmt->close();

    } else {

        echo "Database prepare error";
    }


} else {

    echo "No sensor data received";
}


$conn->close();

?>