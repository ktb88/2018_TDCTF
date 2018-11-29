<?php
	session_start();
?>
<!DOCTYPE html>
<html>
<head>
	<title>CAT Proxy</title>
	<link rel=stylesheet href="index.css">
</head>
<body>
    <div class="menu">
        <div style="text-align: left; padding-left: 50px;font-size: 20px; font-style: bold;">Cat Proxy</div><br>
        <a href="?p=home" class="menu_a">Home</a>
        <?php
            if($_SESSION['is_login']!=1){
                echo '<a href="?p=login" class="menu_a">Login</a> <a href="?p=join" class="menu_a">Join</a>';
            }
            else{
                echo '<a href="?p=nyaa" class="menu_a">Nyaa</a> <a href="?p=profile" class="menu_a">Profile</a> <a href="?p=logout" class="menu_a">Logout</a>';
            }
        ?>
    </div>