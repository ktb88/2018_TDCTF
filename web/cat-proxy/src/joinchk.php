<?php
    $id = $_POST['id'];
	$pw = $_POST['pw'];
	if($id!='' && $pw!='' && strlen($id) < 32 && strlen($pw) < 32 ){
        $id = $mysql->real_escape_string($id);
        $pw = $mysql->real_escape_string($pw);
        $sql = "SELECT * FROM users WHERE id='".$id."'";
        $result = $mysql->query($sql);
        if($result->num_rows){
            die('<script>alert("Already exist ID.");history.back();</script>');
        }
        $sql = "INSERT INTO users VALUES('".$id."','".$pw."','default.png');";
        $result = $mysql->query($sql);
		if($result===TRUE){
			echo '<script>alert("Join Success.");location.href="?p=home";</script>';
		}else{
			echo '<script>alert("Join Fail.");history.back();</script>';
		}
	}else{
		die('<script>alert("Please input id and pw in 32 characters.");history.back();</script>');
    }
?>