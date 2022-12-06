from PIL import Image, ImageDraw, ImageFont

for i in range(10):
    # create image of color 'color' and of size (99, 97)
    img = Image.new('RGB', (25, 25), color = 'white')

    # loads the font to use on text
    fnt = ImageFont.truetype('fonts/HunDIN1451.ttf', 30)

    # draw on the image
    d = ImageDraw.Draw(img)
    d.text((100, 100), str(i), font = fnt, anchor = 'mm', fill = 'black')

    img.save("num_hun_" + str(i) + ".png")

