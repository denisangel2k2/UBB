<?php
    $connection=new PDO("sqlite:../database.db");
    $connection->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);


    $laptops=array();

    if (isset($_GET["cpu"])) {
        $cpus=$_GET["cpu"];
        
        foreach($cpus as $cpu){
            $sql="SELECT * FROM Laptops WHERE cpu = :cpu";
            $statement=$connection->prepare($sql);
            $statement->bindParam(":cpu", $cpu);
            $statement->execute();
            $laptops=array_merge($laptops, $statement->fetchAll());
        }
    }
    if (isset($_GET["gpu"])){
        $gpus=$_GET["gpu"];
        foreach($gpus as $gpu){
            $sql="SELECT * FROM Laptops WHERE gpu = :gpu";
            $statement=$connection->prepare($sql);
            $statement->bindParam(":gpu",$gpu);
            $statement->execute();
            $laptops=array_merge($laptops, $statement->fetchAll(PDO::FETCH_ASSOC));
        }
    }
    if (isset($_GET["hdd_capacity"])){
        $hdds=$_GET["hdd_capacity"];
        foreach($hdds as $hdd){
            $sql="SELECT * FROM Laptops WHERE hdd_capacity = :hdd_capacity";
            $statement=$connection->prepare($sql);
            $statement->bindValue(":hdd_capacity", $hdd, PDO::PARAM_INT);
            $statement->execute();
            $laptops=array_merge($laptops, $statement->fetchAll(PDO::FETCH_ASSOC));
        }
    }
    if (isset($_GET["producer"])){
        $producers=$_GET["producer"];
        foreach($producers as $producer){
            $sql="SELECT * FROM Laptops WHERE producer = :producer";
            $statement=$connection->prepare($sql);
            $statement->bindParam(":producer", $producer);
            $statement->execute();
            $laptops=array_merge($laptops, $statement->fetchAll(PDO::FETCH_ASSOC));
        }
    }

    $laptops=array_unique($laptops, SORT_REGULAR);

    if (empty($_GET)) {
        $sql="SELECT * FROM Laptops";
        $statement = $connection->prepare($sql);
        $statement->execute();
        $laptops = array_merge($laptops, $statement->fetchAll(PDO::FETCH_ASSOC));
    }

    echo "<tr>";
    echo "<th>Producer</th>";
    echo "<th>CPU</th>";
    echo "<th>HDD Capacity</th>";
    echo "<th>GPU</th>";
    echo "</tr>";

    foreach ($laptops as $laptop){
        echo "<tr>";
        echo "<td>" . $laptop["producer"] . "</td>";
        echo "<td>" . $laptop["cpu"] . "</td>";
        echo "<td>" . $laptop["hdd_capacity"] . "</td>";
        echo "<td>" . $laptop["gpu"] . "</td>";
        echo "</tr>";
    }
?>