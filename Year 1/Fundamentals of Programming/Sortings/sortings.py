import unittest
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

    def testBubble(self):
        l=self.__lista
        self.__sorter.BubbleSort(l)
        self.assertTrue(self.__lista_sortata==l)


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
        for j in range(left, right-1):
            if lista[j] <= pivot:
                i+=1
                lista[i], lista[j] = lista[j], lista[i]
        
        lista[i+1], lista[i_pivot] = lista[i_pivot], lista[i+1]
        
        return (i+1)

   
    def QuickSort(self, lista, left, right):
        if left < right:
            Pivot=self.pivot(lista, left, right)

            self.QuickSort(lista, left, Pivot)
            self.QuickSort(lista, Pivot+1, right)

    '''def QuickSort_pythonic(self, lista):

        if len(lista)<=1:
            return lista
        pivot=lista.pop()
        lower=self.QuickSort_pythonic([el for el in lista if el<pivot])
        greater=self.QuickSort_pythonic([el for el in lista if el>=pivot])
        return lower+[pivot]+greater'''

    def SelectionSort(self, lista):
        for i in range(len(lista)-1):
            for j in range(i+1,len(lista)):
                if lista[i]>lista[j]:
                    lista[i], lista[j] = lista[j], lista[i]
    
    def BubbleSort(self, lista):
        ok=False
        while not ok:
            ok=True
            for i in range(len(lista)-1):
                if lista[i]>lista[i+1]:
                    lista[i], lista[i+1] = lista[i+1], lista[i]
                    ok=False
    

def main():  
    unittest.main()
   
main()