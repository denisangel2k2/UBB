import unittest
from domain.entities import Jucator
from errors.erori import ValidError,RepoError
from infrastructure.repos import repoJucator
from business.services import srvJucator
from domain.validataors import validatorJucator
class Testare(unittest.TestCase):
    def setUp(self):
        self.__repo=repoJucator("tests/test_jucatori1.txt")
        self.__val=validatorJucator()
        self.__srv=srvJucator(self.__repo,self.__val)
    
    def testDomain(self):
        juc1=Jucator("Denis","Moldovan",179,"Fundas")
        juc2=Jucator("Denis","Moldovan",-19,"")
        
        self.assertRaises(ValidError,self.__val.validateJucator,juc2)
        
        self.assertTrue(juc1.get_inaltime()==179)
        self.assertTrue(juc1.get_nume()=="Denis")
        self.assertTrue(juc1.get_prenume()=="Moldovan")
        self.assertTrue(juc1.get_post()=="Fundas")
        

    def testAdd(self):
        self.__repo.write_nothing()
        juc1=Jucator("Denis","Moldovan",179,"Fundas")
        lg1=len(self.__repo)
        self.__repo.add(juc1)
        lg2=len(self.__repo)
        self.assertTrue(lg1+1==lg2)
        
    def testModif(self):
        self.__repo.write_nothing()
        juc1=Jucator("Denis","Moldovan",179,"Fundas")
        self.assertRaises(RepoError, self.__repo.change, juc1)
        self.__repo.add(juc1)
        juc2=Jucator("Denis","Moldovan",190,"Fundas")
        
        self.__repo.change(juc2)
        l=self.__repo.getall()
        self.assertTrue(l[0].get_inaltime()==190, "Inaltime incorecta!")
    
    def testLista(self):
        self.__repo.write_nothing()
        self.assertRaises(RepoError,self.__repo.team)
        juc1=Jucator("Denis","Moldovan", 199, "Fundas")
        juc2=Jucator("Denis","Moldovan", 199, "Fundas")
        juc3=Jucator("Denis","Moldovan", 199, "Pivot")
        juc4=Jucator("Denis","Moldovan", 199, "Extrema")
        juc5=Jucator("Denis","Moldovan", 199, "Extrema")
    
        
        self.__repo.add(juc2)
        self.__repo.add(juc1)
        self.__repo.add(juc3)
        self.__repo.add(juc4)
        self.__repo.add(juc5)
        
        l=self.__repo.team()
        self.assertEqual(len(l), 6)
    
    def testFileadd(self):
        self.__repo.write_nothing()
        self.assertRaises(RepoError, self.__repo.fileadd,"denis.txt")
        cate=self.__repo.fileadd("tests/test_jucatori2.txt")
        self.assertTrue(cate==1)
        
    def testSrvAdd(self):
        self.__repo.write_nothing()
        juc1=Jucator("Denis","Moldovan",179,"Fundas")
        lg1=len(self.__repo)
        self.__srv.srv_add("Denis","Moldovan",179,"Fundas")
        lg2=len(self.__repo)
        self.assertTrue(lg1+1==lg2)
    
    def testSrvModif(self):
        self.__repo.write_nothing()
        self.assertRaises(RepoError, self.__srv.srv_change, "Denis","Moldovan",179)
        juc1=Jucator("Denis","Moldovan",179,"Fundas")
        self.__repo.add(juc1)    
        self.__srv.srv_change("Denis","Moldovan",190)
        l=self.__repo.getall()
        self.assertTrue(l[0].get_inaltime()==190, "Inaltime incorecta!")
        
    def testSrvLista(self):
        self.__repo.write_nothing()
        self.assertRaises(RepoError,self.__srv.srv_team)
        juc1=Jucator("Denis","Moldovan", 199, "Fundas")
        juc2=Jucator("Denis","Moldovan", 199, "Fundas")
        juc3=Jucator("Denis","Moldovan", 199, "Pivot")
        juc4=Jucator("Denis","Moldovan", 199, "Extrema")
        juc5=Jucator("Denis","Moldovan", 199, "Extrema")
    
        
        self.__repo.add(juc2)
        self.__repo.add(juc1)
        self.__repo.add(juc3)
        self.__repo.add(juc4)
        self.__repo.add(juc5)
        
        l=self.__srv.srv_team()
        self.assertEqual(len(l), 6)
        
    def testSrvFileadd(self):
        self.__repo.write_nothing()
        self.assertRaises(RepoError, self.__srv.srv_fileadd,"denis.txt")
        cate=self.__srv.srv_fileadd("tests/test_jucatori2.txt")
        self.assertTrue(cate==1)