import pickle

from cautare_tranzactii import *
from adaugare_tranzactii import addTransaction, updateTransaction
from init_functions import searchInDict
from rapoarte import soldByDate, sumTransactionType,creareLista,sortareLista_bySum, printByType_sumOrdered
from stergere_tranzactii import deleteTransactions_interval, deleteTransactions_today, deleteTransactions_type

def functionality_add_transaction(myDict,a_file):
    """
    Afiseaza interfata de lucru cu utilizatorul pe baza dictionarului myDict transmis ca parametru conform cerintei 1.
    input : myDict - dictionar
            a_file - fisierul cu datele salvate din dictionarul myDict in rulari anterioare
    output: 
    """
   
    
    while(True):
        try:
            print("     1. Adaugare tranzactie")
            print("     2. Actualizare tranzactie") 
            print("     99. Inapoi")
            alegere=int(input(">>>"))

            if alegere==1:
                while(True):

                    ziua=input("Introduceti ziua tranzactiei sub forma DD/MM/YYYY: ")
                    suma=float(input("Introduceti suma de bani dorita: "))
                    tip=input("Introduceti tipul tranzactiei (intrare/iesire): ")
                    
                    
                    try:
                        addTransaction(ziua,suma,tip,myDict)
                        print(myDict)
                        break
                    except Exception as ex:
                        print(str(ex))
            elif alegere==2:
                while(True):

                    ziua=input("Introduceti ziua tranzactiei sub forma DD/MM/YYYY: ")
                    suma=float(input("Introduceti suma de bani cautata: "))
                    tip=input("Introduceti tipul tranzactiei (intrare/iesire): ")
                   
                    
                    try:
                        suma_nou=float(input("Introduceti noua suma de bani dorita: "))
                        tip_nou=input("Introduceti noul tip al tranzactiei (intrare/iesire): ")
                    except ValueError:
                        print("Introduceti un numar")
                    
                    try:
                        updateTransaction(ziua,suma,tip,myDict,suma_nou,tip_nou)
                        print(myDict)
                        break
                    except Exception as ex:
                        print(str(ex))
            elif alegere==99:
                break
        except ValueError:
            print("Introduceti un numar de mai sus")
        


    a_file=open("data.pkl","wb")
    pickle.dump(myDict,a_file) #aici il salvez dupa ce ii modificat
    a_file.close()
def functionality_delete_transaction(myDict,a_file):
    """
    Afiseaza interfata de lucru cu utilizatorul pe baza dictionarului myDict transmis ca parametru conform cerintei 2.
    input : myDict - dictionar
            a_file - fisierul cu datele salvate din dictionarul myDict in rulari anterioare
    output:
    """
    while(True):
        try:
            print("     1. Sterge toate tranzactiile dintr-o anumita zi")
            print("     2. Sterge toate tranzactiile dintr-un interval de zile")
            print("     3. Sterge toate tranzactiile de un anumit tip")
            print("     99. Inapoi")
            alegere=int(input(">>>"))

            if alegere==1:

                while(True):
                    ziua=input("Introduceti ziua tranzactiei sub forma DD/MM/YYYY: ")
                    
                    try:
                        deleteTransactions_today(myDict,ziua)
                        print(myDict)
                        break
                    except Exception as ex:
                        print(str(ex))
                    

            elif alegere==2:
                while(True):
                    ziua_inceput=input("Introduceti ziua de inceput sub forma DD/MM/YYYY: ")
                    ziua_sfarsit=input("Introduceti ziua de sfarsit sub forma DD/MM/YYYY: ")
                    try:
                        deleteTransactions_interval(myDict,ziua_inceput,ziua_sfarsit)
                        print(myDict)
                        break
                    except Exception as ex:
                        print(str(ex))
            elif alegere==3:
                while(True):
                    tip=input("Introduceti tipul tranzactiei: ")
                    try:
                        deleteTransactions_type(myDict,tip)
                        print(myDict)
                        break
                    except Exception as ex:
                        print(str(ex))

            elif alegere==99:
                break
        except ValueError:
            print("Introduceti un numar de mai sus")

    


    a_file=open("data.pkl","wb")
    pickle.dump(myDict,a_file) #aici il salvez dupa ce ii modificat
    a_file.close()
def functionality_search_transaction(myDict,a_file):
    '''
    Afiseaza interfata de lucru cu utilizatorul pe baza dictionarului myDict transmis ca parametru conform cerintei 3.
    input : myDict - dictionar
            a_file - fisierul cu datele salvate din dictionarul myDict in rulari anterioare
    output:
    '''
    while (True):
        try:
            print("     1. Tipareste tranzacțiile cu sume mai mari decât o suma data")
            print("     2. Tipareste tranzactiile efectuate inainte de o zi si mai mari decat o suma")
            print("     3. Tipareste tranzactiile de un anumit tip")
            print("     99. Inapoi")
            alegere = int(input('>>>'))

            if alegere==1:
                while(True):
                    suma=float(input("Introduceti suma dorita: "))
                    try:
                        printTransactionGreaterSum(myDict,suma)
                        break
                    except Exception as ex:
                        print(str(ex))
                   
            elif alegere==2:
                while(True):
                    suma=float(input("Introduceti suma dorita: "))
                    ziua=input("Introduceti ziua dorita sub forma DD/MM/YYYY: ")
                    try:
                        printTransactionBeforeDaySum(myDict,suma,ziua)
                        break
                    except Exception as ex:
                        print(str(ex))
            elif alegere==3:
                while(True):
                    tip=input("Introduceti tipul tranzactiei: ")
                    try:
                        printTransactionType(myDict,tip)
                        break
                    except Exception as ex:
                        print(str(ex))
            elif alegere==99:
                break
        except ValueError:
            print("Introduceti un numar de mai sus")
    a_file=open("data.pkl","wb")
    pickle.dump(myDict,a_file) #aici il salvez dupa ce ii modificat
    a_file.close()

def functionality_report_transaction(myDict,a_file):
    '''
    Afiseaza interfata de lucru cu utilizatorul pe baza dictionarului myDict transmis ca parametru conform cerintei 3.
    input : myDict - dictionar
            a_file - fisierul cu datele salvate din dictionarul myDict in rulari anterioare
    output:
    '''
    while (True):
        try:
            print("     1. Suma totala a tranzactiilor de un anumit tip")
            print("     2. Soldul contului la o data specificata")
            print("     3. Tipareste toate tranzactiile de un anumit tip ordonat dupa suma")
            print("     99. Inapoi")
            alegere = int(input('>>>'))

            if alegere==1:
                while(True):
                    tip=input("Introduceti tipul tranzactiei: ")
                    try:
                        l=sumTransactionType(myDict,tip)
                        print("SOLD :"+ str(l))
                        break
                    except Exception as ex:
                        print(str(ex))
                   
            elif alegere==2:
                while(True):
                    ziua=input("Introduceti ziua dorita sub forma DD/MM/YYYY: ")
                    try:
                        S=soldByDate(myDict,ziua)
                        print("SOLD : "+str(S))
                        break
                    except Exception as ex:
                        print(str(ex))

            elif alegere==3:
                while(True):
                    tip=input("Introduceti tipul tranzactiei: ")
                    try:
                        l=creareLista(myDict)
                        sortareLista_bySum(l)
                        printByType_sumOrdered(l,tip)
                        break
                    except Exception as ex:
                        print(str(ex))

            elif alegere==99:
                break
        except ValueError:
            print("Introduceti un numar de mai sus")
    a_file=open("data.pkl","wb")
    pickle.dump(myDict,a_file) #aici il salvez dupa ce ii modificat
    a_file.close()
def functionality_filter_transaction(myDict,a_file): #aici sunt niste simple afisari functiile
    pass
def functionality_undo(myDict,a_file):
    pass

def run(myDict):
    """
    Afiseaza interfata de lucru cu utilizatorul pe baza dictionarului myDict transmis ca parametru
    input : myDict - dictionar
    output: 
    """
    
    a_file = open("data.pkl","rb")
    myDict=pickle.load(a_file) # aici deschid fisierul si il bag in dictionar
    #print(myDict)
    


    while(True):
        print("1. Adaugare de noi tranzactii")
        print("2. Stergere de tranzactii")
        print("3. Cautari de tranzactii")
        print("4. Rapoarte")
        print("99. Iesire")

        try:
            alegere=int(input(">>>"))
            if alegere==1:
                functionality_add_transaction(myDict,a_file)
            elif alegere==2:
                functionality_delete_transaction(myDict,a_file)
            elif alegere==3:
                functionality_search_transaction(myDict,a_file)
            elif alegere==4:
                functionality_report_transaction(myDict,a_file)
            elif alegere==99:
                exit()
        except ValueError:
            print("Introduceti un numar de mai sus")
    