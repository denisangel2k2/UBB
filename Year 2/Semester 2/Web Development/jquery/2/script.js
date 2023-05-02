
$("#send").on("click",function(){
    const birthDate=$("#nastere").val();
    const varsta=$("#varsta").val();
    const email=$("#email").val();
    const nume=$("#nume").val();


    


    if (birthDate === "" || varsta === "" || email.value === "") {
        alert("Vă rugăm să completați toate câmpurile.");
        return;
      }

    const numeValid=/^[a-zA-Z]+$/.test(nume);
    const dataNasteriiValid = !isNaN(Date.parse(birthDate)) && new Date(birthDate) < new Date();
    const varstaValid = /^\d+$/.test(varsta);
    const emailValid = /^[^\s@]+@[^\s@]+\.[^\s@]+$/.test(email);
    error="";

    if (dataNasteriiValid && varstaValid && emailValid && numeValid) {
        alert("Datele sunt completate corect.");
        $("#nume").css("border", "1px solid green");
        $("#nastere").css("border", "1px sold green");
        $("#varsta").css("border","1px solid green");
        $("#email").css("border","1px solid green");
        return;
      } 
      if (!numeValid){
            error+="Campul nume nu este completat corect. \n";
            $("#nume").css("border", "1px solid red");
      }

      if (!dataNasteriiValid){
            error+="Campul data nasterii nu este completat corect. \n";
            $("#nastere").css("border", "1px sold red");
      }
      if (!varstaValid){
           error+="Campul varsta nu este completat corect. \n";
           $("#varsta").css("border","1px solid red");
      } 
      if (!emailValid){
          error+="Campul email nu este completat corect.\n";
          $("#email").css("border","1px solid red");
      }

        alert(error);
        return;
    
});
