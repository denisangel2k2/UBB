// window.onload=function(){
//     loadDir("C:/Users/Denis/Documents/GitHub");
// };
// function loadDir(path){
//     let xmlhttp=new XMLHttpRequest();
//     xmlhttp.onreadystatechange=function(){
//         if(this.readyState==4 && this.status==200){
//             document.getElementById("files").innerHTML=this.responseText;
//         }
//     }
//     xmlhttp.open("GET","loadFiles.php?q="+path,true);
//     xmlhttp.send();
// }

$(document).ready(function(){
    loadDir("C:/Users/Denis/Documents/GitHub");
});
function loadDir(path){
    $.ajax({
        url: "loadFiles.php",
        type: "GET",
        data: {q: path},
        success: function(data){
            $("#files").html(data);
        }
    });
}