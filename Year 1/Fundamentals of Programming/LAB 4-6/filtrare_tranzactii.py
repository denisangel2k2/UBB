from adaugare_tranzactii import addTransaction
from init_functions import validateSum, validateType


def filterTransactionType(myDict, tip):
    '''
    Returneaza un dictionar filtrat pe baza dictionarului myDict si a tipului tip
    input: myDict - dictionar
           tip - string
    output: dictionar 
    '''
    if validateType(tip):
        
        myDict_filtered={}
        for key,value in myDict.items():
            for i in range(len(value)):
             if(value[i][1]==tip):
                addTransaction(key,value[i][0],value[i][1],myDict_filtered)
        return myDict_filtered
    else: raise Exception("Tip invalid")

def filterTransactionLT(myDict, tip, suma):
    '''
    Returneaza un dictionar filtrat pe baza dictionarlui myDict cu
    toate tranzacțiile mai mici decât o sumă dată care 	
	au tipul specificat
    input: myDict - dictionar
           tip - string
           suma - float 
    output: dictionar
    '''
    if validateSum(suma) and validateType(tip):
        myDict_filtered={}
        for key,value in myDict.items():
            for i in range(len(value)):
                if value[i][1]==tip  and suma-value[i][0]>0.000001:
                    addTransaction(key,value[i][0],value[i][1],myDict_filtered)
        return myDict_filtered
    else: raise Exception("Suma/tip invalid")

def main():
    myDict={
        '13/07/2018':[[130,"intrare"],[1,"iesire"]],
        '14/07/2021':[[150,"iesire"]],
        '01/01/2022' :[]
    } 
    print(filterTransactionLT(myDict,"iesire",151))

main()