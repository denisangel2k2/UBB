from datetime import date, timedelta
from adaugare_tranzactii import returnTransaction
from init_functions import *

def interval_dates(startd, endd):
    """
    Returneaza o lista cu toate datele din intervalul stard-endd
    input : startd - string
            endd - string
    output : lista - string
    raises : "Data invalida" - daca parametrii nu sunt valizi
    """
    if validateDay(startd) and validateDay(endd):
        lista=[]
        s=str(startd)
        temp=s.split("/")
        start_date = date(int(temp[2]),int(temp[1]),int(temp[0]))

        s=str(endd)
        temp=s.split("/")
        end_date = date(int(temp[2]),int(temp[1]),int(temp[0]))

        delta = end_date - start_date

        for i in range(delta.days + 1):
            day = start_date + timedelta(days=i)
            s=str(day)
            temp=s.split('-')
            ex=str(temp[2]+"/"+temp[1]+"/"+temp[0])
            lista.append(ex)
        return lista
    else:
        raise Exception("Data invalida")

def deleteTransactions_today(myDict,ziua):
    """
    Sterge toate tranzactiile din dictionarul myDict din ziua "ziua"
    input: myDict - dictionar
           ziua - string
    output: -
    raises: "Data invalida" daca ziua nu corespunde normelor
            "Nu s-a gasit nicio tranzactie in ziua precizata"
    """
    if validateDay(ziua)==False:
        raise Exception("Data invalida")
    #print(len(myDict[ziua]))
    try:
        myDict[ziua]
    except KeyError:
        raise Exception("Nu s-a gasit nicio tranzactie in ziua precizata")
    i=0
    while(len(myDict[ziua])>0):
        del myDict[ziua][i]
    
def deleteTransactions_interval(myDict,ziua_inceput,ziua_sfarsit):
    """
    Sterge toate datele din intervalul ziua_inceput-ziua_sfarsit din dictionarul myDict
    input : myDict - dictionar
            ziua_inceput, ziua_sfarsit - string
    output : -
    raises : la fel ca si la interval_dates ("Data invalida")
    """
    if validateDay(ziua_inceput) and validateDay(ziua_sfarsit):
        lista_date=interval_dates(ziua_inceput,ziua_sfarsit)
        for i in lista_date:
            if searchInDict(myDict,str(i)):
                deleteTransactions_today(myDict,str(i))
    else: raise Exception("Data invalida")

def deleteTransactions_type(myDict,tip):
    """
    Sterge toate tranzactiile de tipul tip din dictionarul myDict
    input : myDict - dictionar
            tip - string (intrare/iesire)
    output : -
    raises : "Tipul nu exista"
    """
    if validateType(tip)==False:
        raise Exception("Tipul nu exista")

    for key,value in myDict.items():
       for i in range(len(value)):
           if value[i][1]==tip:
               del value[i]
    
def main():
    myDict={
        '13/07/2018':[[130,"intrare"],[1,"iesire"]],
        '14/07/2021':[[150,"iesire"]],
        '01/01/2022' :[]
    } 
   # deleteTransactions_today(myDict,'13/03/2500')
    
    
main()