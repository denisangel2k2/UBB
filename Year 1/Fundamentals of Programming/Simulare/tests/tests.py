'''
Created on Dec 8, 2021

@author: Denis
'''
import unittest
from infrastructure.repos import RepoPictura
from business.services import ServicePictura
from domain.entities import Pictura
from errors.errors import RepoError


class Test(unittest.TestCase):


    def setUp(self):
        self.__repo=RepoPictura("tests/testRepoPictura.txt")
        self.__srv=ServicePictura(self.__repo)

    def testDomain(self):
        id=1
        nume="The Star"
        nume_autor="Vincent"
        an=1898
        pictura=Pictura(id,nume,nume_autor,an)
        self.assertTrue(pictura.get_id()==id)
        self.assertTrue(pictura.get_an()==an)
        self.assertTrue(pictura.get_nume()==nume)
        self.assertEqual(pictura.get_nume_autor(), nume_autor)
        
    def testFunc1Repo(self):
        l=self.__repo.functionalitate1("Star")
        l_test=["1,The Starry Night,Vincent Van Gogh,1889"]
        self.assertRaises(RepoError,self.__repo.functionalitate1,"x")
        self.assertTrue(l==l_test)
        
    def testFunct2Repo(self):
        dictionar_test={'Vincent Van Gogh': ['1889,The Starry Night'], 'Leonardo da Vinci': ['1519,Mona Lisa']}
        dict=self.__repo.functionalitate2()
        self.assertEqual(dict, dictionar_test)
        
    def testFunc1Serv(self):
        l=self.__srv.service_funct1('Star')
        l_test=["1,The Starry Night,Vincent Van Gogh,1889"]
        self.assertRaises(RepoError,self.__repo.functionalitate1,"x")
        self.assertTrue(l==l_test)
    
    def testFunct2Serv(self):
        dictionar_test={'Vincent Van Gogh': ['1889,The Starry Night'], 'Leonardo da Vinci': ['1519,Mona Lisa']}
        dict=self.__srv.service_funct2()
        self.assertEqual(dict, dictionar_test)
        
if __name__ == "__main__":
    unittest.main()