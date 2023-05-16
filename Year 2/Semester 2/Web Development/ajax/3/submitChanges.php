<?php
    $db=new PDO('sqlite:../database.db');
    $db->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);

    $stmt = $db->prepare('UPDATE Menu SET food = ?, price = ?, `description` = ? WHERE id = ?');
    $stmt->bindParam(1, $_POST['food'], PDO::PARAM_STR);
    $stmt->bindParam(2, $_POST['price'], PDO::PARAM_STR);
    $stmt->bindParam(3, $_POST['description'], PDO::PARAM_STR);
    $stmt->bindParam(4, $_POST['id'], PDO::PARAM_INT);

    $result=$stmt->execute();
    $result_size=$stmt->rowCount();
    if ($result_size>0)
        echo 'Updated';
    else
        echo 'Error';

?>