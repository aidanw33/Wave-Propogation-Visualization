import matplotlib.pyplot as plt
from matplotlib.widgets import TextBox
import numpy as np
import sys
import math
import matplotlib.patches as patches
from matplotlib.widgets import Button
import time


#GLOBAL VARIABLE
VECTOR_COUNT = 0
VECTOR_HASH = {}


def add_vector_to_graph(ax, x, y, angle_degrees, length, color='red'):
    angle_radians = np.radians(angle_degrees)
    x_component = length * np.cos(angle_radians)
    y_component = length * np.sin(angle_radians)

    # Plot the vector using quiver on the existing axis (ax)
    ax.quiver(x, y, x_component, y_component, angles='xy', scale_units='xy', scale=1, color=color, width=.002, headaxislength=0, headlength=0)

def draw_checkerboard_just_ax(rows, cols, square_size, ax):

    for row in range(rows):
        for col in range(cols):
            # Set all squares to white
            color = 'white' if (row + col) % 2 == 0 else '#d3d3d3'
            
            ax.add_patch(plt.Rectangle((col * square_size, row * square_size), square_size, square_size,
                                       edgecolor='black', facecolor=color))

    ax.set_xlim(0, cols * square_size)
    ax.set_ylim(0, rows * square_size)
    ax.set_aspect('equal', adjustable='box')

    # Show x and y axes
    ax.axhline(0, color='black', linewidth=1)
    ax.axvline(0, color='black', linewidth=1)

    # Add labels to x and y axes
    ax.set_xlabel('Time')
    ax.set_ylabel('Space')

    return ax

def euclidean_distance(point1, point2):
    x1, y1 = point1
    x2, y2 = point2
    distance = math.sqrt((x2 - x1)**2 + (y2 - y1)**2)
    return distance

def find_first_intersection_point(x, y, angle_degrees, vector_length, grid_size):
    # Convert angle to radians
    angle_radians = np.radians(angle_degrees)

    # Calculate slope of the vector
    slope = np.tan(angle_radians)
    # print("CurrentX: ", x)
    # print("CurrentY: ", y)
    # print("angle_degrees", angle_degrees)
    # print("slope: ", slope)


    # Point-slope form of the line equation: y - y1 = m * (x - x1)
    # where (x1, y1) is the starting point of the vector
    line_equation = lambda x_val: slope * (x_val - x) + y
    line_equation_y = lambda y_val: ((y_val - y) / slope) + x

    # Find intersection points with vertical and horizontal grid lines
    x_intercept = np.arange(0, grid_size + 1)
    y_intercept = line_equation(x_intercept)

    # Find the smallest positive intersection points along the x-axis and y-axis
    first_x_intersection = next((x_val for x_val in x_intercept if x_val > x), None)
    # print("TargetX", first_x_intersection)
    first_y_intersection = next((y_val for y_val in y_intercept if y_val > y and y_val <= grid_size), None)

    # Find the first intersection point with horizontal grid lines
    
    if(angle_degrees < 0) :
        y_intercept_horizontal = next((y_val for y_val in np.arange(0, grid_size + 1) if y_val >= y and y_val <= grid_size), None)    
        y_intercept_horizontal -= 1
    else:
        y_intercept_horizontal = next((y_val for y_val in np.arange(0, grid_size + 1) if y_val > y and y_val <= grid_size), None)    

    
    # print("TargetY: ", y_intercept_horizontal)

    # Calculate the coordinates of the first intersection point
    first_y_intersection = (line_equation_y(y_intercept_horizontal), y_intercept_horizontal) if y_intercept_horizontal is not None else None


    # Calculate the coordinates of the first intersection point
    first_intersection_point = (first_x_intersection, line_equation(first_x_intersection))
    second_intersection_point = first_y_intersection

    if(euclidean_distance((x, y), (first_intersection_point)) < euclidean_distance((x, y), (second_intersection_point))) :
        # print("point found: ", first_intersection_point)
        return first_intersection_point
    else:
        # print("point found: ", second_intersection_point)
        return second_intersection_point

def hash_two_points(point1, point2):
    """
    Hash function for two sets of two-dimensional points.

    Args:
    - point1 (tuple): A tuple representing the first point (x1, y1).
    - point2 (tuple): A tuple representing the second point (x2, y2).

    Returns:
    - int: Hash code for the two points.
    """
    if len(point1) != 2 or len(point2) != 2:
        raise ValueError("Points must be tuples with two coordinates (x, y)")

    # Choose a scaling factor (adjust as needed based on your specific use case)
    scaling_factor = 1000

    # Convert floating-point values to integers
    x1_int = int(point1[0] * scaling_factor)
    y1_int = int(point1[1] * scaling_factor)

    x2_int = int(point2[0] * scaling_factor)
    y2_int = int(point2[1] * scaling_factor)


    # Combine the hash codes of x and y for both points using bitwise XOR
    hash_code = hash(x1_int) ^ hash(y1_int) ^ hash(x2_int) ^ hash(y2_int) + ((x2_int*8) + x1_int**3 + y2_int * y1_int)


    global VECTOR_HASH
    mapping = VECTOR_HASH.get(hash_code)
    if mapping is not None :
        return False
    else :
        VECTOR_HASH[hash_code] = True
        return True

def createArray(ax, startX, startY, theta1, theta2, checkSize, thetaOne, grid_size) :

    if(thetaOne) :
        theta = theta1
    else:
        theta = theta2


    #find next intersection point and distance to that point
    interX, interY = find_first_intersection_point(startX, startY, theta, 2, grid_size)
    vectorLength = euclidean_distance((startX, startY), (interX, interY))

    #check to make sure this exact vector hasn't been added to the graph before
    newVector = hash_two_points((startX, startY), (interX, interY))

    if newVector is False:
        return
    
    #can add to the vector count after we make sure this isn't a duplicate vector
    global VECTOR_COUNT
    VECTOR_COUNT += 1

    #draw the given vector 
    add_vector_to_graph(ax, startX, startY, theta, vectorLength)

    #draw the next vector if it is still in the graph
    if(interX < checkSize and interY < checkSize and interY >= 0 ) :
        createArray(ax, interX, interY, theta1, theta2, checkSize, not thetaOne, grid_size)
        createArray(ax, interX, interY, -theta1, -theta2, checkSize, not thetaOne, grid_size)

def main():

    def on_button_click(event):
        update(45)
    

    # Create a graph with a checkerboard pattern
    fig, ax = plt.subplots()
    ax = draw_checkerboard_just_ax(5, 5, 1, ax)
    plt.subplots_adjust(bottom=0.35)

    # Input boxes for theta1 and theta2
    theta1_input = TextBox(plt.axes([0.25, 0.1, 0.65, 0.03]), 'Theta1 (degrees):', initial='45')
    theta2_input = TextBox(plt.axes([0.25, 0.05, 0.65, 0.03]), 'Theta2 (degrees):', initial='45')
    gridSize_input = TextBox(plt.axes([0.25, 0.15, 0.65, 0.03]), 'Width (Boxes):', initial='5')
    startPoint_input = TextBox(plt.axes([0.25, 0.2, 0.65, 0.03]), 'Start Point:', initial='2.5')
    button_ax = plt.axes([0.8, 0.25, 0.15, 0.035])  # [left, bottom, width, height]

    #Calculate button
    button = Button(button_ax, 'Calculate') 
    button.on_clicked(on_button_click)

    #Vector Count Display
    global VECTOR_COUNT 
    vectorBoxString = "Unique Vector Count: "+ str(VECTOR_COUNT)
    text_box = plt.text(-1 , 20, vectorBoxString, bbox=dict(facecolor='white', edgecolor='black'))


    # Function to update the plot when input values change
    def update(val):

        try:
            global VECTOR_COUNT, VECTOR_HASH
            VECTOR_COUNT = 0
            VECTOR_HASH.clear()

            ax.clear()
            gridSize = int(gridSize_input.text)
            startPoint = float(startPoint_input.text)

            draw_checkerboard_just_ax(gridSize, gridSize, 1, ax)
            theta1 = float(theta1_input.text)
            theta2 = float(theta2_input.text)
            
            startX = 0
            startY = startPoint

            createArray(ax, startX, startY, theta1, theta2, gridSize, True, gridSize)
            createArray(ax, startX, startY, -theta1, -theta2, gridSize, True, gridSize)
            text_box.set_text("Unique Vector Count :" + "BROKEN") #str(VECTOR_COUNT))
            plt.grid()
            # Update your existing plot with the new theta1 and theta2 values
        except ValueError:
            print("Invalid input. Please enter valid numeric values.")

    # Register the update function with each input box

    

    update(45)
    plt.grid()
    plt.show()

if __name__ == "__main__":
    main()
