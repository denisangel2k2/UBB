<?php
$sql = "SELECT * FROM Users";
    $db_file = '../database.db';

    
    $pdo = new PDO("sqlite:" . $db_file);
    $pdo->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);

    
    $statement = $pdo->prepare($sql);
    $statement->execute();

    $users=$statement->fetchAll(PDO::FETCH_ASSOC);

    $startIndex=$_GET['startIndex'];

    $index=-1;
    foreach ($users as $user){
        $index++;
        if ($index<($startIndex+3) && $index>=$startIndex){
            echo "<tr>";
            echo "<td>".$user['nume']."</td>";
            echo "<td>".$user['prenume']."</td>";
            echo "<td>".$user['email']."</td>";
            echo "<td>".$user['telefon']."</td>";
        }
        if ($index>=($startIndex+3)){
            break;
        }
    }
?>