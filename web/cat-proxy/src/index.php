<?php
	error_reporting(0);
    include('config.php');
    include('lib.php');
    include('header.php');
    $page = $_GET['p'];
    if(is_null($page) || is_array($page)|| $page==''){
        $page = 'home';
    }else{
        if(preg_match('/phar|zip|gopher|file:|\.\.|dict|iter|glob|ftp/i',$page)){
            $page = 'home';
        }
    }
    include($page.'.php');
    include('footer.php');
?>
