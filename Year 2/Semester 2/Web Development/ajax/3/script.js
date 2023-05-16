// function addEvents(){
//     var foodInput=document.getElementById("food");
//     var priceInput=document.getElementById("price");
//     var descriptionInput=document.getElementById("description");
    
//     foodInput.addEventListener("input",function(){
//         document.querySelector('#submit').disabled = false;
//         document.getElementById("change").innerHTML="<p>Values have changed!</p>";
//     });
//     priceInput.addEventListener("input",function(){
//         document.querySelector('#submit').disabled = false;
//         document.getElementById("change").innerHTML="<p>Values have changed!</p>";
//     });
//     descriptionInput.addEventListener("input",function(){
//         document.querySelector('#submit').disabled = false;
//         document.getElementById("change").innerHTML="<p>Values have changed!</p>";
//     });

// }


// function loadIds(){
//     xmlhttp=new XMLHttpRequest();
//     xmlhttp.onreadystatechange=function(){
//         if (xmlhttp.readyState==4 && xmlhttp.status==200){
//             document.getElementById("id_list").innerHTML=xmlhttp.responseText;
//         }
//     }
//     xmlhttp.open("GET","loadIds.php",true);
//     xmlhttp.send();
//     document.querySelector('#submit').disabled = true;
// }

// function loadForm(value){
//     document.getElementById("change").innerHTML="";
//     xmlhttp=new XMLHttpRequest();
//     xmlhttp.onreadystatechange=function(){
//         if (xmlhttp.readyState==4 && xmlhttp.status==200){
//             document.getElementById("modify_form").innerHTML=xmlhttp.responseText;
//             document.querySelector('#submit').disabled = true;
//             addEvents();
//         }
//     }
//     xmlhttp.open("GET","getFoodForCurrentId.php?id="+value,true);
//     xmlhttp.send();
//     //
    
// }


// function updateFood(){

//     let id=document.getElementById("id").value;
//     let food=document.getElementById("food").value;
//     let price=document.getElementById("price").value;
//     let description=document.getElementById("description").value;

//     xmlhttp=new XMLHttpRequest();
//     xmlhttp.onreadystatechange=function(){
//         if (xmlhttp.readyState==4 && xmlhttp.status==200){
//             document.getElementById("change").innerHTML=xmlhttp.responseText;
//         }
//     }
//     xmlhttp.open("POST","submitChanges.php",true);
//     xmlhttp.setRequestHeader("Content-type","application/x-www-form-urlencoded");
//     xmlhttp.send("id="+id+"&food="+food+"&price="+price+"&description="+description);


// }

// window.onload = () => {
//     document.getElementById("modify_form").addEventListener("submit",(event)=>{
//         event.preventDefault();
//         updateFood();
//     });
//     loadIds();
// }


function addEvents(){
    $("#food").on("input",function(){
        $("#submit").prop("disabled",false);
        $("#change").html("<p>Values have changed!</p>");
    });
    $("#price").on("input",function(){
        $("#submit").prop("disabled",false);
        $("#change").html("<p>Values have changed!</p>");
    });
    $("#description").on("input",function(){
        $("#submit").prop("disabled",false);
        $("#change").html("<p>Values have changed!</p>");
    });
}
function loadIds(){
    $.ajax({
        url:"loadIds.php",
        success:function(result){
            $("#id_list").html(result);
        }
    });
    $("#submit").prop("disabled",true);
}

function loadForm(value){
    $("#change").html("");
    console.log(value);
    $.ajax({
        url:"getFoodForCurrentId.php?id="+value,
        method:"GET",
        success:function(result){
            $("#modify_form").html(result);
            $("#submit").prop("disabled",true);
            addEvents();
        }
    });
}

function updateFood(){
    $.ajax({
        url:"submitChanges.php",
        method:"POST",
        data:{
            id:$("#id").val(),
            food:$("#food").val(),
            price:$("#price").val(),
            description:$("#description").val()
        },
        success:function(result){
            $("#change").html(result);
        }
    });
}
$(document).ready(function() {
    $('#modify_form').submit(function(event) {
        event.preventDefault();
        updateFood();
    });
    loadIds();
});