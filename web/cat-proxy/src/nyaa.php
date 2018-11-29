<?php
    if($_SESSION['is_login'] !==1 ) die("<script>alert('Login please.');history.back();</script>");
?>
<div class="description"><br><br>
	<form action="?p=nyaaa" method="post">
        <center>Cat is going to anywhere!!!</center><br><br>
		<table class="loginform">
			<tr>
                <td>URL : </td>
                <td><input type="text" name="url" size="80"></td>
			</tr>
			<tr>
                <td colspan=2 style="align: right;"><input type="submit" value="Request"></td>
			</tr>
		</table>
	</form>
</div>