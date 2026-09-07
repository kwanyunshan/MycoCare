<?php

include "db_connect.php";

if (
    isset($_GET["temperature"]) &&
    isset($_GET["humidity"]) &&
    isset($_GET["air_quality"])
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

    if (
        $temperature === false ||
        $humidity === false ||
        $air_quality === false
    ) {

        echo "Invalid sensor data";
        exit();
    }

    $sql = "INSERT INTO sensor_data
            (temperature, humidity, air_quality)
            VALUES (?, ?, ?)";

    $stmt = $conn->prepare($sql);

    if ($stmt) {

        $stmt->bind_param(
            "ddi",
            $temperature,
            $humidity,
            $air_quality
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