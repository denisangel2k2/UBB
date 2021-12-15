from errors.errors import RepoError
class Consola(object):
    def __init__(self,servicePictura):
        self.__servicePictura=servicePictura
        self.__comenzi={
            'f1':self.__ui_f1,
            'f2':self.__ui_f2
            }
        
    def __ShowMenu(self):
        '''
        Function that prints every possible command
        '''
        print("Functionalitatea 1: f1")
        print("Functionalitatea 2: f2")
        print("\t exit- Iesire\t help- Afisare meniu")
        
    def __ui_f1(self):
        '''
        UI for the functionality 1
        '''
        sir=input("Introduceti sirul pe care doriti sa il cautati: ")
        try:
            lista=self.__servicePictura.service_funct1(sir)
            for el in lista:
                print(el)
        except RepoError as re:
            print(str(re))
            
    def __ui_f2(self):
        '''
        UI for the functionality 2
        '''
        dict=self.__servicePictura.service_funct2()
        for key,el in dict.items():
            print(str(key)+": "+el[0])
        
    
    def run(self):
        '''
        Run method for the Console class
        '''
        self.__ShowMenu()
        while(True): 
            cmd=input(">>>")
            if cmd in self.__comenzi:
                self.__comenzi[cmd]()
            elif cmd=="exit":
                exit()
            elif cmd=="help":
                self.__ShowMenu()

            
    
    
    
    



