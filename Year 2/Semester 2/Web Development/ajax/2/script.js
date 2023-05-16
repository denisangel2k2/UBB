let startIndex=-3;
window.onload=function(){
    next();
};
function next(){
    startIndex=startIndex+3;
    let table=document.getElementById("users");
    let xmlhttp=new XMLHttpRequest();
    xmlhttp.onreadystatechange=function(){
        if (this.readyState==4 && this.status==200){
            table.innerHTML=this.responseText;
            console.log(this.responseText);
        }
        console.log(this.responseText);
    }
    xmlhttp.open("GET","getUsers.php?startIndex="+startIndex,true);
    xmlhttp.send();

}
function prev(){
    if (startIndex==0) return;
    startIndex=startIndex-3;
    let table=document.getElementById("users");

    let xmlhttp=new XMLHttpRequest();
    xmlhttp.onreadystatechange=function(){
        
        if (this.readyState==4 && this.status==200){
            table.innerHTML=this.responseText;
            console.log(this.responseText);
        }
        console.log(this.responseText);
    }
    xmlhttp.open("GET","getUsers.php?startIndex="+startIndex,true);
    xmlhttp.send();
    
}
// function next(){
//     startIndex=startIndex+3;
//     $.ajax({
//         url: "getUsers.php?startIndex="+startIndex,
//         type: "GET",
//         success: function(response){
//             $("#users").html(response);
//         }
//     });
// }
// function prev(){
//     if (startIndex==0) return;
//     startIndex=startIndex-3;
//     $.ajax({
//         url: "getUsers.php",
//         type: "GET",
//         data: {startIndex: startIndex},
//         success: function(response){
        
//             $("#users").html(response);}
//     });
// }