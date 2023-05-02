let numbers=[1,1,2,2,3,3,4,4,5,5,6,6,7,7,8,8];
let imagesNumbers=[];

for (let i=1; i <=8; i++) {
   var img=$("<img/>").attr("src","./img/"+i+".jpg");
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
    let p=$("<p/>").html(numbers[i]).addClass("number");
    $(".card").eq(i).append(p);
}

let index=0;
$(".flip").each(function(){
    $(this).attr("src",imagesNumbers[index].attr("src"));
    index=index+1;
});



function checkWin(){
    let allFlipped=true;
    $(".card").each(function(){
        if ($(this).find(".flip").css("visibility")==="hidden")
            allFlipped=false;
    });
    if (allFlipped===true)
        alert("You won!");
}

var selectedCards=[];
var selectedNumbers=[];

function runGame(){
    $(".card").each(function(){
        $(this).on("click",function(){
            let selectedImage=$(this).find(".flip");
            let selectedNumber=$(this).find(".number");

            selectedImage.css("visibility","visible");
            selectedCards.push(selectedImage);
            selectedNumber.css("visibility","visible")
            selectedNumbers.push(selectedNumber);

            if (selectedCards.length===2){
                $('.card').css('pointer-events','none');
                setTimeout(()=>{
                    $('.card').css('pointer-events','auto');
                },1000);

                let img1=selectedCards.pop();
                let img2=selectedCards.pop();
    
                let num1=selectedNumbers.pop();
                let num2=selectedNumbers.pop();
    
                if (img1.attr('src')!==img2.attr('src')){
                    console.log("not equal");
                    setTimeout(()=>{
                        if (img1.css("visibility")!=="hidden" && img2.css("visibility")!=="hidden")
                        {
                            img1.css("visibility","hidden");
                            img2.css("visibility","hidden");
                            num1.css("visibility","hidden");
                            num2.css("visibility","hidden");
                        }

                    },1000);
                }
                else{
                    img1.parent().off("click");
                    img2.parent().off("click");
                    checkWin();
                }

            }
        });
    });
}
runGame();
