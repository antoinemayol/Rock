from PIL import Image, ImageDraw, ImageFont

for i in range(10):
    # create image of color 'color' and of size (99, 97)
    img = Image.new('RGB', (15, 15), color = 'white')

    # loads the font to use on text
    fnt = ImageFont.truetype('/home/clery.pelvillain/Downloads/Adventuro.ttf', 80)

    # draw on the image
    d = ImageDraw.Draw(img)
    d.text((75, 75), str(i), font = fnt, anchor = 'mm', fill = 'black')

    img.save("num_" + str(i) + ".png")

