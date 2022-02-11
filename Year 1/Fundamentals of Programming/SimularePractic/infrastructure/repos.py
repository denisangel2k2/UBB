from domain.entities import Jucator
from errors.erori import RepoError
import random
class repoJucator(object):
    
    def __init__(self, filepath):
        self.__filepath=filepath
        self.__repoList=[]
        
    def __read_from_file(self):
        '''
        Functia citeste jucatorii din fisier si ii adauga in lista de jucatori
        '''
        self.__repoList=[]
        with open(self.__filepath, "r") as f:
            content=f.read()
            lines=content.split("\n")
            for line in lines:
                if line.strip()!="":
                    parts=line.split(" ")
                    juc=Jucator(parts[0],parts[1],parts[2],parts[3])
                    self.__repoList.append(juc)

    def __append_to_file(self, jucator):
        '''
        Functia adauga un jucator la fisierul de jucatori
        @param jucator: jucator object
        '''
        with open(self.__filepath, "a") as f:
            f.write(f"{str(jucator.get_nume())} {str(jucator.get_prenume())} {str(jucator.get_inaltime())} {str(jucator.get_post())}\n")
            
    def write_nothing(self):
        '''
        Functia scrie nimic in fisierul de jucatori
        '''
        with open(self.__filepath, "w") as f:
            f.write("")
            
    def __unique(self,jucator):
        '''
        Functia verifica daca un jucator se afla deja in lista
        @param jucator: jucator object
        @return: True - daca se afla
                False - altfel
        '''
        for juc in self.__repoList:
            if juc==jucator:
                return True
            
        return False
        
    def add(self,jucator):
        '''
        Functia adauga un jucator la lista de jucatori
        @param jucator: jucator object
        '''
        self.__read_from_file()
        self.__append_to_file(jucator)
        self.__repoList.append(jucator)
        
    def change(self, jucator_modif):
        '''
        Functia modifica inaltimea unui jucator din lista
        @param jucator_modif: jucator object
        @raise RepoError: daca jucatorul nu exista in lista 
        '''
        self.__read_from_file()
        self.write_nothing()
        sw=0
        for juc in self.__repoList:
            if juc==jucator_modif:
                sw=1
                juc.set_inaltime(jucator_modif.get_inaltime())
                
        
        for juc in self.__repoList:
            self.__append_to_file(juc) #refac lista iarasi
                
        if sw==0:
            raise RepoError("Acest jucator nu exista!")
        
    def __split_people(self,piv,extr,funda):
        '''
        Functia imparte lista de jucatori in lista in functie de postul jucatorului
        @param piv, extr, funda: list 
        '''
        for juc in self.__repoList:
            
            if juc.get_post()=="Pivot":
                piv.append(juc)
            elif juc.get_post()=="Fundas":
                funda.append(juc)
            elif juc.get_post()=="Extrema":
                extr.append(juc)
        
    def team(self):
        '''
        Functia returneaza o lista cu o echipa de jucatori
        @raise RepoError: Daca nu sunt destui jucatori pentru a forma o echipa
        '''
        self.__read_from_file()
        
        lista=[]
        pivoti=[]
        extreme=[]
        fundasi=[]
        self.__split_people(pivoti, extreme, fundasi)
        
        pivoti=sorted(pivoti, key=lambda x: x.get_inaltime(), reverse=True)
        extreme=sorted(extreme, key=lambda x: x.get_inaltime(), reverse=True)
        fundasi=sorted(fundasi, key=lambda x: x.get_inaltime(), reverse=True)
        lista.append("Prenume\tNume\tPost\tInaltime\n")
        
        if len(pivoti)>=1 and len(extreme)>=2 and len(fundasi)>=2:
            lista.append(str(fundasi[0]))
            lista.append(str(fundasi[1]))
            lista.append(str(pivoti[0]))
            lista.append(str(extreme[0]))
            lista.append(str(extreme[1]))
            
        else: raise RepoError("Nu sunt destui jucatori!\n")
        
        return lista
    
    def fileadd(self, file_path):
        '''
        Functia adauga jucatori dintr-un fisier la lista de jucatori si returneaza cati jucatori au fost adaugati
        @param file_path: str
        @return: int 
        @raise RepoError: Daca nu exista fisierul 
        '''
        self.__read_from_file()
        cati=0
        try:
            f=open(file_path,"r")
            content=f.read()
            lines=content.split("\n")
            for line in lines:
                if line.strip()!="":
                    parts=line.split(" ")
                    
                    posturi=["Pivot","Fundas","Extrema"]
                    inaltime=random.randint(150,250)
                    ind=random.randint(0,2)
                    post=posturi[ind]
                    
                    jucatorul=Jucator(parts[0],parts[1],inaltime,post)
                    if self.__unique(jucatorul)==False:
                        cati+=1
                        self.add(jucatorul)
            f.close()
            
        except IOError:
            raise RepoError("Nu exista un fisier cu numele "+file_path+"!\n")
    
        
        
        return cati
    
    def __len__(self):
        return len(self.__repoList)
            
    def getall(self):
        return self.__repoList