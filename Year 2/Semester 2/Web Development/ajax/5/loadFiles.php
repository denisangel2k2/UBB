<?php
    $dir_name=$_GET['q'];
    if (is_file($dir_name)){
        echo "<div onclick=loadDir('../..') class='file'>..</div>";
        echo strip_tags(file_get_contents($dir_name),"<html>");
        exit();
    }
    $filesInDir=scandir($dir_name);
    foreach($filesInDir as $file){
        echo "<li><div onclick=loadDir('" . $_GET["q"] . "/" . $file . "')>" . $file . "</div></li>";
    }

?>