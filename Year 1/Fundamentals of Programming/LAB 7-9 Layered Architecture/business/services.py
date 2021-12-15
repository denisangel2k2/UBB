from domain.dtos import participareDTO, personListEvDTO, personNumberEventsDTO, print_participareDTO,eventNumberParticipationDTO,eventNumberParticipationDTO2
from domain.entities import Eveniment, Participare, Persoana
from infrastructure.repos import repoParticipare, repoPersoane,repoEvents
from validators.validate import validatorEvents, validatorPersoane
from datetime import date
import random
class servicePersoane:
    def __init__(self, repoP, validatorP):
        self.__repository=repoP
        self.__validator=validatorP
    def services_random(self):

        '''
        Adds a random person to the person repository
        '''
        id=random.randint(0,1000)
        nr=random.randint(0,1000)
        nume="Nume"+str(id)
        adresa="Strada "+str(id)+" Numar "+ str(nr)
        self.services_add(id,nume,adresa)  

    def services_add(self, personID, name, adress):
        '''
        Adds the person to the person repository
        '''
        person=Persoana(personID,name,adress)
        self.__validator.validatePerson(person)
        self.__repository.add(person)

    def services_delete(self, personID, name, adress):
        '''
        Deletes the person to the person repository
        '''
        person=Persoana(personID,name,adress)
        self.__validator.validatePerson(person)
        self.__repository.delete(person)

    def services_update(self, personID, name, adress):
        '''
        Updates the person with the personID from the repository to new name and adress
        '''
        person_modif=Persoana(personID,name,adress)
        self.__validator.validatePerson(person_modif)
        self.__repository.update(person_modif)

    def services_printare(self):
        '''
        Prints the repository for persoana
        '''
        self.__repository.printare()

    def services_filter(self,prefix):
        '''
        Returns filtered by prefix list for persoana
        '''
        return self.__repository.filter(prefix)

    def services_search_by_id(self,id):
        '''
        Returns the person whose id is given as parameter
        '''
        return self.__repository.search_by_id(id)

class serviceEvents:
    def __init__(self, repoE, validatorE):
        self.__repository=repoE
        self.__validator=validatorE

    def services_random(self):
            '''
            Adds a random person to the event list
            '''
            id=random.randint(0,1000)
            zi=random.randint(1,31)
            luna=random.randint(1,12)
            an=random.randint(0,2022)
            data=""
            data+=str(zi)+"/"
            if int(luna)<10:
                data+="0"
            data+=str(luna)+"/"
            data+=str(an)
            timp=round(random.uniform(1.1,1000.0),2)
            desc="Desc"+str(id)
            self.services_add(id,data,timp,desc)

    def services_add(self, eventID, data, time, description):
        '''
        Adds the event to the event repository
        '''
        #aici sa folosesc datetime

        event=Eveniment(eventID,data,time,description)
        self.__validator.ValidateEvent(event)
        delim="/"
        l=data.split(delim)
        ziua=date(int(l[2]),int(l[1]),int(l[0]))
        event.setDate(ziua)
        self.__repository.add(event)
    
    def services_delete(self, eventID):
        '''
        Deletes the person to the person repository
        '''
        self.__validator.validateID(eventID)
        self.__repository.delete(eventID)

    def services_update(self, eventID, date, time, description):
        '''
        Updates the event with the eventID to have a new date, time and description
        '''
        event_modif=Eveniment(eventID,date,time,description)
        self.__validator.ValidateEvent(event_modif)
        self.__repository.update(event_modif)

    def services_search_by_id(self,id):
        '''
        Returns the event whose id is given as parameter
        '''
        return self.__repository.search_by_id(id)
    
    def services_printare(self):
        '''
        Prints the repository for event
        '''
        self.__repository.printare()
class serviceParticipare:
    def __init__(self,repoP, repoE, repoPart, validE,validP):
        self.__repositoryP=repoP
        self.__repositoryE=repoE
        self.__repositoryPart=repoPart
        self.__validatorE=validE
        self.__validatorP=validP
        
    def services_print(self):
        '''
        Prints all the participations
        '''
        
        partlist=self.__repositoryPart.getAll()
        for part_dto in partlist:
            person=self.__repositoryP.find(part_dto.getID_Pers())
            event=self.__repositoryE.find(part_dto.getID_Event())
            printi=print_participareDTO(person,event)
            print(str(printi))

    

    def services_delete_by_event(self, id):
        self.__repositoryPart.delete_by_event(id)

    def services_delete_by_person(self, id):
        self.__repositoryPart.delete_by_person(id)

    def services_add(self,id_part,id_pers,id_event):
        '''
        Registers the person with the given id to the event with the given id
        '''
        person=self.__repositoryP.find(id_pers)
        event=self.__repositoryE.find(id_event)
        self.__validatorE.validateID(id_part)
        parti_dto=participareDTO(id_part,id_pers,id_event)
        self.__repositoryPart.find(parti_dto)
        self.__repositoryPart.add(parti_dto)

    def services_personEventList(self,id_pers):
        '''
        Returns the list of events where a person participates
        '''
        partlist=self.__repositoryPart.getAll()
        lista_evenimente=[]
        for part_dto in partlist:
            if id_pers == part_dto.getID_Pers():
                event=self.__repositoryE.find(part_dto.getID_Event())
                lista_evenimente.append(event)
        
        person=self.__repositoryP.find(id_pers)
        lista_evenimente=sorted(lista_evenimente, key=lambda x: (x.getDate(),x.getDescription()), reverse=False)
        persEv=personListEvDTO(person,lista_evenimente)
        
        
        return persEv

    def services_personEventNumberList(self):
        '''
        Prints all the persons who participate in the most events
        '''
        l_print=[]
        partlist=self.__repositoryPart.getAll()
        if len(self.__repositoryPart)==0:
            #print("Nu exista inscrieri la evenimente!")
            return "Nu exista inscrieri la evenimente!"
        else:
            lista={}
            for part_dto in partlist:
                if part_dto.getID_Pers() in lista:
                    lista[part_dto.getID_Pers()]+=1
                else:
                    lista[part_dto.getID_Pers()]=1
            lista_dto=[]
            for key in lista.keys():
                persoana=self.__repositoryP.find(int(key))
                dto=personNumberEventsDTO(persoana,lista[key])
                lista_dto.append(dto)
            lista_dto=sorted(lista_dto, key=lambda x : x.getNumberEvents(), reverse=True)
            for el in lista_dto:
                l_print.append(str(el))
        
        return l_print
    
    def selection_sort(self,l,key=lambda x: x,reversed=False):
        if reversed==True:
            for i in range(len(l)):
                max_index=i
                for j in range(i+1, len(l)):
                    if key(l[max_index])<key(l[j]):
                        max_index=j
                        
                l[i], l[max_index] = l[max_index], l[i]
        else: 
            for i in range(len(l)):
                max_index=i
                for j in range(i+1, len(l)):
                    if key(l[max_index])>key(l[j]):
                        max_index=j
                        
                l[i], l[max_index] = l[max_index], l[i]
        return l
    
    def shake_sort(self,l,key=lambda x : x, reversed=False):
        if reversed==True:
            swapped=True
            start=0
            end=len(l)-1
            
            while swapped==True:
                swapped=False
                for i in range(start,end):
                    if key(l[i])<key(l[i+1]):
                        l[i], l[i+1] = l[i+1], l[i]
                        swapped=True
                        
                if swapped==False:
                    break
                
                swapped=False
                end=end-1
                
                for i in range(end-1, start-1, -1):
                     if key(l[i])<key(l[i+1]):
                        l[i], l[i+1] = l[i+1], l[i]
                        swapped=True
                        
                start+=1
        else:
            swapped=True
            start=0
            end=len(l)
            
            while swapped==True:
                swapped=False
                for i in range(start,end):
                    if key(l[i])>key(l[i+1]):
                        l[i], l[i+1] = l[i+1], l[i]
                        swapped=True
                        
                if swapped==False:
                    break
                
                swapped=False
                end=end-1
                
                for i in range(end-1, start-1, -1):
                     if key(l[i])>key(l[i+1]):
                        l[i], l[i+1] = l[i+1], l[i]
                        swapped=True
                        
                start+=1
        return l
    
    def services_eventPersonNumberList(self):
        '''
        Returns the list of 20% events with most participants
        '''
        partlist=self.__repositoryPart.getAll()
        if len(self.__repositoryPart)==0:
          #  print("Nu exista inscrieri la evenimente!")
          return "Nu exista inscrieri la evenimente!"
        else:
            lista_evenimente={}
            for part_dto in partlist:
                if part_dto.getID_Event() in lista_evenimente:
                    lista_evenimente[part_dto.getID_Event()]+=1
                else:
                    lista_evenimente[part_dto.getID_Event()]=1

            cate_ev=len(lista_evenimente)
            cate_ev_20percent=cate_ev//5
            l_sorted=[]
            l=[]

            for key in lista_evenimente.keys():
                event=self.__repositoryE.find(int(key))
                dto=eventNumberParticipationDTO(event,lista_evenimente[key])
                l_sorted.append(dto)
                
            #l_sorted=sorted(l_sorted, key= lambda x : x.getNumberPerson(), reverse=True)
            #l_sorted=self.selection_sort(l_sorted,key=lambda x: x.getNumberPerson(), reversed=True)
            l_sorted=self.shake_sort(l_sorted, key=lambda x : x.getNumberPerson(), reversed=True)
            for el in l_sorted:
                l.append(str(el))

          
            '''if cate_ev_20percent==0:
                for key in lista_evenimente.keys():
                    event=self.__repositoryE.find(int(key))
                    dto=eventNumberParticipationDTO(event,lista_evenimente[key])
                    l.append(str(dto))
            else:
                k=0
                for key in lista_evenimente.keys():
                    if k==cate_ev_20percent:
                        break
                    event=self.__repositoryE.find(int(key))
                    dto=eventNumberParticipationDTO(event,lista_evenimente[key])
                    l.append(str(dto))
                    k+=1'''
        if cate_ev//5!=0:
            return l[:cate_ev//5]
        else: return l

    def services_sixtypercentEvents(self):
        partlist=self.__repositoryPart.getAll()

        if len(self.__repositoryPart)==0:
            return "Nu exista inscrieri la evenimente!"
        else:
            lista_evenimente={}
            for part_dto in partlist:
                if part_dto.getID_Event() in lista_evenimente:
                    lista_evenimente[part_dto.getID_Event()]+=1
                else:
                    lista_evenimente[part_dto.getID_Event()]=1

            cate_ev=len(lista_evenimente)
            l_sorted=[]
            l=[]
            for key in lista_evenimente.keys():
                event=self.__repositoryE.find(int(key))
                dto=eventNumberParticipationDTO2(event,lista_evenimente[key])
                dto.setDate(event.getDate())
                l_sorted.append(dto)
            
            l_sorted=sorted(l_sorted,key=lambda x : (x.getDate(),x.getNumberPerson()))

            for el in l_sorted:
                l.append(str(el))

            if 3*cate_ev//5!=0:
                return l[:3*cate_ev//5]
            else: return l

            

    

    