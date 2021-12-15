
def createTransaction(ziua,suma,tip):
    """
    se creeaza tranzacita care are la baza ziua, suma, si tipul
    input: ziua - string
            suma : float
            tip : string
    output: -
    raises : data iese din calendar 
             suma este string 
             tipul este altceva in afara de intrare/iesire
             === "Date invalide, incercati sa folositi tipul DD:MM:YYYY pentru data.\nSuma trebuie sa fie un numar, iar tipul poate fi\ndoar iesire/intrare"
             
    """

    if validateDay(ziua) and validateSum(suma) and validateType(tip):
        '''
        return {
            'ziua' : ziua,
            'suma' : float(suma),
            'tip' : tip
        }
        '''
        return [ziua,suma,tip]

    else:
        raise Exception("Date invalide, incercati sa folositi tipul DD:MM:YYYY pentru data.\nSuma trebuie sa fie un numar, iar tipul poate fi\ndoar iesire/intrare")

def validateType(tip):
    """
    verifica daca tipul tranzactiei este fie "intrare", fie "iesire"
    input: tip - string
    output: True, daca tip="intrare" sau "iesire"
            False, altfel
    """
    if tip=="intrare" or tip=="iesire":
        return True
    else:
        return False

def validateSum(suma):
    """
    verifica daca suma de tip float este intr-adevar float
    input: suma - float
    output: True - daca suma este de tip float
            False - altfel
    """
    try:
        float(suma)
        return True
    except ValueError:
        return False
  
def validateDay(ziua):
    """
    valizdeaza string-ul ziua asa incat sa se potriveasca tipului dd/mm/yyyy
    input: ziua - string
    output: True - daca ziua este buna
            False - altfel
    """
    delim = "/"
    temp = ziua.split(delim)
    if len(temp)!=3:
        return False
    # 31 : 1,3,5,7,8,10,12
    # 30 : 4,6,9,11
    # 28 : 2 
    # 29 : 2 - daca (an%4==0 si an%100!=0) sau (an%400==0)
    try:
        day=int(temp[0])
        month=int(temp[1])
        year=int(temp[2])

        if len(temp[0])<2 or len(temp[1])<2:
            return False

        if month>12 or month<1:
            return False

        if day>31:
            return False

        if month==2:
            if day>29:
                return False

            elif day==29:
                if not((year%4==0 and year%100!=0) or year%400==0):
                    return False
                else: 
                    return True
            elif day>0 and day<29:
                return True

        if day==31:
            if month==1 or month==3 or month==5 or month==7 or month==8 or month==10 or month==12:
                return True
            else:
                return False
        elif day>0:       
            return True

    except ValueError:
        return False

def getDay(tranzactie):
    
    """
    intoarce ziua tranzactiei cerute
    input: tranzactie
    output: ziua tranzactiei - string
    """
    #return tranzactie['ziua']
    return tranzactie[0]

def getSum(tranzactie):
    """
    intoarce suma tranzactiei cerute
    input: tranzactie
    output: suma tranzactiei - float
    """
   #return tranzactie['suma']
    return tranzactie[1]

def getType(tranzactie):
    """
    intoarce tipul tranzactiei cerute
    input: tranzactie
    output: tipul tranzactiei cerute - string
    """
    #return tranzactie['tip']
    return tranzactie[2]

def searchInDict(myDict,key):
    """
    cauta in dictionarul myDict cheia key, iar daca o gaseste returneaza True
    altfel returneaza False
    input: myDict - dictionar
           key : string
    output: True daca exita cheia in dictionar
            False altfel
    """
    if key in myDict.keys(): #poate doar myDict
        return True
    return False

def searchMinKey(myDict):
    """
    cauta cel mai mic an din toate cheile dictionarului myDict si returneaza un string de forma 01/01/anul minim
    input : myDict - dictionar
    output : string
    """
    
    minimum=""
    for key in myDict.keys():
        temp=key.split("/")
        if minimum=="":
            minimum=temp[2]
        else:
            if int(minimum)>int(temp[2]):
                minimum=temp[2]
        
    data="01/01/"+minimum
    return data

