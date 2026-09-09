<?php

header("Content-Type: application/json");

include "db_connect.php";

$device = $_GET["device"] ?? "";
$action = $_GET["action"] ?? "";

if ($device !== "pump") {
    echo json_encode([
        "success" => false,
        "message" => "Invalid device"
    ]);
    exit;
}

if ($action === "start") {

    $status = "ON";

} elseif ($action === "stop") {

    $status = "OFF";

} else {

    echo json_encode([
        "success" => false,
        "message" => "Invalid action"
    ]);
    exit;
}

$sql = "UPDATE device_control 
        SET pump_status = '$status'
        WHERE id = 1";

if ($conn->query($sql)) {

    echo json_encode([
        "success" => true,
        "message" => "Pump turned $status",
        "pump_status" => $status
    ]);

} else {

    echo json_encode([
        "success" => false,
        "message" => "Database update failed"
    ]);
}

$conn->close();

?>