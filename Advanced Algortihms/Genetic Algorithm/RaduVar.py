from bitarray.util import *
from bitarray import *
from math import log2
from random import random, randint


class Cromozom: #Calculeaza automat valoarea functiei si fitnessul sau
    def __init__(self, l):
        self.data = bitarray(l) #Poate primi o lungime si atunci se initializeaza cu bits random sau un array de 0 si 1 ce reprezinta bits sau un alt bitarray
        self.x = ((b - a) / (2 ** lungime - 1)) * ba2int(self.data, False) + a
        self.fit = functie(self.x)
        self.prob = 0

    #def __repr__(self):
    #    return f'{self.data.to01()} x= {self.x} f= {self.fit}'


def functie(x):
    return coef[0] * x ** 2 + coef[1] * x + coef[2]


def binSearch(val, array):
    i = 0
    step = 1
    max = len(array)
    while step < max:
        step = step * 2
    while step:
        if i + step < max and array[i + step] < val:
            i += step
        step //= 2
    return i


def recombinare(populatie, i, j):
    f.write(f'Recombinare intre cromozomul {i} si cromozomul {j}:\n')
    punct = randint(0, lungime - 1) #Generez punctul de rupere
    scrom1 = populatie[i].data.to01()
    scrom2 = populatie2[j].data.to01()
    recomb1 = Cromozom(scrom1[:punct] + scrom2[punct:]) #Fac recombinarea
    recomb2 = Cromozom(scrom2[:punct] + scrom1[punct:])
    f.write(f'{scrom1}, {scrom2}, punct: {punct}\n')
    f.write(f'Rezultat {recomb1.data.to01()}, {recomb2.data.to01()}\n')
    populatie[i] = recomb1 #Updatez populatia
    populatie[j] = recomb2


def recombinare2(populatie, i, j): #Ca mai sus doar ca less verbose
    punct = randint(0, lungime - 1)
    scrom1 = populatie[i].data.to01()
    scrom2 = populatie2[j].data.to01()
    recomb1 = Cromozom(scrom1[:punct] + scrom2[punct:])
    recomb2 = Cromozom(scrom2[:punct] + scrom1[punct:])
    populatie[i] = recomb1
    populatie[j] = recomb2


def newPop(populatie):  # Un array de cromozomi
    # Gasesc elita si calculez fitnessul maxim
    maxim = 0
    sumafit = 0
    for cromozom in populatie:
        sumafit += cromozom.fit
        if cromozom.fit > maxim:
            elita = cromozom
            maxim = cromozom.fit
    maxvalues.append(maxim)
    medievalues.append(sumafit / n)
    f.write(f'Maxim {maxim}, valoare medie {sumafit / n}\n')
    # Calculez probabilitatile de selectie
    for cromozom in populatie:
        cromozom.prob = cromozom.fit / sumafit
    # Creez intervalele de selectie
    temp = 0
    selectii = [0] * (n + 1)
    for i in range(len(populatie)):
        temp += populatie[i].prob
        selectii[i + 1] = temp
    populatie2 = []
    for i in range(n):
        u = random()
        index = binSearch(u, selectii)
        populatie2.append(populatie[index])
    # Fac recombinarea
    participanti = []  # lista cu indicii cromozomilor care participa la recombinare
    for i in range(len(populatie2)):
        u = random()
        if u < probs[1]:
            participanti.append(i)
    i = 0
    while (i + 1 < len(participanti)):
        recombinare2(populatie2, participanti[i], participanti[i + 1])
        i += 2
    # Fac mutatia
    i = 0
    for cromozom in populatie2:  # Iau fiecare cromozom din populatie
        if i > 0:  # Primul loc e rezervat pentru elita, nu are sens sa incerc sa il modific
            for j in range(len(cromozom.data)):  # Parcurg fiecare gena
                u = random()
                if u < probs[2]:  # Daca are log mutatia
                    cromozom.data.invert(j)  # Schimb bitul de la pozitia corespunzatoare
                    populatie2[i] = Cromozom(cromozom.data)  # Modific in populatie
        i += 1
    populatie2[0] = elita  # Ma asigur ca cel mai bun cromozom e in populatie
    return populatie2


with open("E:\PyCharmProjects\input.txt") as f:
    n, a, b = [int(x) for x in f.readline().split()]  # Dimensiunea populatiei, intervalul functiei
    coef = [int(x) for x in f.readline().split()]  # Coef polinom grad2
    probs = [float(x) for x in f.readline().split()]  # Precizie, recombinare, mutatie
    etape = int(f.readline())  # Nr etape

f = open("E:\PyCharmProjects\Output.txt","w")

lungime = round(log2((b - a) * 10 ** probs[0]))
populatie = []
medievalues = []  # Pentru graph
maxvalues = []
f.write("Populatia initiala\n")
sumafit = 0
for i in range(n):  # Construiesc populatia initiala
    temp = Cromozom(lungime)
    f.write(f"{i}: {temp}\n")
    populatie.append(Cromozom(lungime))
    sumafit += temp.fit
maxfit = 0

f.write("Probabilitati selectie\n")
for i in range(len(populatie)):
    populatie[i].prob = populatie[i].fit / sumafit
    if populatie[i].fit > maxfit:
        maxfit = populatie[i].fit
        elita = populatie[i]
    f.write(f'Cromozom {i} Probabilitate: {populatie[i].prob}\n')
f.write("Intervale probabilitati selectie\n")

temp = 0
maxvalues.append(maxfit)
medievalues.append(sumafit / n)
selectii = [0] * (n + 1)
for i in range(len(populatie)): #Calculez intervalele de probabilitate
    temp += populatie[i].prob
    selectii[i + 1] = temp
for selectie in selectii:
    f.write(str(selectie)+'\n')
populatie2 = []
for i in range(n):
    u = random()
    index = binSearch(u, selectii)
    f.write(f'u={u}, selectam cromozomul {index}\n')
    populatie2.append(populatie[index])
f.write("Dupa selectie\n")
for i in range(len(populatie2)):
    f.write(f'{i}: {populatie2[i]}\n')


f.write(f"Probabilitatea de incrucisare {probs[1]}\n")
participanti = []  # lista cu indicii cromozomilor care participa la recombinare
for i in range(len(populatie2)):
    u = random()
    if u < probs[1]:
        f.write(f"{i}: {populatie2[i].data.to01()} u={u}<{probs[1]} participa\n")
        participanti.append(i)
    else:
        f.write(f"{i}: {populatie2[i].data.to01()} u={u}\n")


f.write(f'Toti participantii: {participanti}\n')
i = 0
while i + 1 < len(participanti):
    recombinare(populatie2, participanti[i], participanti[i + 1])
    i += 2


f.write("Dupa recombinare:\n")
for i in range(len(populatie2)):
    f.write(f'{i}: {populatie2[i]}\n')


f.write(f"Probabilitate de mutatie pentru fiecare gena {probs[2]}\n")
i = 0
for cromozom in populatie2:  # Iau fiecare cromozom din populatie
    modificat = False
    if i > 0:  # Primul loc e rezervat pentru elita, nu are sens sa incerc sa il modific
        for j in range(len(cromozom.data)):  # Parcurg fiecare gena
            u = random()
            if u < probs[2]:  # Daca are log mutatia
                cromozom.data.invert(j)  # Schimb bitul de la pozitia corespunzatoare
                populatie2[i] = Cromozom(cromozom.data)  # Modific in populatie
                modificat = True
        if modificat:
            f.write(f'A fost modificat cromozomul {i}\n')
    i += 1
populatie2[0] = elita  # Ma asigur ca cel mai bun cromozom e in populatie


f.write('Dupa mutatie\n')
for i in range(len(populatie2)):
    f.write(f'{i}: {populatie2[i]}\n')

f.write('Evolutie:\n')
for i in range(etape - 1):
    populatie2 = newPop(populatie2)