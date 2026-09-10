<?php
?>

<!DOCTYPE html>
<html>

<head>

<meta charset="UTF-8">

<title>MycoCare Control</title>

<link rel="stylesheet" href="style.css">

</head>


<body>


<!-- Sidebar -->

<div class="sidebar">

    <h2>🍄 MycoCare</h2>

    <p>IoT Mushroom System</p>

    <ul>

        <li>
            <a href="index.html">Dashboard</a>
        </li>

        <li>
            <a href="history.php">History</a>
        </li>

        <li class="active">
            <a href="control_page.php">Control</a>
        </li>

        <li>
            <a href="profile.php">Profile</a>
        </li>

    </ul>

</div>



<!-- Main -->

<div class="main">

    <header>

        <div>

            <h1>System Control</h1>

            <p>Control Mushroom Cultivation System</p>

        </div>

        <div class="online">

            ● System Online

        </div>

    </header>
    <div class="control-container">
        <!-- Automatic Control -->
        <div class="control-panel">
            <h3>🤖 Automatic Control</h3>

            <p>The system automatically controls the water pump based on humidity level.</p>

            <div class="status-row">
                <span>Control Mode</span>
                <b id="modeStatus">Automatic</b>
            </div>

            <div class="status-row">
                <span>Temperature</span>
                <b id="currentTemperature">-- °C</b>
            </div>

            <div class="status-row">
                <span>Humidity</span>
                <b id="currentHumidity">-- %</b>
            </div>

            <div class="status-row">
                <span>Water Pump</span>
                <b id="pumpStatus">OFF</b>
            </div>

            <p class="rule">
                Humidity below 75% → Pump ON<br>
                Humidity above 80% → Pump OFF
            </p>
        </div>


    <!-- Manual Control -->
        <div class="control-panel">
            <h3>🚿 Manual Control</h3>

            <p>Manually control the water pump.</p>

            <div class="manual-status">
                Pump Status:
                <b id="manualPumpStatus">OFF</b>
            </div>

            <button onclick="startPump()">Start Pump</button>

            <button onclick="stopPump()">Stop Pump</button>
        </div>
    </div>

</div>


</div>


<script src="control.js"></script>

</body>

</html>