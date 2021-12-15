from business.services import serviceParticipare, servicePersoane,serviceEvents
from raises.errors import RepoError, ValidError
import random
import string
class UI:
    def __init__(self,service_pers,service_e,service_part):
        self.__service_persoana=service_pers
        self.__service_event=service_e
        self.__service_participation=service_part
        self.__commands={
            'add_person':self.__ui_addPerson,
            'add_event':self.__ui_addEvent,
            'delete_person':self.__ui_deletePerson,
            'delete_event':self.__ui_deleteEvent,
            'update_person':self.__ui_updatePerson,
            'update_event':self.__ui_updateEvent,
            'print_person':self.__ui_printPeople,
            'filter_person':self.__ui_filterPerson,
            'search_person':self.__ui_searchPerson,
            'search_event':self.__ui_searchEvent,
            'register':self.__ui_register,
            'print_part':self.__ui_printPart,
            'print_event':self.__ui_printEvent,
            'random_person':self.__ui_random_person,
            'random_event':self.__ui_random_event,
            'person_event_list':self.__ui_listaPersEvent,
            'person_most_events':self.__ui_personEventNumberList,
            'event_most_people':self.__ui_eventPersonNumberList,
            'help':self.__ui_menu,
            'event_few_people':self.__ui_sixtypercentEvents

        }
    def __ui_menu(self):
        print ("\nLISTA DE COMENZI:\n")
        print("1. Adauga persoana: add_person")
        print("2. Adauga eveniment: add_event")
        print("3. Sterge persoana: delete_person")
        print("4. Sterge eveniment: delete_event")
        print("5. Modifica persoana: update_person")
        print("6. Modifica eveniment: update_event")
        print("7. Printare lista persoane: print_person")
       # print("8. Filtrare dupa prefix: filter_person")
        print("9. Cauta persoana dupa id: search_person")
        print("10. Cauta eveniment dupa id: search_event")
        print("11. Inscrie persoana la eveniment: register")
        print("12. Printare lista de participari: print_part")
        print("13. Printare lista de evenimente: print_event")
        print("14. Adauga o persoane random: random_person")
        print("15. Adauga o persoane random: random_event")
        print("16. Lista evenimente la care participa o persoana: person_event_list")
        print("17. Printare persoane participante la cele mai multe evenimente: person_most_events")
        print("18. Printare evenimente 20% la care participa cele mai multe persoane: event_most_people")
        print("19. Printare evenimente 60% la care participa cele mai putine persoane: event_few_people")
        print("\t\texit - exit the application  ||\t help - show this menu")

    def __ui_sixtypercentEvents(self):
        s=self.__service_participation.services_sixtypercentEvents()
        if s=="Nu exista inscrieri la evenimente!":
            print(s)
        else:
            for el in s:
                print(el)
    def __ui_eventPersonNumberList(self):
        '''
        User interface for 20% of the events with most participants
        '''
        s=self.__service_participation.services_eventPersonNumberList()
        if s=="Nu exista inscrieri la evenimente!":
            print(s)
        else:
            for el in s:
                print(el)
    def __ui_personEventNumberList(self):
        s=self.__service_participation.services_personEventNumberList()
        if s=="Nu exista inscrieri la evenimente!":
            print(s)
        else:
            for el in s:
                print(el)

    def __ui_random_person(self):
        '''
        User interfaec for adding random people to the person list
        '''
        try:
            cate_nr=int(input("Introduceti un numar de entitati pe care doriti sa le generati: "))
            for i in range(cate_nr):
                try:
                    self.__service_persoana.services_random()
                    print("Persoana adaugata!")
                except ValidError as ve:
                    print(str(ve))
                except RepoError as re:
                    print(str(re))
        except ValueError:
            print("Introduceti tipuri de date corecte!")
    
    def __ui_random_event(self):
        '''
        User interface for adding random events to the event list
        '''
        try:
            cate_nr=int(input("Introduceti un numar de entitati pe care doriti sa le generati: "))
            for i in range(cate_nr):
                
                try:
                    self.__service_event.services_random()
                    print("Eveniment adaugat!")
                except ValidError as ve:
                    print(str(ve))
                except RepoError as re:
                    print(str(re))
        except ValueError:
            print("Introduceti tipuri de date corecte!")
                    


    def __ui_listaPersEvent(self):
        '''
        User interfaec for adding random events to the event list
        '''
        try:
            id_pers=int(input("Introduceti ID-ul persoanei participante la evenimente: "))
            try:
                s=self.__service_participation.services_personEventList(id_pers)
                print(str(s))
            except RepoError as re:
                print(str(re))
        except ValueError:
            print("Introduceti tipuri de date corecte!")
    def __ui_printEvent(self):
        self.__service_event.services_printare()

    def __ui_printPart(self):
        self.__service_participation.services_print() 
        
    def __ui_register(self):
        try:
            id=int(input("Introduceti ID-ul: "))
            idP=int(input("Introduceti ID-ul persoanei: "))
            idE=int(input("Introduceti ID-ul evenimentului: "))
            try:
                self.__service_participation.services_add(id, idP, idE)
                print("Inregistrare cu succes!")
            except ValidError as ve:
                print (str(ve))
            except RepoError as re:
                print(str(re))

        except ValueError:
            print("Introduceti tipuri de date corecte!")
    def __ui_searchPerson(self):
        try:
            id=int(input("Introduceti ID-ul: "))
            try:
                print(self.__service_persoana.services_search_by_id(id))
            except RepoError as re:
                print(str(re))

        except ValueError:
            print("Introduceti tipuri de date corecte!")

    def __ui_searchEvent(self):

        try:
            id=int(input("Introduceti ID-ul: "))
            try:
                print(self.__service_event.services_search_by_id(id))
            except RepoError as re:
                 print(str(re))
        except ValueError:
            print("Introduceti tipuri de date corecte!")

    def __ui_addPerson(self):

        try:
            id=int(input("Introduceti ID-ul: "))
            name=input("Introduceti numele: ")
            adress=input("Introduceti adresa: ")

            try:
                self.__service_persoana.services_add(id,name,adress)
                print("Persoana adaugata!")
            except ValidError as ve:
                print(str(ve))
            except RepoError as re:
                print(str(re))

        except ValueError:
            print("Introduceti tipuri de date corecte!")
                 
    def __ui_addEvent(self):
        try:
            id=int(input("Introduceti ID-ul: "))
            data=input("Introduceti data: ")
            timp=float(input("Introduceti timpul: "))
            descriere=input("Introduceti o descriere: ")
            try:
                self.__service_event.services_add(id,data,timp,descriere)
                print("Eveniment adaugat!")
            except ValidError as ve:
                print(str(ve))
            except RepoError as re:
                print(str(re))
        except ValueError:
            print("Introduceti tipuri de date corecte!")
        
    def __ui_deletePerson(self):
        try:
            id=int(input("Introduceti ID-ul: "))
            name=input("Introduceti numele: ")
            adress=input("Introduceti adresa: ")
            try:
                self.__service_persoana.services_delete(id,name,adress)
                self.__service_participation.services_delete_by_person(id)
                print("Persoana stearsa!")
            except ValidError as ve:
                print(str(ve))
            except RepoError as re:
                print(str(re))
        except ValueError:
            print("Introduceti tipuri de date corecte!")

    def __ui_deleteEvent(self):
        try:
            id=int(input("Introduceti ID-ul: "))
            ##
            #data=input("Introduceti data: ")
           # timp=float(input("Introduceti timpul: "))
            #descriere=input("Introduceti o descriere: ")
            try:
                self.__service_event.services_delete(id)
                self.__service_participation.services_delete_by_event(id)
                print("Eveniment sters!")
            except ValidError as ve:
                print(str(ve))
            except RepoError as re:
                print(str(re))
        except ValueError:
            print("Introduceti tipuri de date corecte!")
    
    def __ui_updatePerson(self):
        try:
            id=int(input("Introduceti ID-ul persoanei pe care vreti sa o modificati: "))
            name=input("Introduceti numele nou: ")
            adress=input("Introduceti adresa noua: ")
            try:
                self.__service_persoana.services_update(id,name,adress)

                print("Persoana actualizata!")
            except ValidError as ve:
                print(str(ve))
            except RepoError as re:
                print(str(re))
        except ValueError:
            print("Introduceti tipuri de date corecte!")

    def __ui_updateEvent(self):
        try:
            id=int(input("Introduceti ID-ul evenimentului pe care vreti sa il modificati: "))
            data=input("Introduceti data noua: ")
            timp=float(input("Introduceti timpul nou: "))
            descriere=input("Introduceti o descriere noua: ")
            try:
                self.__service_event.services_update(id,data,timp,descriere)

                print("Eveniment actualizat!")
            except ValidError as ve:
                print(str(ve))
            except RepoError as re:
                print(str(re))
        except ValueError:
            print("Introduceti tipuri de date corecte!")

    def __ui_printPeople(self):
        self.__service_persoana.services_printare()


    def __ui_filterPerson(self):
            prefix=input("Introduceti un prefix: ")
            try:
                t=self.__service_persoana.services_filter(prefix)
                print(t)
            except RepoError as re:
                print(str(re))
        
    def run(self):
        self.__ui_menu()
        while (True):
            command=input(">>>")
            if command=="exit":
                return
            elif command in self.__commands:
                self.__commands[command]()
        
