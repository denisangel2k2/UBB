from domain.entities import Jucator
class srvJucator(object):
    def __init__(self,repo,vali):
        self.__repo=repo
        self.__vali=vali

    def srv_add(self,nume,prenume,inaltime,post):
        '''
        Functia adauca la lista de jucatori, jucatorul cu campurile primite ca parametrii
        @param nume: str
        @param prenume: str
        @param inaltime: int
        @param post: str
        @return: -
        '''
        juc=Jucator(nume,prenume,inaltime,post)
        self.__vali.validateJucator(juc)
        self.__repo.add(juc)
        
    def srv_change(self,nume,prenume,inaltime):
        '''
        Functia modifica inaltimea unui jucator din lista de jucatori cu campurile din parametrii
        @param nume: str
        @param prenume: str
        @param inaltime: int
        @return: -
        '''
        jucator_modif=Jucator(nume,prenume,inaltime,"Fundas")
        self.__vali.validateJucator(jucator_modif)
        self.__repo.change(jucator_modif)

    def srv_team(self):
        '''
        Functia returneaza o lista cu echipa de 5 jucatori
        @param: -
        @return: list of jucator objects
        '''
        return self.__repo.team()
    
    def srv_fileadd(self,file_path):
        '''
        Functia returneaza cati jucatori au fost adaugati din fisierul care are path-ul in parametru
        @param file_path: str
        @return: int 
        '''
        return self.__repo.fileadd(file_path)