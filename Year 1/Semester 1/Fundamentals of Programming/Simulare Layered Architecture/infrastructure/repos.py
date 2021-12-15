from domain.entities import Pictura
from errors.errors import RepoError
class RepoPictura(object):
    def __init__(self,filepath):
        self.__filepath=filepath
        self.__picturi=[]

    def __ReadFromFile(self):
        '''
        Function that reads all pictures from file and stores them into the repo list
        '''
        self.__picturi=[]
        with open(self.__filepath, "r") as f:
            content=f.read()
            lines=content.split('\n')
            for line in lines:
                if line.strip()!="":
                    parts=line.split(",")
                    id=int(parts[0])
                    nume=parts[1]
                    nume_autor=parts[2]
                    an=int(parts[3])
                    pictura=Pictura(id, nume, nume_autor, an)
                    self.__picturi.append(pictura)
                    
    def functionalitate1(self,sir):
        '''
        Function that returns a list of every painting that contains a given text inside
        @param sir: string
        @return: list of strings  
        @raise RepoError: if the given parameter is not found in any of the picture names
        '''
        self.__ReadFromFile()
        exista=False
        l=[]
        sir=sir.lower()
        
        for pictura in self.__picturi:
            nume_pictura=pictura.get_nume().lower()
            if sir in nume_pictura:
                exista=True
                l.append(pictura)
                
        if exista==False:
            raise RepoError("Nu exista picturi de acest fel!")
        
        l=sorted(l, key=lambda x : x.get_an(), reverse=True)
        lista_string=[]
        for pictura in l:
            lista_string.append(str(pictura))
        
        return lista_string[:]
        
        
        
    def functionalitate2(self):
        '''
        Function that returns a dictionary of every author's latest picture
        @param : none
        @return: dictionary
         
        '''
        self.__ReadFromFile()
        l=[]
        for pictura in self.__picturi:
            l.append(pictura)
        
        l=sorted(l, key=lambda x : x.get_an(), reverse=True)
        dict={}
        for pictura in l:
            s=str(str(pictura.get_an())+","+pictura.get_nume())
            if pictura.get_nume_autor() in dict:
                dict[pictura.get_nume_autor()].append(s)
            else:
                dict[pictura.get_nume_autor()]=[s]
        
        return dict
    