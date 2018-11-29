<?php
	session_start();
?>
<!DOCTYPE html>
<html>
<head>
	<title>Yagami Kou's Homepage</title>
	<link rel=stylesheet href="index.css">
</head>
<body>
	<?php
		@include_once('menu.php');
	?>
	<br>
	<?php
		$pageList = array(
			'home',
			'login',
			'loginchk',
			'logout',
			'view',
			'board',
			'join'
		);
		if(in_array($_GET['p'], $pageList)) {
		  @include_once($_GET['p'].'.php');
		} else {
		  @include_once('home.php');
		}		
	?>
</body>
</html>