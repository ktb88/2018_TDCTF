<?php
error_reporting(0);
$conn = mysqli_connect('im_blind_not_deaf_db_1','root','@1@2@3@4qwerasdf','tdf');
if (!$conn){
	echo "connection fali";
}

$nice_tendollar="Congraturation!!!!"."<br>"."Next Question: LFI(Local File Inclusion) in "."phpMyAdmin 4.8.0~4.8.1..."."<br>"." URL:phpmyadmin/index.php.........   flag.txt"."<br>"."root's password:@1@2@3@4qwerasdf"."<br>";
?>
