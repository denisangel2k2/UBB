from init_functions import *
from stergere_tranzactii import *
#from cont_bancar import *
from adaugare_tranzactii import *
from cautare_tranzactii import *
from filtrare_tranzactii import *
from rapoarte import *

def test_createTransaction():
    
    try:
        t=createTransaction("32/3/2021",30,"intrare")
        assert(False)
    except Exception as ex:
        assert(str(ex)=="Date invalide, incercati sa folositi tipul DD:MM:YYYY pentru data.\nSuma trebuie sa fie un numar, iar tipul poate fi\ndoar iesire/intrare")
    
    try:
        t=createTransaction("30/2/2021",30,"intrare")
        assert(False)
    except Exception as ex:
        assert(str(ex)=="Date invalide, incercati sa folositi tipul DD:MM:YYYY pentru data.\nSuma trebuie sa fie un numar, iar tipul poate fi\ndoar iesire/intrare")
    
    try:
        t=createTransaction("20/3/2021",30,"da")
        assert(False)
    except Exception as ex:
        assert(str(ex)=="Date invalide, incercati sa folositi tipul DD:MM:YYYY pentru data.\nSuma trebuie sa fie un numar, iar tipul poate fi\ndoar iesire/intrare")
    try:
        t=createTransaction("30/3/2021",30,"intrare")
        assert(True)
    except Exception as ex:
        assert(str(ex)=="Date invalide, incercati sa folositi tipul DD:MM:YYYY pentru data.\nSuma trebuie sa fie un numar, iar tipul poate fi\ndoar iesire/intrare")
        
def test_searchInDict():
    dicT={}
    dicT["cheie1"]=[]
    assert(searchInDict(dicT,"cheie")==False)
    assert(searchInDict(dicT,"cheie1")==True)
def test_validateDay():
    assert(validateDay("31/3/2020/2")==False)
    assert(validateDay("31/3/")==False)
    assert(validateDay("31/3")==False)
    assert(validateDay("31/3/2b20")==False)
    assert(validateDay("31/03/2021")==True)
    assert(validateDay("32/03/2023")==False)
    assert(validateDay("30/02/2021")==False)
    assert(validateDay("29/02/2021")==False)
    assert(validateDay("29/02/2020")==True)
    assert(validateDay("03/02/2021")==True)

def test_validateSum():
    assert(validateSum(13)==True)
    assert(validateSum(13.2)==True)
    assert(validateSum("13.2")==True)
    assert(validateSum("13")==True)
    assert(validateSum("b")==False)

def test_validateType():
    assert(validateType("intrare")==True)
    assert(validateType("iesire")==True)
    assert(validateType("da")==False)
    assert(validateType(3)==False)

def test_addTransaction():
    myDict={}

    try:
        addTransaction("13/a/2020",120,"intrare",myDict)
        assert(False)
    except Exception as ex:
       # print(str(ex))
        assert(str(ex)=="Date invalide, incercati sa folositi tipul DD:MM:YYYY pentru data.\nSuma trebuie sa fie un numar, iar tipul poate fi\ndoar iesire/intrare")
    
    try:
        addTransaction("13/02/2020",120,"intrare",myDict)
        assert(True)
    except Exception as ex:
        #print(str(ex))
        assert(str(ex)=="Date invalide, incercati sa folositi tipul DD:MM:YYYY pentru data.\nSuma trebuie sa fie un numar, iar tipul poate fi\ndoar iesire/intrare")

def test_returnTransaction():
    myDict={
        '13/07/2021':[[130,"intrare"],[1,"iesire"]],
        '14/07/2021':[[150,"iesire"]]
    }
   # print(myDict['13/07/2021'][1][0])
    
    assert(returnTransaction("13/07/2021",130,"intrare",myDict)==0)
    assert(returnTransaction('14/07/2021',150,"iesire",myDict)==0)
    assert(returnTransaction("13/07/2021",1,"iesire",myDict)==1)

    try:
        a=returnTransaction("3",130,"blabla",myDict)
        assert(False)
    except Exception as ex:
        assert(str(ex)=="Nu s-a gasit ziua")
        
    try:
        a=returnTransaction("13/07/2021",130,"blabla",myDict)
        assert(False)
    except Exception as ex:
        assert(str(ex)=="Nu s-a gasit tranzactia precizata in ziua dvs.")  

def test_updateTransaction():
    myDict={
        '13/07/2021':[[130,"intrare"],[1,"iesire"]],
        '14/07/2021':[[150,"iesire"]]
    }
    try:
        updateTransaction('13/07/2021',150,"intrare",myDict,130,"iesire")
        assert(False)
    except Exception as ex:
        assert(str(ex)=="Nu s-a gasit tranzactia precizata in ziua dvs.")
    
    try:
        updateTransaction('13/07/2021',1,"iesire",myDict,130,"intrare")
        assert(True)
    except Exception as ex:
        assert(str(ex)=="Nu s-a gasit tranzactia precizata in ziua dvs.")
    
    try:
        updateTransaction('x',1,"iesire",myDict,130,"intrare")
        assert(False)
    except Exception as ex:
        assert(str(ex)=="Nu s-a gasit ziua")

    try:
        updateTransaction('13/07/2021',130,"intrare",myDict,999,"x")
        assert(False)
    except Exception as ex:
        #print(str(ex))
        assert(str(ex)=="Suma/tipul introduse de tine sunt gresite")
def test_interval_dates():

    try:
        interval_dates("","")
        assert(False)
    except Exception as ex:
        assert(str(ex)=="Data invalida")
    
    try:
        interval_dates("13/07/2020","15/07/2020")
        assert(True)
    except Exception as ex:
        pass
def test_deleteTransactions_today():
    myDict={
        '13/07/2021':[[130,"intrare"],[1,"iesire"]],
        '14/07/2021':[[150,"iesire"]]
    } 
    try:
        deleteTransactions_today(myDict,"x")
        assert(False)
    except Exception as ex:
        assert(str(ex)=="Data invalida")

    try:
        deleteTransactions_today(myDict,"13/07/2021")
        assert(True)
    except Exception as ex:
        #print(str(ex))
        assert(str(ex)=="Data invalida")
def test_deleteTransactions_interval():
    myDict={
        '13/07/2021':[[130,"intrare"],[1,"iesire"]],
        '14/07/2021':[[150,"iesire"]]
    } 
    try:
        deleteTransactions_interval(myDict,"","")
        assert(False)
    except Exception as ex:
        assert(str(ex)=="Data invalida")

    try:
        deleteTransactions_interval(myDict,'13/07/2021','14/07/2021')
        assert(True)
    except Exception as ex:
        assert(str(ex)=="Data invalida")
def test_deleteTransactions_type():
    myDict={
        '13/07/2021':[[130,"intrare"],[1,"iesire"]],
        '14/07/2021':[[150,"iesire"]]
    } 
    try: 
        deleteTransactions_type(myDict,"iesire")
        assert(True)
    except Exception as ex:
        assert(str(ex)=="Tipul nu exista")

    try: 
        deleteTransactions_type(myDict,"x")
        assert(False)
    except Exception as ex:
        assert(str(ex)=="Tipul nu exista")
def test_searchMinKey():
    myDict={
        '13/07/2018':[[130,"intrare"],[1,"iesire"]],
        '14/07/2021':[[150,"iesire"]],
        '01/01/2022' :[]
    } 
   # searchMinKey(myDict)
    #print(searchMinKey(myDict))
    assert(searchMinKey(myDict)=='01/01/2018')
def test_printTransactionGreaterSum():
    myDict={
        '13/07/2018':[[130,"intrare"],[1,"iesire"]],
        '14/07/2021':[[150,"iesire"]],
        '01/01/2022' :[]
    } 
    try:
        printTransactionGreaterSum(myDict,"")
        assert(False)
    except Exception as ex:
        assert(str(ex)=="Suma invalida")

    try:
        printTransactionGreaterSum(myDict,130)
        assert(True)
    except Exception as ex:
        assert(str(ex)=="Suma invalida")

def test_printTransactionBeforeDaySum():
    myDict={
        '13/07/2018':[[130,"intrare"],[1,"iesire"]],
        '14/07/2021':[[150,"iesire"]],
        '01/01/2022' :[]
    } 
    try:
        printTransactionBeforeDaySum(myDict,130,'')
        assert(False)
    except Exception as ex:
        assert(str(ex)=="Ziua/suma sunt invalide")

    try:
        printTransactionBeforeDaySum(myDict,130,'13/07/2021')
        assert(True)
    except Exception as ex:
        assert(str(ex)=="Ziua/suma sunt invalide")
def test_printTransactionType():
    myDict={
        '13/07/2018':[[130,"intrare"],[1,"iesire"]],
        '14/07/2021':[[150,"iesire"]],
        '01/01/2022' :[]
    }
    try:
        printTransactionType(myDict,"iesire")
        assert(True)
    except Exception as ex:
        assert(str(ex)=="Tip invalid") 
    
    try:
        printTransactionType(myDict,"")
        assert(False)
    except Exception as ex:
        assert(str(ex)=="Tip invalid") 
def test_filterTransactionType():
    myDict={
        '13/07/2018':[[130,"intrare"],[1,"iesire"]],
        '14/07/2021':[[150,"iesire"]],
        '01/01/2022' :[]
    }
    myDict_filtered={
        '13/07/2018':[[1,"iesire"]],
        '14/07/2021':[[150,"iesire"]],
    }
    assert(filterTransactionType(myDict,"iesire")==myDict_filtered)
    try:
        filterTransactionType(myDict,'')
        assert(False)
    except Exception as ex:
        assert(str(ex)=="Tip invalid")
        

def test_sumTransactionType():
    myDict={
        '13/07/2018':[[130,"intrare"],[1,"iesire"]],
        '14/07/2021':[[150,"iesire"]],
        '01/01/2022' :[]
    }
    assert (sumTransactionType(myDict,'iesire')==151)
    try:
        sumTransactionType(myDict,'ies')
        assert(False)
    except Exception as ex:
        assert (str(ex)=="Tipul introdus este gresit")

def test_soldByDate():
    myDict={
        '13/07/2018':[[130,"intrare"],[1,"iesire"]],
        '14/07/2021':[[150,"iesire"]],
        '01/01/2022' :[]
    }
    assert(soldByDate(myDict,'01/01/2016')==0)
    assert(soldByDate(myDict,'01/01/2019')==129)
    try:
        soldByDate(myDict,'')
        assert(False)
    except Exception as ex:
        assert(str(ex)=="Date invalide, incercati sa folositi tipul DD:MM:YYYY pentru data.")
    
    #assert()
def test_creareLista():
    myDict={
        '13/07/2018':[[130,"intrare"],[1,"iesire"]],
        '14/07/2021':[[150,"iesire"]],
        '01/01/2022' :[]
    }
    assert(creareLista(myDict)==[['13/07/2018', 130, 'intrare'], ['13/07/2018', 1, 'iesire'], ['14/07/2021', 150, 'iesire']])
  #  print(creareLista(myDict))

def test_sortareLista_bySum():
    myList = [['13/07/2018', 130, 'intrare'], ['13/07/2018', 1, 'iesire'], ['14/07/2021', 150, 'iesire']]
    sortareLista_bySum(myList)
  #  print(myList)
    assert(myList==[['13/07/2018', 1, 'iesire'], ['13/07/2018', 130, 'intrare'], ['14/07/2021', 150, 'iesire']])

def test_filterTransactionLT():
    myDict={
        '13/07/2018':[[130,"intrare"],[1,"iesire"]],
        '14/07/2021':[[150,"iesire"]],
        '01/01/2022' :[]
    }
    myDict_filtered={
        '13/07/2018':[[1,"iesire"]],
        '14/07/2021':[[150,"iesire"]],
    }
    try:
        filterTransactionLT(myDict,'',99)
        assert(False)
    except Exception as ex:
        assert(str(ex)=="Suma/tip invalid")
   # print(filterTransactionLT(myDict,'iesire',151))
    assert(filterTransactionLT(myDict,'iesire',151)==myDict_filtered)
def main():
    test_addTransaction()
    test_createTransaction()
    test_searchInDict()
    test_validateDay()
    test_validateSum()
    test_validateType()
    test_returnTransaction()
    test_updateTransaction()
    test_interval_dates()
    test_deleteTransactions_today()
    test_deleteTransactions_interval()
    test_deleteTransactions_type()
    test_searchMinKey()
    test_filterTransactionType()
    test_soldByDate()
    test_creareLista()
    test_sortareLista_bySum()
    test_sumTransactionType()
    test_filterTransactionLT()
  #  test_printTransactionType()
  #  test_printTransactionGreaterSum()
  #  test_printTransactionBeforeDaySum()
main()