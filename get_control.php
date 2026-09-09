<?php

header("Content-Type: application/json");

include "db_connect.php";

$sql = "SELECT pump_status, mode FROM device_control WHERE id = 1";

$result = $conn->query($sql);

if ($result && $result->num_rows > 0) {

    $data = $result->fetch_assoc();

    echo json_encode([
        "success" => true,
        "pump_status" => $data["pump_status"],
        "mode" => $data["mode"]
    ]);

} else {

    echo json_encode([
        "success" => false,
        "message" => "No control data"
    ]);
}

$conn->close();

?>