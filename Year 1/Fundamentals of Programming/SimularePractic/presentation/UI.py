from errors.erori import ValidError, RepoError
class Consola(object):
    def __init__(self,service):
        self.__serv=service
        self.__comenzi={'add_juc':self.__ui_add,
                        'change_juc':self.__ui_change,
                        'team':self.__ui_team,
                        'fileadd':self.__ui_fileadd
                        }
    
    def __show_menu(self):
        
        '''
        Functia care tipareste meniul
        '''
        print("\n1. Adauga jucator: add_juc")
        print("2. Modifica jucator: change_juc")
        print("3. Printeaza echipa: team")
        print("4. Adauga jucatori din fisier: fileadd")
        print("\t\texit: Iesire")
        
    def __ui_add(self):
        '''
        Functia care adauga un jucator citit de la tastatura in lista de jucatori
        '''
        while True:
            try:
                nume=input("Introduceti numele: ")
                prenume=input("Introduceti prenumele: ")
                inaltime=int(input("Introduceti inaltimea: "))
                post=input("Introduceti postul: ")
                self.__serv.srv_add(nume,prenume,inaltime,post)
                print("Jucator adaugat cu succes!\n")
                break
            
            except ValueError:
                print("Date invalide!")
                break
            except ValidError as ve:
                print(str(ve))
                break
                
    def __ui_change(self):
        '''
        Functia care modifica un jucator cu campuri citite de la tastatura
        '''
        while True:
            try:
                nume=input("Introduceti numele: ")
                prenume=input("Introduceti prenumele: ")
                inaltime=int(input("Introduceti inaltimea noua: "))
                self.__serv.srv_change(nume,prenume,inaltime)
                print("Jucator modificat cu succes!\n")
                break
            except RepoError as re:
                print(str(re))
                break
            except ValueError:
                print("Date invalide!")
                break
            except ValidError as ve:
                print(str(ve))
                break
                
    def __ui_team(self):
        '''
        Functia care tipareste o echipa de jucatori
        '''
        try:
            echipa=self.__serv.srv_team()
            for el in echipa:
                print(el)
        except RepoError as re:
            print(str(re))
            
    def __ui_fileadd(self):
        '''
        Functia care adauga la lista de jucatori, jucatori cititi dintr-un fisier cu path-ul citit de la tastatura
        '''
        while True:
            try:
                filepath=input("Introduceti numele de fisier: ")
                
                if filepath[-4:]!=".txt":
                    filepath+=".txt"
                cati=self.__serv.srv_fileadd(filepath)
                print("Au fost adaugati "+ str(cati) + " jucatori!")
                
            except RepoError as re:
                print(str(re))
                break
    def run(self):
        '''
        Functia run, care leaga toate celelalte functionalitati
        '''
        while(True):
            self.__show_menu()
            cmd=input(">>>")
            if cmd=="exit":
                break
            elif cmd in self.__comenzi:
                self.__comenzi[cmd]()
