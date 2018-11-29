<?php
    if($_SESSION['is_login'] !==1 ) die("<script>alert('Login please.');history.back();</script>");
?>
<div class="description"><br><br>
    Result : <br><br>
    <?php 
        $url = $_POST['url'];
        if(preg_match('/phar|zip|gopher|php|dict|iter|glob|ftp|file|%0d|%0a/i',$url)){
            echo "Hacking Detected!<br>What's are you doing now nyaa?!";
        }else{
            $obj = new Requests($url);
        }
    ?>
</div>