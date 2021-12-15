from domain.entities import Carte,Imprumut
from errors.errors import RepoError
class repoImprumut(object):
    def __init__(self,filepath):
        self.__filepath=filepath
        self.__repoI=[]

    def __readFromFile(self):
        '''
        Functia care citeste toate datele din fisier si le stocheaza in repo
        '''
        self.__repoI=[]
        
        with open(self.__filepath, "r") as f:
            content=f.read()
            
            lines=content.split('\n')
            for line in lines:
                if line.strip()!='':
                    parts=line.split(",")
                    
                    id=int(parts[0])
                    id_carte=int(parts[1])
                    data_imprumut=parts[2]
                    durata=int(parts[3])
                    
                    imprumut=Imprumut(id,id_carte,data_imprumut,durata)
                    
                    self.__repoI.append(imprumut)
    
    def func2(self,durata):
        '''
        Functia din repo care se ocupa cu returnarea unei liste cu toate imprumuturile cu durata data
        @param durata: int
        @return: list  
        '''
        self.__readFromFile()
        l=[]
        sw=False
        for imprumut in self.__repoI:
            if imprumut.get_durata()==durata:
                sw=True
                l.append(str(imprumut))
                
        if sw==False:
            raise RepoError("Nu exista astfel de imprumuturi!")
        
        return l
    
class repoCarte(object):
    def __init__(self,filepath):
        self.__filepath=filepath
        self.__repoC=[]
        
    def __readFromFile(self):
        '''
        Functia care citeste toate datele din fisier si le stocheaza in repo
        '''
        self.__repoC=[]
        
        with open(self.__filepath, "r") as f:
            content=f.read()
            
            lines=content.split('\n')
            for line in lines:
                if line.strip()!='':
                    parts=line.split(",")
                    
                    id=int(parts[0])
                    nume_carte=parts[1]
                    autor=parts[2]
                    an=int(parts[3])
                    
                    carte=Carte(id,nume_carte,autor,an)
                    
                    self.__repoC.append(carte)
    

    def func1(self,sir):
        '''
        Functia din repo care se ocupa cu returnarea unei lista cu toate cartile al caror nume se termina intr-un anumit sir
        @param sir: string
        @return: list 
        '''
        self.__readFromFile()
        sw=False
        l=[]
        l_print=[]
        for carte in self.__repoC:
            if carte.get_nume_carte().endswith(sir):
                l.append(carte)
                sw=True
                
        if sw==False:
            raise RepoError("Nu exista astfel de carti!")
        
        l=sorted(l, key= lambda x: x.get_an())
        for el in l:
            l_print.append(str(el))
            
        return l_print
        