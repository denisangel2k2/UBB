class Pictura(object):
    def __init__(self,id,nume,nume_autor,an):
        self.__id = id
        self.__nume = nume
        self.__nume_autor = nume_autor
        self.__an = an

    def get_id(self):
        return self.__id

    def get_nume(self):
        return self.__nume

    def get_nume_autor(self):
        return self.__nume_autor

    def get_an(self):
        return self.__an
    
    def __str__(self):
 
        
        return f"{str(self.__id)},{self.__nume},{self.__nume_autor},{str(self.__an)}"
    
        
        


