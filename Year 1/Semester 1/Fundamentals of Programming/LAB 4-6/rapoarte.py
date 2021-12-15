from init_functions import searchInDict, searchMinKey, validateDay, validateType
from stergere_tranzactii import interval_dates

def sumTransactionType(myDict, tip):
    '''
    returneaza suma tuturor tranzactiilor de un anumit tip
    input : myDict - dictionar
            tip - string

    output : float

    '''
    if validateType(tip):
        S=0
        for key in myDict.keys():
            for list in myDict[key]:
                if list[1]==tip:
                    S+=list[0]
        return S
    else: raise Exception("Tipul introdus este gresit")
def creareLista(myDict):
    '''
    Creeaza o lista de forma [[z,s,t],[z,s,t]]
    input : myDict - dictionar
    output : lista
    '''
    general_list=[]
    for key in myDict.keys():
        for lista in myDict[key]:
            if len(lista):
                temp_list=[key, lista[0], lista[1]]
                general_list.append(temp_list)
    
    return general_list
def sortareLista_bySum(myList):
    '''
    Sorteaza lista de forma [[z,s,t],[z,s,t]] dupa s
    input : myList - lista
    output : lista
    '''
    
    for i in range(0,len(myList)-1):
        for j in range(1,len(myList)):
            if myList[i][1]>myList[j][1]:
                l=myList[i]
                myList[i]=myList[j]
                myList[j]=l
def soldByDate(myDict, ziua):
    '''
    returneaza soldul contuluit la o data specifica
    input : myDict - dictionar
            ziua - string
    output : float
    '''        
    if validateDay(ziua):
        dataI=searchMinKey(myDict)
        lista=interval_dates(dataI,ziua)
        S=0
        for el in lista:
            if searchInDict(myDict,el):
                for list in myDict[el]:
                    if list[1]=='intrare':
                        S+=list[0]
                    else: S-=list[0]

        return S
    else: raise Exception("Date invalide, incercati sa folositi tipul DD:MM:YYYY pentru data.")
def printByType_sumOrdered(l,tip):
    '''
    Tipareste toate tranzactiile de un anumit tip ordonat dupa suma
    input : l - lista
    output:
    raises : "Tip invalid"
    '''
    if validateType(tip):

        for lista in l:
            if lista[2]==tip:
        # print (lista[0])
                print("Data: "+ lista[0]+"   Suma: "+str(lista[1])+"   Tip: "+lista[2])

    else: raise Exception("Tip invalid")

def main():    
    myDict={
            '13/07/2018':[[130,"intrare"],[1,"iesire"]],
            '14/07/2021':[[150,"iesire"]],
            '01/01/2022' :[]
        } 
    #print(sumTransactionType(myDict,'iesire'))
    l=creareLista(myDict)
    sortareLista_bySum(l)
    printByType_sumOrdered(l,'iesire')
#main()