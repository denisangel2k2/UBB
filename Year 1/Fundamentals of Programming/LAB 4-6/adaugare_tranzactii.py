from init_functions import *
def addTransaction(ziua,suma,tip,myDict):
    '''
    adauga tranzactia cu datele ziua, suma si tip transmisi ca parametri in dictionarul myDict
    input: ziua - string
           suma - float
           tip - string 
           myDict - dictionar
           raises : exceptia de la createTransaction
    output: -
    '''
    try:
        t=createTransaction(ziua,suma,tip)
        if searchInDict(myDict,getDay(t)):
            myDict[getDay(t)].append([getSum(t),getType(t)])
        else:
            myDict[getDay(t)]=[ [getSum(t),getType(t)] ]
    except Exception as ex:
        raise Exception(str(ex))
      # print(str(ex))
def returnTransaction(ziua, suma, tip, myDict):
    """
    returneaza indicele tranzactiei care are ca identificatori ziua, suma si tip in dictionarul myDict
    input: ziua - string
           suma - float
           tip - string
    output:  indicele tranzactiei cerute
    raises : "Nu s-a gasit ziua" - daca nu exista ziua tranzactiei precizata in dictionar
            "Nu s-a gasit tranzactia precizata in ziua dvs." - daca nu exista tranzactia cu suma sau tipul respectiv in dictionar

    """

   # print(len(myDict[ziua]))
    if (searchInDict(myDict,ziua)):
        for i in range(len(myDict[ziua])):
            if abs(myDict[ziua][i][0]-suma)<0.000001 and myDict[ziua][i][1]==tip:
                return i
        raise Exception("Nu s-a gasit tranzactia precizata in ziua dvs.")
    else:
        raise Exception("Nu s-a gasit ziua") 
def updateTransaction(ziua, suma, tip, myDict,suma_nou,tip_nou):
    """
    actualizeaza tranzactia cu ziua suma si tip din parametri in dictionarul myDict cu suma_nou si tip_nou
    input: ziua - string
           suma - float
           tip - string
           myDict - dictionar
           suma_nou -string

    output: -
    raises: aceleasi exceptii ca la returnTransaction
    """
    #validarea suma_now si tip_nou
    if validateSum(suma_nou)==False or validateType(tip_nou)==False:
        raise Exception("Suma/tipul introduse de tine sunt gresite")

    try:
        index = returnTransaction(ziua,suma,tip,myDict)
        myDict[ziua][index][0]=suma_nou
        myDict[ziua][index][1]=tip_nou

    except Exception as ex:
        raise Exception(ex)
