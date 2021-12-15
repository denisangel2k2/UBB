
def run_interface(lista):
    while True:
        
        print("1. Citeste lista de numere")
        print("2. Secventa de lungime maxima care are toate elementele egale")
        print("3. Secventa de lungime maxima care are toate elementele distincte intre ele")
        print("4. Iesire din aplicatie")
        print("5. Secventa in care din oricare 3 elemente consecutive cel putin unul se repeta")

        
        try:
            option = int(input(">>>"))
            if option==1:
                lista=[]
                citire_lista(lista)
            elif option==2:
                print(listaEgala(lista))
            elif option==3:
                print(listaDistincta(lista))
            elif option==4:
                exit()
            elif option==5:
                print(listaTrei(lista))
            else:
                print("Introdu un numar prezentat in optiunile de mai sus")
        except ValueError:
            print("Introdu un numar prezentat in optiunile de mai sus")

def listaEgala(lista):
    """
    Returneaza secventa de lungime maximala in care elementele sunt egale
    din lista transmisa ca parametru
    input : lista - unsigned numbers
    output : lista - unsigned numbers

    """
    if len(lista)==0:
        return None
    lungime=1
    lungime_maxima=0
    index_start=-1
    index_stop=-1
    indexs=0
    indexo=0
    ans=[]
    for i in range(1,len(lista),1):
        if lista[i]==lista[i-1]:
            lungime+=1
            indexo=i
            if lungime>lungime_maxima:
                index_start=indexs
                index_stop=indexo
                lungime_maxima=lungime
        else:
            lungime=1
            indexs=i
            indexo=i

    if index_start==-1 and index_stop==-1:
        index_start=indexs
        index_stop=indexo

    for i in range(index_start, index_stop+1,1):
        ans.append(lista[i])

    return ans


def find(l,x):
    """
    Returneaza true daca x se afla in lista l, false altfel
    input : l - lista de numere reale
            x - numar real
    output : True - daca x se afla in l
             False - altfel
    """
    for i in l:
        if i==x:
            return True
    return False

def test_listaEgala():
    assert(listaEgala([1,2,3,3,3,4,4,5])==[3,3,3])
    assert(listaEgala([1,2,3,3,3,4,4,4,4,5])==[4,4,4,4])
    assert(listaEgala([1])==[1])
    assert(listaEgala([1,2,3,4,5])==[5])
    assert(listaEgala([1,2,2,3,3,4,5])==[2,2])
    assert(listaEgala([])==None)

def  test_listaDistincta():
    assert(listaDistincta([2])==None)
    assert(listaDistincta([1,2,3,3,4,5])==[1,2,3])
    assert(listaDistincta([1,2,1,3])==[1,2])
    assert(listaDistincta([])==None)

def test_listaTrei():
    assert(listaTrei([2])==None)
    assert(listaTrei([1,2])==None)
    assert(listaTrei([])==None)
    assert(listaTrei([1,2,3,4,5,6])==None)
    assert(listaTrei([1,2,2,3])==[1,2,2,3])
    assert(listaTrei([2,2,2,2,2,2])==[2,2,2,2,2,2])
    assert(listaTrei([1,2,2,2,3])==[1,2,2,2,3])
    assert(listaTrei([1,2,2,3,3,4])==[1,2,2,3,3,4])

def listaTrei(lista):
    """
    Returneaza secventa de lungime maximala astfel incat din oricare 3 elemente
    consecutive, cel putin unul se repeta
    input: lista de numere naturale
    output: secventa - lista de numere naturale
    """
    if (len(lista)<3):
        return None

    lungime=2
    lungime_maxima=0
    index_start=0
    index_stop=1
    indexs=0
    indexo=1
    ans=[]
    for i in range(2,len(lista),1):
        #if (lista[i]==lista[i-1] and lista[i]!=lista[i-2]) or (lista[i]!=lista[i-1] and lista[i]==lista[i-2]) or (lista[i-1]==lista[i-2]):
        if lista[i]==lista[i-1] or lista[i]==lista[i-2] or lista[i-1]==lista[i-2]:
            lungime+=1
            indexo=i
            if lungime>lungime_maxima:
                index_start=indexs
                index_stop=indexo
                lungime_maxima=lungime
        else:
            lungime=2
            indexs=i-1
            indexo=i

    if index_start==-1 and index_stop==-1:
        index_start=indexs
        index_stop=indexo

    for i in range(index_start, index_stop+1,1):
        ans.append(lista[i])

    if (len(ans)<3):
        return None

    return ans


def  listaDistincta(lista):
    """
    Returneaza secventa de lungime maximala in care elementele sunt distincte
    intre ele din lista transmisa ca parametru
    input : lista - unsigned numbers
    output : lista - unsigned numbers

    """
    if len(lista)==0:
        return None
    secventa=[lista[0]]
    indexo=0
    indexs=0
    index_start=-1
    index_stop=-1
    lungime=1
    lungime_maxima=1
    ans=[]
    for i in range(1,len(lista),1):
        if find(secventa,lista[i])==False:
            lungime+=1
            indexo=i
            secventa.append(lista[i])
            if lungime>lungime_maxima:
                lungime_maxima=lungime
                index_start=indexs
                index_stop=indexo
        else:
            lungime=1
            secventa=[lista[i]]
            indexs=i
            indexo=i
    
    if lungime_maxima==1:
        return

    for i in range(index_start, index_stop+1,1):
        ans.append(lista[i])
    
    return ans




def citire_lista(lista):
    """
    Citeste o lista de numere naturale in parametrul
    lista
    input : lista - numere naturale
    output : -
    """
    txt=input()
    for s in txt.split():
        if s.isdigit():
            lista.append(int(s))

def main():
    
    
    lista=[]
    test_listaEgala()
    test_listaDistincta()
    test_listaTrei()
    run_interface(lista)

main()
    

