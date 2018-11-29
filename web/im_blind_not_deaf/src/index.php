<?php
include './config.php';
if(preg_match('tdf|/_|\.|\(\)/i', $_GET[pw])) exit("No Hack Please~! -0-"); 
if(preg_match('/or|and|substr\(|=/i', $_GET[pw])) exit("Manner Please~! :) :)"); 
$query = "select id from tdf where id='root' and pw='{$_GET[pw]}'"; 
echo "<hr>query : <strong>{$query}</strong><hr><br>";
$result = mysqli_query($conn,$query);
$row = mysqli_fetch_array($result);
if($row['id'] == 'root'){
#echo "<h2>Nice Meet You! {$row['id']}</h2>";
echo "<h2>Hello {$row[id]}</h2>";
}
 
$_GET[pw] = addslashes($_GET[pw]); 
$query = "select pw from tdf where id='root' and pw='{$_GET[pw]}'"; 
$result = mysqli_query($conn,$query);
$row = mysqli_fetch_array($result);
if(($row['pw']) && ($row['pw'] == $_GET['pw'])){
echo $nice_tendollar;
}
highlight_file(__FILE__); 
?>
