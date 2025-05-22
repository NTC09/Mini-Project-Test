import base64
import pyperclip
from io import StringIO
from PIL import ImageGrab
#import cStringIO

image = ImageGrab.grabclipboard()
jpeg_image_buffer = StringIO()
image.save(jpeg_image_buffer, format="JPEG")

encoded = base64.b64encode(image.readonly())

head = ""
ext = "jpg"
head = "data:image/" + ext + ";base64,"
string = ""
string = encoded.decode("utf-8")
pyperclip.copy(head + string)
spam = pyperclip.paste()
print("Done!")