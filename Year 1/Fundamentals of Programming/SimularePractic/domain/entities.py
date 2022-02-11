class Jucator:
    def __init__(self,nume,prenume,inaltime,post):
        self.__nume = nume
        self.__prenume = prenume
        self.__inaltime = inaltime
        self.__post = post

    def get_nume(self):
        return self.__nume

    def get_prenume(self):
        return self.__prenume

    def get_inaltime(self):
        return self.__inaltime

    def get_post(self):
        return self.__post


    def set_inaltime(self, value):
        self.__inaltime = value
        
    def set_post(self,post):
        self.__post=post
    
    def __eq__(self,juc2):
        return self.__prenume==juc2.get_prenume() and self.__nume==juc2.get_nume()
            
    def __str__(self):
        return f"{self.__prenume}\t{self.__nume}\t{self.__post}\t{str(self.__inaltime)}"
    
  
        