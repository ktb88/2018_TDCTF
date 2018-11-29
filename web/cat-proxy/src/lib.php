<?php
	ini_set('phar.readonly',0);
    class Requests{
        public $url;

        function __construct($url){
            $this->url = $url;
        }
        function __destruct(){
            $ch = curl_init();
            curl_setopt($ch, CURLOPT_URL, $this->url);
            curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
            $output = curl_exec($ch);
            echo '<div class="description">'.$output.'</div>';
        }
    }
?>
