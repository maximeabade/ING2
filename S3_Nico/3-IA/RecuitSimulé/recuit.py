# exp function
import math
# randomint function
import random


# param file_name : string : name of file where the data is
# return mat : int matrix : the edge weight matrix
def get_matrice_from_file(file_name):
    f = open(file_name)

    mat = [[]]
    size = 0
    bool_data = False
    datas = []

    #Get size of square mat and datas
    for line in f:
        if "DIMENSION" in line:
            size = int(line.split(' ')[2].replace("\n",""))
        elif "EDGE_WEIGHT_SECTION" in line:
            bool_data = True
        elif bool_data:
            
            datas += list(line.replace("\n","").split(" "))

    datas.remove('EOF')

    #
    cpt = 0
    current_line = 0
    for data in datas:
        if cpt%size == 0 and cpt != 0:
            mat.append([])
            current_line+=1
            cpt = 0
        if data != '':
            mat[current_line].append(int(data))
            cpt+=1

    f.close()
    
    return mat

# param weight_matrix : int matrix : the edge weight matrix
# return
def initial_solution(weight_matrix):
    current_solution = []

    for i in range( len(weight_matrix) ):
        current_solution.append( i )
    current_solution.append(0)

    return current_solution

# param solution : list : the solution we want the neighbour of
# return neighbour_solution : list : the neighbour solution
def get_neighbour_solution(solution):
    rand = random.randint(0,len(solution)-2)
    neighbour_solution = solution
    save = neighbour_solution[rand]
    neighbour_solution[rand] = solution[rand + 1]
    neighbour_solution[rand + 1] = save

    if rand == 0:
        neighbour_solution[-1] = neighbour_solution[0]
    elif rand == len(solution) -2:
        neighbour_solution[0] = neighbour_solution[-1]

    return solution


# param neighbour_solution : list : hamiltonian cycle
# param current_solution : list : hamiltonian cycle
# param temperature : float : current temperature
# return double : metropolis criteria
def metropolis(neighbour_solution, current_solution,temperature, weight_matrix):
    return math.exp( -( abs( cost_function(current_solution,weight_matrix) - cost_function(neighbour_solution,weight_matrix) ) / temperature ) )

# param solution : list : hamiltonian cycle
# param weight_matrix : int matrix : the edge weight matrix
# return cost : int : the cost of solution
def cost_function(solution, weight_matrix):
    cost = 0

    for i in range( len(solution)-1 ):
        cost += weight_matrix[ solution[i] ][ solution[i+1] ]

    return cost

# param temperature : float
# return updated temperature : float
def update_temperature(temperature):
    return temperature * 0.99

# param weight_matrix : int matrix : the edge weight matrix
# param temperature : float : initial temperature
# return best found solution : list int
def recuit_simule(weight_matrix,temperature,current_solution):
    best_current_solution = current_solution.copy()

    count_iteration_without_improvment = 0

    while count_iteration_without_improvment < 1000:
        neighbour_solution = get_neighbour_solution(current_solution)

        if cost_function(neighbour_solution,weight_matrix) < cost_function(current_solution,weight_matrix) or random.random() < metropolis( neighbour_solution , current_solution , temperature, weight_matrix ):
            current_solution = neighbour_solution

        if cost_function(current_solution,weight_matrix) < cost_function(best_current_solution,weight_matrix):
            best_current_solution = current_solution.copy()
            count_iteration_without_improvment = 0
        else:
            count_iteration_without_improvment += 1

        temperature = update_temperature(temperature)
    
    return best_current_solution



weight_matrix = get_matrice_from_file("br17.atsp")



current_solution = initial_solution(weight_matrix)
best_found_solution = recuit_simule(weight_matrix, 1000, current_solution)

curr_best = cost_function(best_found_solution,weight_matrix)

n=0
while  n < 1000:
    if cost_function(best_found_solution,weight_matrix) < curr_best:
        curr_best = cost_function(best_found_solution,weight_matrix)
        print(best_found_solution)
        print(cost_function(best_found_solution,weight_matrix))
    

    if n%100 == 0:
        print("iter n° :",n)
    
    n+=1
    best_found_solution = recuit_simule(weight_matrix, 1000,best_found_solution)

print(best_found_solution)
print(cost_function(best_found_solution,weight_matrix))


# Current Best : [2, 0, 11, 16, 8, 7, 4, 3, 5, 6, 15, 14, 10, 12, 1, 9, 13, 2]
# Cost : 39


# Alternative solution : [7, 16, 3, 4, 6, 14, 5, 15, 12, 1, 10, 9, 2, 13, 11, 0, 8, 7]
# Cost : 39

# Alternative solution : [11, 7, 16, 8, 4, 3, 6, 15, 14, 5, 1, 9, 10, 12, 2, 13, 0, 11]
# Cost : 39

# Alternative solution  : [10, 12, 1, 9, 5, 14, 15, 6, 3, 4, 16, 8, 7, 0, 11, 13, 2, 10]
# Cost : 39

#[8, 16, 4, 3, 15, 6, 5, 14, 0, 11, 13, 2, 1, 10, 12, 9, 7, 8]

#[3, 14, 6, 15, 5, 9, 1, 12, 10, 13, 2, 0, 11, 8, 7, 16, 4, 3]

#[0, 11, 2, 13, 12, 1, 10, 9, 5, 14, 6, 15, 3, 4, 16, 8, 7, 0]

#[4, 3, 16, 8, 7, 12, 1, 9, 10, 13, 2, 11, 0, 14, 5, 6, 15, 4]

#[1, 16, 8, 7, 3, 4, 15, 5, 6, 14, 11, 0, 13, 2, 12, 10, 9, 1]

#[14, 12, 9, 10, 1, 13, 2, 0, 11, 16, 8, 7, 3, 4, 5, 15, 6, 14]

#[4, 14, 6, 15, 5, 0, 11, 2, 13, 12, 10, 9, 1, 7, 8, 16, 3, 4]

#[13, 0, 11, 14, 6, 5, 15, 4, 3, 8, 7, 16, 10, 12, 1, 9, 2, 13]

#[12, 1, 10, 14, 5, 15, 6, 4, 3, 8, 16, 7, 0, 11, 2, 13, 9, 12]


def get_points_from_weight(weight_matrix):
    d_max = weight_matrix[0][0]
    x_max, y_max = 0,0

    for i in range(1,len(weight_matrix)-1):
        for j in range( 0 , i ):
            if weight_matrix[i][j] > d_max:
                d_max = weight_matrix[i][j]
                x_max = i
                y_max = j
    
    points = []
    points.append([0,0])
    points.append([0,d_max])

    tmp = weight_matrix[y_max]
    weight_matrix.remove( weight_matrix[x_max] )
    weight_matrix.remove( tmp )

    #for i in range(len(weight_matrix)):

