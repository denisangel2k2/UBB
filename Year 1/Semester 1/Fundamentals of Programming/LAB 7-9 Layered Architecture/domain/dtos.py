class participareDTO:
    def __init__(self, id_part, id_pers, id_event):
        self.__idPart=id_part
        self.__idPers=id_pers
        self.__idEvent=id_event
        self.__person=None
        self.__event=None
    
    def getID_Part(self):
        return self.__idPart

    def getID_Pers(self):
        return self.__idPers

    def getID_Event(self):
        return self.__idEvent

    def getPerson(self):
        return self.__person
    
    def getEvent(self):
        return self.__event
    
    def setPerson(self,persoana):
        self.__person=persoana
    
    def setEvent(self,eveniment):
        self.__event=eveniment

    def __eq__(self, other):
        return self.__idPart==other.getID_Part()

class print_participareDTO:
    def __init__(self,persoana,event):
        self.__person=persoana
        self.__event=event

    def __str__(self):
        return str(self.__person)+" participa la evenimentul: "+str(self.__event)

class personListEvDTO:
    def __init__(self,persoana,listaEv):
        self.__lista=listaEv
        self.__person=persoana

    def getList(self):
        return self.__lista[:]
    
    def getPerson(self):
        return self.__person

    def __str__(self):
        s=str(self.__person)+"\n\t"
        for event in self.__lista:
            s+=str(event)+"\n\t"
        return s

class personNumberEventsDTO:
    def __init__(self,persoana,numar_ev):
        self.__person=persoana
        self.__nr_e=numar_ev

    def getPerson(self):
        return self.__person

    def getNumberEvents(self):
        return self.__nr_e

    def setNumberEvents(self,nr):
        self.__nr_e=nr
    def __str__(self):
        s=""
        s+="Persoana ["+str(self.__person.getID())+"]"+str(self.__person.getName())+" participa la "+str(self.__nr_e)+" evenimente"
        return s
        
class eventNumberParticipationDTO:
    def __init__(self,event,numar_pers):
        self.__event=event
        self.__nr_pers=numar_pers
        self.__data=None
    
    def getEvent(self):
        return self.__event

    def getNumberPerson(self):
        return self.__nr_pers
    
    def setDate(self,data):
        self.__data=data
    
    def getDate(self):
        return self.__data

    def __str__(self):

        s="La evenimentul \t"+str(self.__event.getDescription())+"\t participa "+str(self.__nr_pers)+" persoane!"
        return s

class eventNumberParticipationDTO2:
    def __init__(self,event,numar_pers):
        self.__event=event
        self.__nr_pers=numar_pers
        self.__data=None
    
    def getEvent(self):
        return self.__event

    def getNumberPerson(self):
        return self.__nr_pers
    
    def setDate(self,data):
        self.__data=data
    
    def getDate(self):
        return self.__data

    def __str__(self):

        #s="La evenimentul \t"+str(self.__event.getDescription())+"\t participa "+str(self.__nr_pers)+" persoane!"
        return f"La evenimentul \t {str(self.__event.getDescription())} din data {str(self.__data)} participa {str(self.__nr_pers)} persoane!"