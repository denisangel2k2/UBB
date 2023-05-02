function sortColumns(column_index){
    let table=$("#tableColumns");
    let rows=table.find("tr");
    let columns=[];
    let columns_length=rows.eq(0).children().length;
    for (let i=0; i<columns_length-1; i++)
        columns.push([]);

        for (let i=0; i<rows.length; i++){
            for (let j=1; j<columns_length; j++){
                columns[j-1].push(rows.eq(i).children().eq(j).html());
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
                rows.eq(i).children().eq(j+1).html(columns[j][i]);
            }
        }
}

function sortRows(attributeIndex){
    rows=$("#tableRows").find("tr");
    let rowsWork=[];
    for (let i=1; i<rows.length; i++)
        rowsWork.push([]);

    for (let i=1; i<rows.length; i++)
        for (let j=0; j<rows.eq(i).children().length; j++)
            rowsWork[i-1].push(rows.eq(i).children().eq(j).html());

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
        for (let j=0; j<rows.eq(i).children().length; j++)
            rows.eq(i+1).children().eq(j).html(rowsWork[i][j]);

}