from domain.entities import *
from raises.errors import ValidError

class validatorPersoane:

    def validatePerson(self, person):
        '''
        Validates the person object given as parameter
        input: person - Persoana
        Raises : ValidError
        '''
        errors=""
        if person.getID()<0:
            errors+="ID invalid\n"
        if person.getName()=="":
            errors+="Nume invalid\n"

        adresa=person.getAdress()
        l=adresa.split(" ")
        
        if len(l)<3:
            errors+="Adresa invalida\n"

        else:
            if not(l[0]=="Strada" and l[2]=="Numar"):
                errors+="Adresa invalida\n"


        if len(errors)>0:
            raise ValidError(errors)


class validatorEvents:
    
    def __validateDay(self, ziua):
        ''' Validates the day to be as DD/MM/YYYY
            input: ziua - string
        '''
        delim = "/"
        temp = ziua.split(delim)
        if len(temp)!=3:
            return False
        # 31 : 1,3,5,7,8,10,12
        # 30 : 4,6,9,11
        # 28 : 2 
        # 29 : 2 - daca (an%4==0 si an%100!=0) sau (an%400==0)
        try:
            day=int(temp[0])
            month=int(temp[1])
            year=int(temp[2])

            if len(temp[0])<2 or len(temp[1])<2:
                return False

            if month>12 or month<1:
                return False

            if day>31:
                return False

            if month==2:
                if day>29:
                    return False

                elif day==29:
                    if not((year%4==0 and year%100!=0) or year%400==0):
                        return False
                    else: 
                        return True
                elif day>0 and day<29:
                    return True

            if day==31:
                if month==1 or month==3 or month==5 or month==7 or month==8 or month==10 or month==12:
                    return True
                else:
                    return False
            elif day>0:       
                return True

        except ValueError:
            return False

    def validateID(self, id):
        if id<0:
            raise ValidError("ID invalid\n")
         
    def ValidateEvent(self, event):
        '''
        Validates the event given as parameter
        input: event - Eveniment
        Raises: ValidError
        '''
        errors=""

        if event.getID()<0:
            errors+="ID invalid\n"
        if self.__validateDay(event.getDate())==False:
            errors+="Data invalida\n"
        if event.getTime()<0:
            errors+="Timp invalid\n"

        if len(errors)>0:
            raise ValidError(errors)        


