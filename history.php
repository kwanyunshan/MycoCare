<?php

require_once "db_connect.php";

// Get all sensor data, newest first
$sql = "SELECT * FROM sensor_data ORDER BY id DESC";

$result = $conn->query($sql);

?>

<!DOCTYPE html>
<html>

<head>

<meta charset="UTF-8">

<title>MycoCare History</title>

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

        <li class="active">
            <a href="history.php">History</a>
        </li>

        <li>
            <a href="control_page.php">Control</a>
        </li>

        <li>
            <a href="profile.php">Profile</a>
        </li>

    </ul>

</div>



<!-- Main Content -->

<div class="main">

    <header>

        <div>

            <h1>Sensor Data History</h1>

            <p>Historical Environmental Monitoring Data</p>

        </div>

        <div class="online">
            ● System Online
        </div>

    </header>

<br><br>
    <h2>Environmental Data History</h2>


    <div class="history-card">

        <table>

            <thead>

                <tr>

                    <th>ID</th>
                    
                    <th>Temperature</th>
                    
                    <th>Humidity</th>
                    
                    <th>Air Quality</th>

                    <th>Date & Time</th>
                   
                </tr>

            </thead>

            <tbody>

            <?php

            if ($result && $result->num_rows > 0) {

                while ($row = $result->fetch_assoc()) {

            ?>

                <tr>

                    <td>
                        <?php echo $row['id']; ?>
                    </td>

                    <td>
                        <?php echo $row['temperature']; ?> °C
                    </td>

                    <td>
                        <?php echo $row['humidity']; ?> %
                    </td>

                    <td>
                        <?php echo $row['air_quality']; ?>
                    </td>

                    <td>
                        <?php echo $row['created_at']; ?>
                    </td>

                </tr>

            <?php

                }

            } else {

            ?>

                <tr>

                    <td colspan="5">
                        No sensor data available.
                    </td>

                </tr>

            <?php

            }

            ?>

            </tbody>

        </table>

    </div>


</div>


</body>

</html>