<?php
//	error_reporting(0);
    $host = "cat-proxy_db_1";
    $user = "cat";
    $db_schema = "cat";
	$port = 3306;
    $mysql = new mysqli($host, $user, "", $db_schema,$port);
    $mysql->query("SET NAMES utf8");

    
?>
