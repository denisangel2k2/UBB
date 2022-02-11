'''
Created on Jan 15, 2022

@author: Denis
'''

from infrastructure.repos import repoJucator
from domain.validataors import validatorJucator
from business.services import srvJucator
from presentation.UI import Consola
from tests.teste import Testare
import unittest

def main():
    
    repJucator=repoJucator("jucatori.txt")
    valJucator=validatorJucator()
    serviceJucator=srvJucator(repJucator,valJucator)
    ui=Consola(serviceJucator)
    ui.run()
    
if __name__ == '__main__':
    #unittest.main()
    main()