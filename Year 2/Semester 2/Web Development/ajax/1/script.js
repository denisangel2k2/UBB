// console.log("script.js loaded");
// function showAvailable(param) {
//     console.log("showAvailable called with param: " + param);
//     if (param.length === 0) {
//         document.getElementById('destinations').innerHTML = "";
//         return;
//     }
//     console.log("param: " + param);
//     let xmlhttp = new XMLHttpRequest();
//     xmlhttp.onreadystatechange = function() {
//         if (this.readyState === 4 && this.status === 200) {
//             document.getElementById("destinations").innerHTML = this.responseText;
//             console.log("responseText: " + this.responseText);
//         }
//     };
//     xmlhttp.open("GET", "getDest.php?q=" + param, true);
//     xmlhttp.send();
//     console.log("showAvailable finished");
// }

function showAvailable(param){
    if (param.length === 0) {
        $('#destinations').html("");
        return;
    }
    $.ajax({
        url: "getDest.php?q=" + param,
        method: "GET",
        success: function (response) {
            $('#destinations').html(response);
        }
    });
}