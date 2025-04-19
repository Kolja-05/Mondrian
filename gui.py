import tkinter as tk
import subprocess
from PIL import Image, ImageTk

def generate_image():
    subprocess.run(["./generate"])  # This runs the C program to generate the image
    load_image()

def load_image():
    try:
        img = Image.open("output.png")  
        img = img.resize((300, 300))  
        img_tk = ImageTk.PhotoImage(img)  # Convert the image to a format Tkinter can display
        
        label.config(image=img_tk)  # Update the label with the new image
        label.image = img_tk  # Keep a reference to the image so it doesn't get garbage-collected
    except FileNotFoundError:
        print("Error: output.png not found.")

# Create window
root = tk.Tk()
root.title("Image Generator GUI")

generate_button = tk.Button(root, text="Generate Image", command=generate_image)
generate_button.pack()

label = tk.Label(root)
label.pack()

root.mainloop()

