from business.services import *
from domain.dtos import *
from domain.entities import Participare, Persoana, Eveniment
from raises.errors import RepoError, ValidError
from validators.validate import validatorEvents, validatorPersoane
from infrastructure.repos import FileRepoEvents, FileRepoParticipare, FileRepoPersoane, repoParticipare, repoPersoane, repoEvents
import unittest

class Teste:
#domain tests
    def __test_createPersoana(self):

        id=1
        nume="Ion"
        adresa="Strada"
        persoana=Persoana(id, nume, adresa)
        assert(persoana.getID()==id)
        assert (persoana.getName()==nume)
        assert(persoana.getAdress()==adresa) 
        print("Test finished!") 
    def __test_createEvent(self):

        id=1
        data="13/05/2003"
        timp=23
        descriere="abc"
        event=Eveniment(id,data,timp,descriere)

        assert(event.getID()==id)
        assert(event.getDate()==data)
        assert(event.getTime()==timp)
        assert(event.getDescription()==descriere)
        print("Test finished!") 
    def __test_createParticipation(self):
        id=1
        nume="Ion"
        adresa="Strada 3 Numar 5"
        data="13/05/2003"
        timp=23
        descriere="abc"
        person=Persoana(id, nume, adresa)
        event=Eveniment(id,data,timp,descriere)
        participare=Participare(1,person,event)
        assert(participare.getID()==1)
        assert(participare.getEvent()==event)
        assert(participare.getEventID()==id)
        assert(participare.getPerson()==person)
        assert(participare.getEventID()==id)
        assert(participare.getPersonID()==id)
        print("Test finished!")
#validate tests
    def __test_validatorPersoana(self):
        id=1
        nume="Ion"
        adresa="Strada 3 Numar 7"
        persoana=Persoana(id, nume, adresa)
        validP=validatorPersoane()

        try:
            validP.validatePerson(persoana)
            assert (True)
        except ValidError as ve:
            pass

        id=1
        nume="Ion"
        adresa="Strad 3 Numar 7"
        persoana=Persoana(id, nume, adresa)
        validP=validatorPersoane()

        try:
            validP.validatePerson(persoana)
            assert (False)
        except ValidError as ve:
            assert(str(ve)=="Adresa invalida\n")

        id=-1
        nume=""
        adresa="Strad 3 Numar 7"
        persoana=Persoana(id, nume, adresa)
        validP=validatorPersoane()

        try:
            validP.validatePerson(persoana)
            assert (False)
        except ValidError as ve:
            assert(str(ve)=="ID invalid\nNume invalid\nAdresa invalida\n")

        print("Test finished!") 
    def __test_validatorEveniment(self):
        id=1
        data="13/05/2003"
        timp=23
        descriere="abc"
        event=Eveniment(id,data,timp,descriere)
        valE=validatorEvents()
        try:
            valE.ValidateEvent(event)
            assert(True)
        except ValidError as ve:
            pass

        id=1
        data="13/5/2003"
        timp=23
        descriere="abc"
        event=Eveniment(id,data,timp,descriere)
        valE=validatorEvents()

        try:
            valE.ValidateEvent(event)
            assert(False)
        except ValidError as ve:
            assert(str(ve)=="Data invalida\n")
        
        id=-1
        data=""
        timp=-3
        descriere=""
        event=Eveniment(id,data,timp,descriere)
        valE=validatorEvents()

        try:
            valE.ValidateEvent(event)
            assert(False)
        except ValidError as ve:
            assert(str(ve)=="ID invalid\nData invalida\nTimp invalid\n")

        print("Test finished!")
#repository tests

    def __test__addPerson_PersonRepo(self):
        repoP=repoPersoane()
        persoana=Persoana(3,"Denis","Strada 3 Numar 7")

        length1=len(repoP)
        repoP.add(persoana)
        length2=len(repoP)
        assert(length1+1==length2)

        try:
            repoP.add(persoana)
            assert(False)
        except RepoError as re:
            assert(str(re)=="ID-ul precizat deja exista")
        
        person_bad=Persoana(3,"aaa","Strada 3 Numar 7")
        try:
            repoP.add(person_bad)
            assert(False)
        except RepoError as re:
            assert(str(re)=="ID-ul precizat deja exista")

        print("Test finished!")
    def __test__addEvent_EventRepo(self):
        id=1
        data="13/05/2003"
        timp=23
        descriere="abc"
        event=Eveniment(id,data,timp,descriere)
        repoE=repoEvents()

        length1=len(repoE)
        repoE.add(event)
        length2=len(repoE)
        assert(length1+1==length2)

        event2=Eveniment(1,data,13,descriere)
        try:
            repoE.add(event2)
            assert(False)
        except RepoError as re:
            assert(str(re)=="ID-ul precizat deja exista")

        try:
            repoE.add(event)
            assert(False)
        except RepoError as re:
            assert(str(re)=="ID-ul precizat deja exista")

        print("Test finished!")
    def __test_deletePerson_PersonRepo(self):
        repoP=repoPersoane()
        persoana=Persoana(3,"Denis","Strada 3 Numar 7")
        repoP.add(persoana)
        #repoP.getAll()
        length1=len(repoP)
        repoP.delete(persoana)
        #repoP.getAll()
        length2=len(repoP)

        assert(length1-1==length2)

        try:
            repoP.delete(persoana)
            assert(False)
        except RepoError as re:
            assert(str(re)=="Persoana nu a fost gasita!")

        print("Test finished!")  
    def __test_deleteEvent_EventRepo(self):
        id=1
        data="13/05/2003"
        timp=23
        descriere="abc"

        event=Eveniment(id,data,timp,descriere)

        repoE=repoEvents()
        repoE.add(event)

        length1=len(repoE)
        repoE.delete(id)
        length2=len(repoE)
        assert(length1-1==length2)

        try:
            repoE.delete(1)
            assert(False)
        except RepoError as re:
            assert(str(re)=="Evenimentul nu a fost gasit!")

        print("Test finished!")
    def __test_filterPerson_PersonRepo(self):
        repoP=repoPersoane()
        prefix="De"
        repoP.add(Persoana(1,"Denis","Strada 1 Numar 1"))
        repoP.add(Persoana(2,"Denisa","Strada 2 Numar 2"))
        assert(repoP.filter(prefix)==["Denis","Denisa"])

        print("Test finished!")
    def __test_updatePerson_PersonRepo(self):
        repoP=repoPersoane()
        persoana=Persoana(3,"Denis","Strada 3 Numar 7")
        repoP.add(persoana)
        l1=repoP.getAll()
        persoana_modif=Persoana(3,"Darius","Strada 5 Numar 3")
        repoP.update(persoana_modif)
        l2=repoP.getAll()
        assert(l1[0].getName()!=l2[0].getName())
        assert(l1[0].getAdress()!=l2[0].getAdress())

        try:
            repoP.update(Persoana(4,"Darius","Strada 5 Numar 3"))
            assert(False)
        except RepoError as re:
            assert(str(re)=="Persoana inexistenta!")

        print("Test finished!")
    def __test_updateEvent_EventRepo(self):
        repoE=repoEvents()
        event=Eveniment(3,"13/07/2009",15.3,"da")

        repoE.add(event)
        l1=repoE.getAll()
        event_modif=Eveniment(3,"13/08/2009",15.4,"daa")
        repoE.update(event_modif)
        l2=repoE.getAll()
        assert(l1[0].getDate()!=l2[0].getDate())
        assert(l1[0].getTime()!=l2[0].getTime())
        assert(l1[0].getDescription()!=l2[0].getDescription())

        try:
            repoE.update(Eveniment(4,"13/08/2009",15.4,"daa"))
            assert(False)
        except RepoError as re:
            assert(str(re)=="Eveniment inexistent!")

        print("Test finished!")
    def __test_serachPerson_PersonRepo(self):
        repoP=repoPersoane()
        person=Persoana(3,"Denis","Strada 3 Numar 7")
        repoP.add(person)
        str_pers=str(person)
        assert(repoP.search_by_id(person.getID())==str_pers)

        try:
            t=repoP.search_by_id(33)
            assert(False)
        except RepoError as re:
            assert (str(re)=="ID-ul nu a fost gasit!\n")

        print("Test finished!")
    def __test_searchEvent_EventRepo(self):
        repoE=repoEvents()
        event=Eveniment(3,"13/07/2009",15.3,"da")
        repoE.add(event)
        str_ev=str(event)
        assert(repoE.search_by_id(event.getID())==str_ev)
        
        try:
            t=repoE.search_by_id(33)
            assert(False)
        except RepoError as re:
            assert (str(re)=="ID-ul nu a fost gasit!\n")
        
        print("Test finished!")
    def __test_registerParticipation(self):
        repoP=FileRepoParticipare("tests/test_repoParticipare.txt")
        participare_dto=participareDTO(1,1,2)
       # le=len(repoP)
        repoP.add(participare_dto)
        assert(len(repoP)-1==0)
        print("Test finished!")   
    def __test_getAllPart(self):
         repoP=FileRepoParticipare("tests/test_repoParticipare.txt")
         partlist=[]
         assert(len(partlist)==0)
         partlist=repoP.getAll()
         assert(len(partlist)!=0)
         print("Test finished!")
#services tests

    def __test_service_searchPerson(self):
        repoP=repoPersoane()
        valP=validatorPersoane()
        srvP=servicePersoane(repoP,valP)
        person=Persoana(3,"Denis","Strada 3 Numar 7")
        str_p=str(person)
        repoP.add(person)
        assert(srvP.services_search_by_id(person.getID())==str_p)
        try:
            srvP.services_search_by_id(33)
            assert False
        except RepoError as re:
             assert (str(re)=="ID-ul nu a fost gasit!\n")

        print("Test finished!")
    def __test_service_searchEvent(self):
        repoE=repoEvents()
        event=Eveniment(3,"13/07/2009",15.3,"da")
        valE=validatorEvents()
        srvE=serviceEvents(repoE,valE)
        repoE.add(event)
        str_ev=str(event)
        assert(repoE.search_by_id(event.getID())==str_ev)
        
        try:
            srvE.services_search_by_id(33)
            assert False
        except RepoError as re:
            assert (str(re)=="ID-ul nu a fost gasit!\n")

        print("Test finished!")
    def __test_service_addPerson(self):
        repo=repoPersoane()
        validator=validatorPersoane()
        id=1
        nume="Ion"
        adresa="Strada"
        srv=servicePersoane(repo,validator)

        try:
            srv.services_add(id,nume,adresa)
            assert(False)
        except ValidError as ve:
            assert(str(ve)=="Adresa invalida\n")
        except RepoError as re:
            assert(str(re)=="ID-ul precizat deja exista")

        id=3
        nume="Ionel"
        adresa="Strada 3 Numar 3"
        srv=servicePersoane(repo,validator)
        try:
            srv.services_add(id,nume,adresa)
            assert(True)

        except ValidError as ve:
            assert(str(ve)=="Adresa invalida\n")
        except RepoError as re:
            assert(str(re)=="ID-ul precizat deja exista")

        id=3
        nume="Denis"
        adresa="Strada 3 Numar 3"
        srv=servicePersoane(repo,validator)
        try:
            srv.services_add(id,nume,adresa)
            assert(False)
            
        except ValidError as ve:
            assert(str(ve)=="ID invalid\n")
        except RepoError as re:
            assert(str(re)=="ID-ul precizat deja exista")

        id=-3
        nume="Denis"
        adresa="Strada 3 Numar 3"
        srv=servicePersoane(repo,validator)
        try:
            srv.services_add(id,nume,adresa)
            assert(False)
            
        except ValidError as ve:
            assert(str(ve)=="ID invalid\n")
        except RepoError as re:
            assert(str(re)=="ID-ul precizat deja exista")   
        
        '''l=repo.getAll()
        for x in l:
            print (x.getName())'''
    def __test_service_addEvent(self):
        id=1
        data="13/05/2003"
        timp=23
        descriere="abc"
        valE=validatorEvents()
        repoE=repoEvents()
        try:
            event=Eveniment(id,data,timp,descriere)
            valE.ValidateEvent(event)
            repoE.add(event)
            assert(True)
        except ValidError as ve:
            pass
        except RepoError as re:
            pass

        id=-1
        data="13/05/203"
        timp=-3
        descriere="abc"
        try:
            event=Eveniment(id,data,timp,descriere)
            valE.ValidateEvent(event)
            repoE.add(event)
            assert(False)
        except ValidError as ve:
            assert(str(ve)=="ID invalid\nTimp invalid\n")
        except RepoError as re:
            pass
        
        id=1
        data="13/05/2003"
        timp=23
        descriere="abc"
        try:
            event=Eveniment(id,data,timp,descriere)
            valE.ValidateEvent(event)
            repoE.add(event)
            assert(False)
        except ValidError as ve:
            pass
        except RepoError as re:
            assert(str(re)=="ID-ul precizat deja exista")
        
        print("Test finished!")
    def __test_service_deletePerson(self):
        repoP=repoPersoane()
        validP=validatorPersoane()
        srvP=servicePersoane(repoP,validP)
        id=1
        nume="Ion"
        adresa="Strada 3 Numar 5"
        try:
            srvP.services_delete(id,nume,adresa)
            assert(False)
        except RepoError as re:
            assert(str(re)=="Persoana nu a fost gasita!")
        
        try:
            srvP.services_delete(id,nume,adresa)
            assert(True)
        except RepoError as re:
            assert(str(re)=="Persoana nu a fost gasita!")

        try:
            srvP.services_delete(-1,nume,adresa)
            assert(True)
        except ValidError as ve:
            assert(str(ve)=="ID invalid\n")

        print("Test finished!")
    def __test_service_deleteEvent(self):
        id=1
        data="13/05/2003"
        timp=23
        descriere="abc"
        repoE=repoEvents()
        valE=validatorEvents()
        srvE=serviceEvents(repoE,valE)
        try:
            srvE.services_delete(id)
            assert(False)
        except RepoError as re:
            assert(str(re)=="Evenimentul nu a fost gasit!")
        
        try:
            srvE.services_delete(-1)
            assert(False)
        except ValidError as ve:
            assert(str(ve)=="ID invalid\n")
        
        print("Test finished!")
    def __test_service_updatePerson(self):
        repoP=repoPersoane()
        valP=validatorPersoane()
        srvP=servicePersoane(repoP,valP)
        try:
            srvP.services_update(3,"denis","Strada 3 Numar 7")
            assert(False)
        except RepoError as re:
            assert(str(re)=="Persoana inexistenta!")
        
        repoP.add(Persoana(3,"denis","Strada 3 Numar 7"))

        try:
            srvP.services_update(3,"denis","Strad 3 Numar 7")
            assert(False)
        except ValidError as ve:
            assert(str(ve)=="Adresa invalida\n")

        try:
            srvP.services_update(3,"De","Strada 3 Numar 7")
            assert(True)
        except ValidError as ve:
            assert(str(ve)=="Adresa invalida\n")

        print("Test finished!")
    def __test_service_updateEvent(self):
        repoE=repoEvents()
        valE=validatorEvents()
        srvE=serviceEvents(repoE,valE)
        try:
            srvE.services_update(1,"13/07/2001",15.3,"da")
            assert(False)
        except RepoError as re:
            assert(str(re)=="Eveniment inexistent!")
        
        repoE.add(Eveniment(1,"13/07/2001",15.3,"da"))

        try:
            srvE.services_update(1,"14/032011",-3,"da")
            assert(False)
        except ValidError as ve:
            assert(str(ve)=="Data invalida\nTimp invalid\n")

        try:
            srvE.services_update(-1,"14/03/2011",3,"da")
            assert(False)
        except ValidError as ve:
            assert(str(ve)=="ID invalid\n")

        try:
            srvE.services_update(1,"14/03/2011",15.2,"da")
            assert(True)
        except ValidError as ve:
            pass

        print("Test finished!")
    def __test_service__filterPerson(self):
        repoP=repoPersoane()
        valP=validatorPersoane()
        srvP=servicePersoane(repoP,valP)
        prefix="De"
        repoP.add(Persoana(1,"Denis","Strada 1 Numar 1"))
        repoP.add(Persoana(2,"Denisa","Strada 2 Numar 2"))
        repoP.add(Persoana(3,"Elmo","Strada 3 Numar 2"))
        try:
            srvP.services_filter(prefix)
            assert(True)
        except RepoError as re:
           # assert(str(re)=="")
           pass

        try:
            srvP.services_filter("x")
            assert(False)
        except RepoError as re:
            assert(str(re)=="Nu exista persoane!")
        
        print("Test finished!")
    def __test_service_registerPart(self):
        repoP=FileRepoPersoane("tests/test_repoPers.txt")
        repoE=FileRepoEvents("tests/test_repoEvent.txt")
        repoPart=FileRepoParticipare("tests/test_repoParticipare.txt")
        validE=validatorEvents()
        validP=validatorPersoane()
        srv=serviceParticipare(repoP,repoE,repoPart,validE,validP)
        try:
            srv.services_add(-1,3,3)
            assert False
        except RepoError as re:
            assert(str(re)=="ID-ul nu a fost gasit!\n")
        except ValidError as ve:
            assert(str(ve)=="ID invalid\n")
        
        try:
            srv.services_add(2,3,3)
            assert False
        except RepoError as re:
            assert(str(re)=="ID-ul nu a fost gasit!\n")
        except ValidError as ve:
            assert(str(ve)=="ID invalid\n")
        
        try:
            srv.services_add(2,1,1)
            assert True
        except RepoError as re:
            assert(str(re)=="ID-ul nu a fost gasit!\n")
        except ValidError as ve:
            assert(str(ve)=="ID invalid\n")

        try:
            srv.services_add(1,1,1)
            assert False
        except RepoError as re:
            assert(str(re)=="ID existent!\n")

        print("Test finished!!")


#All tests
    def run(self):
        print("Starting all tests instance...\n\n")

        self.__test_createPersoana()
        self.__test_createEvent()
        self.__test_validatorPersoana()
        self.__test_validatorEveniment()
        self.__test__addPerson_PersonRepo()
        self.__test__addEvent_EventRepo()
        self.__test_service_addPerson()
        self.__test_service_addEvent()
        self.__test_deletePerson_PersonRepo()
        self.__test_service_deletePerson()
        self.__test_deleteEvent_EventRepo()
        self.__test_service_deleteEvent()
        self.__test_serachPerson_PersonRepo()
        self.__test_searchEvent_EventRepo()
        self.__test_updatePerson_PersonRepo()
        self.__test_updateEvent_EventRepo()
        self.__test_service_updatePerson()
        self.__test_service_updateEvent()
        self.__test_service_searchPerson()
        self.__test_service_searchEvent()
        self.__test_filterPerson_PersonRepo()
        self.__test_service__filterPerson()
        self.__test_createParticipation()
        self.__test_getAllPart()
       # self.__test_registerParticipation()
       # self.__test_service_registerPart()
       
        print("\n\nEnding all tests instance...")

class RepoPersonTests(unittest.TestCase):
    def setUp(self):
        self.__repoP=repoPersoane()
        #self.__repoP=FileRepoPersoane("tests/test_repoPers.txt")

    

    def testAdd(self):

        persoana=Persoana(3,"Denis","Strada 3 Numar 7")
        

        length1=len(self.__repoP)
        self.__repoP.add(persoana)
        length2=len(self.__repoP)
        self.assertTrue(length1+1==length2)
        self.assertRaises(RepoError,self.__repoP.add,persoana)
        
        person_bad=Persoana(3,"aaa","Strada 3 Numar 7")
        self.assertRaises(RepoError,self.__repoP.add,person_bad)
    
    def testRemove(self):
        persoana=Persoana(3,"Denis","Strada 3 Numar 7")
        self.__repoP.add(persoana)
        length1=len(self.__repoP)
        self.__repoP.delete(persoana)
        length2=len(self.__repoP)

        self.assertEqual(length1-1,length2)
        self.assertRaises(RepoError,self.__repoP.delete,persoana)     

    def testUpdate(self):

        persoana=Persoana(3,"Denis","Strada 3 Numar 7")
        self.__repoP.add(persoana)
        l1=self.__repoP.getAll()
        persoana_modif=Persoana(3,"Darius","Strada 5 Numar 3")
        self.__repoP.update(persoana_modif)
        l2=self.__repoP.getAll()
        self.assertTrue(l1[0].getName()!=l2[0].getName())
        self.assertTrue(l1[0].getAdress()!=l2[0].getAdress())
        self.assertRaises(RepoError,self.__repoP.update,Persoana(4,"Darius","Strada 5 Numar 3"))

    def testSearch(self):
        person=Persoana(3,"Denis","Strada 3 Numar 7")
        self.__repoP.add(person)
        str_pers=str(person)
        self.assertTrue(self.__repoP.search_by_id(person.getID())==str_pers)
        self.assertRaises(RepoError, self.__repoP.search_by_id, 33)
    
class RepoEventTests(unittest.TestCase):
    def setUp(self):
        self.__repoE=repoEvents()

    def testAdd(self):
        id=1
        data="13/05/2003"
        timp=23
        descriere="abc"
        event=Eveniment(id,data,timp,descriere)

        length1=len(self.__repoE)
        self.__repoE.add(event)
        length2=len(self.__repoE)

        self.assertTrue(length1+1==length2)

        event2=Eveniment(1,data,13,descriere)

        self.assertRaises(RepoError, self.__repoE.add,event)
        self.assertRaises(RepoError, self.__repoE.add,event2)

    def testRemove(self):
        id=1
        data="13/05/2003"
        timp=23
        descriere="abc"

        event=Eveniment(id,data,timp,descriere)
        
        self.__repoE.add(event)
        len1=len(self.__repoE)
        self.__repoE.delete(1)
        self.assertTrue(len1-1==len(self.__repoE))

        self.assertRaises(RepoError, self.__repoE.delete, 1)

    def testUpdate(self):
        
        event=Eveniment(3,"13/07/2009",15.3,"da")

        self.__repoE.add(event)
        l1=self.__repoE.getAll()
        event_modif=Eveniment(3,"13/08/2009",15.4,"daa")
        self.__repoE.update(event_modif)
        l2=self.__repoE.getAll()
        self.assertTrue(l1[0].getDate()!=l2[0].getDate())
        self.assertTrue(l1[0].getTime()!=l2[0].getTime())
        self.assertTrue(l1[0].getDescription()!=l2[0].getDescription())
        self.assertRaises(RepoError,self.__repoE.update,Eveniment(4,"13/08/2009",15.4,"daa"))

    def testSearch(self):
        
        event=Eveniment(3,"13/07/2009",15.3,"da")
        self.__repoE.add(event)
        str_ev=str(event)
        self.assertTrue(self.__repoE.search_by_id(event.getID())==str_ev)
        self.assertRaises(RepoError,self.__repoE.search_by_id,33)
    
class RepoParticipationTests(unittest.TestCase):
    
    def setUp(self):
        self.__repoP=FileRepoParticipare("tests/test_repoParticipare.txt")
    
    def testGetAll(self):
        partlist=[]
        self.assertTrue(len(partlist)==0)
        partlist=self.__repoP.getAll()
        self.assertTrue(len(partlist)!=0)
    
    def testAdd(self):
        with open("tests/test_repoParticipare.txt","w") as f:
            f.write("")
        
        participation=participareDTO(1,1,1)
        len1=len(self.__repoP)
        self.__repoP.add(participation)
        self.assertTrue(len1+1==len(self.__repoP))
    
    def testDeleteByPerson(self):
        participant=participareDTO(1,1,1)
        self.__repoP.add(participant)
        len1=len(self.__repoP)
        self.__repoP.delete_by_person(1)
        self.assertEqual(len(self.__repoP),len1-1)

    def testDeleteByEvent(self):
        participant=participareDTO(1,1,1)
        self.__repoP.add(participant)
        len1=len(self.__repoP)
        self.__repoP.delete_by_event(1)
        self.assertEqual(len(self.__repoP),len1-1)

class DomainPersonTests(unittest.TestCase):
    
    def testCreate(self):
        id=1
        nume="Ion"
        adresa="Strada"
        persoana=Persoana(id, nume, adresa)
        self.assertTrue(persoana.getID()==id)
        self.assertTrue (persoana.getName()==nume)
        self.assertTrue(persoana.getAdress()==adresa)
      
class DomainEventTests(unittest.TestCase):
    
    def testCreate(self):
        id=1
        data="13/05/2003"
        timp=23
        descriere="abc"
        event=Eveniment(id,data,timp,descriere)

        self.assertTrue(event.getID()==id)
        self.assertTrue(event.getDate()==data)
        self.assertTrue(event.getTime()==timp)
        self.assertTrue(event.getDescription()==descriere)

class DomainParticipationTests(unittest.TestCase):
    
    def testCreate(self):
        id=1
        nume="Ion"
        adresa="Strada 3 Numar 5"
        data="13/05/2003"
        timp=23
        descriere="abc"
        person=Persoana(id, nume, adresa)
        event=Eveniment(id,data,timp,descriere)
        participare=Participare(1,person,event)
        self.assertTrue(participare.getID()==1)
        self.assertTrue(participare.getEvent()==event)
        self.assertTrue(participare.getEventID()==id)
        self.assertTrue(participare.getPerson()==person)
        self.assertTrue(participare.getEventID()==id)
        self.assertTrue(participare.getPersonID()==id)

    def testCreateParticipareDTO(self):
        p=participareDTO(1,1,1)
        self.assertTrue(p.getID_Pers()==1)
        self.assertTrue(p.getID_Event()==1)
        self.assertTrue(p.getID_Part()==1)
        person=Persoana(1,"Denis","Strada 1 Numar 1")
        event=Eveniment(1,"13/02/2003",13.2,'abc')
        p.setPerson(person)
        p.setEvent(event)
        self.assertTrue(p.getPerson()==person)
        self.assertTrue(p.getEvent()==event)
    
    def testCreatePersonListEvDTO(self):
        lista=[]
        person=Persoana(1,"Denis","Strada 1 Numar 1")
        p=personListEvDTO(person,lista)
        self.assertTrue(p.getList()==lista)
        self.assertTrue(p.getPerson()==person)
    
    def testCreatePersonNumberEventsDTO(self):

        person=Persoana(1,"Denis","Strada 1 Numar 1")
        p=personNumberEventsDTO(person,3)

        self.assertTrue(p.getPerson()==person)
        self.assertTrue(p.getNumberEvents()==3)
        p.setNumberEvents(4)
        self.assertTrue(p.getNumberEvents()==4)
        
class ValidatorPersonTests(unittest.TestCase):
    def setUp(self):
        self.__validP=validatorPersoane()
    
    def testValidatePerson(self):
        id=1
        nume="Ion"
        adresa="Strad 3 Numar 7"
        persoana=Persoana(id, nume, adresa)
        self.assertRaises(ValidError,self.__validP.validatePerson,persoana)

        id=-1
        nume=""
        adresa="Strad 3 Numar 7"
        persoana=Persoana(id, nume, adresa)

        self.assertRaises(ValidError,self.__validP.validatePerson,persoana)

        id=1
        nume="Ion"
        adresa="Strada 3 Numar 7"
        persoana=Persoana(id, nume, adresa)
        self.assertTrue(True)

class ValidatorEventTests(unittest.TestCase):
    def setUp(self):
        self.__validE=validatorEvents()
    
    def testValidEvent(self):
        id=1
        data="13/05/2003"
        timp=23
        descriere="abc"
        event=Eveniment(id,data,timp,descriere)

        self.assertTrue(True)

        id=1
        data="13/5/2003"
        timp=23
        descriere="abc"
        event=Eveniment(id,data,timp,descriere)

        self.assertRaises(ValidError, self.__validE.ValidateEvent,event)

    
        
        id=-1
        data=""
        timp=-3
        descriere=""
        event=Eveniment(id,data,timp,descriere)

        self.assertRaises(ValidError, self.__validE.ValidateEvent,event)

class ServicePersonTests(unittest.TestCase):
    def setUp(self):
        self.__repo=repoPersoane()
        self.__validator=validatorPersoane()
        self.__srv=servicePersoane(self.__repo, self.__validator)
    
    def testAdd(self):
         
        id=1
        nume="Ion"
        adresa="Strada"
        self.assertRaises(ValidError, self.__srv.services_add, id, nume, adresa)

        id=3
        nume="Ionel"
        adresa="Strada 3 Numar 3"
        self.assertTrue(True)

        id=-3
        nume="Denis"
        adresa="Strada 3 Numar 3"
        
        self.assertRaises(ValidError, self.__srv.services_add,id,nume,adresa)

    def testRemove(self):
        id=1
        nume="Ion"
        adresa="Strada 3 Numar 5"
        self.assertRaises(RepoError, self.__srv.services_delete,id,nume,adresa)
        self.assertRaises(ValidError, self.__srv.services_delete,-1,nume,adresa)
    
    def testUpdate(self):
        self.assertRaises(RepoError, self.__srv.services_update,3,"denis","Strada 3 Numar 7")
        self.__repo.add(Persoana(3,"denis","Strada 3 Numar 7"))
        self.assertRaises(ValidError, self.__srv.services_update,3,"denis","Strad 3 Numar 7")
        self.__srv.services_update(3,"De","Strada 3 Numar 7")
        self.assertTrue(True)
       
    def testSearch(self):
        
        person=Persoana(3,"Denis","Strada 3 Numar 7")
        str_p=str(person)
        self.__repo.add(person)
        self.assertTrue(self.__srv.services_search_by_id(person.getID())==str_p)
        self.assertRaises(RepoError,self.__srv.services_search_by_id,33)
           
    def testFilter(self):
        prefix="De"
        self.__repo.add(Persoana(1,"Denis","Strada 1 Numar 1"))
        self.__repo.add(Persoana(2,"Denisa","Strada 2 Numar 2"))
        self.__repo.add(Persoana(3,"Elmo","Strada 3 Numar 2"))
        self.__srv.services_filter(prefix)
        self.assertTrue(True)
        
        self.assertRaises(RepoError,self.__srv.services_filter,"x")
        
class ServiceEventTests(unittest.TestCase):
    def setUp(self):
        self.__repo=repoEvents()
        self.__val=validatorEvents()
        self.__srv=serviceEvents(self.__repo,self.__val)

    def testAdd(self):
        id=1
        data="13/05/2003"
        timp=23
        descriere="abc"
        self.__srv.services_add(id,data,timp,descriere)
        self.assertTrue(True)
        id=-1
        data="13/05/203"
        timp=-3
        descriere="abc"
        self.assertRaises(ValidError, self.__srv.services_add,id,data,timp,descriere)
        id=1
        data="13/05/2003"
        timp=23
        descriere="abc"
        self.assertRaises(RepoError, self.__srv.services_add,id,data,timp,descriere)
        
    def testRemove(self):
        id=1
        data="13/05/2003"
        timp=23
        descriere="abc"

        self.assertRaises(RepoError, self.__srv.services_delete,id)
        self.assertRaises(ValidError, self.__srv.services_delete,-1)
        
    def testUpdate(self):
        self.assertRaises(RepoError, self.__srv.services_update,1,"13/07/2001",15.3,"da")
        
        self.__repo.add(Eveniment(1,"13/07/2001",15.3,"da"))
        self.assertRaises(ValidError, self.__srv.services_update,1,"14/032011",-3,"da")
        self.assertRaises(ValidError, self.__srv.services_update,-1,"14/03/2011",3,"da")
        self.__srv.services_update(1,"14/03/2011",15.2,"da")
        self.assertTrue(True)
    
    def testSearch(self):

        event=Eveniment(3,"13/07/2009",15.3,"da")
        self.__repo.add(event)
        str_ev=str(event)
        self.assertTrue(self.__repo.search_by_id(event.getID())==str_ev)
        self.assertRaises(RepoError, self.__repo.search_by_id, 33)

class ServiceParticipationTests(unittest.TestCase):
    def setUp(self):
        self.__repoP=FileRepoPersoane("tests/test_repoPers.txt")
        self.__repoE=FileRepoEvents("tests/test_repoEvent.txt")
        self.__repoPart=FileRepoParticipare("tests/test_repoParticipare.txt")
        self.__validE=validatorEvents()
        self.__validP=validatorPersoane()
        self.__srv=serviceParticipare(self.__repoP,self.__repoE,self.__repoPart,self.__validE,self.__validP)
    
    def testAdd(self):
        with open("tests/test_repoParticipare.txt","w") as f:
            f.write("1,1,1\n")

        self.assertRaises(RepoError,self.__srv.services_add,11,3,3)
        self.assertRaises(RepoError,self.__srv.services_add,2,3,3)
        self.__srv.services_add(2,33,1)
        self.assertTrue(True)
        self.assertRaises(RepoError,self.__srv.services_add,1,1,1)
   
    def testDelPers(self):
        with open("tests/test_repoParticipare.txt","w") as f:
            f.write("")

        self.__srv.services_add(99,99,99)
        len_initPart=len(self.__repoPart)
        self.__srv.services_delete_by_person(99)
        self.assertTrue(len_initPart-1==len(self.__repoPart))


    def testDelEvent(self):
        with open("tests/test_repoParticipare.txt","w") as f:
            f.write("")

        self.__srv.services_add(99,99,99)
        len_initPart=len(self.__repoPart)
        self.__srv.services_delete_by_event(99)
        self.assertTrue(len_initPart-1==len(self.__repoPart))

    def testPersonEventNumberList(self):
        with open("tests/test_repoParticipare.txt","w") as f:
            f.write("1,1,1\n")
        s="Persoana [1]Denis participa la 1 evenimente"
        self.assertEqual(self.__srv.services_personEventNumberList(),[s])
    


