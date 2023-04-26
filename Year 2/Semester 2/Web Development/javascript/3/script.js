cards=document.querySelectorAll('.card');
let numbers=[1,1,2,2,3,3,4,4,5,5,6,6,7,7,8,8];
let imagesNumbers=[];

for (let i=1; i<=8; i=i+1){
    var img=new Image();
    img.src="./img/"+i+".jpg";
    console.log(img.src);
    imagesNumbers.push(img);
    imagesNumbers.push(img);
}


//shuffle
for (let i=0; i<imagesNumbers.length; i=i+1){
    let random=Math.floor(Math.random()*imagesNumbers.length);
    let temp=imagesNumbers[i];
    imagesNumbers[i]=imagesNumbers[random];
    imagesNumbers[random]=temp;

    temp=numbers[i];
    numbers[i]=numbers[random];
    numbers[random]=temp;
}
//add paragraph numbers

for (let i=0; i<numbers.length; i=i+1){
    let p=document.createElement('p');
    p.innerHTML=numbers[i];
    p.classList.add('number');
    cards[i].appendChild(p);
}


//set images
let index=0;
document.querySelectorAll('.flip').forEach(e=>{
    e.src=imagesNumbers[index].src;
    index=index+1;
    
});

var selectedCards=[];
var selectedNumbers=[];

//check if all the cards are flipped
function checkWin(){
    let allFlipped=true;
    document.querySelectorAll('.card').forEach(e=>{
        if (e.querySelector('.flip').style.visibility==="hidden"){
            allFlipped=false;
        }
    });
    if (allFlipped===true){
        alert('You won!');
    }
    
    
}

function runGame(){
    
    document.querySelectorAll('.card').forEach(e=>{
        e.addEventListener('click',function(){
            let selectedImage=e.querySelector(".flip");
            let selectedNumber=e.querySelector(".number");

            


            selectedImage.style.visibility="visible";
            selectedCards.push(selectedImage);
            selectedNumbers.push(selectedNumber);
            selectedNumber.style.visibility="visible";
                
    
            if (selectedCards.length===2){
                
                //freeze the game for 1 second
                document.querySelectorAll('.card').forEach(e=>{
                    e.style.pointerEvents="none";
                });
                setTimeout(()=>{
                    document.querySelectorAll('.card').forEach(e=>{
                        e.style.pointerEvents="auto";
                    });
                },1000);
                
                let img1=selectedCards.pop();
                let img2=selectedCards.pop();
    
                let num1=selectedNumbers.pop();
                let num2=selectedNumbers.pop();
    
    
                if (img1.src!==img2.src){
                    console.log('not equal');
                    setTimeout(()=>{
                        img1.style.visibility="hidden";
                        img2.style.visibility="hidden";
    
                        num1.style.visibility="hidden";
                        num2.style.visibility="hidden";
                        
    
                    },1000)
                }
                else{
                    img1.parentNode.removeEventListener('click',arguments.callee);
                    img2.parentNode.removeEventListener('click',arguments.callee);
                    checkWin();
                }
            } 
        });
    });
}

runGame();







