import tkinter as tk
import subprocess
from PIL import Image, ImageTk
import os

# Create the main window
root = tk.Tk()
root.title("Mondrian Generator Slideshow")

# Label to display images
label = tk.Label(root)
label.pack()

# Duration settings in milliseconds
SHOW_TIME = 4000  # 4 seconds
WHITE_TIME = 1000  # 1 second

# Path for the output image
image_path = "output.png"

# Create a white image for the pause screen
def create_white_image(size=(300, 300)):
    white_img = Image.new("RGB", size, (255, 255, 255))  # RGB with (255, 255, 255) for white
    return ImageTk.PhotoImage(white_img)

white_image = create_white_image()

# Function to display the generated image
def show_image():
    try:
        img = Image.open(image_path)
        img = img.resize((300, 300))
        img_tk = ImageTk.PhotoImage(img)
        
        label.config(image=img_tk)
        label.image = img_tk
    except FileNotFoundError:
        print("output.png not found, showing white screen instead.")
        label.config(image=white_image)
        label.image = white_image

# Function to run the slideshow
def slideshow():
    # Step 1: Generate new image
    subprocess.run(["./build/mondrian"])
    
    # Step 2: Show image
    show_image()
    
    # Step 3: After 4 seconds, show white screen
    root.after(SHOW_TIME, show_white)

# Function to show white screen, then schedule next image generation
def show_white():
    label.config(image=white_image)
    label.image = white_image
    
    # After 1 second, generate and show the next image
    root.after(WHITE_TIME, slideshow)

# Start the slideshow loop
slideshow()

# Run the GUI loop
root.mainloop()

