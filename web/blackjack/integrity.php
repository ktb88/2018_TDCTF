<!DOCTYPE html>
<html>
<head>
    <title>
    <?php
        error_reporting(0);
        $conn = mysqli_connect('localhost','db_bj','db_password','auth');

        if(isset($_POST['hash'])) {
            if(strlen($_POST['hash']) < 12 || !isMobile()) echo("You don't have enough money! ;(");
            else if($_POST['hash'][0] == '0') echo("You have no money! :P");
            else if(preg_match("/[^0-9a-zA-Z<>]/", $_POST['hash'])) echo("sir, ID Card please. :)");
            else {
                $query = mysqli_query($conn, "SELECT hash, flag FROM hash_table WHERE hash=$_POST[hash]") or die("get away! :<");
                $data = mysqli_fetch_array($query);
                if($_POST['hash'] == "201061090121") echo("Oh, This is it. :D");
                else if($data[0] === "221061099042") echo("Flag is................................................................integrity.php.backup.201810");
                else if($data[0] === "10_dollar") echo("Flag is TDCTF{{$data[1]}}");
                else echo("Nice try!");
            }   
        } else {
            echo("BlackJack!");
        }   

    function isMobile() {
        return preg_match("/(android|avantgo|blackberry|bolt|boost|cricket|docomo|fone|hiptop|mini|mobi|palm|phone|pie|tablet|up\.browser|up\.link|webos|wos)/i", $_SERVER["HTTP_USER_AGENT"]);
    }   

    ?> 
    </title>
    <style type="text/css">
        body {
            background-color: #FFFFFF;
            background-image: url("back.gif");
            text-align: center;
            vertical-align: middle;
        }   
    </style>
</head>
<body>
    <img src=hack.png>
</body>
</html>
