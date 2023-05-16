<?php
// create a PDO object for connecting to the database
$db_file = '../database.db';

        
        $pdo = new PDO("sqlite:" . $db_file);
        $pdo->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);

        $sql = "SELECT `to` FROM routes WHERE `from` = :fr";
        $stmt = $pdo->prepare($sql);
        $stmt->bindParam(':fr', $_GET['q']);
        
        $stmt->execute();
        $destinations = $stmt->fetchAll(PDO::FETCH_ASSOC);
        foreach ($destinations as $destination) {
            echo "<option value='" . $destination['to'] . "'>" . $destination['to'] . "</option>";
        }

?>