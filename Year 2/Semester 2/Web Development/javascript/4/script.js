function sortColumns(column_index){
    let table=document.getElementById("tableColumns");
    let rows=table.rows;
    let columns=[];
    let columns_length=rows[0].children.length;
    for (let i=0; i<columns_length-1; i++)
        columns.push([]);
  
    for (let i=0; i<rows.length; i++){
        for (let j=1; j<columns_length; j++){
            columns[j-1].push(rows[i].children[j].innerHTML);
        }
    }

    function asc(a,b){
        if (a[column_index]>b[column_index])
            return 1;
        if (a[column_index]<b[column_index])
            return -1;
        return 0;
    }
    function desc(a,b){
        if (a[column_index]>b[column_index])
            return -1;
        if (a[column_index]<b[column_index])
            return 1;
        return 0;
    }
    
    let before=columns.toString();
    if (!isNaN(parseInt(columns[0][column_index]))){
        for (let i=0; i<columns_length-1; i++)
            columns[i][column_index]=parseInt(columns[i][column_index]);
    }
   
    columns.sort(asc);

    if (before===columns.toString()) columns.sort(desc);
    

    for (let i=0; i<rows.length; i++){
        for (let j=0; j<columns_length-1; j++){
            rows[i].children[j+1].innerHTML=columns[j][i];
        }
    }

}


function sortRows(attributeIndex){
    table=document.getElementById("tableRows");
    rows=table.rows;
    rowsWork=[];
    for (let i=1; i<rows.length; i++){
        rowsWork.push([]);
    }

    for (let i=1; i<rows.length; i++)
        for (let j=0; j<rows[i].children.length; j++)
            rowsWork[i-1].push(rows[i].children[j].innerHTML);
        
    
    function asc(a,b){
        if (a[attributeIndex]>b[attributeIndex])
            return 1;
        if (a[attributeIndex]<b[attributeIndex])
            return -1;
        return 0;
    }

    function desc(a,b){
        if (a[attributeIndex]>b[attributeIndex])
            return -1;
        if (a[attributeIndex]<b[attributeIndex])
            return 1;
        return 0;
    }
   
    if (!isNaN(parseInt(rowsWork[0][attributeIndex]))){
        for (let i=0; i<rowsWork.length; i++)
            rowsWork[i][attributeIndex]=parseInt(rowsWork[i][attributeIndex]);
    }

    let before=rowsWork.toString();
    rowsWork.sort(asc);
    
    if (rowsWork.toString()===before) {
        rowsWork.sort(desc);
    }
    for (let i=0; i<rows.length-1; i++)
        for (let j=0; j<rows[i].children.length; j++)
            rows[i+1].children[j].innerHTML=rowsWork[i][j];

}

