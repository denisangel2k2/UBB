class Carte(object):
    def __init__(self,id,nume_carte,autor,an):
        self.__id = id
        self.__nume_carte = nume_carte
        self.__autor = autor
        self.__an = an
        
    

    def get_id(self):
        return self.__id


    def get_nume_carte(self):
        return self.__nume_carte


    def get_autor(self):
        return self.__autor

    def get_an(self):
        return self.__an

    def __str__(self):
        return f"{str(self.__id)}, {self.__nume_carte}, {self.__autor}, {str(self.__an)}"
    

class Imprumut(object):
    def __init__(self,id, idc, dataI,durata):
        self.__id = id
        self.__idc = idc
        self.__dataI = dataI
        self.__durata = durata
        
    

    def get_id(self):
        return self.__id


    def get_idc(self):
        return self.__idc


    def get_data_i(self):
        return self.__dataI


    def get_durata(self):
        return self.__durata

    def __str__(self):
        return f"{str(self.__id)},{str(self.__idc)},{self.__dataI},{str(self.__durata)}"

