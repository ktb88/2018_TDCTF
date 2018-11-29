<?php
    if($_SESSION['is_login'] !==1 ) die("<script>alert('Login please.');history.back();</script>");
    chdir('uploads');
    $allowExt = Array('jpg','jpeg','png','gif');
    $fname = $_FILES['thumb']['name'];
    $fname = array_pop(explode('./',$fname));
    if(file_exists(urldecode($fname))){
        
        echo "<script>alert('Already uploaded file.\\nPlease change filename.');history.back();</script>";
    }else{
        $ext = strtolower(array_pop(explode('.',$fname)));
        if($_FILES['thumb']['error'] !== 0){
            die("<script>alert('Upload Error!');history.back();</script>");
        }
        if(!in_array($ext, $allowExt)){
            die("<script>alert('Sorry, not allow extension.');history.back();</script>");
        }

        $contents = file_get_contents($_FILES['thumb']['tmp_name']);
        
        if($ext=="jpg"){
            if(substr($contents,0,4)!="\xFF\xD8\xFF") die("<script>alert('JPG is corrupted.\\nSorry.');history.back();</script>");
        }else if($ext=="jpeg"){
            if(substr($contents,0,4)!="\xFF\xD8\xFF") die("<script>alert('JPEG is corrupted.\\nSorry.');history.back();</script>");
        }else if($ext=="png"){
            if(substr($contents,0,4)!="\x89PNG") die("<script>alert('PNG is corrupted.\\nSorry.');history.back();</script>");
        }else if($ext=="gif"){
            if(substr($contents,0,4)!="GIF8") die("<script>alert('GIF is corrupted.\\nSorry.');history.back();</script>");
        }else{
            die("<script>alert('Something error.\\nSorry.');history.back();</script>");
        }

        @move_uploaded_file($_FILES['thumb']['tmp_name'], $fname);
        
        $id = $mysql->real_escape_string($_SESSION['id']);
		$sql = "UPDATE users SET thumb='".$mysql->real->escape_string($fname)."' WHERE id='".$id."';";
        $result = $mysql->query($sql);
        if($result===TRUE){
            $_SESSION['avatar'] = $fname;
            echo("<script>alert('Successfully Avatar Change!');history.back();</script>");    
        }else{
            echo("<script>alert('Upload failed!');history.back();</script>");    
        }
    }
?>
