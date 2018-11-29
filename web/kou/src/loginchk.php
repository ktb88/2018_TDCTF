<?php
	$id = $_POST['id'];
	$pw = $_POST['pw'];
	if($id!='' && $pw!=''){
		if(preg_match('/kou/i',$id)){
			die('<script>alert("Don\'t login at kou.");history.back();</script>');
		}
		if(login($id,$pw)){
			$_SESSION['is_login'] = 1;
			$_SESSION['admin'] = 1;
			echo '<script>alert("Login Success.");location.href="?p=home";</script>';
		}else{
			echo '<script>alert("Login Fail.");history.back();</script>';
		}
	}else{
		echo '<script>alert("Login Fail.");history.back();</script>';
	}
?>
