'''
Created on Dec 10, 2021

@author: Denis
'''
import unittest
from domain.entities import Carte, Imprumut
from infrastructure.repos import repoCarte, repoImprumut
from errors.errors import RepoError
from business.services import serviceCarte, serviceImprumut



class Test(unittest.TestCase):


    def setUp(self):
        self.__repoC=repoCarte("tests/test_carti.txt")
        self.__repoI=repoImprumut("tests/test_imprumut.txt")
        self.__srvC=serviceCarte(self.__repoC)
        self.__srvI=serviceImprumut(self.__repoI)
        

    def testDomain(self):
        
        carte=Carte(1,"abc","a",2003)
        self.assertTrue(carte.get_an()==2003)
        self.assertTrue(carte.get_autor()=="a")
        self.assertTrue(carte.get_id()==1)
        self.assertTrue(carte.get_nume_carte()=="abc")
        
        imprumut=Imprumut(1,1,"13/02/2002",13)
        self.assertTrue(imprumut.get_id()==1)
        self.assertTrue(imprumut.get_idc()==1)
        self.assertTrue(imprumut.get_data_i()=="13/02/2002")
        self.assertTrue(imprumut.get_durata()==13)
        
    def testFunc1Repo(self):
        l=self.__repoC.func1("eu")
        l_test=['1, Zori la Semineu,  Petre Ispirescu, 1990', '2, Catelul meu, Claudiu Costea, 2021']
        self.assertEqual(l,l_test)
        
        self.assertRaises(RepoError,self.__repoC.func1,"x")

    def testFunc2Repo(self):
        l=self.__repoI.func2(13)
        l_test=['1,1,11.12.2021,13', '3,3,03.05.2018,13']
        self.assertEqual(l,l_test)
        self.assertRaises(RepoError,self.__repoI.func2,2)
        
    def testFunc1Serv(self):
        l=self.__srvC.servFunc1("eu")
        l_test=['1, Zori la Semineu,  Petre Ispirescu, 1990', '2, Catelul meu, Claudiu Costea, 2021']
        self.assertEqual(l,l_test)
        
        self.assertRaises(RepoError,self.__srvC.servFunc1,"x")
    
    def testFunc2Serv(self):
        l=self.__srvI.servFunc2(13)
        l_test=['1,1,11.12.2021,13', '3,3,03.05.2018,13']
        self.assertEqual(l,l_test)
        self.assertRaises(RepoError,self.__srvI.servFunc2,2)
        

if __name__ == "__main__":
    #import sys;sys.argv = ['', 'Test.testName']
    unittest.main()