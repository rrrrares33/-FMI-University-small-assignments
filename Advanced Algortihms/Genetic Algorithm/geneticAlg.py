from math import log2
import random

count = 0

# Functie pentru cautare binara a valorii x in vectorul vec
def binnarySearchInterval(u, vec):
    i = 0
    step = 1
    length = len(vec)
    while step < length:
        step = step * 2
    while step:
        if i + step < length and vec[i + step] < u:
            i = i + step
        step = step // 2
    return i

# Binnary values to integer values.
def bin2int(bin_array):
    int_ = 0
    for i in range(len(bin_array)-1, 0, -1):
        if bin_array[i] == 1:
            int_ += 2 ** i
    return int_

class Chromosome:
    def __init__(self, crom_length):
        # Cromozomul are o lungime data și este format doar din 0/1
        self.bits = []
        # Voi adauga bits random in self.bits.
        for i in range(0, crom_length, 1):
            self.bits.append(random.randint(0,21442124) % 2)
        # Conform formulei de translație liniară
        self.x = ((dom_def_b - dom_def_a) / 2 ** crom_length) * bin2int(self.bits) + dom_def_a
        # Functia de fitness, care practic este functia noastra (functie : -x^2 + x + 2).
        self.fitness = coef[0]*(self.x)**2 + coef[1] * (self.x) + coef[2]
        self.ps = 0

    def afisare(self):
        string_Afis = ''
        for x in self.bits:
            if x == True:
                string_Afis += '1'
            else:
                string_Afis += '0'
        string_Afis += ' x=' + str(self.x) + ' f=' + str(self.fitness)
        return string_Afis

    def afisare_bits(self):
        string_Afis = ''
        for x in self.bits:
            string_Afis += str(x)
        return string_Afis


# Citire din fisier și initializare variabile.
with open("./data.in") as fin:
    # Populația de cromozomi
    pop = []
    # Fitness-ul întregii populații (pentru probabilitatea de selectie)
    pop_fitness = 0
    best_vals = []
    pop_nr = int(fin.readline())
    aux = fin.readline()
    dom_def_a = int(aux[0]+aux[1])
    dom_def_b = int(aux[3])
    aux = fin.readline()
    coef = [int(aux[0]+aux[1]), int(aux[3]), int(aux[5])]
    precizie = int(fin.readline())
    prob_cross = float(fin.readline())
    prob_mut = float(fin.readline())
    pasi = int(fin.readline())
    # Lungimea unui cromozom
    len_crom = round(log2((dom_def_b - dom_def_a) * 10 ** precizie))

# Prima etapa: Generez populatia initiala

fout = open("./rez.out", "w")
fout.write("Populatia initiala: ")
fout.write("\n")
# Îmi generez populația inițială.
for i in range(0, pop_nr, 1):
    pop.append(Chromosome(len_crom))
    str_to_show = str(i+1) + ': ' + pop[len(pop)-1].afisare() +'\n'
    fout.write(str_to_show)
    pop_fitness = pop_fitness + pop[len(pop)-1].fitness

# A doua etapa: Calculez probabilitatile de selectie si retin elita.

# Elita care se va pastra de la o generatie la alta
# Pentru inceput, o initializez cu primul cromozom din populatie
# Dupa care o modific in functie de nivelul de antrenare
elit = pop[0]
pop[0].ps = pop[0].fitness / pop_fitness
fout.write("\n \n \nProbabilitati pentru selectie: \n")
str_to_show = 'cromozom  ' + str(1) + '  probabilitate  ' + str(pop[0].ps) + '\n'
fout.write(str_to_show)
for i in range(1, pop_nr, 1):
    if pop[i].fitness > elit.fitness:
        elit = pop[i]
    pop[i].ps = pop[i].fitness / pop_fitness
    str_to_show = 'cromozom  ' + str(i+1) + '  probabilitate  ' + str(pop[i].ps) + '\n'
    fout.write(str_to_show)

# A treia etapa: Calculez intervalele de selectie

total_prob = 0
intervale_prob = [0]
fout.write('\n \n \n Intervale probabilitati selectie: \n0 \n')
for i in range(0, pop_nr, 1):
    total_prob = total_prob + pop[i].ps
    intervale_prob.append(total_prob)
    fout.write(str(intervale_prob[len(intervale_prob)-1]))
    fout.write('\n')

# A patra etapa: Generare numar aleator si distribuirea cromozomilor in functie de aceste numere random.

cromozomi_selectati = []
for i in range(0, pop_nr, 1):
    # Numar random
    u = random.random()
    pos = binnarySearchInterval(u, intervale_prob)
    string_to_print = 'u = ' +  str(u) + ' selectam cromozomul ' +  str(pos + 1) + '. \n'
    fout.write(string_to_print)
    cromozomi_selectati.append(pop[pos])

# A cincea etapa: Afisam cromozomii ramasi dupa selectie

fout.write("\n\n\nDupa selectie:\n")
for i in range(0, pop_nr, 1):
    str_to_show = str(i+1) +': '+ cromozomi_selectati[i].afisare() + '\n'
    fout.write(str_to_show)

# A sasea etapa: Selectarea cromozomilor(indicilor) care participă la încrucișare

fout.write('\n\n\nProbabilitate de incrucisare:\n')
incrucisare = []
for i in range(0, pop_nr, 1):
    u = random.random()
    # prob_cross este probabilitatea ca o recombinare sa aiba loc
    if u < prob_cross:
        str_to_show = 'i:'+ str(i+1) + '  ' + cromozomi_selectati[i].afisare() + ' u='+ str(u) + '<' + str(prob_cross) + ' parcticipa.\n'
        fout.write(str_to_show)
        incrucisare.append(i)
    else:
        str_to_show = 'i:' + str(i+1) + '  ' + cromozomi_selectati[i].afisare() + ' u ='+ str(u) + '.\n'
        fout.write(str_to_show)

# Realizez incrucisarile
for i in range(0, len(incrucisare) - 1, 2):
    str_to_show = 'Recombinare dintre cromozomul ' + str(incrucisare[i]) + ' si cromozomul ' + str(incrucisare[i+1]) + ':\n'
    fout.write(str_to_show)
    # Punctul de recombinare
    punct_recombinare = random.randint(0, len_crom - 1)

    genom1 = cromozomi_selectati[incrucisare[i]].bits
    genom2 = cromozomi_selectati[incrucisare[i+1]].bits
    for j in range(punct_recombinare, len_crom, 1):
        cromozomi_selectati[incrucisare[i]].bits[j] = genom2[j]
        cromozomi_selectati[incrucisare[i+1]].bits[j] = genom1[j]

    str_to_show = str(cromozomi_selectati[incrucisare[i]].afisare_bits()) + ' ' + str(cromozomi_selectati[incrucisare[i+1]].afisare_bits()) + ' punct:' + str(punct_recombinare) + '\n'
    fout.write(str_to_show)

# Afisez populatia dupa incrucisare:
fout.write("\n\nDupa incrucisare:\n")
for i in range(0, pop_nr, 1):
    str_to_show = 'i:'+ str(i+1) + '  ' + cromozomi_selectati[i].afisare() + '\n'
    fout.write(str_to_show)

# Etapa 7 : Realizez mutațiile pentru fiecare genă care se nimerește să sufere mutație:
fout.write("\n\n\nProbabilitate de mutatie pentru fiecare gena ")
fout.write(str(prob_mut))
fout.write('.\n')

fout.write('Au fost modificati urmatorii cromozomi:')
for i in range(0, pop_nr, 1):
    mutated = 0
    # Am grija sa nu schimb elita
    if (cromozomi_selectati[i] != elit):
        for j in range(len(cromozomi_selectati[i].bits)):
            u = random.random()
            # Daca are loc mutatia, o realizez
            if u < prob_mut:
                cromozomi_selectati[i].bits[j] = abs(cromozomi_selectati[i].bits[j] - 1)
                mutated = mutated + 1
        # Daca a avut loc o mutatie, consemnez în fisier
        if mutated > 0:
            str_to_show = '\n' + str(i+1)
            fout.write(str_to_show)
# Ma asigur ca elita trece in generatia urmatoare
pos_elit = 0
for i in range(0, pop_nr, 1):
    if cromozomi_selectati[i] == elit:
        pos_elit = i

aux_cromo = cromozomi_selectati[0]
cromozomi_selectati[0] = cromozomi_selectati[pos_elit]
cromozomi_selectati[pos_elit] = aux_cromo

# Afisez noii cromozomi dupa mutatie
fout.write('\nDupa mutatie: \n')
for i in range(0, pop_nr, 1):
    string_to_print = 'i:' + str(i+1) + ' ' + cromozomi_selectati[i].afisare() + '\n'
    fout.write(string_to_print)



# Pentru evolutie doar reapelez pasii anteriori într-un for
fout.write('\n\n\nEvolutie:\n')
for k in range(0, pasi, 1):
    pop = cromozomi_selectati
    # =============================
    pop_fitness = 0
    for x in pop:
        pop_fitness = pop_fitness + x.fitness

    elit = pop[0]
    pop[0].ps = pop[0].fitness / pop_fitness
    for i in range(1, pop_nr, 1):
        if pop[i].fitness > elit.fitness:
            elit = pop[i]
        pop[i].ps = pop[i].fitness / pop_fitness
    str_to_show = str(elit.fitness) + '\n'
    fout.write(str_to_show)
    # ============================
    total_prob = 0
    intervale_prob = [0]
    for i in range(0, pop_nr, 1):
        total_prob = total_prob + pop[i].ps
        intervale_prob.append(total_prob)
    # ============================
    cromozomi_selectati = []
    for i in range(0, pop_nr, 1):
        # Numar random
        u = random.random()
        pos = binnarySearchInterval(u, intervale_prob)
        cromozomi_selectati.append(pop[pos])
    # ============================
    incrucisare = []
    for i in range(0, pop_nr, 1):
        u = random.random()
        if u < prob_cross and cromozomi_selectati[i].fitness != elit.fitness:
            incrucisare.append(i)

    for i in range(0, len(incrucisare) - 1, 2):
        punct_recombinare = random.randint(0, len_crom - 1)
        genom1 = cromozomi_selectati[incrucisare[i]].bits
        genom2 = cromozomi_selectati[incrucisare[i+1]].bits
        for j in range(punct_recombinare, len_crom, 1):
            cromozomi_selectati[incrucisare[i]].bits[j] = genom2[j]
            cromozomi_selectati[incrucisare[i+1]].bits[j] = genom1[j]
    # ============================
    for i in range(1, pop_nr, 1):
        if (cromozomi_selectati[i].fitness != elit.fitness):
            for j in range(len(cromozomi_selectati[i].bits)):
                u = random.random()
                if u < prob_mut:
                    cromozomi_selectati[i].bits[j] = abs(cromozomi_selectati[i].bits[j] - 1)

    pos_elit = 0
    for i in range(0, pop_nr, 1):
        if cromozomi_selectati[i].fitness == elit.fitness:
            pos_elit = i

    aux_cromo = cromozomi_selectati[0]
    cromozomi_selectati[0] = cromozomi_selectati[pos_elit]
    cromozomi_selectati[pos_elit] = aux_cromo