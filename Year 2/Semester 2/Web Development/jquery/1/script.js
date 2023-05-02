$("#firstlist").on("dblclick", function(event){
    if (event.target != $("#firstlist")[0]){
        $("#secondlist").append(event.target);
    }
});
$("#secondlist").on("dblclick", function(event){
    if (event.target != $("#secondlist")[0])
        $("#firstlist").append(event.target);
});