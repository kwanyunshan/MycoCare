<!DOCTYPE html>
<html>

<head>

<meta charset="UTF-8">

<title>MycoCare Profile</title>

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

        <li>
            <a href="control_page.php">Control</a>
        </li>

        <li class="active">
            <a href="profile.php">Profile</a>
        </li>

    </ul>

</div>


<!-- Main -->

<div class="main">

    <header>

        <div>

            <h1>Profile</h1>

            <p>MycoCare User Profile</p>

        </div>

        <div class="online">
            ● System Online
        </div>

    </header>


    <!-- Profile -->

    <div class="profile-container">

        <div class="profile-card">

            <div class="profile-icon">
                👤
            </div>

            <h2>MycoCare Administrator</h2>

            <p class="role">System Administrator</p>

            <hr>

            <div class="profile-info">

                <div>
                    <span>Name</span>
                    <b>MycoCare Admin</b>
                </div>

                <div>
                    <span>Email</span>
                    <b>admin@mycocare.com</b>
                </div>

                <div>
                    <span>Role</span>
                    <b>Administrator</b>
                </div>

                <div>
                    <span>Status</span>
                    <b class="status">Active</b>
                </div>

            </div>

            <button>Edit Profile</button>

        </div>


        <!-- System Information -->

        <div class="profile-card">

            <h2>⚙️ System Information</h2>

            <div class="profile-info">

                <div>
                    <span>System Name</span>
                    <b>MycoCare</b>
                </div>

                <div>
                    <span>System Type</span>
                    <b>IoT Mushroom Cultivation</b>
                </div>

                <div>
                    <span>Controller</span>
                    <b>ESP32</b>
                </div>

                <div>
                    <span>Temperature Sensor</span>
                    <b>DHT22</b>
                </div>

                <div>
                    <span>Air Quality Sensor</span>
                    <b>MQ135</b>
                </div>

                <div>
                    <span>Database</span>
                    <b>MySQL</b>
                </div>

            </div>

        </div>

    </div>

</div>

</body>

</html>