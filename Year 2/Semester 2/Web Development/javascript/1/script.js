const list1=document.getElementById('firstlist')
const list2=document.getElementById('secondlist')



list1.addEventListener('dblclick',function(event){
    if (event.target != list1){
        list2.appendChild(event.target)
    }
})

list2.addEventListener("dblclick",function(event){
    if (event.target != list2){
        list1.appendChild(event.target)
    }
    
})
