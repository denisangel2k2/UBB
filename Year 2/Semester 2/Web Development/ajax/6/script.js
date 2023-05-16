let filter="?";

// window.onload = () => {
//     loadProducts();
//     document.querySelectorAll("input[type=checkbox]").forEach((checkbox) => {
//         checkbox.addEventListener("change", () => {
//             if (checkbox.checked) {
//                 filter += "&" + checkbox.name + "[]=" + checkbox.id;
//             } else {
//                 filter = filter.replace("&" + checkbox.name + "[]=" + checkbox.id, "");
//             }
//             console.log(filter);
//             loadProducts();
//         });
//     });
// }

// function loadProducts() {
//     let xmlhttp = new XMLHttpRequest();
//     xmlhttp.onreadystatechange = function () {
//         if (this.readyState == 4 && this.status == 200) {
//             document.getElementById("laptops").innerHTML = this.responseText;
//         }
//     }
//     xmlhttp.open("GET", "loadLaptops.php" + filter, true);
//     xmlhttp.send();
// }

$(document).ready(function () {
    loadProducts();
    $("input[type=checkbox]").change(function () {
        if (this.checked) {
            filter += "&" + this.name + "[]=" + this.id;
        } else {
            filter = filter.replace("&" + this.name + "[]=" + this.id, "");
        }
        console.log(filter);
        loadProducts();
    });
});

function loadProducts() {
    $.ajax({
        url: "loadLaptops.php" + filter,
        type: "GET",
        success: function (result) {
            $("#laptops").html(result);
        }
    });
}
