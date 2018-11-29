<div class="description"><br><br>
	<table class=board>
		<thead>
			<tr>
				<th style="width: 10%">*</th>
				<th style="width: 90%">Article</th>
			</tr>
		</thead>
		<tbody>
			<?php
				$fileList = array_reverse(glob('board/*'));
				for($i=0;$i<sizeof($fileList);$i++){
					$f = explode('/',$fileList[$i])[1];
			?>
			<tr>
				<th><?=(sizeof($fileList)-$i)?></th>
				<th><a href="?p=view&f=<?=$f?>" style="text-decoration: none;"><?=$f?></a></th>
			</tr>
			<?php
				}
			?>
		</tbody>
	</table>
</div>