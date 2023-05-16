<?php
    $data=json_decode(file_get_contents("php://input"),true);
    $board=$data['table'];
    function isWinning($board, $player) {
        for ($i = 0; $i < 3; $i++) {
          if ($board[$i][0] == $player && $board[$i][0] == $board[$i][1] && $board[$i][1] == $board[$i][2]) {
            return true;
          }
        }
        for ($i = 0; $i < 3; $i++) {
          if ($board[0][$i] == $player && $board[0][$i] == $board[1][$i] && $board[1][$i] == $board[2][$i]) {
            return true;
          }
        }
        if ($board[0][0] == $player && $board[0][0] == $board[1][1] && $board[1][1] == $board[2][2]) {
          return true;
        }
        if ($board[0][2] == $player && $board[0][2] == $board[1][1] && $board[1][1] == $board[2][0]) {
          return true;
        }
        return false;
      }

$freeCells = 0;

foreach ($board as $row) {
    foreach ($row as $cell) {
        if ($cell == '') {
            $freeCells++;
        }
    }
}

if (isWinning($board, "X")) {
    echo "x";
    exit();
}

if ($freeCells == 0) {
    echo "r";
    exit();
}

$row = rand(0, 2);
$column = rand(0, 2);

while ($board[$row][$column] != '') {
    $row = rand(0, 2);
    $column = rand(0, 2);
}

$board[$row][$column] = "O";
echo $row . $column;

if (isWinning($board, "O")) {
    echo "o";
    exit();
}

if ($freeCells == 1) {
    echo "r";
    exit();
}


?>