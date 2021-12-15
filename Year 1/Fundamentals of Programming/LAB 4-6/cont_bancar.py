from typing import OrderedDict
from init_functions import *
from ui import *
from adaugare_tranzactii import *
import pickle
import collections
'''
def _open(myDict):
    """
    Deschide in dictionarul myDict toate datele referitoare la tranzactii salvate ulteriorin fisierul data.pkl
    input: myDict - dictionar
    """
    a_file = open("data.pkl","rb")
    myDict=pickle.load(a_file) # aici deschid fisierul si il bag in dictionar

def _write(myDict):
    """
    Scrie toate modificarile aduse la datele referitoare la tranzactii in dictionarul myDict pe care le salveaza in
    fisierul data.pkl
    input: myDict - dictionar
    """
    a_file=open("data.pkl","wb")
    pickle.dump(myDict,a_file) #aici il salvez dupa ce ii modificat
    a_file.close()
'''
def main():
 
    dictTransactions={}
    run(dictTransactions)
 
main()
