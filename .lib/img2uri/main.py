import base64
import pyperclip
from xml.etree.ElementTree import tostring

path = r"C:\Users\cuong.nguyen\Downloads\Picture1.jpg"
with open(path, "rb") as image_file:
    encoded = base64.b64encode(image_file.read())
    head = ""
    ext = []
    ext = path.split(".")
    head = "data:image/" + ext[-1] + ";base64,"
    string = ""
    string = encoded.decode("utf-8")
    pyperclip.copy(head + string)
    spam = pyperclip.paste()
    print("Done!")