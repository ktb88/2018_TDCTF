<?php
    if($_SESSION['is_login'] !==1 ) die("<script>alert('Login please.');history.back();</script>");
?>
<div class="description"><br><br>
	<form enctype="multipart/form-data" action="?p=uploadThumb" method="post">
		<table class="loginform">
			<tr>
				<td colspan=2 style="text-align: left;"><img src="uploads/<?=$_SESSION['avatar'];?>" style="height: 100px; width: 100px; object-fit: contain; vertical-align: middle; border: 1px solid #000000;"></td><td style="text-align: left;">ID : <?=$_SESSION['id'];?></td>
			</tr>
			<tr>
                <td>Update Avatar : </td>
                <td colspan=2 style="text-align: right;"><input type="file" name="thumb" value="upload"><input type="submit" value="upload"></td>
			</tr>
		</table>
	</form>
</div>