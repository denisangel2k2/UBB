from infrastructure.repos import repoCarte,repoImprumut
class serviceCarte(object):
    def __init__(self,repoC):
        self.__repoC=repoC
    
    def servFunc1(self,sir):
        '''
        Functia din service care se ocupa cu returnarea unei lista cu toate cartile al caror nume se termina intr-un anumit sir
        @param sir: string
        @return: list 
        '''
        return self.__repoC.func1(sir)

class serviceImprumut(object):
    
    def __init__(self,repoI):
        self.__repoI=repoI
        
    def servFunc2(self,durata):
        '''
        Functia din service care se ocupa cu returnarea unei liste cu toate imprumuturile cu durata data
        @param durata: int
        @return: list  
        '''
        return self.__repoI.func2(durata)


