import unittest
from pywin.framework import startup
class Teste(unittest.TestCase):

    def setUp(self):
        self.__lista=[5,3,1,7,9,2,16,13]
        self.__sorter=Sortings()
        self.__lista_sortata=[1,2,3,5,7,9,13,16]


    def testQuick(self):
        l=self.__lista
        self.__sorter.QuickSort(self.__lista,0,len(l))
        self.assertTrue(self.__lista_sortata==l)

    def testSelection(self):
        l=self.__lista
        self.__sorter.SelectionSort(l)
        self.assertTrue(self.__lista_sortata==l)
    
    def testSelection2(self):
        l=self.__lista
        self.__sorter.SelectionSort2(l)
        self.assertTrue(self.__lista_sortata==l)

    def testBubble(self):
        l=self.__lista
        self.__sorter.BubbleSort(l)
        self.assertTrue(self.__lista_sortata==l)

    def testInsertion(self):
        l=self.__lista
        self.__sorter.InsertionSort(l)
        self.assertTrue(self.__lista_sortata==l)
    
    def testMerge(self):
        l=self.__lista
        self.__sorter.MergeSort(l, 0, len(l)-1)
        #print(l)
        #print(self.__lista_sortata)
        self.assertTrue(l==self.__lista_sortata)

class Sortings:
    def __init__(self):
        pass
    
    
    def pivot(self, lista, left, right):

        '''
        Pivotul este pe ultima pozitie iar in variabila i se tine minte indexul ultimului numar mai mic ca si pivotul
        Numerele mai mici ca si pivotul sunt pozitionate la inceputul listei
        '''

        i=left-1
        pivot=lista[right-1]
        i_pivot=right-1
        for j in range(left, right):
            if lista[j] <= pivot:
                i+=1
                lista[i], lista[j] = lista[j], lista[i]
        
        #lista[i+1], lista[i_pivot] = lista[i_pivot], lista[i+1]
        
        return (i)

   
    def QuickSort(self, lista, left, right):
        if left < right:
            Pivot=self.pivot(lista, left, right)

            self.QuickSort(lista, left, Pivot)
            self.QuickSort(lista, Pivot+1, right)
            

    def SelectionSort(self, lista): #teta(n^2)
        for i in range(len(lista)-1):
            for j in range(i+1,len(lista)):
                if lista[i]>lista[j]:
                    lista[i], lista[j] = lista[j], lista[i]
        
    
    def SelectionSort2(self,lista): #teta(n^2)
        for i in range(len(lista)-1):
            imin=i
            Min=lista[i]
            for j in range(i+1, len(lista)):
                if lista[j]<Min:
                    Min=lista[j]
                    imin=j
            lista[imin], lista[i] = lista[i], lista[imin]
            
            
    def BubbleSort(self, lista):
        ok=False
        while not ok:
            ok=True
            for i in range(len(lista)-1):
                if lista[i]>lista[i+1]:
                    lista[i], lista[i+1] = lista[i+1], lista[i]
                    ok=False
    
    def InsertionSort(self, lista):
        for i in range(len(lista)):
            ind=i-1
            nr=lista[i]
            while ind>=0 and nr<lista[ind]:
                lista[ind+1]=lista[ind]
                ind-=1
                         
            lista[ind+1]=nr
    
    def Merge(self, l, start, end, mij):
        i=start
        j=mij+1
        aux=[None]*len(l)
        k=start
        while i<=mij and  j<=end:
            if l[i] < l[j]:
                aux[k]=l[i]
                i+=1
                k+=1
            else:
                aux[k]=l[j]
                j+=1
                k+=1
        
        while i<=mij:
            aux[k]=l[i]
            i+=1
            k+=1
        
        while j<=end:
            aux[k]=l[j]
            j+=1
            k+=1
                    
        for i in range(start, end+1):
            l[i]=aux[i]    
            
    def MergeSort(self, lista, st, dr):
        
        if st<dr:
            
            mij=(st+dr)//2
            self.MergeSort(lista, st, mij)
            self.MergeSort(lista, mij+1, dr)
            self.Merge(lista, st, dr, mij)
            

def main():  
    unittest.main()
    


   
main()