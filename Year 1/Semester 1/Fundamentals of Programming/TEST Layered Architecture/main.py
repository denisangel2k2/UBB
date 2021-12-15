'''
Created on Dec 10, 2021

@author: Denis
'''
from business.services import serviceImprumut, serviceCarte
from consola.ui import *
from infrastructure.repos import repoImprumut,repoCarte
from tests.test import *

def main():
    repoI=repoImprumut("imprumuturi.txt")
    repoC=repoCarte("carti.txt")
    srvC=serviceCarte(repoC)
    srvI=serviceImprumut(repoI)
    ui=Consola(srvI, srvC)
    ui.run()
    
if __name__ == '__main__':
    main()