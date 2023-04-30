let slides=document.querySelectorAll('.slides')
let currentVisibleSlideIndex=0;
let timer;

function showSlide(index){
    
    if (slides[index].style.display==='none')
        index++;
    slides[index].style.display='block';
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
   for (let i=0;i<currentVisibleSlideIndex;i++)
       slides[i].style.display='block';

    for (let i=currentVisibleSlideIndex+1;i<slides.length;i++)
        slides[i].style.display='none';

}
function showNextSlide(n){
    clearTimeout(timer);
    console.log(currentVisibleSlideIndex);
    showSlides(currentVisibleSlideIndex+=n);
    timer=setTimeout(run,5000);
}
run();


