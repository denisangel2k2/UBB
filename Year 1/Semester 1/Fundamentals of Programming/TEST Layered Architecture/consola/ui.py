from errors.errors import RepoError
class Consola(object):
    def __init__(self,srvI, srvC):
        self.__srvI=srvI
        self.__srvC=srvC
        self.__comenzi={
            'f1':self.__ui_f1,
            'f2':self.__ui_f2
            }
        
    def __showmenu(self):
        '''
        Functia care afiseaza meniul
        '''
        print("Carti care se termina intr-un anumit sir: f1")
        print("Toate imprumuturile care au durata un numar dat: f2")
        print("\t exit- Iesire \t help- Afisare meniu")
            
    def __ui_f1(self):
        '''
        Functia din ui care se ocupa cu returnarea unei lista cu toate cartile al caror nume se termina intr-un anumit sir
        '''
        sir=input("Introduceti sirul de caractere: ")
        try:
            l=self.__srvC.servFunc1(sir)
            for el in l:
                print(el)
        except RepoError as re:
            print(str(re))
            
    def __ui_f2(self):
        '''
        Functia din ui care se ocupa cu returnarea unei liste cu toate imprumuturile cu durata data
        '''
        try:
            durata=int(input("Introduceti durata: "))
            if durata<0:
                print ("Introduceti date valide!")
                return 
            else: 
                l=self.__srvI.servFunc2(durata)
                for el in l:
                    print(el)
                    
        except ValueError:
            print ("Introduceti date valide!")
        except RepoError as re:
            print(str(re))
            
    def run(self):
        '''
        Functia run, ruleaza interfata cu utilizatorul
        '''
        self.__showmenu()
        while True:
            cmd=input(">>>")
            if cmd in self.__comenzi:
                self.__comenzi[cmd]()
            elif cmd=="exit":
                exit()
            elif cmd=="help":
                self.__showmenu()
                    
                
                
        

