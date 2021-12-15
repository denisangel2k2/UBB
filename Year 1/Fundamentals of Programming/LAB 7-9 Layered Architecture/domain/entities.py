class Persoana:
    
    def __init__(self, id, nume, adresa):
        self.__personID=id
        self.__name=nume
        self.__adress=adresa

    def getID(self):
        '''
        Returns person's ID
        '''
        return self.__personID

    def getName(self):
        '''
        Returns person's NAME
        '''
        return self.__name

    def getAdress(self):
        '''
        Returns person's ADRESS
        '''
        return self.__adress
    
    def setID(self,id):
        self.__personID=id
    
    def setName(self,name):
        self.__name=name

    def setAdress(self, adress):
        self.__adress=adress

    def __str__(self):
        return "["+str(self.__personID)+"] "+str(self.__name) + " " + str(self.__adress)

    def __eq__(self,other):
        return self.getID()==other.getID()
    

class Eveniment:
    def __init__(self, id, data, timp, desc):
        self.__eventID=id
        self.__date=data
        self.__time=timp
        self.__description=desc
    
    def getID(self):
        '''
        Returns event's ID
        '''
        return self.__eventID
    
    def getDate(self):
        '''
        Returns event's DATE
        '''
        return str(self.__date)
    
    def getTime(self):
        '''
        Returns event's TIME
        '''
        return self.__time

    def getDescription(self):
        '''
        Returns event's DESCRIPTION
        '''
        return self.__description

    def setID(self,id):
        self.__eventID=id

    def setDate(self, date):
        self.__date=date

    def setTime(self,time):
        self.__time=time
    
    def setDescription(self, desc):
        self.__description=desc

    def __eq__(self,other):
        return self.getID()==other.getID()
        
    def __str__(self):
        return "["+str(self.__eventID)+"] "+str(self.__date)+ "; " + str(self.__time) + "; " + str(self.__description) 


##this isnt used
class Participare:
    def __init__(self,id,persoana,event):
        self.__participationID=id
        self.__person=persoana
        self.__event=event
    
    def getPerson(self):
        return self.__person
    
    def getEvent(self):
        return self.__event

    def getPersonID(self):
        return self.__person.getID()
    
    def getEventID(self):
        return self.__event.getID()
    
    def getID(self):
        return self.__participationID

    def __str__(self):
        return "{"+str(self.__participationID)+"}\t"+str(self.__person)+" @ "+ str(self.__event)