<?php
	$id = $_POST['id'];
	$pw = $_POST['pw'];
	if($id!='' && $pw!='' && strlen($id) < 32 && strlen($pw) < 32 ){
        $id = $mysql->real_escape_string($id);
        $pw = $mysql->real_escape_string($pw);
        $sql = "SELECT * FROM users WHERE id='".$id."' AND pw='".$pw."'";
        $result = $mysql->query($sql);
		if($result->num_rows){
            $row = $result->fetch_assoc();
            $_SESSION['is_login'] = 1;
            $_SESSION['id'] = $row['id'];
            $_SESSION['avatar'] = $row['thumb'];
			echo '<script>alert("Login Success.");location.href="?p=home";</script>';
		}else{
			echo '<script>alert("Login Fail.");history.back();</script>';
		}
	}else{
		die('<script>alert("Please input id and pw in 32 characters.");history.back();</script>');
	}
?>