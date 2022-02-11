from domain.entities import Persoana,Eveniment
from raises.errors import RepoError 
from domain.dtos import *
class repoPersoane:
    def __init__(self):
        self._personList=[]

    def __uniquePerson(self,persoana,lista):
        '''
        Return true if the given person's id already is in the given list
        input: persoana - Persoana
               lista - list
        '''
        for person in lista:
            if person.getID()==persoana.getID():
                return True
        return False

    '''def add_event(self, event, persoana):
        for p in self.__personList:
            if p.getID()==persoana.getID():
                p.add_ev(event)'''

    def add(self,persoana):
        '''
        Adds the person given as parameter to the person repository
        input: persoana - Persoana
        Raises: RepoError
        '''
        
        if self.__uniquePerson(persoana,self._personList):
            raise RepoError("ID-ul precizat deja exista")
        else: self._personList.append(persoana)
            
    def delete(self, persoana):
        '''
        Deletes the person persoana from person repository given as parameter
        input: persoana
        '''
        for p in self._personList:
            if p.getID()==persoana.getID() and p.getName()==persoana.getName() and p.getAdress()==persoana.getAdress(): ###
                self._personList.remove(p)
                return
        raise RepoError("Persoana nu a fost gasita!")
    
    def update(self, persoana_modif):

        '''
        Updates the person persoana from person repository 
        input: person_modif - modified person
        '''
        for i in range(len(self._personList)):
            if self._personList[i].getID()==persoana_modif.getID():
                self._personList[i]=persoana_modif
                return
        
        raise RepoError("Persoana inexistenta!")

    def printare(self):
        for persoana in self._personList:
            print(str(persoana))

    def __len__(self):
        return len(self._personList)

    def getAll(self):
        '''
        Returns the person repository as a list
        '''
        return self._personList[:]

    def filter(self,prefix):
        lista=[]
        ok=False
        for person in self._personList:
            nume=person.getName()
            t=nume.startswith(prefix)
            if t==True:
                ok=True
                lista.append(person.getName())
        if ok==False:
            raise RepoError("Nu exista persoane!")
        return lista

    def search_by_id(self,id):
        '''
        Searches the person and returns the string in the person repository
        input: id - id of the person
        '''
        for person in self._personList:
          #  print(str(person.getID()))
            if person.getID()==id:
                return str(person)
        
        raise RepoError("ID-ul nu a fost gasit!\n")

    def find(self, id):
        '''
        Searches the person and returns the person from the repository
        input: id - id of the person
        '''
        for person in self._personList:
            if person.getID()==id:
                return person
        raise RepoError("ID-ul nu a fost gasit!\n")
class repoEvents:
    def __init__(self):
        self._eventList=[]
    
    def __len__(self):
        return len(self._eventList)

    def __uniqueEvent(self,ev,lista):
        '''
        Return true if the given event's id already is in the given list
        input: ev - Eveniment
               lista - list
        '''
        for event in lista:
            if event.getID()==ev.getID():
                return True
        return False

    def add(self,eveniment):
        '''
        Adds the given event to the even repo
        input: eveniment - Eveniment
        raises: RepoError
        '''
        if self.__uniqueEvent(eveniment,self._eventList):
            raise RepoError("ID-ul precizat deja exista")
        else: self._eventList.append(eveniment)

    def delete(self,id):
        '''
        Deletes event from event repository
        input: id - id of the event
        '''
        for ev in self._eventList:
            if ev.getID()==id:
                self._eventList.remove(ev)
                return
        raise RepoError("Evenimentul nu a fost gasit!")
    
    def delete_rec(self,id,n):
        if n==-1:
            raise RepoError("Evenimentul nu a fost gasit!")
        elif self._eventList[n].getID()==id:
            self._eventList.remove(self._eventList[n])
            return
        else: return self.delete_rec(id,n-1)
            
            
            
    def update(self, event_modif):
        '''
        Updates the event from event repository 
        input: event_modif - modified event
        '''
        for i in range(len(self._eventList)):
            if self._eventList[i].getID()==event_modif.getID():
                self._eventList[i]=event_modif
                return
        raise RepoError("Eveniment inexistent!")
    
    def getAll(self):
        '''
        Returns the event repository as a list
        '''
        return self._eventList[:]
    
    def search_by_id(self,id):

        for event in self._eventList:
            if event.getID()==id:
                return str(event)
        
        raise RepoError("ID-ul nu a fost gasit!\n")

    def search_by_id_rec(self,id,n):
        
        if n==-1:
            raise RepoError("ID-ul nu a fost gasit!\n")
        
        elif self._eventList[n].getID()==id:
            return str(self._eventList[n])
        
        else: return self.search_by_id_rec(id,n-1)
        
    def find(self, id):
        '''
        Searches the event and returns the event from the repository
        input: id - id of the person
        '''
        for event in self._eventList:
            if event.getID()==id:
                return event
        
        raise RepoError("ID-ul nu a fost gasit!\n")

    def find_rec(self,id,n):
        
        if n==-1:
            raise RepoError("ID-ul nu a fost gasit!\n")
        
        elif self._eventList[n].getID()==id:
            return self._eventList[n]
        
        else: return find_rec(id,n-1)
        
    def printare(self):
        for event in self._eventList:
            print(str(event))
    
    def __len__(self):
        return len(self._eventList)
class repoParticipare:
    
    def __init__(self):
        self._participationList=[]

    def add(self,participation):
        '''
        Adds the participation to the participation repo
        input: participation - participationDTO
        '''
        if self.__uniqueID(participation.getID_Part()):
            self._participationList.append(participation)

    def __uniqueID(self, id):
        for participare_dto in self._participationList:
            if participare_dto.getID_Part()==id:
                return False
        return True

    def __len__(self):
        return len(self._participationList)
    
    def find(self, participare):
        '''
        Raises exception if participation already exists
        '''
        for p in self._participationList:
            if p.getID_Part()==participare.getID_Part() and participare.getID_Pers()==p.getID_Pers() and participare.getID_Event()==p.getID_Event():
                raise RepoError("ID existent!\n")
            elif p.getID_Part()==participare.getID_Part():
                raise RepoError("ID existent!\n")
            elif p.getID_Part()!=participare.getID_Part() and participare.getID_Pers()==p.getID_Pers() and participare.getID_Event()==p.getID_Event():
                raise RepoError("ID existent!\n")
    
    def delete_by_event(self,id):
        for p in self._participationList:
            if p.getID_Event()==id:
                self._participationList.remove(p)
                return

    def delete_by_person(self,id):
        for p in self._participationList:
            if p.getID_Pers()==id:
                self._participationList.remove(p)
                return
            
class FileRepoEvents(repoEvents):
    def __init__(self, file_path):
        self.__file_path=file_path
        repoEvents.__init__(self)
       # self.__read__all_from_file()

    def __read_all_from_file(self):
        self._eventList=[]
        f=open(self.__file_path,"r")
        content=f.read()
        f.close()
        lines=content.split('\n')
        for line in lines:
            if line.strip()!="":
                parts=line.split(",")
                event=Eveniment(int(parts[0]),parts[1],float(parts[2]),parts[3])
                self._eventList.append(event)

    '''def __read_all_from_file(self):
        self._eventList=[]
        f=open(self.__file_path,"r")
        content=f.read()
        f.close()
        lines=content.split('\n')
        i=0
        while i<len(lines):
            if lines[i].strip()!="":
                event=Eveniment(int(lines[i]),lines[i+1],float(lines[i+2]),lines[i+3])
                self._eventList.append(event)
                i+=4
            else:
                i+=1'''

    def __write_to_file_nothing(self):
            f=open(self.__file_path,"w")
            f.write("")
            f.close() ##

    def __append_to_file(self,event):
        f=open(self.__file_path, "a")
        f.write(str(event.getID())+","+event.getDate()+","+str(event.getTime())+","+event.getDescription()+"\n")
        f.close()

    '''def __append_to_file(self,event):
        f=open(self.__file_path, "a")
        f.write(str(event.getID())+"\n"+event.getDate()+"\n"+str(event.getTime())+"\n"+event.getDescription()+"\n")
        f.close()
'''
    def add(self,eveniment):
        self.__read_all_from_file()
        repoEvents.add(self,eveniment)
        self.__append_to_file(eveniment)
    
    def delete(self,id):
        self.__read_all_from_file()
        #repoEvents.delete(self,id)
        repoEvents.delete_rec(self, id, len(self._eventList)-1)
        self.__write_to_file_nothing()
        for event in self._eventList:
            self.__append_to_file(event)

    def update(self, event_modif):
        self.__read_all_from_file()
        repoEvents.update(self,event_modif)
        self.__write_to_file_nothing()
        for event in self._eventList:
            self.__append_to_file(event)

    def getAll(self):
        self.__read_all_from_file()
        repoEvents.getAll(self)

    def search_by_id(self,id):
        self.__read_all_from_file()
        #return repoEvents.search_by_id(self,id)
        return repoEvents.search_by_id_rec(self, id, len(self._eventList)-1)
    
    def find(self,id):
        self.__read_all_from_file()
        return repoEvents.find(self,id)

    def printare(self):
        self.__read_all_from_file()
        repoEvents.printare(self)

    def __len__(self):
        self.__read_all_from_file()
        repoEvents.__len__(self)
        
class FileRepoPersoane(repoPersoane):
    def __init__(self,file_path):
        self.__file_path=file_path
        repoPersoane.__init__(self)
      #  self.__read_all_from_file()
    
    def __read_all_from_file(self):
        self._personList=[]
        with open(self.__file_path, "r") as f:
            lines=f.readlines()
            for line in lines:
                line=line.strip()
                if line!="": #skip the empty line
                    parts=line.split(",")
                    id_persoana=int(parts[0])
                    nume_persoana=parts[1]
                    adresa_persoana=parts[2]
                    persoana=Persoana(id_persoana,nume_persoana,adresa_persoana)
                    self._personList.append(persoana)

    '''def __read_all_from_file(self):
        self._personList=[]
        f=open(self.__file_path,"r")
        content=f.read()
        f.close()
        lines=content.split('\n')
        i=0
        while i<len(lines):
            if lines[i].strip()!="":
                persoana=Persoana(int(lines[i]),lines[i+1],lines[i+2])
                self._personList.append(persoana)
                i+=3
            else:
                i+=1
    def __append_to_file(self,persoana):
        f=open(self.__file_path, "a")
        f.write(str(persoana.getID())+"\n"+persoana.getName()+"\n"+persoana.getAdress()+"\n")
        f.close()'''

    def __append_to_file(self,persoana):
        with open(self.__file_path,"a") as f:
            f.write(str(persoana.getID())+","+persoana.getName()+","+persoana.getAdress()+"\n")

    def __write_to_file_nothing(self):
        f=open(self.__file_path,"w")
        f.write("")

    def add(self, persoana):
        self.__read_all_from_file()
        repoPersoane.add(self,persoana)
        self.__append_to_file(persoana)

    def printare(self):
        self.__read_all_from_file()
        repoPersoane.printare(self)

    def find(self, id):
        self.__read_all_from_file()
        repoPersoane.find(self,id)
    
    def delete(self, persoana):
        self.__read_all_from_file()
        self.__write_to_file_nothing()
        repoPersoane.delete(self,persoana)
        for person in self._personList:
            self.__append_to_file(person)

    def update(self, persoana_modif):
        self.__read_all_from_file()
        self.__write_to_file_nothing()
        repoPersoane.update(self,persoana_modif)
        for person in self._personList:
            self.__append_to_file(person)

    def search_by_id(self,id):
        self.__read_all_from_file()
       # repoPersoane.printare(self)
        return repoPersoane.search_by_id(self,id)
        
        
    def find(self,id):
        self.__read_all_from_file()
        return repoPersoane.find(self,id)
        
    def __len__(self):
        self.__read_all_from_file()
        return repoPersoane.__len__(self)
    
    def getAll(self):
        self.__read_all_from_file()
        repoPersoane.getAll(self)

    def filter(self,prefix):
        self.__read_all_from_file()
        repoPersoane.filter(self,prefix)

class FileRepoParticipare(repoParticipare):
    def __init__(self,file_path):
        self.__file_path=file_path
        repoParticipare.__init__(self)

    def __write_to_file_nothing(self):
            f=open(self.__file_path,"w")
            f.write("")
            f.close() ##

    def __read_all_from_file(self):
        self._participationList=[]
        f=open(self.__file_path,"r")
        content=f.read()
        f.close()
        lines=content.split("\n")
        for line in lines:
            if line.strip()!="":
                parts=line.split(",")
                id_participare=int(parts[0])
                id_persoana=int(parts[1])
                id_event=int(parts[2])
                participare_dto=participareDTO(id_participare,id_persoana,id_event)
                self._participationList.append(participare_dto)

    def __append_to_file(self,participare):
        try:
            f=open(self.__file_path,"a")
        except IOError:
            return

        f.write(str(participare.getID_Part())+","+str(participare.getID_Pers())+","+str(participare.getID_Event())+"\n")
        f.close()

    '''def __read_all_from_file(self):
        self._participationList=[]
        f=open(self.__file_path,"r")
        content=f.read()
        f.close()
        lines=content.split('\n')
        i=0
        while i<len(lines):
            if lines[i].strip()!="":
                participare_dto=participareDTO(int(lines[i]),int(lines[i+1]),int(lines[i+2]))
                self._participationList.append(participare_dto)
                i+=3
            else:
                i+=1
    def __append_to_file(self,participare):
        f=open(self.__file_path, "a")
        f.write(str(participare.getID_Part())+"\n"+str(participare.getID_Pers())+"\n"+str(participare.getID_Event())+"\n")
        f.close()'''

    def add(self,participare):
        self.__read_all_from_file()
        repoParticipare.add(self,participare)
        self.__append_to_file(participare)
    
    def getAll(self):
        self.__read_all_from_file()
        return self._participationList[:]
    
    def __len__(self):
        self.__read_all_from_file()
        return repoParticipare.__len__(self)
    
    def find(self,participare):
        self.__read_all_from_file()
        repoParticipare.find(self,participare)
    
    def delete_by_event(self,id):
        self.__read_all_from_file()
        repoParticipare.delete_by_event(self,id)
        self.__write_to_file_nothing()
        for p in self._participationList:
            self.__append_to_file(p)
    
    def delete_by_person(self,id):
        self.__read_all_from_file()
        repoParticipare.delete_by_person(self,id)
        self.__write_to_file_nothing()
        for p in self._participationList:
            self.__append_to_file(p)
