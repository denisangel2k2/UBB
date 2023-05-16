let board=[['','',''],['','',''],['','','']];

// window.onload=function(){
//     let computerTurn=Math.floor(Math.random()*2);
//     if(computerTurn==0){
//         let randomRow=Math.floor(Math.random()*3);
//         let randomCol=Math.floor(Math.random()*3);
//         updateTableAfterComputerMove(randomRow.toString()+randomCol.toString());
//     }
// }

// function playCell(row,col){
//     if(board[row][col]==''){
//         board[row][col]='X';
//         let id=row.toString()+col.toString();
//         document.getElementById(id).innerHTML='<td>X<td>';
//         computerMove();
//     }
// }
// function updateTableAfterComputerMove(response){
//     let row=response[0];
//     let col=response[1];
//     board[row][col]='O';
//     let id=row.toString()+col.toString();
//     document.getElementById(id).innerHTML='<td>O<td>';
// }
// function computerMove(){
//     let xmlhttp=new XMLHttpRequest();
//         xmlhttp.onreadystatechange=function(){
//             if(this.readyState==4 && this.status==200){
//                 document.getElementById("message").innerHTML=this.responseText;
//                 if (this.responseText[this.responseText.length - 1] === "r") {
//                         setTimeout(() => {alert("Remiza")}, 1);
//                     } else if (this.responseText[this.responseText.length - 1] === "o") {
//                         setTimeout(() => {alert("Ai pierdut")}, 1);
//                     } else if (this.responseText[this.responseText.length - 1] === "x") {
//                         setTimeout(() => {alert("Ai castigat")}, 1);
//                         return;
//                     }
//              }
//              updateTableAfterComputerMove(this.responseText);
//         };
//         xmlhttp.open("POST","calculateMove.php",true);
//         xmlhttp.setRequestHeader("Content-type","application/x-www-form-urlencoded");
//         xmlhttp.send(JSON.stringify({table: board}));
// }
function playCell(row,col){
    if(board[row][col]==''){
        board[row][col]='X';
        let id=row.toString()+col.toString();
        $('#'+id).html('X');
        computerMove();
    }
}
function updateTableAfterComputerMove(response){
    let row=response[0];
    let col=response[1];
    board[row][col]='O';
    let id='#'+row.toString()+col.toString();
    $(id).html('O');
}
function computerMove(){
    $.ajax({
        url: "calculateMove.php",
        type: "POST",
        data: JSON.stringify({table: board}),
        success: function(response){
            
            if (response[response.length - 1] === "r") {
                setTimeout(() => {alert("Remiza")}, 1);
            } else if (response[response.length - 1] === "o") {
                setTimeout(() => {alert("Ai pierdut")}, 1);
            } else if (response[response.length - 1] === "x") {
                setTimeout(() => {alert("Ai castigat")}, 1);
                return;
            }
            updateTableAfterComputerMove(response);
        }
    });
}
$(document).ready(function(){
    let computerTurn=Math.floor(Math.random()*2);
    if(computerTurn==0){
        let randomRow=Math.floor(Math.random()*3);
        let randomCol=Math.floor(Math.random()*3);
        updateTableAfterComputerMove(randomRow.toString()+randomCol.toString());
    }
});