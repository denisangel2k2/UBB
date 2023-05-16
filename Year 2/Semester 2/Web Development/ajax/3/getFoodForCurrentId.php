<?php
    $db=new PDO('sqlite:../database.db');
    $db->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);

    $stmt = $db->prepare('SELECT * FROM Menu WHERE id = ?');
    $stmt->bindParam(1, $_GET['id'], PDO::PARAM_INT);

    $stmt->execute();

    $food=$stmt->fetchAll();
    
    echo '<input type="text" id="id" placeholder="id" value="'.$food[0]['id'].'" disabled="true">';
    echo '<input type="text" id="food" placeholder="food" value="'.$food[0]['food'].'">';
    echo '<input type="text" id="price" placeholder="price" value="'.$food[0]['price'].'">';
    echo '<input type="text" id="description" placeholder="description" value="'.$food[0]['description'].'">';
    echo '<input type="submit" onclick="updateFood()" value="Submit" id="submit">';
?>