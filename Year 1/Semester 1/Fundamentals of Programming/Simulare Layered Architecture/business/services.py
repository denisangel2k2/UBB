from domain.entities import Pictura

class ServicePictura(object):
    def __init__(self,repo):
        self.__repoPictura=repo
    
    def service_funct1(self,sir):
        '''
        Function that returns a list of every painting that contains a given text inside
        @param sir: string
        @return: list of strings  
        @raise RepoError: if the given parameter is not found in any of the picture names
        '''
        return self.__repoPictura.functionalitate1(sir)
    
    def service_funct2(self):
        '''
        Function that returns a dictionary of every author's latest picture
        @param : none
        @return: dictionary
        '''
        return self.__repoPictura.functionalitate2()
        


