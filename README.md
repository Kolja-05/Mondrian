# Mondrian "Art" generator
## Indroduction
Piet Mondrian was a Dutch painter, art theoretician, and a pioneer of 20th-century abstract art. Coming from an Impressionist art style, Mondrian evolved, and since the 1920s, created his famous geometric paintings, which follow the ideas of his art-theoretical essay "Le Neoplasticism", in which he wrote:

"As a pure representation of the human mind, art will express itself in an aesthetically purified — that is to say, abstract — form. The new plastic idea cannot, therefore, take the form of a natural or concrete representation. This new plastic idea will ignore the particulars of appearance — that is to say, natural form and colour. On the contrary, it should find its expression in the abstraction of natural form and colour—that is to say, the straight line and the clearly defined
primary colours".

![Screenshot](https://www.meisterdrucke.de/kunstwerke/400w/Piet%20Mondrian%20-%20Composition%20II%20in%20Red%20Blue%20and%20Yellow%20-%20(MeisterDrucke-32610).jpg)

This repository is a collection of code to generate images that follow Mondrian's artistic Ideas. Based on a random seed and some input parameters, it generates an image that aligns with the Neoplasticist idea of abstraction. The images generated in this way should not have the ambition to be acknowledged as some form of art. However this form of image generation takes Mondrian's ideas further. By abstracting even the *pure representation of the human mind*, only the logical pattern of a *human* idea remains.  One could claim that whatever the *human mind* did, it did it by following the structure of a logical system. Which means its logical structure could just as well be represented in some other medium.  That idea leads to a purely materialist view of *mind* that is following self-imposed rules to express itself in an aesthetically pleasing form.


## How to Use


1. Clone the repository or download the C script.
2. Either generate images using the provided  gui.py
   ```bash
   python3 gui.py
4. Or directly generate images by compiling and executing the C-code
5. Ensure you have a C compiler (e.g., `gcc`) and the necessary libraries installed (e.g., `libpng` for PNG generation).
6. Compile the script:
   ```bash
   gcc  generator.c -o test -lpng
7. Execute the compiled file
   ```bash
   ./test
8. Open the output
   ```bash
   output.png

## License, Feedback and Contributions

Feel free to use, modify, and distribute! Ideas, improvements, or bugs? Open an issue or submit a pull request!

