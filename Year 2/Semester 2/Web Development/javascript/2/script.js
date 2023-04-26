// Asociați elementele din formular cu ID-uri unice
const dataNasterii = document.getElementById('nastere');
const varsta = document.getElementById('varsta');
const email = document.getElementById('email');
const trimiteBtn = document.getElementById('send');
const nume=document.getElementById('nume');


trimiteBtn.addEventListener('click', () =>{
    if (dataNasterii.value === "" || varsta.value === "" || email.value === "") {
        alert("Vă rugăm să completați toate câmpurile.");
        return;
      }
    
      const numeValid=/^[a-zA-Z]+$/.test(nume.value);
      const dataNasteriiValid = !isNaN(Date.parse(dataNasterii.value)) && new Date(dataNasterii.value) < new Date();
      console.log(new Date(dataNasterii.value) < new Date());
      const varstaValid = /^\d+$/.test(varsta.value);
      const emailValid = /^[^\s@]+@[^\s@]+\.[^\s@]+$/.test(email.value);
      error="";
      if (dataNasteriiValid && varstaValid && emailValid && numeValid) {
        alert("Datele sunt completate corect.");
        varsta.style.border="1px solid green";
        dataNasterii.style.border="1px solid green";
        email.style.border="1px solid green";
        return;
      } 
      if (!numeValid){
            error+="Campul nume nu este completat corect. \n";
            nume.style.border="1px solid red";
      }

      if (!dataNasteriiValid){
            error+="Campul data nasterii nu este completat corect. \n";
            dataNasterii.style.border="1px solid red";
      }
      if (!varstaValid){
           error+="Campul varsta nu este completat corect. \n";
           varsta.style.border="1px solid red";
      } 
        alert(error);
        return;
      }
);