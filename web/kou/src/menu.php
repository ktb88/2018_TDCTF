<div class="menu">
	<div style="text-align: left; padding-left: 10px;font-size: 20px; font-style: bold;">(੭ ᐕ)੭*⁾⁾ Yagami Kou's Homepage </div><br>
	<a href="?p=home" class="menu_a">Home</a> <a href="?p=board" class="menu_a">Article</a>
	<?php
		if($_SESSION['is_login']!=1){
			echo '<a href="?p=login" class="menu_a">Login</a> <a href="?p=join" class="menu_a">Join</a>';
		}
		else{
			echo '<a href="?p=logout" class="menu_a">Logout</a>';
		}
	?>
</div>
