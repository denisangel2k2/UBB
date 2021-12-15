from init_functions import searchInDict, searchMinKey, validateDay, validateSum, validateType
from stergere_tranzactii import interval_dates


def printTransactionGreaterSum(myDict,suma):
    """
    Tipareste toate tranzactiile din dicitonarul myDict cu sume mai mari decat suma transmisa ca parametrul suma
    input : myDict - dictionar
            suma - float
    output : Data, suma, tip
    raises : "Suma invalida" daca suma nu este float
    """
    if validateSum(suma):

        for key in myDict.keys():
            for t in range(len(myDict[key])):
                S=str(myDict[key][t][0])
                if myDict[key][t][0]>suma:
                    print("Data: "+ key+"   Suma: "+S+"   Tip: "+str(myDict[key][t][1]))
    else:
        raise Exception("Suma invalida")

def printTransactionBeforeDaySum(myDict,suma,ziua):
    '''
    Tipărește toate tranzacțiile efectuate înainte de o zi și mai mari decât o
    sumă (se dă suma și ziua)
    input : myDict - dictionar
            suma - float
            ziua - string
    output: Data, suma, tip
    raises : daca ziua si suma nu sunt corespunzatoare "Ziua/suma sunt invalide"
    '''
    
    if validateSum(suma)==False or validateDay(ziua)==False:
        raise Exception("Ziua/suma sunt invalide")

    data_inceput=searchMinKey(myDict)
    lista_date=interval_dates(data_inceput,ziua)

    for i in range(len(lista_date)-1):
        #print(lista_date[i])
        if searchInDict(myDict,lista_date[i]):
            
            for t in range(len(myDict[lista_date[i]])):
                S=str(myDict[lista_date[i]][t][0])
                if myDict[lista_date[i]][t][0]>suma:
                    print("Data: "+ lista_date[i]+"   Suma: "+S+"   Tip: "+str(myDict[lista_date[i]][t][1]))
    
def printTransactionType(myDict,tip):
    '''
    Tipărește tranzacțiile de un anumit tip din dictionarul myDict
    input: myDict - dictionar
           tip - string
    output: Data, suma, tip
    raises: daca tipul este invalid atunci "Tip invalid"
    '''
    if validateType(tip)==False:
        raise Exception("Tip invalid")

    for key in myDict.keys():
        for lista in myDict[key]:
            if lista[1]==tip:
                print("Data: "+ key+"   Suma: "+str(lista[0])+"   Tip: "+str(lista[1]))

    
def main():
    '''
    myDict={
        '13/07/2018':[[130,"intrare"],[1,"iesire"]],
        '14/07/2021':[[150,"iesire"]],
        '01/01/2022' :[]
    } 
    '''
    #printTransactionGreaterSum(myDict,120)
    #printTransactionBeforeDaySum(myDict,2,'14/07/2021')
    
#main()

