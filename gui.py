import tkinter as tk
import subprocess
from PIL import Image, ImageTk

def generate_image():
    subprocess.run(["./build/mondrian"]) 
    load_image()

def load_image():
    try:
        img = Image.open("output.png")
        img = img.resize((300, 300))  
        img_tk = ImageTk.PhotoImage(img)  
        
        label.config(image=img_tk)  
        label.image = img_tk  
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

