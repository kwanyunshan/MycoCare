<?php

include "db_connect.php";

$sql = "SELECT * FROM sensor_data ORDER BY id DESC LIMIT 1";

$result = $conn->query($sql);

if ($result->num_rows > 0) {

    $row = $result->fetch_assoc();

    echo json_encode($row);

} else {

    echo json_encode([
        "temperature" => 0,
        "humidity" => 0,
        "air_quality" => 0
    ]);
}

$conn->close();

?>