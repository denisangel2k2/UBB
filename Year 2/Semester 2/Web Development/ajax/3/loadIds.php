<?php
    $db=new PDO("sqlite:../database.db");
    $db->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);

    $stmt = $db->prepare('SELECT id FROM Menu');
    $stmt->execute();

    $ids=$stmt->fetchAll();

    foreach($ids as $id){
        echo '<li onclick="loadForm('.$id['id'].')">'.$id['id'].'</li>';
    }
?>