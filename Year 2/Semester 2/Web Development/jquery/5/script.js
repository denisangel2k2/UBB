let slides=$(".slides");
let currentVisibleSlideIndex=0;
let timer;

function showSlide(index){
    if (slides.eq(index).css("display")==="none")
        index++;
    slides.eq(index).css("display","block");
}

function run(){
    showSlides(currentVisibleSlideIndex);
    timer=setTimeout(run,5000);
    currentVisibleSlideIndex++;
}

function showSlides(n){
    if (n>slides.length)
        currentVisibleSlideIndex=0;
    if (n<0)
        currentVisibleSlideIndex=slides.length-1;

    for (let i=0; i<currentVisibleSlideIndex; i++)
        slides.eq(i).css("display","block");

    for (let i=currentVisibleSlideIndex+1; i<slides.length; i++)
        slides.eq(i).css("display","none")
}

function showNextSlide(n){
    clearTimeout(timer);
    console.log(currentVisibleSlideIndex);
    showSlides(currentVisibleSlideIndex+=n);
    timer=setTimeout(run,5000);
}
run();