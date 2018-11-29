<?php
	$f = $_GET['f'];
	if(!is_array($f) && !is_null($f) && $f!=''){
		if($f[strlen($f)-1]=='/'){
			$f[strlen($f)-1]=='\0';
		}
		if(preg_match('/Secret Data/i',$f) && $_SESSION['admin']==1){
?>
	<div class="description">
		<p style="font-size: 20px;">Secret Data</p>
		<br><br>
		<pre><?php loadFile($f); ?></pre>
	</div>
<?php
		}else if(preg_match('/Secret Data/i',$f) && $_SESSION['admin']==0){
?>
	<div class="description">
		<p style="font-size: 20px;">Secret Data</p>
		<br><br>
		<pre>You're not admin.</pre>
	</div>
<?php
		}else{
?>
	<div class="description">
		<p style="font-size: 20px;"><?=$f;?></p>
		<br><br>
		<pre><?php loadFile($f); ?></pre>
	</div>
<?php
		}

	}else{
		echo '<script>alert("No found.");history.back();</script>';
	}
?>


